#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class ReadersWriters {
private:
    std::mutex mutex;
    std::condition_variable cv;
    int readers_count;

public:
    ReadersWriters() : readers_count(0) {}

    void start_read() {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this] { return readers_count == 0; });
        readers_count++;
    }

    void end_read() {
        std::lock_guard<std::mutex> lock(mutex);
        readers_count--;
        if (readers_count == 0) {
            cv.notify_all();
        }
    }

    void start_write() {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this] { return readers_count == 0; });
    }

    void end_write() {
        cv.notify_all();
    }
};

void reader_thread(ReadersWriters& rw, int id) {
    while (true) {
        // Reading
        rw.start_read();
        std::cout << "Reader " << id << " is reading" << std::endl;
        // Simulating some delay for reading
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        rw.end_read();
    }
}

void writer_thread(ReadersWriters& rw, int id) {
    while (true) {
        // Writing
        rw.start_write();
        std::cout << "Writer " << id << " is writing" << std::endl;
        // Simulating some delay for writing
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        rw.end_write();
    }
}

int main() {
    ReadersWriters rw;

    // Creating reader threads
    std::thread readers[5];
    for (int i = 0; i < 5; ++i) {
        readers[i] = std::thread(reader_thread, std::ref(rw), i);
    }

    // Creating writer threads
    std::thread writers[2];
    for (int i = 0; i < 2; ++i) {
        writers[i] = std::thread(writer_thread, std::ref(rw), i);
    }

    // Joining threads
    for (int i = 0; i < 5; ++i) {
        readers[i].join();
    }
    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }

    return 0;
}
