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
    explicit TimeScheduler(const std::string &cron);
    auto set_next_run(std::time_t from = std::time(nullptr)) -> bool;
    auto set_cron(const std::string &cron) -> bool;
    [[nodiscard]] auto get_next_run() const -> std::time_t;
    auto operator<(const TimeScheduler &rhs) const -> bool;
    auto operator>(const TimeScheduler &rhs) const -> bool;
};

#endif // TIMESCHEDULER_H
