#ifndef IMAGEDATASTRUCTURE_EXTENSIONS_H
#define IMAGEDATASTRUCTURE_EXTENSIONS_H

#include "ImageDataStructure.h"

// Provides direct access to a row pointer
inline Pixel* getRowPointer(ImageDataStructure& ids, int row) {
    return ids.GetRowPointer(row);
}

#endif
