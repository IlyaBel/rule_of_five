#include <iostream>
#include <memory>
#include <algorithm>
#include <cassert>

using std::cout;
using std::endl;

template <class T>
class MyArray{
private:
    T *ptr;
    size_t size;

    using index_type = size_t;

    //Destroy and deallocate
    void destructMyself(){
        std::destroy(begin(), end());
        free(ptr);
    }

    //For the move constructor and the assignment operator
    void stealObject(MyArray&& rhs){
        size = rhs.size;
        ptr = rhs.ptr;
        rhs.ptr = nullptr;
    }

public:
    MyArray(size_t size_0, T init_value = T{}) : size(size_0) {

        cout << "Constructor was called with size = " << size
             << " and initial value = " << init_value << endl;

        ptr = static_cast<T*>(malloc(size*sizeof(T)));

        std::fill(begin(), end(), init_value);
    }

    MyArray(const MyArray& rhs) : size(rhs.size) {

        cout << "Copy constructor was called" << endl;

        ptr = static_cast<T*>(malloc(size*sizeof(T)));

        std::copy(rhs.begin(), rhs.end(), begin());
    }

    MyArray& operator = (const MyArray& rhs){

        cout << "Copy assignment operator was called" << endl;

        assert(this != &rhs);

        size = rhs.size;

        ptr = static_cast<T*>(realloc(ptr, size));

        std::copy(rhs.begin(), rhs.end(), begin());

        return *this;
    }

    MyArray(MyArray&& rhs) {

        cout << "Move constructor was called" << endl;

        stealObject(std::move(rhs));
    }

    MyArray& operator = (MyArray&& rhs) {

        cout << "Move assignment operator was called" << endl;

        assert(this != &rhs);

        destructMyself();

        stealObject(std::move(rhs));

        return *this;
    }

    T& operator[] (index_type index){
        return *(ptr+index);
    }

    const T& operator[] (index_type index) const{
        return *(ptr+index);
    }

    T* begin() const{
        return ptr;
    }

    T* end() const{
        return ptr+size;
    }


    ~MyArray(){
        if (ptr != nullptr){
            destructMyself();
        }
    }
};

template <class T>
std::ostream& operator << (std::ostream& stream, const MyArray<T>& arr){

    std::for_each(arr.begin(), arr.end(), [&stream](const auto& elt){stream << elt << endl;});

    return stream;
}

using IntegerArray = MyArray<int>;

int main()
{
    //Usual constructor
    IntegerArray arr1(5);

    //Copy constructor
    auto arr2{arr1};

    //Copy assignment operator
    arr1 = arr2;

    //Move constructor?????
    auto arr3 { IntegerArray(10, 100) };

    //Move assignment operator
    arr3 = IntegerArray(10, 100);

    return 0;
}
