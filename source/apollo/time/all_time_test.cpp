#include <gtest/gtest.h>
#include "chrono_time_test.h"

#include "chrono_duration_test.h"

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}