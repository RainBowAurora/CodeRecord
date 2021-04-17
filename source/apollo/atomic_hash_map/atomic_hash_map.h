#ifndef __ATOMIC_HASH_MAP_H__
#define __ATOMIC_HASH_MAP_H__

#include <iostream>
#include <atomic>

template<typename K, typename V, std::size_t TableSize = 128,
         typename std::enable_if<std::is_integral<K>::value && 
                                (TableSize & (TableSize - 1)) == 0,
                                int>::type = 0>
class AtomicHashMap
{
public:
    AtomicHashMap(): capacity_(TableSize), mode_num_(capacity_ - 1) {}
    bool Hash(const K& key) { 
        std::size_t index = key & mode_num_;
        return table_[index].Hash(key);
    }
    
    bool Get(const K& key, V* value){
        std::size_t index = key & mode_num_;
        V* val = nullptr;
        if(table_[index].Get(key, &val)){
            *value = *val;
            return true;
        }
        return false;
    }

    bool Get(const K& key, V** value){
        std::size_t index = key & mode_num_;
        return table_[index].Get(key, value);
    }

    void Set(const K& key, V& value){
        std::size_t index = key & mode_num_;
        table_[index].Insert(key, value);
    }

    void Set(const K& key, V&& value){
        std::size_t index = key & mode_num_;
        table_[index].Insert(key, std::forward<V>(value));
    }

    void Set(const K& key){
        std::size_t index = key & mode_num_;
        table_[index].Insert(key);
    }

private:
    struct Entry{
        K key_ = 0;
        std::atomic<V *> value_ptr_ = {nullptr};
        std::atomic<Entry *> next_ = {nullptr}; 
        Entry() = default;
        ~Entry() { delete value_ptr_.load(std::memory_order_acquire); }
        explicit Entry(const K& key): key_(key){
            value_ptr_.store(new V(), std::memory_order_release);
        }

        explicit Entry(const K& key, const V& value): key_(key){
            value_ptr_.store(new V(value), std::memory_order_release);
        }

        explicit Entry(const K& key, V&& value): key_(key){
            value_ptr_.store(new V(std::forward<V>(value)), std::memory_order_release);
        }

    };

    class Bucket{
    public:
        Bucket(): entry_(new Entry()) {}
        ~Bucket(){};

        bool Hash(const K& key){
            Entry * m_head = entry_->next_.load(std::memory_order_acquire);
            while(Entry* target = m_head ){
                if(target->key_ < key){
                    m_head = target->next_.load(std::memory_order_acquire);
                    continue;
                }else{
                    return target->key_ == key;
                }
            }
            return false;
        }

        bool Find(const K& key, Entry **prev_ptr, Entry **target_ptr){
            Entry *prev = entry_;
            Entry *current = entry_->next_.load(std::memory_order_acquire);
            while( Entry* target =  current){
                if(target->key_ == key){
                    *prev_ptr = prev;
                    *target_ptr = target;
                    return true;
                }else if(target->key_ > key){
                    *prev_ptr = prev;
                    *target_ptr = target;
                    return false;
                }else{
                    prev = target;
                    current = target->next_.load(std::memory_order_acquire);
                    continue;
                }
            }
            *prev_ptr = prev;
            *target_ptr = nullptr;
            return false;
        }

        void Insert(const K& key, V& value){
            Entry* prev = nullptr;
            Entry* target = nullptr;
            Entry* new_entry = nullptr;
            V* new_value = nullptr;
            while(true){
                if( Find(key, &prev, &target) ){
                    if(!new_value) new_value = new V(value);
                    auto old_var_ptr = target->value_ptr_.load(std::memory_order_acquire);
                    if(target->value_ptr_.compare_exchange_strong(old_var_ptr, new_value, 
                        std::memory_order_acq_rel,std::memory_order_relaxed)){
                        delete old_var_ptr;
                        if(new_entry){
                            delete new_entry;
                            new_entry = nullptr;
                        }
                        return;
                    }
                    continue;
                }else{
                    if(!new_entry) new_entry = new Entry(key, value);
                    new_entry->next_.store(target, std::memory_order_release);
                    if(prev->next_.compare_exchange_strong(target, new_entry,
                        std::memory_order_acq_rel,std::memory_order_relaxed)){
                            if(new_value){
                                delete new_value;
                                new_value = nullptr;
                            }
                            return;
                    }
                }
            }
        }

        void Insert(const K& key, V&& value){
            Entry* prev = nullptr;
            Entry* target = nullptr;
            Entry* new_entry = nullptr;
            V* new_value = nullptr;
            while(true){
                if( Find(key, &prev, &target) ){
                    if(!new_value) new_value = new V(std::forward<V>(value));
                    auto old_var_ptr = target->value_ptr_.load(std::memory_order_acquire);
                    if(target->value_ptr_.compare_exchange_strong(old_var_ptr, new_value, 
                        std::memory_order_acq_rel,std::memory_order_relaxed)){
                        delete old_var_ptr;
                        if(new_entry){
                            delete new_entry;
                            new_entry = nullptr;
                        }
                        return;
                    }
                    continue;
                }else{
                    if(!new_entry) new_entry = new Entry(key, std::forward<V>(value));
                    new_entry->next_.store(target, std::memory_order_release);
                    if(prev->next_.compare_exchange_strong(target, new_entry,
                        std::memory_order_acq_rel,std::memory_order_relaxed)){
                            if(new_value){
                                delete new_value;
                                new_value = nullptr;
                            }
                            return;
                    }
                }
            }
        }

        void Insert(const K& key)
        {
            Entry* prev = nullptr;
            Entry* target = nullptr;
            Entry* new_entry = nullptr;
            V* new_value = nullptr;
            while(true){
                if( Find(key, &prev, &target) ){
                    if(!new_value) new_value = new V();
                    auto old_var_ptr = target->value_ptr_.load(std::memory_order_acquire);
                    if(target->value_ptr_.compare_exchange_strong(old_var_ptr, new_value, 
                        std::memory_order_acq_rel,std::memory_order_relaxed)){
                        delete old_var_ptr;
                        if(new_entry){
                            delete new_entry;
                            new_entry = nullptr;
                        }
                        return;
                    }
                    continue;
                }else{
                    if(!new_entry) new_entry = new Entry(key);
                    new_entry->next_.store(target, std::memory_order_release);
                    if(prev->next_.compare_exchange_strong(target, new_entry,
                        std::memory_order_acq_rel,std::memory_order_relaxed)){
                            if(new_value){
                                delete new_value;
                                new_value = nullptr;
                            }
                            return;
                    }
                }
            }
        }

        bool Get(const K& key, V **value){
            Entry *prev = nullptr;
            Entry *target = nullptr;
            if(Find(key, &prev, &target)){
                *value = target->value_ptr_.load(std::memory_order_acquire);
                return true;
            }
            return false;
        }


    private:
        Entry* entry_;
    
    };

private:
    Bucket table_[TableSize];
    uint64_t capacity_;
    uint64_t mode_num_; 
    
    AtomicHashMap(const AtomicHashMap&) = delete;
    AtomicHashMap& operator=(const AtomicHashMap&) = delete;

};


#endif /*__ATOMIC_HASH_MAP_H__*/