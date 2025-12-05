#include <CXXCircularBuffer/CircularBuffer.hpp>
#include <iostream>

int main()
{
    CXXCircularBuffer::CircularBuffer<int, 5> buffer;

    // Add elements to the circular buffer
    for (int i = 1; i <= 7; ++i)
    {
        buffer.push_back(i);
        std::cout << "Added: " << i << ", Buffer contents: ";
        for (const auto &item : buffer)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    // Remove elements from the circular buffer
    for (int i = 0; i < 3; ++i)
    {
        buffer.pop_front();
        std::cout << "Removed front element, Buffer contents: ";
        for (const auto &item : buffer)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}