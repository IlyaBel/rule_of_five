#include "rule_of_five.h"

using namespace MyArray;

using std::cout;
using std::endl;

using IntegerArray = MyArray<int>;

int main()
{
    //Usual constructor
    IntegerArray arr1(5);

    //Copy constructor
    auto arr2{arr1};

    //Copy assignment operator
    arr1 = arr2;

    //Usual constructor! Our compiler is smart enough!
    auto arr3 { IntegerArray(10, 100) };

    //Move constructor
    auto arr4 { std::move(IntegerArray(10, 100)) };

    //Move assignment operator
    arr4 = IntegerArray(10, 100);

    return 0;
}
