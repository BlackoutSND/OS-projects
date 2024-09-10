#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <random>

const int N = 10; // Maximum size of each buffer

template<typename T>
class Buffer {
public:
    Buffer(int max_size) : max_size(max_size) {}

    void produce(const T& item) {
        std::unique_lock<std::mutex> lock(mtx);
        cond_full.wait(lock, [this]() { return buffer.size() < max_size; });
        buffer.push(item);
        cond_empty.notify_all();
    }

    T consume() {
        std::unique_lock<std::mutex> lock(mtx);
        cond_empty.wait(lock, [this]() { return !buffer.empty(); });
        T item = buffer.front();
        buffer.pop();
        cond_full.notify_all();
        return item;
    }

private:
    std::queue<T> buffer;
    std::mutex mtx;
    std::condition_variable cond_full;
    std::condition_variable cond_empty;
    int max_size;
};

Buffer<int> doughBuffer(N);
Buffer<int> meatBuffer(N);
Buffer<int> cheeseBuffer(N);
Buffer<int> cabbageBuffer(N);

void produceDough(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
        doughBuffer.produce(1);
        std::cout << "Producer of Dough " << id << " produced dough.\n";
    }
}

void produceMeat(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
        meatBuffer.produce(1);
        std::cout << "Producer of Meat " << id << " produced meat.\n";
    }
}

void produceCheese(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
        cheeseBuffer.produce(1);
        std::cout << "Producer of Cheese " << id << " produced cheese.\n";
    }
}

void produceCabbage(int id) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));
        cabbageBuffer.produce(1);
        std::cout << "Producer of Cabbage " << id << " produced cabbage.\n";
    }
}

void consumeMeatDumplings(int id) {
    while (true) {
        doughBuffer.consume();
        meatBuffer.consume();
        std::cout << "Consumer of Meat Dumplings " << id << " made a meat dumpling.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1500));
    }
}

void consumeCheeseDumplings(int id) {
    while (true) {
        doughBuffer.consume();
        cheeseBuffer.consume();
        std::cout << "Consumer of Cheese Dumplings " << id << " made a cheese dumpling.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1500));
    }
}

void consumeCabbageDumplings(int id) {
    while (true) {
        doughBuffer.consume();
        cabbageBuffer.consume();
        std::cout << "Consumer of Cabbage Dumplings " << id << " made a cabbage dumpling.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1500));
    }
}

int main(int argc, char* argv[]) {
    int num_producers = 2;
    int num_consumers = 3;

    if (argc > 1) num_producers = std::stoi(argv[1]);
    if (argc > 2) num_consumers = std::stoi(argv[2]);

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 0; i < num_producers; ++i) {
        producers.emplace_back(produceDough, i);
        producers.emplace_back(produceMeat, i);
        producers.emplace_back(produceCheese, i);
        producers.emplace_back(produceCabbage, i);
    }

    for (int i = 0; i < num_consumers; ++i) {
        consumers.emplace_back(consumeMeatDumplings, i);
        consumers.emplace_back(consumeCheeseDumplings, i);
        consumers.emplace_back(consumeCabbageDumplings, i);
    }

    for (auto& producer : producers) producer.join();
    for (auto& consumer : consumers) consumer.join();

    return 0;
}
