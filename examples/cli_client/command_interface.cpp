#include "job_scheduler.h"
#include "job.h"
#include "command_interface.h"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <limits>
#include <thread>

void get_positive_int(int &job_id);
command_interface::command_interface(JobScheduler *job_schd) : job_schd(job_schd)
{
}

auto command_interface::run() -> std::thread
{
    return std::thread([this]()
                       {
                           int choice = 0;
                           while (choice != EXIT)
                           {
                               /* code */
                               std::cout << "Select an option: " << '\n';
                               std::cout << "1. Add job" << '\n';
                               std::cout << "2. Remove job" << '\n';
                               std::cout << "3. Edit job" << '\n';
                               std::cout << "4. Run job" << '\n';
                               std::cout << "5. Exit" << '\n';
                               std::cout << "6. List jobs" << '\n';
                               std::cout << "thread id: " << std::this_thread::get_id() << '\n';

                               std::cin >> choice;
                               switch (choice)
                               {
                               case ADD_JOB:
                                   add_job();
                                   break;
                               case REMOVE_JOB:
                                   remove_job();
                                   break;
                               case EDIT_JOB:
                                   edit_job();
                                   break;
                               case RUN_JOB:
                                   run_job();
                                   break;
                               case EXIT:
                                    job_schd->exit();
                                   return;
                               case LIST_JOBS:
                                   list_jobs();
                                   break;
                               default:
                                   break;
                               }
                           } });
}

auto command_interface::add_job() -> void
{
    int job_id = 0;
    while (job_id <= 0)
    {
        get_positive_int(job_id);
    }
    std::string cron;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore leftover '\n'
    std::cout << "Enter job cron: ";
    std::getline(std::cin, cron);

    auto *job = new Job(job_id, cron, [](int job_id)
                     { std::cout << "Job with id: " << job_id << " ran on thread id: " << std::this_thread::get_id() << '\n';
                 std::cout << "sleepingfor: " << job_id << " seconds" << '\n';
                 std::this_thread::sleep_for(std::chrono::seconds(job_id)); });

    job_schd->add_job(job);
}

auto command_interface::list_jobs() -> void
{
    std::cout << "current jobs: " << '\n';
    job_schd->print();
}

auto command_interface::select_job() -> std::optional<int>
{
    int job_id = 0;
    list_jobs();
    std::cout << "to cancel press 0" << '\n';
    get_positive_int(job_id);
    if (job_id == 0)
    {
        return std::nullopt;
    }
    return job_id;
}

auto command_interface::remove_job() -> void
{
    auto job_opt = select_job();
    if (!job_opt.has_value())
    {
        return;
    }
    auto job_id = job_opt.value();
    std::cout << "Job : " << job_id << " removed" << '\n';
    job_schd->extract_job(job_id);
}

auto command_interface::edit_job() -> void
{
    auto job_opt = select_job();
    if (!job_opt.has_value())
    {
        return;
    }
    auto job_id = job_opt.value();
    std::string cron;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore leftover '\n'
    std::cout << "Enter new cron: ";
    std::getline(std::cin, cron);
    auto *job = job_schd->extract_job(job_id);
    job->set_cron(cron);
    job->set_next_run();
    job_schd->add_job(job);
}

auto command_interface::run_job() -> void
{
    auto job_opt = select_job();
    if (!job_opt.has_value())
    {
        return;
    }
    auto job_id = job_opt.value();
    auto *job = job_schd->extract_job(job_id);
    job->set_next_run(job->get_next_run());
    job_schd->add_job(job);
}

void get_positive_int(int &job_id)
{
    while (true)
    {
        std::cout << "Enter job id: ";
        std::cin >> job_id;
        if (job_id < 0)
        {
            std::cout << "id should be greater than or equal to 0" << '\n';
            continue;
        }

        if (std::cin.fail())
        {
            std::cout << "id should be a number" << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        break;
    }
}
