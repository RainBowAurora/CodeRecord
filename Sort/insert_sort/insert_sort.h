#ifndef __INSERT_SORT_H__
#define __INSERT_SORT_H__

#include <iostream>
#include <vector>

template<typename Iterator,typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
void InsertSort(const Iterator begin, const Iterator end, CompareType compare = CompareType())
{
    //typedef typename std::iterator_traits<Iterator>::value_type value_type;// 迭代器指向对象的值类型
    auto size=std::distance(begin, end);
    if(size <= 1) return;

    for(auto current = begin; current != end; current++){
        auto small_iter = current;
        
        //找到要插入的位置
        while(small_iter != begin && compare(*current, *(small_iter - 1))){ 
            small_iter--;  
        }

        //插入后方的元素右移1
        auto key = *current;
        for(auto iter = current; iter != small_iter; iter--){
            *iter = *(iter - 1);
        }

        //插入元素
        *small_iter = key;
    }
}


#endif /*__INSERT_SORT_H__*/