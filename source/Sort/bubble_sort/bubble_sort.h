#ifndef __BUBBLE_SORT_H__
#define __BUBBLE_SORT_H__

#include <iostream>
#include <vector>
#include <memory>

template<typename Iterator>
void BubbleSort(const Iterator begin, const Iterator end)
{                                                                                                                                                                                                                                  
    // using value_type = typename std::iterator_traits<Iterator>::value_type;   //迭代器指向对象的值类型      
    
    auto size=std::distance(begin, end);
    if(size <= 1) return;
    
    for(int i = 0; i < size - 1; i++){ 
        for(auto left = begin; left != begin + (size - i - 1); left++){
            if(*left > *(left+1)){
                auto temp_value = *left;
                *left = *(left+1);
                *(left+1) = temp_value;
            }
        }
    }   
}

#endif /*__BUBBLE_SORT_H__*/