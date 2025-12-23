 #pragma once

#include <exception>
#include <iostream>
#include <utility>

using std::forward;
using std::move;
using std::underflow_error;

namespace bmstu
{
template <typename T>
class stack
{
   public:
  stack() = default;
  ~stack() { clear(); }

  bool empty() const noexcept { return size_ == 0; }

  size_t size() const noexcept { return size_; }

  template <typename... Args>
                 void emplace(Args&&... args)
  {
    T* new_data = get_new();
    new (&new_data[size_]) T(forward<Args>(
      args)...);
    operator delete(data_);
    data_ = new_data;
    size_++;
  }

  void clear() noexcept
  {
    for (size_t i = 0; i < size_; ++i)

    {
      T* ptr = &data_[i];
      ptr->~T();
    }
    operator delete(data_);
    data_ = nullptr;
    size_ = 0;
  }

  void push(const T& value)
  {
    emplace(value);
  } 

  void push(T&& value)
  {
    emplace(move(value));
  }

  void pop()
  {
    if (empty())
    {
      throw underflow_error(
        "Stack is empty");
    }
    data_[size_ - 1].~T();
    --size_;
  }

  T& top()
  {
    if (empty())
    {
      throw underflow_error(
        "Stack is empty");
    }
    else
    {
      return data_[size_ - 1];
    }
  }

  const T& top() const
  {
    if (empty())
    {
      throw underflow_error(
        "Stack is empty");
    }
    else
    {
      return data_[size_ - 1];
    }
  }

   private:
  T* data_ = nullptr;
  size_t size_ = 0;

  T* get_new()
  {
    T* new_data = static_cast<T*>(operator new(
      sizeof(T) *
      (size_ + 1)));
    for (size_t i = 0; i < size_; i++)
    {
      new (&new_data[i]) T(
        move(data_[i]));
      data_[i].~T();
    }
    return new_data;
  }
};
}  // namespace bmstu