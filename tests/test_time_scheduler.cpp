#include <gtest/gtest.h>
#include <ctime>
#include "time_scheduler.h"

class TimeSchedulerTest : public ::testing::Test // NOLINT
{
protected:
    TimeScheduler *timeScheduler;
    ~TimeSchedulerTest() override = default;

    void SetUp() override
    {
        timeScheduler = new TimeScheduler("0/1 * * * * *");
    }
};

TEST_F(TimeSchedulerTest, SetNextRunTest)
{
    std::time_t const currentTime = std::time(nullptr);
    std::time_t const nextRunTime = currentTime + 60; // Set next run time to be 1 minute from current time

    bool const result = timeScheduler->set_next_run(nextRunTime);

    EXPECT_TRUE(result);
    EXPECT_NEAR(timeScheduler->get_next_run(), nextRunTime, 1);
}

TEST_F(TimeSchedulerTest, SetCronTest)
{
    // Test with valid cron string
    std::string const validCron = "0/1 * * * * *";
    bool const resultValid = timeScheduler->set_cron(validCron);
    EXPECT_TRUE(resultValid);

    // Test with invalid cron string
    std::string const invalidCron = "invalid cron string";
    bool const resultInvalid = timeScheduler->set_cron(invalidCron);
    EXPECT_FALSE(resultInvalid);
}

TEST_F(TimeSchedulerTest, GetNextRunTest)
{
    std::time_t const currentTime = std::time(nullptr);
    std::time_t const nextRunTime = currentTime + 60; // Set next run time to be 1 minute from current time

    bool const setResult = timeScheduler->set_next_run(nextRunTime);
    ASSERT_TRUE(setResult);

    std::time_t const getNextRunResult = timeScheduler->get_next_run();

    EXPECT_NEAR(getNextRunResult, nextRunTime, 1);
}

TEST_F(TimeSchedulerTest, OperatorTest)
{
    // Create two TimeScheduler objects with different cron strings
    auto *timeScheduler1 = new TimeScheduler("0/1 * * * * *");
    auto *timeScheduler2 = new TimeScheduler("0/2 * * * * *");

    // Set next run times
    std::time_t const currentTime = std::time(nullptr);
    timeScheduler1->set_next_run(currentTime + 60);  // Set next run time to be 1 minute from current time
    timeScheduler2->set_next_run(currentTime + 120); // Set next run time to be 2 minutes from current time

    // Test the '<' operator
    EXPECT_TRUE(*timeScheduler1 < *timeScheduler2);

    // Test the '>' operator
    EXPECT_TRUE(*timeScheduler2 > *timeScheduler1);

    delete timeScheduler1;
    delete timeScheduler2;
}
