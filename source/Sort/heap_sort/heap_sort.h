#ifndef __HEAP_SORT_H__
#define __HEAP_SORT_H__

#include <iostream>
#include <vector>

template<typename Iterator>
class HeapSort{
public:
    template<typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
    void operator()(const Iterator begin, const Iterator end, CompareType compare=CompareType()){
        heap_size_ = std::distance(begin, end);
        root_ = begin;
        
        BuildHeap(compare);

        for(int num = heap_size_ - 1; num > 0; num--){
            std::swap(*root_, *(root_+ num));
            Heapify(0, num, compare);
        }
    }
    template<typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
    void BuildHeap(CompareType compare=CompareType()){
        for(int i = ((heap_size_>>1)-1); i >= 0; i--){  // n/2-1
            Heapify(i, heap_size_, compare);
        }
    }

    template<typename CompareType=std::less<typename std::iterator_traits<Iterator>::value_type>>
    void Heapify(int i, size_t size,CompareType compare=CompareType()){
        size_t max_index = i;
        size_t left = i*2+1;    
        size_t right = left+1;
        
        if(left < size && compare(*(root_+max_index), *(root_+left))){
            max_index = left;
        }
        if(right < size && compare(*(root_+max_index), *(root_+right))){
            max_index = right;
        }
        if(max_index != i){
            std::swap(*(root_+i), *(root_+max_index));
            Heapify(max_index, size, compare);
        }
    }

private:
    std::size_t heap_size_ = {0};
    Iterator root_;
};

#endif /*__HEAP_SORT_H__*/


