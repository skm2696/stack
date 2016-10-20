#include "Stack.hpp"
#include <stdexcept>
#ifndef STACK_CPP
#define STACK_CPP
template <typename T1, typename T2>
void construct(T1 * ptr, T2 const & value)
{
	new(ptr) T1(value);
}

template <typename T>
void destroy(T * array) noexcept
{
	array->~T();
}

template <typename FwdIter>
void destroy(FwdIter first, FwdIter last) noexcept
{
	for (; first != last; ++first) 
	{
		destroy(&*first);
	}
}



template <typename T>
T* copy_with_new(const T * arr, size_t count, size_t array_size)
{
	T * stk = new T[array_size];
	try
	{
		std::copy(arr, arr + count, stk);
	}
	catch (...)
	{
		delete[] stk;
		throw;
	}
	return stk;
};
template <typename T>// конструктор аллокатора
allocator<T>::allocator(size_t size) : array_(static_cast<T *>(size == 0 ? nullptr : operator new(size * sizeof(T)))), array_size_(0), count_(size) {
};
template <typename T>//деструктор аллокатора
allocator<T>::~allocator() 
{
	operator delete(array_);
};
template <typename T>//swap allocator
void allocator<T>::swap(allocator& stk)
{
	std::swap(array_, stk.array_);
	std::swap(array_size_, stk.array_size_);
	std::swap(count_, stk.count_);
};

template <typename T>
stack<T>::stack()  
{
	destroy(allocator<T>::array_);
}
template <typename T>
size_t stack<T>::count() const noexcept
{
	return allocator<T>::count_;
}
template <typename T>
void stack<T>::push(T const &elem)
{

	if (allocator<T>::count_ == allocator<T>::array_size_)
	{
		size_t array_size = allocator<T>::array_size_*2+(allocator<T>::array_size_==0);
		T * stk = copy_with_new(allocator<T>::array_, allocator<T>::count_, array_size);
		delete[] allocator<T>::array_;
		allocator<T>::array_ = stk;
		allocator<T>::array_size_ = array_size;
	}
	construct(allocator<T>::array_ + allocator<T>::count_, elem);
	++allocator<T>::count_;

}
template <typename T>
void stack<T>::pop()
{
	if (allocator<T>::count_ == 0)
	{
		throw std::logic_error("Stack is empty!");
	}
	destroy(allocator<T>::array_ + allocator<T>::count_);
	--allocator<T>::count_;
}
template <typename T>
const T& stack<T>::top()
{
	if (allocator<T>::count_ == 0)
	{
		throw std::logic_error("Stack is empty!");
	}
	return allocator<T>::array_[allocator<T>::count_ - 1];
}
template <typename T>
stack<T>::~stack()
{}

template <typename T>
stack<T>::stack(const stack&tmp) 
{
	allocator<T>::count_ = tmp.count_;
	allocator<T>::array_size_ = tmp.array_size_;
	allocator<T>::array_=copy_with_new(tmp.array_, tmp.count_, tmp.array_size_); 
}
template <typename T>
stack<T>& stack<T>::operator=(const stack &obj)
{

	if (this != &obj)
	{
		T* stk = copy_with_new(obj.array_, obj.count_, obj.array_size_);
		delete[] allocator<T>::array_;
		allocator<T>::array_ = stk;
		allocator<T>::array_size_ = obj.array_size_;
		allocator<T>::count_ = obj.count_;
	}

	return *this;
}

template<typename T>
bool stack<T>::operator==(stack const & rhs)
{
	if ((rhs.count_ != allocator<T>::count_) || (rhs.array_size_ != allocator<T>::array_size_)) {
		return false;
	}
	else {
		for (size_t i = 0; i < allocator<T>::count_; i++) {
			if (rhs.array_[i] != allocator<T>::array_[i]) {
				return false;
			}
		}
	}
	return true;
}

#endif
