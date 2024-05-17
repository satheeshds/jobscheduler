#ifndef TIMESCHEDULER_H
#define TIMESCHEDULER_H

#include <ctime>
#include <string>
#include "croncpp.h"

class TimeScheduler
{
private:
    std::time_t next_run{};
    cron::cronexpr expr;

public:
    TimeScheduler(const std::string& cron);
    bool set_next_run(std::time_t from = std::time(0));
    bool set_cron(const std::string& cron);
    std::time_t get_next_run() const;
    bool operator<(const TimeScheduler &rhs) const;
    bool operator>(const TimeScheduler &rhs) const;
};

#endif // TIMESCHEDULER_H