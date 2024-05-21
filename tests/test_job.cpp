#include <ctime>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "job.h"

class JobTest : public ::testing::Test // NOLINT
{
protected:
    Job *job; // NOLINT
    ~JobTest() override = default;
    void SetUp() override
    {
        job = new Job(1, "0/1 * * * * *", nullptr);
    }
    void TearDown() override
    {
        delete job;
    }
};

TEST_F(JobTest, OutputOperatorTest)
{
    std::ostringstream oss;
    oss << *job;
    std::string const expected = "Job ID: 1, Schedule: 0/1 * * * * *, Next run: " + std::to_string(job->get_next_run());
    EXPECT_EQ(oss.str(), expected);
}

TEST_F(JobTest, SetCronTest)
{
    job->set_cron("0/2 * * * * *");
    auto now = std::time(nullptr);
    job->set_next_run(now);
    EXPECT_NEAR(job->get_next_run(), now + 2, 1);
    EXPECT_EQ(1, job->get_id());
}
