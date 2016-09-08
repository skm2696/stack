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
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};
template <typename T>
stack<T>::stack()
{
	array_ = new T[array_size_];
	count_ = 0;
}
template <typename T>
size_t stack<T>::count() const
{
	size_t count;
	return count = count_;
}
template <typename T>
void stack<T>::push(T const &elem)
{
	array_size_++;
	array_ = new T[array_size_];
	if (count_ < array_size_)
	{
		count_++;
		array_[count_] = elem;
	}
	//else
		//cout << "abc";
}
template <typename T>
T stack<T>::pop()
{
if (count_>0)
	return	array_[count_--];
}
#endif
