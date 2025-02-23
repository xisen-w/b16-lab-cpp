#include <vector> // for vector class template
#include <stdexcept> // for out_of_range exception

class Image {

// In essence, we have a list of pixels (or 2D array of pixels
// We need to know the width and height so that we constuct a picture and store them with 0s.
// For each pixel we nable the indexing so that we can both set and enquire. 
private:
    // Single vector with width*height elements
    std::vector<unsigned char> pixels;
    
    int width;
    int height;

public:
    // Constructor - initializes image with given dimensions
    Image(int w, int h) : width(w), height(h) {
        // Initialize single vector
        pixels.resize(width * height, 0);  // Initialize all pixels to 0 (black)
        
    }
    
    // Get pixel value at (x,y)
    unsigned char getPixel(int x, int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("Pixel coordinates out of bounds");
        }
        // Calculate index in single vector
        return pixels[y * width + x];
    }
    
    // Set pixel value at (x,y)
    void setPixel(int x, int y, unsigned char value) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("Pixel coordinates out of bounds");
        }
        // Calculate index in single vector
        pixels[y * width + x] = value;
    }
    
    // Get image dimensions
    int getWidth() const { return width; }
    int getHeight() const { return height; }
}; 

// Note, there's another method.
// We can use a vector of vectors to store the pixel values.
// std::vector<std::vector<unsigned char>> pixels;
// Option 2: Initialize vector of vectors
// pixels.resize(height, std::vector<unsigned char>(width, 0)); -> Note not to put as only 0 here. 
// Option 2: Use vector of vectors
// return pixels[y][x];