#include <gtest/gtest.h>
#include "job.h"
#include "node.h"

class NodeTest : public ::testing::Test // NOLINT
{
protected:
    Node *node1, *node2, *node3, *node4; // NOLINT
    ~NodeTest() override = default;
    void SetUp() override
    {
        node1 = new Node();
        node2 = new Node();
        node3 = new Node();
        node4 = new Node();
    }
    void TearDown() override
    {
        delete node1;
        delete node2;
        delete node3;
        delete node4;
    }
};

TEST_F(NodeTest, SetChildTest)
{
    // Test setting left child
    EXPECT_TRUE(node1->set_child(node2));

    // Test setting right child
    EXPECT_TRUE(node1->set_child(node3));

    // Test not setting child when both left and right are already set
    EXPECT_FALSE(node1->set_child(node4));
    EXPECT_EQ(node1->left_child(), node2);
    EXPECT_EQ(node1->right_child(), node3);
}

TEST_F(NodeTest, RemoveChildTest)
{
    EXPECT_TRUE(node1->set_child(node2));
    EXPECT_TRUE(node1->set_child(node3));

    // Test removing left child
    EXPECT_TRUE(node1->remove_child(node2));
    EXPECT_EQ(node1->left_child(), nullptr);

    // Test removing right child
    EXPECT_TRUE(node1->remove_child(node3));
    EXPECT_EQ(node1->right_child(), nullptr);

    // Test not removing child when child is not present
    EXPECT_FALSE(node1->remove_child(node4));
}

TEST_F(NodeTest, ParentTest)
{
    // Test parent of left child
    EXPECT_TRUE(node1->set_child(node2));
    EXPECT_EQ(node2->parent(node1), node1);

    // Test parent of right child
    EXPECT_TRUE(node1->set_child(node3));
    EXPECT_EQ(node3->parent(node1), node1);

    EXPECT_TRUE(node3->set_child(node4));
    EXPECT_EQ(node4->parent(node1), node3);

    // Test parent of root
    EXPECT_EQ(node1->parent(nullptr), nullptr);
}

TEST_F(NodeTest, OperatorTest)
{
    Job job1(1, "0/1 * * * * *", nullptr);
    Job job2(2, "0/5 * * * * *", nullptr);

    Node node1(&job1);
    Node node2(&job2);

    // Test operator>
    // auto first = node1.get_job()->get_next_run();
    // auto second = node2.get_job()->get_next_run();
    auto expected = job1 < job2;
    EXPECT_EQ(expected, node1 < node2);
    EXPECT_EQ(job2 > job1, node2 > node1);

    // Test operator<
    // EXPECT_TRUE(node1 > node2);
}
