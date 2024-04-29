#include <string>
// #include <chrono>
#include "croncpp.h"
#include <iostream>
#include <functional>
#include <thread>

class TimeSchduler
{
private:
    std::time_t next_run;
    cron::cronexpr expr;

public:
    TimeSchduler(std::string cron)
    {
        // parse cron
        std::cout << "Parsing cron: " << cron << std::endl;
        expr = cron::make_cron(cron);
        std::cout << "Cron parsed" << std::endl;
        set_next_run();
    };

    bool set_next_run(std::time_t from = std::time(0))
    {
        try
        {
            /* code */
            auto next = cron::cron_next(expr, from);
            if (next == cron::INVALID_TIME)
            {
                std::cerr << "Invalid TIME" << std::endl;
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

    std::time_t get_next_run()
    {
        return next_run;
    }

    bool operator<(const TimeSchduler &rhs) const
    {
        return next_run < rhs.next_run;
    }

    bool operator>(const TimeSchduler &rhs) const
    {
        return next_run > rhs.next_run;
    }
};

class Runnable
{
public:
    Runnable(std::function<void()> func) : func(func) {}
    void run()
    {
        std::thread t([this]()
                      { func(); });
        t.detach();
    }

private:
    std::function<void()> func;
};

class Job : public TimeSchduler, public Runnable
{
public:
    Job(int id, std::string cron, std::function<void(int)> func) : id(id), cron(cron), TimeSchduler(cron), Runnable([this, func, id]()
                                                                                                                    { func(id); }) {}
    int id;
    std::string cron;
    friend std::ostream &operator<<(std::ostream &os, Job &job)
    {
        os << "Job id: " << job.id << " cron: " << job.cron << " next run: " << job.get_next_run();
        return os;
    }
};