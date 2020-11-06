#ifndef SMART_PTR_H
#define SMART_PTR_H
#include<stdexcept>
#include <string>

class null_ptr_excepton : public std::exception {
public:
	const char* what() const throw() {
		return "nullptr exception";
	}
};

template <typename T> 
class smart_ptr {
private:
	// pointer to the referred object 
	T* ptr_;

	// pointer to a reference count
	int* ref_;

public:     
	// Create a smart_ptr that is initialized to nullptr. The
	// reference count should be initialized to nullptr
	smart_ptr() noexcept;
	
	// Create a smart_ptr that is initialized to raw_ptr. The
	// reference count should be one.   
	explicit smart_ptr(T* raw_ptr) noexcept;

	// Copy construct a pointer from rhs. The reference count
	// should be incremented by one. 
	smart_ptr(const smart_ptr& rhs) noexcept;
		
	// Move construct a pointer from rhs.
	smart_ptr(smart_ptr&& rhs) noexcept;

	// This assignment should make a shallow copy of the
	// right-hand side's pointer data. The reference count  
	// should be incremented as appropriate. 	
	smart_ptr& operator=(const smart_ptr& rhs) noexcept;

	// This move assignment should steal the right-hand side's
	// pointer data.            
	smart_ptr& operator=(smart_ptr&& rhs) noexcept;

	// If the smart_ptr is either nullptr or has a reference
	// count of one, this function will do nothing and return
	// false. Otherwise, the referred to object's reference
	// count will be decreased and a new deep copy of the
	// object will be created. This new copy will be the  
	// object that this smart_ptr points and its reference
	// count will be one.
	bool clone();

	// Returns the reference count of the pointed to data. 
	int ref_count() const noexcept;

	// The dereference operator shall return a reference to
	// the referred object. Throws null_ptr_exception on 
	// invalid access.  
	T& operator*();

	// The arrow operator shall return the pointer ptr_. 
	// Throws null_ptr_exception on invalid access. 
	T* operator->();

	// deallocate all dynamic memory
	~smart_ptr() noexcept;                 
};

template <typename T>
smart_ptr<T>::smart_ptr() noexcept{
	ptr_ = nullptr;
	ref_ = nullptr;
}

template <typename T>
smart_ptr<T>::smart_ptr(T* raw_ptr) noexcept{
	ptr_ = raw_ptr;
	ref_ = new int(1);
}

//copy constructor
template <typename T>
smart_ptr<T>::smart_ptr(const smart_ptr& rhs) noexcept {
	ptr_ = rhs.ptr_;

	ref_ = rhs.ref_;
	if (rhs.ref_ != nullptr) {
		(*ref_)++;
	}
}

//move copy constructor
template <typename T>
smart_ptr<T>::smart_ptr(smart_ptr&& rhs) noexcept {
	ptr_ = rhs.ptr_;
	ref_ = rhs.ref_;

	rhs.ptr_ = nullptr;
	rhs.ref_ = nullptr;
}

//assignment operator
template <typename T>
smart_ptr<T>& smart_ptr<T>::operator=(const smart_ptr& rhs) noexcept {
	if (this == &rhs)
		return *this;

	if (ref_ != nullptr)
		(*ref_)--;

	ptr_ = rhs.ptr_;
	ref_ = rhs.ref_;

	if (ref_ != nullptr)
		(*ref_)++;

	return *this;
}

//move assignment operator
template <typename T>
smart_ptr<T>& smart_ptr<T>::operator=(smart_ptr&& rhs) noexcept {
	if (this == &rhs)
		return *this;

	ptr_ = rhs.ptr_;
	ref_ = rhs.ref_;

	rhs.ptr_ = nullptr;
	rhs.ref_ = nullptr;
	
	return *this;
}

template <typename T>
int smart_ptr<T>::ref_count() const noexcept{
	if (ref_ != nullptr)
		return *ref_;
	else
		return 0;
}

template <typename T>
bool smart_ptr<T>::clone() {
	T* tempPtr = nullptr;
	int *tempRef = nullptr;

	try {
		if (ptr_ == nullptr || *ref_ == 1)
			return false;

		tempPtr = new T(*ptr_);
		tempRef = new int(1);


		(*ref_)--;
		ref_ = tempRef;
		ptr_ = tempPtr;
		return true;
	}
	catch (std::bad_alloc &ba) {
		delete tempPtr;
		delete tempRef;

		throw ba;
	}
}

template <typename T>
T& smart_ptr<T>::operator*() {
	//if T cannot be dealocated, throw nullptr exception
	try {
		if (ptr_ != nullptr)
			return *ptr_;

		throw null_ptr_excepton();
	}
	catch (null_ptr_excepton &e) {
		throw null_ptr_excepton();
	}
}

template <typename T>
T* smart_ptr<T>::operator->() {
	//if T cannot be dealocated, throw nullptr exception
	try {
		if (ptr_ != nullptr)
			return ptr_;

		throw null_ptr_excepton();
	}
	catch (null_ptr_excepton &e) {
		throw null_ptr_excepton();
	}
}

template <typename T>
smart_ptr<T>::~smart_ptr() noexcept{
	if (ref_ != nullptr && ptr_ != nullptr) {
		//if there's only 1 smart_ptr associated to the object,
		//delete the object
		if (*ref_ == 1) {
			delete ptr_;
			delete ref_;
		}
		else {
			(*ref_)--;
		}
	}
}
#endif