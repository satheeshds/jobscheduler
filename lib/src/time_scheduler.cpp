#include <ctime>
#include <exception>
#include <iostream>
#include <string>
#include "time_scheduler.h"
#include "croncpp.h"

TimeScheduler::TimeScheduler(const std::string &cron)
{
    // parse cron
    std::cout << "Parsing cron: " << cron << '\n';
    set_cron(cron);
    std::cout << "Cron parsed" << '\n';
    set_next_run();
}

auto TimeScheduler::set_next_run(std::time_t from) -> bool
{
    try
    {
        /* code */
        auto next = cron::cron_next(expr, from);
        if (next == cron::INVALID_TIME)
        {
            std::cerr << "Invalid TIME" << '\n';
            return false;
        }
        next_run = next;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return true;
}

auto TimeScheduler::set_cron(const std::string &cron) -> bool
{
    try
    {
        /* code */
        expr = cron::make_cron(cron);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

auto TimeScheduler::get_next_run() const -> std::time_t
{
    return next_run;
}

auto TimeScheduler::operator<(const TimeScheduler &rhs) const -> bool
{
    return next_run < rhs.next_run;
}

auto TimeScheduler::operator>(const TimeScheduler &rhs) const -> bool
{
    return next_run > rhs.next_run;
}
