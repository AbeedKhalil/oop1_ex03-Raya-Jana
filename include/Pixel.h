#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>
using std::ostream;

class Pixel {
private:
    char value;

public:
    static const char BLACK = (char)219;
    static const char GRAY = (char)176;
    static const char WHITE = ' ';

    Pixel(char c = WHITE) : value(c) {}

    bool operator==(const Pixel& other) const {
        return value == other.value;
    }
    bool operator!=(const Pixel& other) const {
        return !(*this == other);
    }

    static int darknessLevel(char c) {
        if (c == BLACK) return 3;
        if (c == GRAY)  return 2;
        return 1; // WHITE
    }

    Pixel operator|(const Pixel& other) const {
        return (darknessLevel(value) >= darknessLevel(other.value)) ? *this : other;
    }
    Pixel& operator|=(const Pixel& other) {
        *this = *this | other;
        return *this;
    }

    Pixel operator&(const Pixel& other) const {
        return (darknessLevel(value) <= darknessLevel(other.value)) ? *this : other;
    }
    Pixel& operator&=(const Pixel& other) {
        *this = *this & other;
        return *this;
    }

    Pixel operator~() const {
        if (value == BLACK) return Pixel(WHITE);
        if (value == WHITE) return Pixel(BLACK);
        return Pixel(GRAY);
    }

    friend ostream& operator<<(ostream& os, const Pixel& p) {
        os << p.value;
        return os;
    }

    char getChar() const { return value; }
};

#endif
