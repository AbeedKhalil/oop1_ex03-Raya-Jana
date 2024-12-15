#ifndef IMAGE_H
#define IMAGE_H

#include "ImageDataStructure.h"
#include "imageDataStructure_extensions.h"
#include "Pixel.h"
#include <iostream>
using std::cout;
using std::ostream;

class Image {
private:
    ImageDataStructure ids;

public:
    Image() : ids(0, 0) {}
    Image(int h, int w, Pixel fill = Pixel::WHITE) : ids(h, w, fill) {}
    Image(const Image& other) : ids(other.ids) {}

    Image& operator=(const Image& other) {
        if (this != &other) {
            ids = other.ids;
        }
        return *this;
    }

    int GetHeight() const { return ids.GetHeight(); }
    int GetWidth() const { return ids.GetWidth(); }

    Pixel GetPixel(int row, int col) const {
        return ids.GetPixel(row, col);
    }

    void SetPixel(int row, int col, const Pixel& p) {
        ids.SetPixel(row, col, p);
    }

    bool operator==(const Image& other) const {
        if (GetHeight() != other.GetHeight() || GetWidth() != other.GetWidth())
            return false;
        for (int i = 0; i < GetHeight(); i++) {
            for (int j = 0; j < GetWidth(); j++) {
                if (GetPixel(i, j) != other.GetPixel(i, j))
                    return false;
            }
        }
        return true;
    }
    bool operator!=(const Image& other) const {
        return !(*this == other);
    }

    Image operator+(const Image& other) const {
        int newHeight = (GetHeight() > other.GetHeight()) ? GetHeight() : other.GetHeight();
        int newWidth = GetWidth() + other.GetWidth();
        Image result(newHeight, newWidth, Pixel::WHITE);

        for (int i = 0; i < GetHeight(); i++) {
            for (int j = 0; j < GetWidth(); j++) {
                result.SetPixel(i, j, GetPixel(i, j));
            }
        }

        for (int i = 0; i < other.GetHeight(); i++) {
            for (int j = 0; j < other.GetWidth(); j++) {
                result.SetPixel(i, j + GetWidth(), other.GetPixel(i, j));
            }
        }

        return result;
    }

    Image operator|(const Image& other) const {
        int newHeight = (GetHeight() > other.GetHeight()) ? GetHeight() : other.GetHeight();
        int newWidth = (GetWidth() > other.GetWidth()) ? GetWidth() : other.GetWidth();
        Image result(newHeight, newWidth, Pixel::WHITE);

        for (int i = 0; i < newHeight; i++) {
            for (int j = 0; j < newWidth; j++) {
                Pixel p1 = Pixel::WHITE;
                Pixel p2 = Pixel::WHITE;
                if (i < GetHeight() && j < GetWidth()) p1 = GetPixel(i, j);
                if (i < other.GetHeight() && j < other.GetWidth()) p2 = other.GetPixel(i, j);
                result.SetPixel(i, j, p1 | p2);
            }
        }
        return result;
    }

    Image operator&(const Image& other) const {
        int newHeight = (GetHeight() > other.GetHeight()) ? GetHeight() : other.GetHeight();
        int newWidth = (GetWidth() > other.GetWidth()) ? GetWidth() : other.GetWidth();
        Image result(newHeight, newWidth, Pixel::WHITE);

        for (int i = 0; i < newHeight; i++) {
            for (int j = 0; j < newWidth; j++) {
                Pixel p1 = Pixel::WHITE;
                Pixel p2 = Pixel::WHITE;
                if (i < GetHeight() && j < GetWidth()) p1 = GetPixel(i, j);
                if (i < other.GetHeight() && j < other.GetWidth()) p2 = other.GetPixel(i, j);
                result.SetPixel(i, j, p1 & p2);
            }
        }
        return result;
    }

    Image operator*(int n) const {
        if (n <= 0) {
            return Image();
        }
        Image result = *this;
        for (int i = 1; i < n; i++) {
            result = result + (*this);
        }
        return result;
    }

    Image operator~() const {
        Image result(GetHeight(), GetWidth());
        for (int i = 0; i < GetHeight(); i++) {
            for (int j = 0; j < GetWidth(); j++) {
                result.SetPixel(i, j, ~GetPixel(i, j));
            }
        }
        return result;
    }

    class RowProxy {
    private:
        Image& img;
        int row;
    public:
        RowProxy(Image& i, int r) : img(i), row(r) {}
        Pixel& operator[](int col) {
            static Pixel dummy;
            if (row < 0 || row >= img.GetHeight() || col < 0 || col >= img.GetWidth()) {
                dummy = Pixel::WHITE;
                return dummy;
            }
            return img.pixelRef(row, col);
        }
    };

    RowProxy operator[](int r) {
        return RowProxy(*this, r);
    }

    class ConstRowProxy {
    private:
        const Image& img;
        int row;
    public:
        ConstRowProxy(const Image& i, int r) : img(i), row(r) {}
        Pixel operator[](int col) const {
            if (row < 0 || row >= img.GetHeight() || col < 0 || col >= img.GetWidth()) {
                return Pixel::WHITE;
            }
            return img.GetPixel(row, col);
        }
    };

    ConstRowProxy operator[](int r) const {
        return ConstRowProxy(*this, r);
    }

private:
    Pixel& pixelRef(int row, int col) {
        return *getPixelAddress(row, col);
    }

    Pixel* getPixelAddress(int row, int col) {
        return &getRowPointer(ids, row)[col];
    }

public:
    friend ostream& operator<<(ostream& os, const Image& img) {
        for (int i = 0; i < img.GetHeight(); i++) {
            for (int j = 0; j < img.GetWidth(); j++) {
                os << img.GetPixel(i, j);
            }
            os << "\n";
        }
        return os;
    }
};

#endif
