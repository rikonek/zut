// Napisać implementację RingBuffer: 
// RingBuffer - potrafi przechowywać maksymalnie N elementów
// https://en.wikipedia.org/wiki/Circular_buffer
// RingBuffer ma być kontenerem STL
// ma wspierać range for oraz podstawowe algorytmy STL'a
// nie ma gwaracji co do stanu iteratorów
// jeżeli RB zostanie zaimplementowany jako adaptor - std::list ma zostać wyłączony z możliwości użycia

#include <iostream>
#include <array>
#include <gtest/gtest.h>

template<typename T, std::size_t N>
class RingBuffer
{
    public:
        void push_back(const T& t)
        {
            arr[write_index]=t;
            write_index++;
            if(write_index>=N) write_index=0;
            if(fill<N) fill++;
        }

        auto read()
        {
            return arr[read_index];
        }

        auto readAll()
        {
            std::array<T, N> arr_tmp;
            begin();
            for(unsigned int i=0; i<fill; i++)
            {
                arr_tmp[i]=arr[read_index];
                next();
            }
            return arr_tmp;
        }

        void next()
        {
            read_index++;
            if(read_index>=fill) read_index=0;
        }

        void prev()
        {
            if(read_index<=0)
            {
                if(fill==0)
                {
                    read_index=0;
                }
                else
                {
                    read_index=fill-1;
                }
            }
            else
            {
                read_index--;
            }
        }

        void begin()
        {
            read_index=write_index;
            if(fill<N) read_index=0;
        }

        void end()
        {
            read_index=write_index;
            prev();
        }

    private:
        std::size_t read_index=0;
        std::size_t write_index=0;
        std::size_t fill=0;
        std::array<T, N> arr;
};

TEST(RingBuffer, strings)
{
    RingBuffer<std::string, 5> buffer;
    buffer.push_back("a");
    EXPECT_EQ(buffer.read(), "a");
    buffer.push_back("b");
    buffer.push_back("c");
    buffer.push_back("d");
    buffer.push_back("e");
    buffer.push_back("f");
    EXPECT_EQ(buffer.read(), "f");
    buffer.push_back("g");
    buffer.begin();
    EXPECT_EQ(buffer.read(), "c");
    buffer.end();
    EXPECT_EQ(buffer.read(), "g");
    buffer.next();
    EXPECT_EQ(buffer.read(), "c");
    buffer.next();
    EXPECT_EQ(buffer.read(), "d");
    buffer.prev();
    EXPECT_EQ(buffer.read(), "c");
}

TEST(RingBuffer, int_loop)
{
    RingBuffer<int, 5> buffer;
    for(std::size_t i=0; i<22; i++)
    {
        buffer.push_back(i);
    }
    buffer.begin();
    EXPECT_EQ(buffer.read(), 17);
    buffer.end();
    EXPECT_EQ(buffer.read(), 21);
}

TEST(RingBuffer, readAll)
{
    RingBuffer<int, 5> buffer;
    for(std::size_t i=0; i<7; i++)
    {
        buffer.push_back(i);
    }
    buffer.begin();
    EXPECT_EQ(buffer.read(), 2);

    std::array<int, 5> expect = {2, 3, 4, 5, 6};
    EXPECT_EQ(buffer.readAll(), expect);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}