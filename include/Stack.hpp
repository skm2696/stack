#pragma once
#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
using namespace std;
template <typename T>
T* copy_with_new(const T * arr, size_t count, size_t array_size);
template <typename T>
class stack
{
public:
	stack();/*noexcept*/
	size_t count() const noexcept;/*noexcept*/
	void push(T const &);/*strong*/
	void pop();/*strong*/
	const T& top();/*strong*/
	~stack();/*noexcept*/
	stack(const stack & tmp);/*strong*/
	stack & operator=(const stack &obj);/*strong*/
	bool operator==(stack const & rhs);/*noexcept*/
private:
	size_t array_size_;
	size_t count_;
	T * array_;
};
#include "Stack.cpp"
#endif
