#ifndef JOBSCHEDULER_H
#define JOBSCHEDULER_H

#include "minheap.h"
#include "job.h"
#include <chrono>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>

constexpr unsigned int IDLE_WAIT_TIME_SECONDS = 15;

// template <typename T>
class JobScheduler
{
private:
    MinHeap job_heap;
    const std::chrono::seconds idle_wait_time{};
    std::atomic<bool> awake = false;
    std::atomic<bool> should_run = false;
    std::condition_variable condition_variable;
    std::mutex mtx;                         // Added the declaration of the mutex
    std::unique_lock<std::mutex> lock{mtx}; // Moved the lock declaration here

    void wake_up();

public:
    explicit JobScheduler(unsigned int idle_wait_time = IDLE_WAIT_TIME_SECONDS);
    ~JobScheduler() = default;
    auto run() -> std::thread;
    auto add_job(Job *job) -> void;
    auto extract_job(unsigned int job_id) -> Job *;
    auto print() -> void;
    auto exit() -> void;
};

#endif
