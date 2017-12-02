#include <gmock/gmock.h>
#include "src/Picture.hpp"
#include "src/Rectangle.hpp"

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

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
