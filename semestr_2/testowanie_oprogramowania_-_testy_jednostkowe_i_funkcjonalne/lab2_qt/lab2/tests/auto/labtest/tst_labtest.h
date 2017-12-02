#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../../../src/Picture.hpp"
#include "../../../src/Rectangle.hpp"
using namespace testing;

TEST(LabTest, TestOK)
{
    Picture myPicture;
    Rectangle rec1(2,4);
    myPicture.addShape(&rec1);
    ASSERT_THAT(myPicture.getTotalArea(), 8);
}
TEST(LabTest, TestNOK)
{
    Picture myPicture;
    Rectangle rec1(2,4);
    myPicture.addShape(&rec1);
    ASSERT_THAT(myPicture.getTotalArea(), 9);
}
