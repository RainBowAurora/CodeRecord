#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

#include <iostream>
#include <vector>

template<typename Iterator, typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_tpye>>
void Merge(const Iterator begin, const Iterator end, const Iterator middle, CompareType compare= CompareType())
{
    using value_type = typename std::iterator_traits<Iterator>::value_type;// 迭代器指向对象的值类型
    if(std::distance(begin, middle)<=0 || std::distance(middle, end) <= 0) return;
    std::vector<value_type> result(begin,end); //暂存结果

    auto current=result.begin();
    auto left_current=begin; //左侧序列当前比较位置
    auto right_current=middle;//右序列当前比较位置 

    while(left_current != middle && right_current != end){
        if(compare(*left_current, *right_current)){
            *current++ = *left_current++;
        }else{
            *current++ = *right_current++;
        }
    }

    if(left_current != middle){ 
        std::copy(left_current, middle, current);
    }

    if(right_current != end){
        std::copy(right_current, end, current);
    }

    std::copy(result.begin(), result.end(), begin);
}

template<typename Iterator,typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
void MergeSort(const Iterator begin,const Iterator end,CompareType compare=CompareType())
{
    auto size=std::distance(begin,end);
    if(size<=1) return;
    
    Iterator middle=begin+size/2;

    MergeSort(begin,middle,compare);
    MergeSort(middle,end,compare);
    Merge(begin,end,middle,compare);
    
}

#endif /*__MERGE_SORT_H__*/
