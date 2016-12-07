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
allocator<T>::allocator(size_t size) : ptr_((T*)operator new(size*sizeof(T))), size_(size), map_(std::make_unique<bitset>(size)), count_(0) {}

template<typename T>
allocator<T>::allocator(allocator const& other) : allocator<T>(other.size_) {
	for (size_t i = 0; i < other.count_; i++) if(map_->test(i)) construct(ptr_ + i, other.ptr_[i]);
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
	allocator<T> al(size_ * 2 + (size_ == 0));
	for (size_t i = 0; i < size_; ++i) if (al.map_->test(i)) al.construct(al.get() + i, ptr_[i]);
	al.swap(*this);
}

template<typename T>
auto allocator<T>::construct(T * ptr, T const & value)->void{
	if (ptr >= ptr_&&ptr < ptr_ + size_){
		new(ptr)T(value);
		map_->set(ptr - ptr_);
		++count_;
	}
	else { throw("error"); }
}

template<typename T>
auto allocator<T>::destroy(T* ptr)->void{
	if (!map_->test(ptr - ptr_) && ptr >= ptr_&&ptr <= ptr_ + this->count())
	{
		ptr->~T();
		map_->reset(ptr - ptr_);
		--count_;
	}
}

template<typename T>
auto allocator<T>::get()-> T* { return ptr_; }

template<typename T>
auto allocator<T>::get() const -> T const * { return ptr_; }

template<typename T>
auto allocator<T>::count() const -> size_t{ return count_; }

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
	std::swap(count_, other.count_);
}

///////////////

template <typename T>
stack<T>::stack(size_t size) : allocate(size), mutex_() {};

template <typename T>
stack<T>::stack(stack const & tmp) : allocate(0), mutex_() 
{
	std::lock_guard<std::mutex> lock(tmp.mutex_);
	allocate.swap(allocator<T>(tmp.allocate));
}

template <typename T>
auto stack<T>::operator=(const stack &tmp)->stack&  
{
	if (this != &tmp) 
	{
		std::lock(mutex_, tmp.mutex_);
		std::lock_guard<std::mutex> lock1(mutex_, std::adopt_lock);
		std::lock_guard<std::mutex> lock2(tmp.mutex_, std::adopt_lock);
		(allocator<T>(tmp.allocate)).swap(allocate);
	}
	return *this;
}

template<typename T>
auto stack<T>::empty() const->bool 
{
	std::lock_guard<std::mutex> lock(mutex_);
	return (allocate.count() == 0);
}

template <typename T>
auto stack<T>::count() const ->size_t 
{
	std::lock_guard<std::mutex> lock(mutex_);
	return allocate.count();
}

template <typename T>
auto stack<T>::push(T const &val)->void 
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (allocate.full()) allocate.resize();
	allocate.construct(allocate.get() + allocate.count(), val);
}

template <typename T>
auto stack<T>::pop()->std::shared_ptr<T> 
{
	std::lock_guard<std::mutex> lock(mutex_);
			if(allocate.empty()) throw std::logic_error("Empty!"); 
				std::shared_ptr<T> const res(std::make_shared<T>(std::move(allocate.get()[allocate.count()-1])));//Make_shared than shared_ptr to directly construct high efficiency 
			allocate.destroy(allocate.get() + allocate.count() - 1);
			return res;
}
#endif // STACK_CPP
