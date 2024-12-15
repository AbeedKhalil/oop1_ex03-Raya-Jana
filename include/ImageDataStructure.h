#ifndef IMAGEDATASTRUCTURE_H
#define IMAGEDATASTRUCTURE_H

#include "Pixel.h"

class Image; // Forward declaration

class ImageDataStructure {
private:
    Pixel** data;
    int height;
    int width;

    void allocateData() {
        if (height > 0 && width > 0) {
            data = new Pixel * [height];
            for (int i = 0; i < height; i++) {
                data[i] = new Pixel[width];
            }
        }
        else {
            data = nullptr;
        }
    }

    void freeData() {
        if (data) {
            for (int i = 0; i < height; i++) {
                delete[] data[i];
            }
            delete[] data;
            data = nullptr;
        }
    }

public:
    ImageDataStructure(int h = 0, int w = 0, Pixel fill = Pixel::WHITE)
        : data(nullptr), height(h), width(w)
    {
        allocateData();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                data[i][j] = fill;
            }
        }
    }

    ImageDataStructure(const ImageDataStructure& other)
        : data(nullptr), height(other.height), width(other.width) {
        allocateData();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    ImageDataStructure& operator=(const ImageDataStructure& other) {
        if (this != &other) {
            freeData();
            height = other.height;
            width = other.width;
            allocateData();
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }

    ~ImageDataStructure() {
        freeData();
    }

    Pixel GetPixel(int row, int col) const {
        return data[row][col];
    }

    void SetPixel(int row, int col, const Pixel& p) {
        data[row][col] = p;
    }

    int GetHeight() const { return height; }
    int GetWidth() const { return width; }

    void Resize(int newHeight, int newWidth, Pixel fill = Pixel::WHITE) {
        Pixel** newData = nullptr;
        if (newHeight > 0 && newWidth > 0) {
            newData = new Pixel * [newHeight];
            for (int i = 0; i < newHeight; i++) {
                newData[i] = new Pixel[newWidth];
            }
            for (int i = 0; i < newHeight; i++) {
                for (int j = 0; j < newWidth; j++) {
                    newData[i][j] = fill;
                }
            }
            int copyH = (newHeight < height) ? newHeight : height;
            int copyW = (newWidth < width) ? newWidth : width;
            for (int i = 0; i < copyH; i++) {
                for (int j = 0; j < copyW; j++) {
                    newData[i][j] = data[i][j];
                }
            }
        }

        freeData();
        data = newData;
        height = newHeight;
        width = newWidth;
    }

    Pixel* GetRowPointer(int row) const {
        return data[row];
    }
};

#endif
