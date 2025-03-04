Write a function templtate that impelments a binary search of a sortef array of objects

Sketch how binary search works and describe th e alrgoithm
Wtriet a progran that calls your templated function with an array of objects of your choices
test the output of your program to verify your answr. 

Binary search is an efficient algorithm for finding an item from a sorted list of items. It works by repeatedly dividing the search interval in half. If the value of the search key is less than the item in the middle of the interval, narrow the interval to the lower half. Otherwise, narrow it to the upper half. Repeatedly check until the value is found or the interval is empty.

```cpp
template <class T>
int search(T a[], T key, int first, int last){
    while (first <=  last) {
        int mid = (first + last) / 2
        if (key < a[mid]) last = mid - 1;
        else if (key > a[mid]) first = mid + 1;
        else return mid; 
    }
}

class MyObject {
public:
    int value;

    MyObject(int v) : value(v) {}

    // Overload < operator for comparison
    bool operator<(const MyObject& other) const {
        return value < other.value;
    }

    // Overload == operator for comparison
    bool operator==(const MyObject& other) const {
        return value == other.value;
    }
};


```