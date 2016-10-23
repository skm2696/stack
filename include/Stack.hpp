#pragma once
#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
template<typename T>
class allocator
{
protected:
	allocator(size_t size = 0);
	~allocator();
	void swap(allocator& stk);
	allocator(allocator const&) = delete;
	allocator& operator=(allocator const&) = delete;

	T * array_;
	size_t array_size_;
	size_t count_;
};
template <typename T>
class stack : private allocator<T>
{
public:
	stack(size_t size=0);
	~stack();
	stack(const stack & obj);
	size_t count() const noexcept;
	void push(T const &);
	size_t pop();
	const T& top();
	stack & operator=(const stack &obj);
	bool operator==(stack const & rhs);
	bool empty() noexcept;

};
#include "Stack.cpp"
#endif
