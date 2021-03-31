#ifndef __SHELL_SORT_H__
#define __SHELL_SORT_H__

#include <iostream>
#include <vector>

template<typename Iterator,typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
void ShellSort(const Iterator begin, const Iterator end, CompareType compare=CompareType())
{
    int size = std::distance(begin, end);

    for (int gap = size / 2; gap > 0; gap /= 2) { //间隔序列，在希尔排序中我们称之为增量序列
        for (int i = gap; i < size; i++) { // 从 gap 开始，按照顺序将每个元素依次向前插入自己所在的组
            int pre_index = i - gap;    // 该组前一个数字的索引
            auto key = *(begin+i);

            while(pre_index >= 0 && compare(key, *(begin+pre_index))){
                *(begin+pre_index+gap) = *(begin+pre_index);
                pre_index -= gap;
            }
                *(begin+pre_index+gap) = key;
        }
    }
}

#endif /*__SHELL_SORT_H__*/
