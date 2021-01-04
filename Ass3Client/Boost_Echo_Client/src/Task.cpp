//
// Created by spl211 on 03/01/2021.
//

#include <iostream>
#include <mutex>
#include <thread>

class Task{
private:
    int _id;
    std::mutex & _mutex;
public:
    Task (int id, std::mutex& mutex) : _id(id), _mutex(mutex) {}

    void run(){
        for (int i= 0; i < 100; i++){
            std::lock_guard<std::mutex> lock(_mutex); // constructor locks the mutex while destructor (out of scope) unlocks it
            std::cout << i << ") Task " << _id << " is working" << std::endl;
        }
    }
};

int main(){
    std::mutex mutex;
    Task task1(1, mutex);
    Task task2(2, mutex);

    std::thread th1(&Task::run, &task1);
    std::thread th2(&Task::run, &task2);
    th1.join();
    th2.join();
    return 0;
}
