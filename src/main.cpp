#include <iostream>
#include <thread>
#include <mutex>
#include "minheap.cpp"
#include "job.cpp"
#include <fstream>
#include <condition_variable>
#include <atomic>
#include <optional>

void interface();
void job_runner();
void ADD_JOB();
void REMOVE_JOB();
void EDIT_JOB();
void RUN_JOB();
std::optional<Job> Select_Job();
void wake_up();
const char *current_time();

std::mutex mtx;
MinHeap<Job> job_heap;
std::ofstream log_file("runner_log.txt", std::ios::out);
std::condition_variable cv;
std::atomic<bool> stop_sleeping(false);

int main()
{
    std::thread interface_thread(interface);
    std::thread job_runner_thread(job_runner);

    interface_thread.join();
    job_runner_thread.join();

    return 0;
}

void job_runner()
{
    log_file.close();
    std::ofstream log_file("runner_log.txt", std::ios::app);
    log_file << "Job runner started at: " << current_time() << "on thread: " << std::this_thread::get_id() << std::endl;
    while (true)
    {
        int next_run_time = 0;
        if (!job_heap.empty())
        {
            log_file << "Current time: " << current_time() << std::endl;

            Job current_job = job_heap.top();
            if (current_job.get_next_run() <= time(0))
            {
                mtx.lock();
                job_heap.pop();
                log_file << "Running job with id: " << current_job.id << " & cron: " << current_job.cron << std::endl;

                current_job.run();
                if (current_job.set_next_run())
                {
                    job_heap.push(current_job);
                }
                mtx.unlock();
            }
            Job next_job = job_heap.top();
            next_run_time = next_job.get_next_run() - time(0);
            log_file << " current time:" << current_time() << " Next job (" << next_job.id << ") will run in: " << next_run_time << " seconds" << std::endl;
        }
        else
        {
            log_file << "No jobs to run sleeping for 15 seconds" << std::endl;
            next_run_time = 15;
        }
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait_for(lock, std::chrono::seconds(next_run_time), []
                    { return stop_sleeping.load(); });
        stop_sleeping = false;
    }
    log_file.close();
}

void interface()
{
    int choice;
    do
    {
        /* code */
        std::cout << "Select an option: " << std::endl;
        std::cout << "1. Add job" << std::endl;
        std::cout << "2. Remove job" << std::endl;
        std::cout << "3. Edit job" << std::endl;
        std::cout << "4. Run job" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "6. List jobs" << std::endl;
        std::cout << "thread id: " << std::this_thread::get_id() << std::endl;

        std::cin >> choice;
        switch (choice)
        {
        case 1:
            ADD_JOB();
            break;
        case 2:
            REMOVE_JOB();
            break;
        case 3:
            EDIT_JOB();
            break;
        case 4:
            RUN_JOB();
            break;
        case 5:
            exit(0);
            break;
        case 6:
            job_heap.List();
            break;

        default:
            break;
        }
    } while (choice != 5);
}

void ADD_JOB()
{
    int id;
    do
    {
        std::cin.clear();
        std::cout << "Enter job id: ";
        std::cin >> id;
    } while (std::cin.fail() || id <= 0);

    std::string cron;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore leftover '\n'
    std::cout << "Enter job cron: ";
    std::getline(std::cin, cron);

    Job job(id, cron, [](int id)
            { std::cout << "Job with id: " << id << " ran on thread id: " << std::this_thread::get_id() << std::endl;
             std::cout << "sleepingfor: " << id << " seconds" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(id)); });
    mtx.lock();
    job_heap.push(job);
    mtx.unlock();
    wake_up();
}

void REMOVE_JOB()
{
    auto top = job_heap.top();
    auto job_opt = Select_Job();
    if (!job_opt.has_value())
    {
        return;
    }
    auto job = job_opt.value();
    std::cout << "Job with id: " << job.id << " removed" << std::endl;
    if (job.id == top.id)
    {
        wake_up();
    }
}

void EDIT_JOB()
{
    auto job_opt = Select_Job();
    if (!job_opt.has_value())
    {
        return;
    }
    auto job = job_opt.value();
    std::string cron;
    std::cout << "Enter new cron: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore leftover '\n'
    std::getline(std::cin, cron);
    job.cron = cron;
    job.set_next_run();
    mtx.lock();
    job_heap.push(job);
    mtx.unlock();
    wake_up();
}

void RUN_JOB()
{
    auto job_opt = Select_Job();
    if (!job_opt.has_value())
    {
        return;
    }
    auto job = job_opt.value();
    job.set_next_run(job.get_next_run());
    mtx.lock();
    job_heap.push(job);
    mtx.unlock();
    wake_up();
}

std::optional<Job> Select_Job()
{
    if (job_heap.empty())
    {
        std::cout << "No jobs in heap" << std::endl;
        return std::nullopt;
    }
    std::cout << "Current jobs in heap: " << std::endl;
    job_heap.List();
    std::cout << "Enter job id to remove: ";
    int id;
    std::cin >> id;
    auto pred = [id](Job job)
    { return job.id == id; };
    try
    {
        mtx.lock();
        auto job = job_heap.extract(pred);
        mtx.unlock();
        return job;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << e.what() << '\n';
    }
    return std::nullopt;
}

void wake_up()
{
    stop_sleeping = true;
    cv.notify_all();
}

const char *current_time()
{
    static char buffer[80];
    std::time_t now = std::time(nullptr);
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buffer;
}