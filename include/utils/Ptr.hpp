#ifndef PTR_H_
#define PTR_H_

#include<iostream>
template<typename T>
struct PtrDeleter{
  PtrDeleter() = default;
  PtrDeleter(PtrDeleter<T>&D)
  :D(std::move(D)) {}
  void operator()(T* ptr) const { delete ptr; }
};

template<typename T, typename Deleter = PtrDeleter<T>>
class Ptr{
private:
  T* m_ptr{nullptr};
  Deleter deleter = Deleter();
public:
  Ptr() = default;
  
  Ptr(T *otherptr)
    :m_ptr(otherptr) {}
  Ptr(T *otherptr, const Deleter &_Deleter)
    :m_ptr(otherptr), deleter(_deleter) {}

  template<typename U, typename D>
  Ptr(Ptr<U,D> &&other)
    :m_ptr(other.release()), deleter(std::forward<D>(other.getDeleter())) {}

  
  Ptr(Ptr &&other)
    :m_ptr(other.release()){}

  template<typename U, typename D>
  Ptr(Ptr<U,D> &other) = delete;
  Ptr(Ptr &other) = delete;

  ~Ptr(){
    deleter(m_ptr);
  }

  bool isNullPtr(){
    return m_ptr == nullptr;
  }

  template<typename U,typename D>
  T& operator=(Ptr<U,D>& otherptr) = delete;

  template<typename U,typename D>
  T&& operator=(Ptr<U,D>&& otherptr) = delete;

  
  T& operator=(Ptr &otherptr) = delete;
  T&& operator=(Ptr &&otherptr);
 

  T* release(T *ptr) noexcept {
    auto tptr = get();
    m_ptr = nullptr;
    return tptr;
  }

  DeleterPtr getDeleterer(){
    return Deleter;
  }

  void reset(T *ptr) noexcept {
    if(ptr != get()){
      if(get() != nullptr){
        deleter(get());
      }
    }
    m_ptr = ptr;
  }

  void swap(Ptr &otherptr) noexcept {
    auto temp1 = std::move(m_ptr);
    auto temp2 = std::move(otherptr.m_ptr);
    m_ptr = temp1;
    otherptr.m_ptr = temp1;
  }


  T* operator->() const noexcept {
    return m_ptr;
  }

  T& operator*() const noexcept {
    return *m_ptr;
  }

  T* get() const noexcept { return m_ptr;}

};
#endif