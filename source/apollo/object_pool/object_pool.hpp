#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__

#include <new>
#include <memory>
#include <iostream>
#include <functional>


template <typename T>
class ObjectPool : public std::enable_shared_from_this<ObjectPool<T>> {
 public:
  using InitFunc = std::function<void(T *)>;
  using ObjectPoolPtr = std::shared_ptr<ObjectPool<T>>;

  template <typename... Args>
  explicit ObjectPool(uint32_t num_objects, Args &&... args);

  template <typename... Args>
  ObjectPool(uint32_t num_objects, InitFunc f, Args &&... args);

  virtual ~ObjectPool();

  std::shared_ptr<T> GetObject();

 private:
  struct Node {
    T object;
    Node *next;
  };

  ObjectPool(ObjectPool &) = delete;
  ObjectPool &operator=(ObjectPool &) = delete;
  void ReleaseObject(T *);

  uint32_t num_objects_ = 0;
  char *object_arena_ = nullptr;
  Node *free_head_ = nullptr;
};

template <typename T>
template <typename... Args>
ObjectPool<T>::ObjectPool(uint32_t num_objects, Args &&... args)
    : num_objects_(num_objects) {
  const size_t size = sizeof(Node);
  object_arena_ = static_cast<char *>(std::calloc(num_objects_, size));
  if (object_arena_ == nullptr) {
    throw std::bad_alloc();
  }

  for(int i = 0; i < num_objects_; i++) {
    T *obj = new (object_arena_ + i * size) T(std::forward<Args>(args)...);
    reinterpret_cast<Node *>(obj)->next = free_head_;
    free_head_ = reinterpret_cast<Node *>(obj);
  }
}

template <typename T>
template <typename... Args>
ObjectPool<T>::ObjectPool(uint32_t num_objects, InitFunc f, Args &&... args)
    : num_objects_(num_objects) {
  const size_t size = sizeof(Node);
  object_arena_ = static_cast<char *>(std::calloc(num_objects_, size));
  if (object_arena_ == nullptr) {
    throw std::bad_alloc();
  }

  for(int i = 0; i < num_objects_; i++) {
    T *obj = new (object_arena_ + i * size) T(std::forward<Args>(args)...);
    f(obj);
    reinterpret_cast<Node *>(obj)->next = free_head_;
    free_head_ = reinterpret_cast<Node *>(obj);
  }
}

template <typename T>
ObjectPool<T>::~ObjectPool() {
  if (object_arena_ != nullptr) {
    const size_t size = sizeof(Node);
    for(int i= 0; i < num_objects_; i++) {
      reinterpret_cast<Node *>(object_arena_ + i * size)->object.~T();
    }
    std::free(object_arena_);
  }
}

template <typename T>
void ObjectPool<T>::ReleaseObject(T *object) {
  if (object == nullptr) {
    return;
  }

  reinterpret_cast<Node *>(object)->next = free_head_;
  free_head_ = reinterpret_cast<Node *>(object);
}

template <typename T>
std::shared_ptr<T> ObjectPool<T>::GetObject() {
  if (free_head_ == nullptr) {
    return nullptr;
  }

  auto self = this->shared_from_this();
  auto obj =
      std::shared_ptr<T>(reinterpret_cast<T *>(free_head_),
                         [self](T *object) { self->ReleaseObject(object); 
                         });
  free_head_ = free_head_->next;
  return obj;
}

#endif /*__OBJECT_POOL_H__*/