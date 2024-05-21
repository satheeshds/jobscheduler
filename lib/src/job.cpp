#include <functional>
#include <iostream>
#include <string>
#include "time_scheduler.h"
#include "runnable.h"
#include "job.h"

Job::Job(int job_id, const std::string &cron, const std::function<void(int)> &func) : id(job_id), cron(cron), TimeScheduler(cron), Runnable([this, func, job_id]()
                                                                                                                                            { func(job_id); }) {}
auto Job::get_id() const -> int
{
    return id;
}
void Job::set_cron(const std::string &cron)
{
    this->cron = cron;
    TimeScheduler::set_cron(cron);
}
auto operator<<(std::ostream &ostream, Job &job) -> std::ostream &
{
    ostream << "Job ID: " << job.id << ", Schedule: " << job.cron << ", Next run: " << job.get_next_run();
    return ostream;
}
