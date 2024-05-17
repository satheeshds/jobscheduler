#include "job_scheduler.h"
#include "minheap.h"
#include "job.h"
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <ctime>

JobScheduler::JobScheduler(unsigned int idle_wait_time)
    : idle_wait_time(std::chrono::seconds(idle_wait_time))
{
    // TODO(satheesh): Move this to heap than stack
    // job_heap = MinHeap<Job>();
}

auto JobScheduler::run() -> std::thread
{
    return std::thread([this]()
                       {
                           // log_file.close();
                           // std::ofstream log_file("runner_log.txt", std::ios::app);
                           // log_file << "Job runner started at: " << current_time() << "on thread: " << std::this_thread::get_id() << '\n';

                           should_run = true;
                           while (should_run.load())
                           {
                               if (job_heap.empty())
                               {
                                   condition_variable.wait_for(lock, idle_wait_time, [this]()
                                                               { return awake.load(); });
                                   continue;
                               }

                               // log_file << "Current time: " << current_time() << '\n';
                               Job current_job = job_heap.top();
                               if (current_job.get_next_run() <= time(nullptr))
                               {
                                   job_heap.pop();
                                   // log_file << "Running job : " << current_job << '\n';
                                   current_job.run();

                                   if (current_job.set_next_run())
                                   {
                                       job_heap.push(current_job);
                                   }
                               }

                               if (job_heap.empty())
                               {
                                   continue;
                               }

                               Job const next_job = job_heap.top();
                               auto next_run_time = next_job.get_next_run() - time(nullptr);
                               awake = false;
                               condition_variable.wait_for(lock, std::chrono::seconds(next_run_time), [this]()
                                                           { return awake.load(); });
                               // log_file << " current time:" << current_time() << " Next job (" << next_job << ") will run in: " << next_run_time << " seconds" << '\n';
                           }
                           // log_file.close();
                       });
}

auto JobScheduler::wake_up() -> void
{
    awake = true;
    condition_variable.notify_all();
}

auto JobScheduler::add_job(const Job &job) -> void
{
    mtx.lock();
    job_heap.push(job);
    mtx.unlock();
    wake_up();
}

auto JobScheduler::print() -> void
{
    if (job_heap.empty())
    {
        std::cout << "No jobs in heap" << '\n';
        return;
    }
    job_heap.print();
}

auto JobScheduler::extract_job(unsigned int job_id) -> Job
{
    if (job_heap.empty())
    {
        throw std::out_of_range("Heap is empty");
    }
    auto current_top = job_heap.top();
    auto pred = [job_id](const Job &job)
    { return job.get_id() == job_id; };
    mtx.lock();
    auto job = job_heap.extract(pred);
    mtx.unlock();
    if (job.get_id() == current_top.get_id())
    {
        wake_up();
    }
    return job;
}

auto JobScheduler::exit() -> void
{
    should_run = false;
    wake_up();
}

// template <typename T>
// void JobScheduler<T>::edit_job(T job, std::string cron)
// {
//     auto pred = [job](const Job &j)
//     { return j.get_id() == job.get_id(); };
//     mtx.lock();
//     job_heap.extract(pred);
//     job.set_cron(cron);
//     job.set_next_run();
//     job_heap.push(job);
//     mtx.unlock();
//     wake_up();
// }

// template <typename T>
// void JobScheduler<T>::remove_job(T job)
// {
//     auto pred = [job](const Job &j)
//     { return j.get_id() == job.get_id(); };
//     mtx.lock();
//     job_heap.extract(pred);
//     mtx.unlock();
//     wake_up();
// }
