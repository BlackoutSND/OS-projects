#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <iomanip>
#include <algorithm>
#include <filesystem>
//#include <conio.h>

const int DISK_SIZE = 1024 * 1024; // 1 MB virtual disk
const int BLOCK_SIZE = 4096; // 4 KB blocks
const int MAX_FILES = 100; // Maximum number of files

struct FileEntry {
    char name[256];
    int size;
    int startBlock;
    bool occupied;
};

class FileSystem {
private:
    std::fstream disk;
    std::vector<FileEntry> directory;
    std::vector<bool> blockMap;
    std::string fileName;

public:
    FileSystem() : blockMap(DISK_SIZE / BLOCK_SIZE, false) {}

    bool createDisk(const std::string& diskName) {
        disk.open(diskName, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
        if (!disk) {
            std::cerr << "Failed to create virtual disk." << std::endl;
            return false;
        }
        disk.seekp(DISK_SIZE - 1);
        disk.write("", 1);
        disk.flush();
        disk.seekp(0);
       
        
        fileName = diskName;
        return true;
    }

    bool loadDisk(const std::string& diskName) {  /*This function is under development; 
                                                    currently does almost nothing; 
                                                    loads the file but because of lack of entries 
                                                    descriptors will result in an empty disk*/
        std::fstream tempDisk;
        tempDisk.open(diskName, std::ios::in | std::ios::out | std::ios::binary);
        if (!tempDisk) {
            std::cerr << "Failed to open virtual disk." << std::endl;
            return false;
        }
        disk.swap(tempDisk);
        fileName = diskName;
        std::cout<<"Data was loaded successfully! (Not really)"<<std::endl;
        return true;
    }

    bool copyToDisk(const std::string& systemFile) {
        std::ifstream src(systemFile, std::ios::binary);
        if (!src) {
            std::cerr << "Failed to open source file." << std::endl;
            return false;
        }

        for (const auto& file : directory) {
            if (file.name==systemFile) {
                std::cerr << "A file with such name already exits." << std::endl;
                return false;
            }
        }

        src.seekg(0, std::ios::end);
        int fileSize = src.tellg();
        src.seekg(0, std::ios::beg);

        int requiredBlocks = (fileSize + BLOCK_SIZE - 1) / BLOCK_SIZE;
        int startBlock = findFreeBlocks(requiredBlocks);

        if (startBlock == -1 || directory.size() >= MAX_FILES) {
            std::cerr << "Not enough space or directory is full." << std::endl;
            return false;
        }

        FileEntry newFile;
        std::strncpy(newFile.name, systemFile.c_str(), sizeof(newFile.name) - 1);
        newFile.size = fileSize;
        newFile.startBlock = startBlock;
        newFile.occupied = true;



        directory.push_back(newFile);
        markBlocks(startBlock, requiredBlocks, true);

        disk.seekp(startBlock * BLOCK_SIZE);
        char buffer[BLOCK_SIZE];
        while (fileSize > 0) {
            src.read(buffer, BLOCK_SIZE);
            disk.write(buffer, src.gcount());
            fileSize -= src.gcount();
        }
        disk.flush();
        std::cout<<"The file was copied successfully!"<<std::endl;
        return true;
    }

    bool copyFromDisk(const std::string& virtualFile, const std::string& destFile) {
        auto it = findFile(virtualFile);
        if (it == directory.end()) {
            std::cerr << "File not found on virtual disk." << std::endl;
            return false;
        }

        std::ofstream dest(destFile, std::ios::binary);
        if (!dest) {
            std::cerr << "Failed to create destination file." << std::endl;
            return false;
        }

        int fileSize = it->size;
        disk.seekg(it->startBlock * BLOCK_SIZE);
        char buffer[BLOCK_SIZE];
        while (fileSize > 0) {
            disk.read(buffer, std::min(fileSize, BLOCK_SIZE));
            dest.write(buffer, disk.gcount());
            fileSize -= disk.gcount();
        }

        std::cout << "The file was copied successfully!" << std::endl;
        return true;
    }

    void listFiles() const {
        std::cout << std::left << std::setw(20) << "Name" << std::setw(10) << "Size" << std::setw(10) << "Start Block" << std::endl;
        for (const auto& file : directory) {
            if (file.occupied) {
                std::cout << std::left << std::setw(20) << file.name << std::setw(10) << file.size << std::setw(10) << file.startBlock << std::endl;
            }
        }
    }

    bool deleteFile(const std::string& virtualFile) {
        auto it = findFile(virtualFile);
        if (it == directory.end()) {
            std::cerr << "File not found on virtual disk." << std::endl;
            return false;
        }

        int requiredBlocks = (it->size + BLOCK_SIZE - 1) / BLOCK_SIZE;
        markBlocks(it->startBlock, requiredBlocks, false);
        it->occupied = false;
        std::cout<<"The file was deleted successfully!"<<std::endl;
        return true;
    }

    void deleteDisk() {
        const std::filesystem::path path(fileName);
        remove(path);
    }

    void displayOccupancyMap() const {
        int start = 0;
        while (start < blockMap.size()) {
            int end = start;
            bool status = blockMap[start];
            while (end < blockMap.size() && blockMap[end] == status) {
                end++;
            }
            std::cout << "Address: " << start * BLOCK_SIZE
                      << " - " << (end * BLOCK_SIZE - 1)
                      << ", Type: " << (status ? "Data Block" : "Free Block")
                      << ", Size: " << (end - start) * BLOCK_SIZE
                      << ", Status: " << (status ? "Busy" : "Free") << std::endl;
            start = end;
        }
    }

private:
    __gnu_cxx::__normal_iterator<FileEntry*, std::vector<FileEntry> > findFile(const std::string& name) {
        return std::find_if(directory.begin(), directory.end(),
                            [&](const FileEntry& file) {
                                return file.occupied && name == file.name;
                            });
    }

    int findFreeBlocks(int requiredBlocks) const {
        int consecutive = 0;
        for (int i = 0; i < blockMap.size(); i++) {
            if (!blockMap[i]) {
                consecutive++;
                if (consecutive == requiredBlocks) {
                    return i - consecutive + 1;
                }
            } else {
                consecutive = 0;
            }
        }
        return -1;
    }

    void markBlocks(int startBlock, int count, bool status) {
        for (int i = 0; i < count; i++) {
            blockMap[startBlock + i] = status;
        }
    }
};

bool saveFileEntry(const std::vector<FileEntry>& entries, std::fstream& disk) {
    if(!disk){
        std::cerr << "Failed to open virtual disk." << std::endl;
        return false;
    }
    for(const auto& entry : entries){
        disk.write(reinterpret_cast<const char*>(&entry), sizeof(FileEntry));
    } 
    disk.close();
    if (!disk.good()) {
        std::cerr << "Error: Problem occurred while writing to the disk.\n";
    } else {
        std::cout << "Data was saved successfully!\n";
    }
}
void doACLIJmp(){
    std::cout << "\033[2J\033[1;1H";
}
void clearCLIInput(){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void prsAnyBtn2CntPrompt(){
    std::cout << "<--Press any button to continue-->";
    clearCLIInput();
    std::cin.get();
}

int main() {
    doACLIJmp();
    std::string diskName; 
    std::cout<<sizeof(FileEntry)*8*100<<std::endl;
    std::cout << "Input The DiskName: ";
    std::cin >> diskName;
    diskName+=".bin";
    FileSystem fs;

    fs.createDisk(diskName);

    while(true){
        doACLIJmp();
        
        std::string nextOp; 
        std::cout << "List Of Commands:\n"
        <<"1. copyToDisk\n" 
        <<"2. listFiles\n" 
        <<"3. displayOccupancyMap\n"
        <<"4. copyFromDisk\n"
        <<"5. deleteDisk\n"
        <<"6. deleteFile\n"
        <<"7. loadDisk\n"
        <<"8. quit\n"
        <<"<------------------------------------------------------------>\n"
        << " Waiting for the next command: ";
        std::cin >> nextOp; 
        if (nextOp=="copyToDisk"||nextOp=="1")
        {
            std::string firstArg; 
            clearCLIInput();
            std::cout << "Input The FileName: "; 
            std::cin >> firstArg;
            fs.copyToDisk(firstArg);
            std::cout<<"\n";
            prsAnyBtn2CntPrompt();
        }
        else if(nextOp=="listFiles"||nextOp=="2"){
            fs.listFiles();
            prsAnyBtn2CntPrompt();
        }
        else if(nextOp=="displayOccupancyMap"||nextOp=="3"){
            fs.displayOccupancyMap();
            prsAnyBtn2CntPrompt();
        }
        else if (nextOp=="copyFromDisk" || nextOp=="4")
        {
            fs.listFiles();
            std::string firstArg; 
            clearCLIInput();
            std::cout << "Input The name of a file to copy: "; 
            std::cin >> firstArg;

            std::string secondArg;
            clearCLIInput();
            std::cout << "Input the FileName: "; 
            std::cin >> secondArg;
            fs.copyFromDisk(firstArg, secondArg);
            std::cout<<"\n";
            prsAnyBtn2CntPrompt();
        }
        else if(nextOp=="deleteDisk" || nextOp=="5"){
            fs.deleteDisk();
            return 0;
        }
        else if(nextOp=="deleteFile" || nextOp=="6"){
            fs.listFiles();
            clearCLIInput();
            std::cout << "Input a File to Delete: "; 
            std::string firstArg;
            std::cin >> firstArg; 
            fs.deleteFile(firstArg);
            prsAnyBtn2CntPrompt();
        }
        else if(nextOp=="loadDisk" || nextOp=="7"){ //under development
            clearCLIInput();
            std::cout << "Input the Disk to Load: "; 
            std::string firstArg; 
            std::cin >> firstArg;
            fs.loadDisk(firstArg);
            prsAnyBtn2CntPrompt();
        }
        else if (nextOp=="quit" || nextOp=="8")
            return 0;
    }
    return 1;
}
