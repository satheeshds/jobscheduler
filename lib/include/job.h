#ifndef JOB_H
#define JOB_H

#include <string>
#include <iostream>
#include <functional>
#include "time_scheduler.h"
#include "runnable.h"

class Job : public TimeScheduler, public Runnable
{
private:
    int id;
    std::string cron;

public:
    Job(int job_id, const std::string &cron, const std::function<void(int)> &func);
    [[nodiscard]] auto get_id() const -> int;
    void set_cron(const std::string &cron);
    friend auto operator<<(std::ostream &ostream, Job &job) -> std::ostream &;
};

#endif // JOB_H
