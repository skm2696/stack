#include "Stack.hpp"
#ifndef STACK_CPP
#define STACK_CPP
bitset::bitset(size_t size) : ptr_(std::make_unique<bool[]>(size)), size_(size), counter_(0){}

auto bitset::set(size_t index)->void {
	if (index >= 0 && index < size_) { ptr_[index] = true; ++counter_; }
	else throw("bad_index");
}

auto bitset::reset(size_t index)->void {
	if (index >= 0 && index < size_) { ptr_[index] = false; --counter_; }
	else throw("bad_index");
}

auto bitset::test(size_t index)->bool {
	if (index >= 0 && index < size_) return !ptr_[index];
	else throw("bad_index");
}

auto bitset::size()->size_t{ return size_; }

auto bitset::counter()->size_t{ return counter_; }

///////////////////////

template<typename T>
allocator<T>::allocator(size_t size) : ptr_((T*)operator new(size*sizeof(T))), size_(size), map_(std::make_unique<bitset>(size)) {}

template<typename T>
allocator<T>::allocator(allocator const& other) : allocator<T>(other.size_) {
	for (size_t i = 0; i < size_; i++) construct(ptr_ + i, other.ptr_[i]);
}

template<typename T>
allocator<T>::~allocator(){
	if (this->count() > 0) {
		destroy(ptr_, ptr_ + size_);
	}
	operator delete(ptr_);
}

template<typename T>
auto allocator<T>::resize()->void{
	allocator<T> al(size_ * 2 + (size_ == 0)); //std::cout << size_ << "!!!" << map_->counter()<<std::endl;
	for (size_t i = 0; i < size_; ++i) if (al.map_->test(i)) al.construct(al.get() + i, ptr_[i]);
	this->swap(al);
}

template<typename T>
auto allocator<T>::construct(T * ptr, T const & value)->void{
	if (ptr >= ptr_&&ptr < ptr_ + size_){
		new(ptr)T(value);
		map_->set(ptr - ptr_);
	}
	else { throw("error"); }
}

template<typename T>
auto allocator<T>::destroy(T* ptr)->void{
	if (!map_->test(ptr - ptr_) && ptr >= ptr_&&ptr <= ptr_ + this->count())
	{
		ptr->~T(); map_->reset(ptr - ptr_);
	}
}

template<typename T>
auto allocator<T>::get()-> T* { return ptr_; }

template<typename T>
auto allocator<T>::get() const -> T const * { return ptr_; }

template<typename T>
auto allocator<T>::count() const -> size_t{ return map_->counter(); }

template<typename T>
auto allocator<T>::full() const -> bool { return (map_->counter() == size_); }

template<typename T>
auto allocator<T>::empty() const -> bool { return (map_->counter() == 0); }

template<typename T>
auto allocator<T>::destroy(T * first, T * last)->void{
	if (first >= ptr_&&last <= ptr_ + this->count())
	for (; first != last; ++first) {
		destroy(&*first);
	}
}

template<typename T>
auto allocator<T>::swap(allocator & other)->void{
	std::swap(ptr_, other.ptr_);
	std::swap(size_, other.size_);
	std::swap(map_, other.map_);
}
///////////////

template<typename T>
stack<T>::stack(size_t size) : allocator_(size){}
////////////////////////////////B JIIO6ou HenoH9lTHou cuTyaLLuu 3axBaTblBau mutex.
template<typename T>
auto stack<T>::operator =(stack const & other)-> stack &{
	if (this != &other) {
		std::lock_guard<std::mutex> lk(m);
		(allocator<T>(other.allocator_)).swap(allocator_);
	}
	return *this;
}

template<typename T>
auto stack<T>::empty() const ->bool
{
	return allocator_.empty();
}

template<typename T>
auto stack<T>::count()const->size_t
{
	return allocator_.count();
}

template<typename T>
auto stack<T>::push(T const & value)->void{
	std::lock_guard<std::mutex> lk(m);
	if (allocator_.full()) allocator_.resize();
	allocator_.construct(allocator_.get() + this->count(), value);
}

template<typename T>
auto stack<T>::pop()->void{
	std::lock_guard<std::mutex> lk(m);
	if (this->count() > 0) allocator_.destroy(allocator_.get() + (this->count() - 1));
	else 
	{
		this->throw_is_empty();
	}
}

template<typename T>
auto stack<T>::top()->T& {
	std::lock_guard<std::mutex> lk(m);
	if (this->count() > 0)
	{
		return(*(allocator_.get() + this->count() - 1));
	}
	else
	{
		this->throw_is_empty();
	}
}

template<typename T>
auto stack<T>::top()const->T const & {
	if (this->count() > 0)
	{
		return(*(allocator_.get() + this->count() - 1));
	}
	else
	{
		this->throw_is_empty();
	}
}

template<typename T>
auto stack<T>::throw_is_empty()const->void{ throw("empty"); }
#endif // STACK_CPP
