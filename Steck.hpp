#pragma once
#ifndef STACK_HPP
#define STACK_HPP
#include <cstdlib>
#include <iostream>
#include <memory>
using namespace std;

template <typename T>
class stack
{
public:
	stack();
	size_t count() const;
	void push(T const &);
	T pop();
	~stack();
	stack(const stack & obj);
	stack & operator=(const stack &obj);
	void swap(stack & obj);
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};
#include "Stack.cpp"
#endif
