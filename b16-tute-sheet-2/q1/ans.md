# Question 1

## Title: Patterns, Class design and the Standard Template Library  

**(a)** Using C++'s Standard Template Library vector class template, define the
private data and public interface of an Image class in which each pixel is a
single byte (in C++ this is an unsigned char).

Hint: the private data will need to store the image data itself and you could either use a vector of vectors of unsigned chars for this, or a single flat vector of unsigned chars; it will also need the height and width of the image; the interface will need methods to get and store pixel data, etc; the constructor should take the height and width as arguments and create the pixel data.

**Solution:**

1. What is Standard Template Library? [Reminder]
- The Standard Template Library (STL) is a library of generic classes and functions designed to be widely applicable and reusable. It is a part of the C++ Standard Library.

The code is written in q1.cpp.

2. How does resize() work?

- The resize() method has two parameters:
  1. width * height: New size of vector (total number of pixels)
  2. 0: Value to initialize new elements with (black pixels in this case)

3. What does it mean by 'real number per pixel'? 
In our q1, each pixel is a single byte (unsigned char), which is a integer between 0 and 255. 
```cpp
std::vector<unsigned char> pixels;
```

What we can also do is to use a vector of doubles to store the pixel values.
```cpp
class Image {
    // Current - efficient storage
    std::vector<unsigned char> pixels;  // 1 byte each
    
    // Real numbers - wasteful for most uses
    std::vector<double> pixels;  // 8 bytes each
    
    // Exception: Some specialized applications
    // - HDR imaging
    // - Scientific visualization
    // - Image processing intermediates
};
```

**(b)** How could you change your class so that it could store a real number per
pixel instead (i.e. double)?

Answered above. 

