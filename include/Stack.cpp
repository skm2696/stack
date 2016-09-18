
#include "Stack.hpp"
#ifndef STACK_CPP

#define STACK_CPP

template <typename T>
stack<T>::stack()
{
	count_ = 0;
	array_size_ = 1;
	array_ = new T[array_size_];
}
template <typename T>
size_t stack<T>::count() const
{
	return count_;
}
template <typename T>
void stack<T>::push(T const &elem)
{

	if (count_ == array_size_)
	{
		array_size_ *= 2;
		T * stk = copy_with_new(array_, count_, array_size_);
		delete[] array_;
		array_ = stk;
		stk = nullptr;
	}
	array_[count_] = elem;
	count_++;

}
/*template <typename T>
T stack<T>::pop()
{
	if (count_ <= 0)
	{
		throw std::logic_error("Stack is empty!");
	}
	return array_[--count_];

}*/
template <typename T>
void stack<T>::pop()
{
	if (count_ == 0)
	{
		throw std::logic_error("Stack is empty!");
	}
	 --count_;
}
template <typename T>
const T& stack<T>::top()
{
	return array_[count_];
}
template <typename T>
stack<T>::~stack()
{
	delete[] array_;
}

template <typename T>//конструктор копирования
stack<T>::stack(const stack&tmp) :count_(tmp.count_), array_size_(tmp.array_size_), array_(copy_with_new(tmp.array_, count_, array_size_ )) {};
template <typename T>
stack<T>& stack<T>::operator=(const stack &obj) 
{
	
	if (this != &obj)
	{
		delete[] array_;
	array_size_ = obj.array_size_;
	count_ = obj.count_;
	array_ = copy_with_new(obj.array_, count_, array_size_);
	}

	return *this;
}

template<typename T>
bool stack<T>::operator==(stack const & rhs) 
{
	if ((rhs.count_ != count_) || (rhs.array_size_ != array_size_)) {
		return false;
	}
	else {
		for (size_t i = 0; i < count_; i++) {
			if (rhs.array_[i] != array_[i]) {
				return false;
			}
		}
	}
	return true;
}

template <typename T>
T* stack<T>::copy_with_new(const T * arr, size_t count, size_t array_size)
{
	T * stk = new T[array_size];
	std::copy(arr, arr + count, stk);
	return stk;
}
#endif
