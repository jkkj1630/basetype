#include <stdlib.h>

#include "vbytes.h"
#include "vcrypto.h"

namespace  fcpp{

vbytes::vbytes()
{
    _data = nullptr;
    _size = 0;
}

vbytes::~vbytes()
{
    if(_data){
        free(_data);
        _data = nullptr;
    }
}

vbytes::vbytes(int size)
{
    _data = (vuchar*)malloc(size);
    // need zero?
    //memset(_data, 0, size);
    _size = size;
}

vbytes::vbytes(const vbytes&b)
{
    _data = (vuchar*)malloc(b.size());
    _size = b.size();
    memcpy(_data, b.data(), b.size());
}

bool vbytes::isNull()
{
    return _data == nullptr;
}

vbytes::vbytes(const vchar* src, int size)
{
    _data = (vuchar*)malloc(size);
    memcpy(_data, src, size);
    _size = size;
}


vchar*vbytes::addrByte(vint32 i)
{
    return &((vchar*)_data)[i];
}

const vchar*vbytes::addrByte(vint32 i) const
{
    return &((vchar*)_data)[i];
}

vptr vbytes::insert(vint32 offsetAddr, vint32 lenOfByte)
{
    resize(_size + lenOfByte);
    memmove(((vchar*)data() + offsetAddr + lenOfByte), ((vuchar*)data() + offsetAddr), _size - offsetAddr);
    return (vchar*)data() + offsetAddr;
}

vptr vbytes::insert(vint32 offsetAddr, vint32 lenOfByte, const vptr src)
{
    resize(_size + lenOfByte);
    memmove(((vchar*)data() + offsetAddr + lenOfByte), ((vuchar*)data() + offsetAddr), _size - offsetAddr);
    memcpy((vchar*)data() + offsetAddr, src, lenOfByte);
    return (vchar*)data() + offsetAddr;
}

vptr vbytes::append(vint32 lenOfByte)
{
    vint32 oldSize = _size;
    resize(_size + lenOfByte);
    return (vchar*)data() + oldSize;
}

vptr vbytes::append(vconst_ptr src, vint32 lenOfByte)
{
    vint32 oldSize = _size;
    resize(_size + lenOfByte);
    memcpy((vchar*)data() + oldSize, src, lenOfByte);
    return (vchar*)data() + oldSize;
}

vptr vbytes::append(const vbytes&b)
{
    vint32 oldSize = _size;
    resize(_size + b.size());
    memcpy((vchar*)data() + oldSize, b.data(), b.size());
    return (vchar*)data() + oldSize;
}

void vbytes::moveFrom(vbytes&b, const vint32 lenOfByte)
{
    append(b.sub(0, lenOfByte));
    b.remove(0, lenOfByte);
}

void vbytes::setZero()
{
    memset(_data, 0, _size);
}

void vbytes::remove(vint32 offsetAddr, vint32 lenOfByte)
{
    memmove(((vchar*)data() + offsetAddr), ((vuchar*)data() + offsetAddr + lenOfByte), _size - offsetAddr - lenOfByte);
    resize(_size - lenOfByte);
}

void vbytes::clear()
{
    if(_data){
        free(_data);
        _data = nullptr;
    }
    _size = 0;
}

vint32 vbytes::resize(vint32 size)
{
    if(size == _size)
    {
        return _size;
    }
    if(size)
    {
        _data = (vuchar*)realloc(_data, size);
        _size = size;
    }
    else
    {
        clear();
    }
    return  _size;
}

vuchar& vbytes::operator[](vint32 i)
{
    return (vuchar&)_data[i];
}

vbytes& vbytes::operator=(const vbytes&b)
{
    setBytes(b.data(), b.size());
    return *this;
}

vstr vbytes::toBase64()
{
    return vcrypto::Base64Encode(*this);
}

vstr vbytes::toHexStr()
{
    vstr strHex;
    for(int i = 0;i < _size;i++) {
        strHex += vstr::fromFormat("%02X", _data[i]);
    }
    return strHex;
}

vbytes& vbytes::operator+=(const vbytes&b)
{
    append(b);
    return *this;
}

}   //fcpp
