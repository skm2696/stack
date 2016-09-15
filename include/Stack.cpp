#include "stdafx.h"
#include "Stack.hpp"
#ifndef STACK_CPP

#define STACK_CPP

//#include <stdio>
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
		T * stk = new T[array_size_];
		for (size_t i = 0; i < count_; i++)
			stk[i] = array_[i];
		delete[] array_;

		array_ = stk;
		stk = nullptr;
	}
	array_[count_] = elem;
	count_++;

}
template <typename T>
T stack<T>::pop()
{
	if (count_ <= 0)
	{
		throw std::logic_error("Stack is empty!");
	}
	return array_[--count_];

}
template <typename T>
stack<T>::~stack()
{
	delete[] array_;
}
template <typename T>
stack<T>::stack(const stack & obj) : array_size_(obj.array_size_), count_(obj.count_)
{
	array_ = new T[array_size_];
	for (size_t i = 0; i < count_; i++)
		array_[i] = obj.array_[i];
}
template <typename T>
stack<T>& stack<T>::operator=(const stack &obj) 
{
	array_size_ = obj.array_size_;
	count_ = obj.count_;
	array_ = new T[array_size_];
	if (this != &obj)
	{
		for (size_t i = 0; i < count_; i++)
			array_[i] = obj.array_[i];
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
#endif
