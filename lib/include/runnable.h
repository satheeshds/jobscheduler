#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <functional>

class Runnable
{
private:
    std::function<void()> func;

public:
    explicit Runnable(std::function<void()> func);
    // virtual ~Runnable(){}; // Virtual destructor
    void run(); // Pure virtual function makes this class Abstract class
};

#endif // RUNNABLE_H
