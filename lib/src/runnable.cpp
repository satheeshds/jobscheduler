#include "runnable.h"
#include <functional>
#include <thread>
#include <utility>

Runnable::Runnable(std::function<void()> func) : func(std::move(std::move(func))) {}

void Runnable::run()
{
    std::thread thread([this]()
                       { func(); });
    thread.detach();
}
