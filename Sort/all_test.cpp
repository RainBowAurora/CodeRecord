#include <gtest/gtest.h>

#include "bubble_sort/bubble_sort_test.h"
#include "heap_sort/heap_sort_test.h"
#include "insert_sort/insert_sort.h"
#include "merge_sort/merge_sort_test.h"
#include "quick_sort/quick_sort_test.h"
#include "selection_sort/selection_sort_test.h"
#include "shell_sort/shell_sort_test.h"


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}