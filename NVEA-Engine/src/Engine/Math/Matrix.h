#ifndef SMatrix_header
#define SMatrix_header
#include "Vector.h"

template<typename T, unsigned char width, unsigned char height>
class SMatrix
{
    SVector<T, width> Element[height];
public:
    SMatrix()
    {
        int j = 0;
        for(int i = 0; i < height; ++i)
            Element[i][j++] = 1;
    }
    
    SVector<T, width>& operator[](int i) const
    {
        assert(i >= 0 && i < height);
        return Element[i];
    }
};

#endif
