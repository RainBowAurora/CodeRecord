#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "assert/assert.hpp"
#include "fixtures/fixtures.hpp"
#include "fixtures/run_time.hpp"

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}