#pragma once
#ifndef STACK_H

#define STACK_H

#include <iostream>


template <typename T>
class stack
{
public:
	stack();
	size_t count() const;
	void push(T const &);
	T pop();
	~stack();
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};
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
	/*if (count_ == 0)
	{
		array_ = new T[1];
		array_[count_] = elem;
		array_size_ = 1;
		count_++;
		return;
	}*/
	if (count_<=array_size_)
	{
		array_[count_] = elem;
		count_++;
		return;
	}

	if (count_ > array_size_)
	{
		
		T * stk = new T[array_size_*2];
		/*for (size_t i = 0; i < array_size_; i++)
				stk[i] = array_[i];
		delete[] array_;
		array_size_ = array_size_ * 2;
		array_ = new T[array_size_];
		for (size_t i = 0; i < count_; i++)
			array_[i] = stk[i];
		delete[] stk;
		array_[count_] = elem;
		count_++;*/
		//memcpy(stk, array_, array_size_*sizeof(T));
		for (size_t i = 0; i < array_size_; i++)
			stk[i] = array_[i];
		delete[] array_;
		array_size_ *= 2;
		// T * array_ = new T[array_size_];
		array_ = stk;
		stk = nullptr;
		array_[count_] = elem;
		count_++;
	}
	
	
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
#endif
