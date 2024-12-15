#include "Image.h"
#include "Pixel.h"
#include <iostream>

int main() {
    // Create a small image with Gray pixels
    Image img1(3, 3, Pixel::GRAY);
    // Set one pixel to BLACK
    img1.SetPixel(1, 1, Pixel(Pixel::BLACK));

    // Create another image (5x4, all WHITE)
    Image img2(5, 4, Pixel::WHITE);
    img2.SetPixel(0, 0, Pixel(Pixel::BLACK));
    img2.SetPixel(4, 3, Pixel(Pixel::BLACK));

    // Print img1
    std::cout << "Image 1:\n" << img1 << std::endl;

    // Print img2
    std::cout << "Image 2:\n" << img2 << std::endl;

    // Combine images horizontally
    Image combined = img1 + img2;
    std::cout << "Combined (img1 + img2):\n" << combined << std::endl;

    // Union
    Image uni = img1 | img2;
    std::cout << "Union (img1 | img2):\n" << uni << std::endl;

    // Intersection
    Image inter = img1 & img2;
    std::cout << "Intersection (img1 & img2):\n" << inter << std::endl;

    // Negation
    Image neg = ~img1;
    std::cout << "Negation (~img1):\n" << neg << std::endl;

    // Scalar multiplication
    Image triple = img1 * 3;
    std::cout << "Triple (img1 * 3):\n" << triple << std::endl;

    // Modify a pixel using subscript operators
    triple[0][0] = Pixel(Pixel::BLACK);
    std::cout << "After triple[0][0] = BLACK:\n" << triple << std::endl;

    return 0;
}
