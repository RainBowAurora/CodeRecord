#ifndef __SELECTION_SORT_H__
#define __SELECTION_SORT_H__

#include <iostream>
#include <vector>
#include <memory>

template<typename Iterator>
void SelectionSort(const Iterator begin, const Iterator end)
{
    //获取容器内元素的类型  
    using value_type = typename std::iterator_traits<Iterator>::value_type; 

    auto size=std::distance(begin, end);
    if(size <= 1) return;

    for(auto current = begin; current != end; current++){
        auto min_iter = current;
        for(auto iter = current + 1; iter != end; iter++){
            if(*iter < *min_iter) min_iter = iter;
        }
        value_type  temp_value = *min_iter;
        *min_iter = *current;
        *current = temp_value;
    }
}

#endif /*__SELECTION_SORT_H__*/
