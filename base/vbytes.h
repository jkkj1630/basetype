#ifndef VBYTES_H
#define VBYTES_H

#include <string.h>

#include "vtypes.h"
#include "vstring.h"

namespace  fcpp{

class vstr;

class vbytes
{
public:
    vbytes();
    vbytes(int size);
    vbytes(const vbytes&b);
    vbytes(const vchar* data, int size);

    ~vbytes();

    vbytes& operator=(const vbytes&b);
    vbytes& operator+=(const vbytes&b);
    vuchar& operator[](vint32 i);

    inline vptr data()
    {
        return _data;
    }

    inline const vptr data() const
    {
        return _data;
    }

    inline void setBytes(const void*src, int size)
    {
        resize(size);
        memcpy(_data, src, size);
    }

    vint32 resize(vint32 size);

    vptr insert(vint32 startAddr, vint32 lenOfByte);
    vptr insert(vint32 startAddr, vint32 lenOfByte, const vptr src);

    vptr append(vint32 lenOfByte);
    vptr append(vconst_ptr src, vint32 lenOfByte);
    vptr append(const vbytes&b);

    vstring toBase64();
    vstring toHexStr();

    void moveFrom(vbytes&b, const vint32 lenOfByte);

    inline vbytes sub(vint32 startAddr, vint32 lenOfByte) const
    {
        return vbytes(addrByte(startAddr), lenOfByte);
    }

    void remove(vint32 startAddr, vint32 lenOfByte);

    void setZero();

    inline vint32 size() const
    {
        return _size;
    }

    vchar*addrByte(vint32 i);

    const vchar*addrByte(vint32 i) const;

    bool isNull();

    void clear();

private:

    vuchar* _data;

    vint32 _size;
};

}
#endif // VBYTES_H
