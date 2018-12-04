#ifndef RULE_OF_FIVE_H
#define RULE_OF_FIVE_H

#include <iostream>
#include <memory>
#include <algorithm>
#include <cassert>
#include <iterator>

namespace MyArray
{

using std::cout;
using std::endl;

template <class T>
class MyArray {
private:
    T *ptr_;
    size_t size_;

    using index_type = size_t;

    //Destroy and deallocate
    void destructMyself();

    //For the move constructor and the assignment operator
    //Now takes lvalue ref, no need of std::move call in calling function
    void stealObject(MyArray& rhs);

public:
    MyArray(size_t size_0, T init_value = T{});

    MyArray(const MyArray& rhs);

    MyArray& operator = (const MyArray& rhs);

    MyArray(MyArray&& rhs);

    MyArray& operator = (MyArray&& rhs);

    T& operator[] (index_type index);

    const T& operator[] (index_type index) const;

    T* begin();

    T* end();

    const T* cbegin() const;

    const T* cend() const;

    ~MyArray();
};

template<class T>
MyArray<T> :: MyArray(size_t size_0, T init_value) : size_(size_0) {

    cout << "Constructor was called with size = " << size_
         << " and initial value = " << init_value << endl;

    ptr_ = static_cast<T*>(malloc(size_*sizeof(T)));

    std::fill(begin(), end(), init_value);
}

template<class T>
MyArray<T> :: MyArray(const MyArray& rhs) : size_(rhs.size_) {

    cout << "Copy constructor was called" << endl;

    ptr_ = static_cast<T*>(malloc(size_*sizeof(T)));

    std::copy(rhs.cbegin(), rhs.cend(), begin());
}

template<class T>
MyArray<T>& MyArray<T>::operator = (const MyArray& rhs){

    cout << "Copy assignment operator was called" << endl;

    if (this == &rhs)
        return *this;

    size_ = rhs.size_;

    ptr_ = static_cast<T*>(realloc(ptr_, size_));

    std::copy(rhs.cbegin(), rhs.cend(), begin());

    return *this;
}

template<class T>
MyArray<T> :: MyArray(MyArray&& rhs) {

    cout << "Move constructor was called" << endl;

    stealObject(rhs);
}

template<class T>
MyArray<T>& MyArray<T>::operator = (MyArray&& rhs) {

    cout << "Move assignment operator was called" << endl;

    assert(this != &rhs);

    destructMyself();

    stealObject(rhs);

    return *this;
}

template<class T>
T& MyArray<T>::operator[] (index_type index){
    assert(index < size_);
    return *(ptr_+index);
}

template<class T>
const T& MyArray<T>::operator[] (index_type index) const{
    assert(index < size_);
    return *(ptr_+index);
}

template<class T>
T* MyArray<T>::begin() {
    return ptr_;
}

template<class T>
T* MyArray<T>::end() {
    return ptr_ + size_;
}

template<class T>
const T* MyArray<T>::cbegin() const {
    return ptr_;
}

template<class T>
const T* MyArray<T>::cend() const {
    return ptr_ + size_;
}

template<class T>
MyArray<T>::~MyArray(){
    if (ptr_ != nullptr){
        destructMyself();
    }
}

template<class T>
void MyArray<T>::destructMyself(){
    std::destroy(begin(), end());
    free(ptr_);
}

template<class T>
void MyArray<T>::stealObject(MyArray& rhs){
    size_ = rhs.size_;
    ptr_ = rhs.ptr_;
    rhs.ptr_ = nullptr;
}

//Overloaded << operator for our container
template <class T>
std::ostream& operator << (std::ostream& stream, const MyArray<T>& arr){
    std::copy( arr.cbegin(), arr.cend(), std::ostream_iterator<T>(stream,"\n") );
    return stream;
}

}

#endif // RULE_OF_FIVE_H
