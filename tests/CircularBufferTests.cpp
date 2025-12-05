#include <CXXCircularBuffer/CircularBuffer.hpp>
#include <gtest/gtest.h>

using namespace CXXCircularBuffer;

TEST(CircularBufferTest, PushBackAndPopFront)
{
    CircularBuffer<int, 3> buffer;

    // Initially, the buffer should be empty
    EXPECT_TRUE(buffer.empty());
    EXPECT_EQ(buffer.size(), 0);

    // Push elements into the buffer
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);

    // Now the buffer should be full
    EXPECT_FALSE(buffer.empty());
    EXPECT_EQ(buffer.size(), 3);

    // Pushing another element should overwrite the oldest one
    buffer.push_back(4);
    EXPECT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer[0], 2); // The oldest element (1) should be overwritten

    // Pop an element from the front
    buffer.pop_front();
    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer[0], 3); // The new front should be 3

    // Pop all elements
    buffer.pop_front();
    buffer.pop_front();
    EXPECT_TRUE(buffer.empty());
    EXPECT_EQ(buffer.size(), 0);
}

TEST(CircularBufferTest, IteratorFunctionality)
{
    CircularBuffer<int, 5> buffer;

    // Push elements into the buffer
    for (int i = 1; i <= 5; ++i)
    {
        buffer.push_back(i);
    }

    // Test forward iterator
    int expected = 1;
    for (auto it = buffer.begin(); it != buffer.end(); ++it, ++expected)
    {
        EXPECT_EQ(*it, expected);
    }

    // Test reverse iterator
    expected = 5;
    for (auto rit = buffer.rbegin(); rit != buffer.rend(); ++rit, --expected)
    {
        EXPECT_EQ(*rit, expected);
    }
}

TEST(CircularBufferTest, ClearFunctionality)
{
    CircularBuffer<int, 4> buffer;

    // Push elements into the buffer
    buffer.push_back(10);
    buffer.push_back(20);
    buffer.push_back(30);

    EXPECT_EQ(buffer.size(), 3);

    // Clear the buffer
    buffer.clear();

    EXPECT_TRUE(buffer.empty());
    EXPECT_EQ(buffer.size(), 0);

    // Ensure we can push new elements after clearing
    buffer.push_back(40);
    EXPECT_EQ(buffer.size(), 1);
    EXPECT_EQ(buffer[0], 40);
}
TEST(CircularBufferTest, FrontAndBackAccess)
{
    CircularBuffer<int, 3> buffer;

    buffer.push_back(100);
    buffer.push_back(200);
    buffer.push_back(300);

    EXPECT_EQ(buffer.front(), 100);
    EXPECT_EQ(buffer.back(), 300);

    buffer.pop_front();
    EXPECT_EQ(buffer.front(), 200);

    buffer.push_back(400);
    EXPECT_EQ(buffer.back(), 400);
}
TEST(CircularBufferTest, OverwriteBehavior)
{
    CircularBuffer<int, 2> buffer;

    buffer.push_back(1);
    buffer.push_back(2);
    EXPECT_EQ(buffer.size(), 2);

    // This push should overwrite the oldest element (1)
    buffer.push_back(3);
    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer[0], 2);
    EXPECT_EQ(buffer[1], 3);

    // This push should overwrite the oldest element (2)
    buffer.push_back(4);
    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer[0], 3);
    EXPECT_EQ(buffer[1], 4);
}

TEST(CircularBufferTest, CapacityAndMaxSize)
{
    CircularBuffer<int, 10> buffer;

    EXPECT_EQ(buffer.capacity(), 10);
    EXPECT_EQ(buffer.max_size(), 10);

    for (int i = 0; i < 5; ++i)
    {
        buffer.push_back(i);
    }

    EXPECT_EQ(buffer.size(), 5);
}

TEST(CircularBufferTest, ConstIteratorFunctionality)
{
    CircularBuffer<int, 4> buffer;

    for (int i = 1; i <= 4; ++i)
    {
        buffer.push_back(i);
    }

    const CircularBuffer<int, 4> &constBuffer = buffer;

    int expected = 1;
    for (auto it = constBuffer.begin(); it != constBuffer.end(); ++it, ++expected)
    {
        EXPECT_EQ(*it, expected);
    }

    expected = 4;
    for (auto rit = constBuffer.rbegin(); rit != constBuffer.rend(); ++rit, --expected)
    {
        EXPECT_EQ(*rit, expected);
    }
}

TEST(CircularBufferTest, IndexOperator)
{
    CircularBuffer<int, 5> buffer;

    for (int i = 0; i < 5; ++i)
    {
        buffer.push_back(i * 10);
    }

    for (std::size_t i = 0; i < buffer.size(); ++i)
    {
        EXPECT_EQ(buffer[i], static_cast<int>(i * 10));
    }
}

TEST(CircularBufferTest, PopFrontOnEmptyBuffer)
{
    CircularBuffer<int, 3> buffer;

    // Popping from an empty buffer should not change its state
    buffer.pop_front();
    EXPECT_TRUE(buffer.empty());
    EXPECT_EQ(buffer.size(), 0);

    // Push and pop to ensure normal functionality
    buffer.push_back(42);
    EXPECT_EQ(buffer.size(), 1);
    buffer.pop_front();
    EXPECT_TRUE(buffer.empty());
}

TEST(CircularBufferTest, MultipleWrapArounds)
{
    CircularBuffer<int, 3> buffer;

    for (int i = 1; i <= 10; ++i)
    {
        buffer.push_back(i);
    }

    EXPECT_EQ(buffer.size(), 3);
    EXPECT_EQ(buffer[0], 8);
    EXPECT_EQ(buffer[1], 9);
    EXPECT_EQ(buffer[2], 10);
}

TEST(CircularBufferTest, IteratorArithmetic)
{
    CircularBuffer<int, 5> buffer;

    for (int i = 1; i <= 5; ++i)
    {
        buffer.push_back(i);
    }

    auto it = buffer.begin();
    EXPECT_EQ(*it, 1);

    it += 2;
    EXPECT_EQ(*it, 3);

    it = it + 1;
    EXPECT_EQ(*it, 4);

    it -= 2;
    EXPECT_EQ(*it, 2);

    it = it - 1;
    EXPECT_EQ(*it, 1);
}

TEST(CircularBufferTest, ReverseIteratorArithmetic)
{
    CircularBuffer<int, 5> buffer;

    for (int i = 1; i <= 5; ++i)
    {
        buffer.push_back(i);
    }

    auto rit = buffer.rbegin();
    EXPECT_EQ(*rit, 5);

    rit += 2;
    EXPECT_EQ(*rit, 3);

    rit = rit + 1;
    EXPECT_EQ(*rit, 2);

    rit -= 2;
    EXPECT_EQ(*rit, 4);

    rit = rit - 1;
    EXPECT_EQ(*rit, 5);
}

TEST(CircularBufferTest, SizeAfterMultipleOperations)
{
    CircularBuffer<int, 4> buffer;

    EXPECT_EQ(buffer.size(), 0);

    buffer.push_back(1);
    buffer.push_back(2);
    EXPECT_EQ(buffer.size(), 2);

    buffer.pop_front();
    EXPECT_EQ(buffer.size(), 1);

    buffer.push_back(3);
    buffer.push_back(4);
    buffer.push_back(5); // This should overwrite the oldest (2)
    EXPECT_EQ(buffer.size(), 4);

    buffer.pop_front();
    buffer.pop_front();
    EXPECT_EQ(buffer.size(), 2);
}

TEST(CircularBufferTest, AccessAfterWrapAround)
{
    CircularBuffer<int, 3> buffer;

    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);

    // Overwrite oldest
    buffer.push_back(4);

    EXPECT_EQ(buffer[0], 2);
    EXPECT_EQ(buffer[1], 3);
    EXPECT_EQ(buffer[2], 4);

    buffer.pop_front();
    EXPECT_EQ(buffer[0], 3);
    EXPECT_EQ(buffer[1], 4);
}

TEST(CircularBufferTest, ClearAndReuse)
{
    CircularBuffer<int, 3> buffer;

    buffer.push_back(10);
    buffer.push_back(20);
    buffer.push_back(30);

    EXPECT_EQ(buffer.size(), 3);

    buffer.clear();
    EXPECT_TRUE(buffer.empty());

    buffer.push_back(40);
    buffer.push_back(50);

    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer[0], 40);
    EXPECT_EQ(buffer[1], 50);
}

TEST(CircularBufferTest, BackAfterMultiplePushes)
{
    CircularBuffer<int, 3> buffer;

    buffer.push_back(5);
    EXPECT_EQ(buffer.back(), 5);

    buffer.push_back(10);
    EXPECT_EQ(buffer.back(), 10);

    buffer.push_back(15);
    EXPECT_EQ(buffer.back(), 15);

    // This push should overwrite the oldest element (5)
    buffer.push_back(20);
    EXPECT_EQ(buffer.back(), 20);
}

TEST(CircularBufferTest, FrontAfterMultiplePops)
{
    CircularBuffer<int, 3> buffer;

    buffer.push_back(100);
    buffer.push_back(200);
    buffer.push_back(300);

    EXPECT_EQ(buffer.front(), 100);

    buffer.pop_front();
    EXPECT_EQ(buffer.front(), 200);

    buffer.pop_front();
    EXPECT_EQ(buffer.front(), 300);

    buffer.pop_front();
    EXPECT_TRUE(buffer.empty());
}

TEST(CircularBufferTest, IteratorOnEmptyBuffer)
{
    CircularBuffer<int, 3> buffer;

    auto it = buffer.begin();
    auto end = buffer.end();

    EXPECT_EQ(it, end); // Both should be equal for an empty buffer
}

TEST(CircularBufferTest, ReverseIteratorOnEmptyBuffer)
{
    CircularBuffer<int, 3> buffer;

    auto rit = buffer.rbegin();
    auto rend = buffer.rend();

    EXPECT_EQ(rit, rend); // Both should be equal for an empty buffer
}
