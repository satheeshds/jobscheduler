#include <cstdlib>
#include <ctime>
#include <thread>
#include "job_scheduler.h"
#include "command_interface.h"
#include <array>
#include <cstdint> // for std::uint8_t

enum : std::uint8_t
{
    TIME_STR_LEN = 80
};

auto current_time() -> const char *;

auto main() -> int
{
    JobScheduler job_scheduler;
    command_interface interface(&job_scheduler);

    auto job_scheduler_thread = job_scheduler.run();
    auto interface_thread = interface.run();

    job_scheduler_thread.join();
    interface_thread.join();

    return 0;
}

auto current_time() -> const char *
{
    static std::array<char, TIME_STR_LEN> buffer;
    std::time_t const now = std::time(nullptr);
    std::tm local_time{};

#ifdef _WIN32
    localtime_s(&local_time, &now);
#else
    localtime_r(&now, &local_time);
#endif
    std::strftime(buffer.data(), TIME_STR_LEN, "%Y-%m-%d %H:%M:%S", &local_time);
    return buffer.data();
}
