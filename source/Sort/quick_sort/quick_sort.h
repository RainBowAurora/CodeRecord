#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

#include <iostream>
#include <vector>
#include <assert.h>

template<typename Iterator,typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
Iterator partition(const Iterator begin, const Iterator end, const Iterator partition_iter, CompareType comapre=CompareType())
{
    auto size = std::distance(begin, end);
    if(size < 1) return end;

    assert(std::distance(begin,partition_iter)>=0 &&std::distance(partition_iter,end)>0);

    std::swap(*partition_iter, *(end - 1));
    auto small_next = begin;

    for(auto iter = begin; iter != end; iter++){
        if(*iter < *(end - 1)){
            std::swap(*iter, *(small_next++));
        }
    }
    
    std::swap(*small_next, *(end - 1)); //交换partition元素到它的位置
    return small_next;
}

template<typename Iterator,typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
void QuickSort(const Iterator begin, const Iterator end, CompareType comapre=CompareType())
{
    auto size = std::distance(begin, end);
    if(size <=1) return;

    auto partition_iter = partition(begin, end, end-1);
    QuickSort(begin, partition_iter, comapre);
    QuickSort(partition_iter+1, end, comapre);
}

#endif /*__QUICK_SORT_H__*/
