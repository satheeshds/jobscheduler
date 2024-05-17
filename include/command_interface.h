#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include "job_scheduler.h"
#include "job.h"
#include <cstdlib>
#include <iostream>
#include <thread>
#include <optional>

#define ADD_JOB 1
#define REMOVE_JOB 2
#define EDIT_JOB 3
#define RUN_JOB 4
#define EXIT 5
#define LIST_JOBS 6

class command_interface
{
private:
    /* data */
    JobScheduler *job_schd;

public:
    command_interface(JobScheduler *job_schd);
    ~command_interface() = default;
    auto run() -> std::thread;
    auto add_job() -> void;
    auto remove_job() -> void;
    auto edit_job() -> void;
    auto run_job() -> void;
    auto list_jobs() -> void;
    auto select_job() -> std::optional<int>;
};

#endif
