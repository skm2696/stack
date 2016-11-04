#include <iostream>
#include "Stack.hpp"
#include <stdexcept>
#ifndef STACK_CPP
#define STACK_CPP
auto bitset::size()-> size_t 
{
	return size_;
}
auto bitset::counter()-> size_t 
{
	return counter_;
}
bitset::bitset(size_t size) : ptr_(std::make_unique<bool[]>(size)), size_(size), counter_(0)
{}
auto bitset::test(size_t index) ->bool 
{
	if (index <= size()) 
	{
		return ptr_[index];
	}
	else 
	{
		throw std::out_of_range("Error");
	}
}
auto bitset::reset(size_t index)->void 
{
	if (test(index) != false) 
	{
		ptr_[index] = false;
		--counter_;
	}
}
auto bitset::set(size_t index)->void 
{
	if (test(index) != true) 
	{
		ptr_[index] = true;
		++counter_;
	}
}
template <typename T> 
allocator<T>::allocator(size_t size) : ptr_(static_cast<T *>(size == 0 ? nullptr : operator new(size * sizeof(T)))), size_(size), map_(std::make_unique<bitset>(size)) 
{};
template <typename T>
auto allocator<T>::construct(T * ptr, T const & value)->void 
{
	if (ptr < ptr_ || ptr >= ptr_ + size_)
	{
		throw std::out_of_range("Error");
	}
	new(ptr) T(value);
	map_->set(ptr - ptr_);
}
template <typename T>
auto allocator<T>::destroy(T * ptr)->void
{
	ptr->~T();
	map_->reset(ptr - ptr_);
}
template <typename T>
auto allocator<T>::destroy(T * first, T * last)->void
{
	for (; first != last; ++first) 
	{
		destroy(&*first);
	}
}
template<typename T> 
allocator<T>::allocator(allocator const & tmp) :allocator<T>(tmp.size_) 
{
	for (size_t i = 0; i < size_; ++i) 
	{
		construct(ptr_ + i, tmp.ptr_[i]);
	}
}
template <typename T>
allocator<T>::~allocator() 
{
	if (map_->counter() > 0) 
	{
		destroy(ptr_, ptr_ + map_->counter());
	}
	operator delete(ptr_);
};
template <typename T>
auto allocator<T>::swap(allocator & other)->void 
{
	std::swap(ptr_, other.ptr_);
	std::swap(size_, other.size_);
	std::swap(map_, other.map_);
};
template<typename T>
auto allocator<T>::resize()-> void 
{
	size_t size = size_ * 2 + (size_ == 0);
	allocator<T> buff(size);
	for (size_t i = 0; i < size_; ++i) 
	{
		if (map_->test(i))
		{
			buff.construct(buff.ptr_ + i, ptr_[i]);
		}
	}
	this->swap(buff);
	size_ = size;
}
template<typename T>
auto allocator<T>::empty() const -> bool 
{
	return (map_->counter() == 0);
}
template<typename T>
auto allocator<T>::full() const -> bool 
{
	return (map_->counter() == size_);
}
template<typename T>
auto allocator<T>::get() -> T * 
{
	return ptr_;
}
template<typename T>
auto allocator<T>::get() const -> T const * 
{
	return ptr_;
}
template<typename T>
auto allocator<T>::count() const -> size_t 
{
	return map_->counter();
}
template<typename T>
auto stack<T>::empty() const->bool 
{
	return (allocate.count() == 0);
}
template <typename T>
stack<T>::stack(size_t size) : allocate(size) 
{};
template <typename T>
auto stack<T>::push(T const &val)->void 
{
	if (allocate.full()) 
	{
		allocate.resize();
	}
	allocate.construct(allocate.get() + allocate.count(), val);
}
template <typename T>
auto stack<T>::operator=(const stack &tmp)->stack& 
{
	if (this != &tmp) 
	{
		stack(tmp).allocate.swap(allocate);
	}
	return *this;
}
template <typename T>
auto stack<T>::count() const->size_t 
{
	return allocate.count();
}
template <typename T>
auto stack<T>::pop()->void 
{
	if (allocate.count() == 0) throw std::logic_error("Empty!");
	allocate.destroy(allocate.get() + (this->count() - 1));
}
template <typename T>
auto stack<T>::top() const->const T&
{
	if (allocate.count() == 0) throw std::logic_error("Empty!");
	return(*(allocate.get() + this->count() - 1));

}
template <typename T>
auto stack<T>::top()->T& 
{
	if (allocate.count() == 0) throw std::logic_error("Empty!");
	return(*(allocate.get() + this->count() - 1));
}

#endif
