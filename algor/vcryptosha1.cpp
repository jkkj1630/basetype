#include <stdlib.h>
#include <string.h>

#include "vendian.h"
#include "vcryptosha1.h"

namespace  fcpp{

vcryptosha1::vcryptosha1()
{
    _h[0] = 0x67452301;
    _h[1] = 0xEFCDAB89;
    _h[2] = 0x98BADCFE;
    _h[3] = 0x10325476;
    _h[4] = 0xC3D2E1F0;

    _msgSz = 0;
}

vcryptosha1::~vcryptosha1()
{
}

vbytes vcryptosha1::compute()
{
    vuint64 bigSize = endianLittleToBig64(_msgSz << 3);
    vuchar bigSizBt[8];
    memcpy(bigSizBt, &bigSize, 8);
    appendData(static_cast<vconst_ptr>("\200"), 1);

    if(_encodeBuffer.size() > 55) {
        vbytes tmpBuf;
        tmpBuf.resize(64 - _encodeBuffer.size());
        tmpBuf.setZero();
        appendData(tmpBuf);
        tmpBuf.resize(64 - 8);
        tmpBuf.setZero();
        appendData(tmpBuf);
    }
    else {
        vbytes tmpBuf;
        tmpBuf.resize(64 - _encodeBuffer.size() - 8);
        tmpBuf.setZero();
        appendData(tmpBuf);
    }
    appendData(&bigSize, 8);

    vbytes hash(20);
    *reinterpret_cast<int*>(hash.addrByte(0)) = endianLittleToBig32(_h[0]);
    *reinterpret_cast<int*>(hash.addrByte(4)) = endianLittleToBig32(_h[1]);
    *reinterpret_cast<int*>(hash.addrByte(8)) = endianLittleToBig32(_h[2]);
    *reinterpret_cast<int*>(hash.addrByte(12)) = endianLittleToBig32(_h[3]);
    *reinterpret_cast<int*>(hash.addrByte(16)) = endianLittleToBig32(_h[4]);
    return hash;
}

void vcryptosha1::appendData(const vbytes&b)
{
    vint32 oldSz = _encodeBuffer.size();
    vint32 newSz = _encodeBuffer.size() + b.size();
    _msgSz += b.size();
    if(newSz < 64) {
        _encodeBuffer.append(b);
    }
    else {
        _encodeBuffer.append(b.sub(0, 64 - oldSz));
        chunk();
        vint32 curData = (64 - oldSz);
        vint32 remainingLen = b.size() - curData;
        while (remainingLen > 64) {
            _encodeBuffer = b.sub(curData, 64);
            chunk();
            curData += 64;
            remainingLen -= 64;
        }
        _encodeBuffer = b.sub(curData, remainingLen);
    }
}

void vcryptosha1::appendData(vconst_ptr data, const vint32 len)
{
    appendData(vbytes(static_cast<vconst_char_ptr>(data), len));
}

void vcryptosha1::chunk()
{

    vuint32 h1 = _h[0];
    vuint32 h2 = _h[1];
    vuint32 h3 = _h[2];
    vuint32 h4 = _h[3];
    vuint32 h5 = _h[4];

    vuint32*chunk = static_cast<vuint32*>(_encodeBuffer.data());
    for(vint32 i = 0;i < 16;i++) {
        (static_cast<vuint32*>(_encodeBuffer.data())[i]) = endianBigToLittle32((static_cast<vuint32*>(_encodeBuffer.data()))[i]);
    }
    round0(chunk,  0, h1,h2,h3,h4,h5); round0(chunk,  1, h5,h1,h2,h3,h4); round0(chunk,  2, h4,h5,h1,h2,h3); round0(chunk,  3, h3,h4,h5,h1,h2);
    round0(chunk,  4, h2,h3,h4,h5,h1); round0(chunk,  5, h1,h2,h3,h4,h5); round0(chunk,  6, h5,h1,h2,h3,h4); round0(chunk,  7, h4,h5,h1,h2,h3);
    round0(chunk,  8, h3,h4,h5,h1,h2); round0(chunk,  9, h2,h3,h4,h5,h1); round0(chunk, 10, h1,h2,h3,h4,h5); round0(chunk, 11, h5,h1,h2,h3,h4);
    round0(chunk, 12, h4,h5,h1,h2,h3); round0(chunk, 13, h3,h4,h5,h1,h2); round0(chunk, 14, h2,h3,h4,h5,h1); round0(chunk, 15, h1,h2,h3,h4,h5);
    round1(chunk, 16, h5,h1,h2,h3,h4); round1(chunk, 17, h4,h5,h1,h2,h3); round1(chunk, 18, h3,h4,h5,h1,h2); round1(chunk, 19, h2,h3,h4,h5,h1);
    round2(chunk, 20, h1,h2,h3,h4,h5); round2(chunk, 21, h5,h1,h2,h3,h4); round2(chunk, 22, h4,h5,h1,h2,h3); round2(chunk, 23, h3,h4,h5,h1,h2);
    round2(chunk, 24, h2,h3,h4,h5,h1); round2(chunk, 25, h1,h2,h3,h4,h5); round2(chunk, 26, h5,h1,h2,h3,h4); round2(chunk, 27, h4,h5,h1,h2,h3);
    round2(chunk, 28, h3,h4,h5,h1,h2); round2(chunk, 29, h2,h3,h4,h5,h1); round2(chunk, 30, h1,h2,h3,h4,h5); round2(chunk, 31, h5,h1,h2,h3,h4);
    round2(chunk, 32, h4,h5,h1,h2,h3); round2(chunk, 33, h3,h4,h5,h1,h2); round2(chunk, 34, h2,h3,h4,h5,h1); round2(chunk, 35, h1,h2,h3,h4,h5);
    round2(chunk, 36, h5,h1,h2,h3,h4); round2(chunk, 37, h4,h5,h1,h2,h3); round2(chunk, 38, h3,h4,h5,h1,h2); round2(chunk, 39, h2,h3,h4,h5,h1);
    round3(chunk, 40, h1,h2,h3,h4,h5); round3(chunk, 41, h5,h1,h2,h3,h4); round3(chunk, 42, h4,h5,h1,h2,h3); round3(chunk, 43, h3,h4,h5,h1,h2);
    round3(chunk, 44, h2,h3,h4,h5,h1); round3(chunk, 45, h1,h2,h3,h4,h5); round3(chunk, 46, h5,h1,h2,h3,h4); round3(chunk, 47, h4,h5,h1,h2,h3);
    round3(chunk, 48, h3,h4,h5,h1,h2); round3(chunk, 49, h2,h3,h4,h5,h1); round3(chunk, 50, h1,h2,h3,h4,h5); round3(chunk, 51, h5,h1,h2,h3,h4);
    round3(chunk, 52, h4,h5,h1,h2,h3); round3(chunk, 53, h3,h4,h5,h1,h2); round3(chunk, 54, h2,h3,h4,h5,h1); round3(chunk, 55, h1,h2,h3,h4,h5);
    round3(chunk, 56, h5,h1,h2,h3,h4); round3(chunk, 57, h4,h5,h1,h2,h3); round3(chunk, 58, h3,h4,h5,h1,h2); round3(chunk, 59, h2,h3,h4,h5,h1);
    round4(chunk, 60, h1,h2,h3,h4,h5); round4(chunk, 61, h5,h1,h2,h3,h4); round4(chunk, 62, h4,h5,h1,h2,h3); round4(chunk, 63, h3,h4,h5,h1,h2);
    round4(chunk, 64, h2,h3,h4,h5,h1); round4(chunk, 65, h1,h2,h3,h4,h5); round4(chunk, 66, h5,h1,h2,h3,h4); round4(chunk, 67, h4,h5,h1,h2,h3);
    round4(chunk, 68, h3,h4,h5,h1,h2); round4(chunk, 69, h2,h3,h4,h5,h1); round4(chunk, 70, h1,h2,h3,h4,h5); round4(chunk, 71, h5,h1,h2,h3,h4);
    round4(chunk, 72, h4,h5,h1,h2,h3); round4(chunk, 73, h3,h4,h5,h1,h2); round4(chunk, 74, h2,h3,h4,h5,h1); round4(chunk, 75, h1,h2,h3,h4,h5);
    round4(chunk, 76, h5,h1,h2,h3,h4); round4(chunk, 77, h4,h5,h1,h2,h3); round4(chunk, 78, h3,h4,h5,h1,h2); round4(chunk, 79, h2,h3,h4,h5,h1);

    _h[0] += h1;
    _h[1] += h2;
    _h[2] += h3;
    _h[3] += h4;
    _h[4] += h5;
}

inline vuint32 vcryptosha1::vrtol(vuint32 val, vuint32 shift)
{
    return ((val << shift) | (val >> (32 - shift)));
}

inline vuint32 vcryptosha1::sha1Word(vuint32 *chunk, const vuint32 position)
{
    return (chunk[position & 0xf] = vrtol(  chunk[(position+13) & 0xf]
                                                 ^ chunk[(position+ 8) & 0xf]
                                                 ^ chunk[(position+ 2) & 0xf]
                                                 ^ chunk[(position)    & 0xf], 1));
}

inline void vcryptosha1::round0(vuint32 *chunk, const vuint32 position,
                              vuint32 &v, vuint32 &w, vuint32 &x, vuint32 &y, vuint32 &z)
{
    z += ((( w & (x ^ y)) ^ y) + chunk[position] + 0x5A827999 + vrtol(v, 5));
    w = vrtol(w, 30);
}

inline void vcryptosha1::round1(vuint32 *chunk, const vuint32 position,
                              vuint32 &v, vuint32 &w, vuint32 &x, vuint32 &y, vuint32 &z)
{
    z += ((( w & (x ^ y)) ^ y) + sha1Word(chunk,position) + 0x5A827999 + vrtol(v, 5));
    w = vrtol(w, 30);
}

inline void vcryptosha1::round2(vuint32 *chunk, const vuint32 position,
                              vuint32 &v, vuint32 &w, vuint32 &x, vuint32 &y, vuint32 &z)
{
    z += (( w ^ x ^ y) + sha1Word(chunk, position) + 0x6ED9EBA1 + vrtol(v, 5));
    w = vrtol(w, 30);
}

inline void vcryptosha1::round3(vuint32 *chunk, const vuint32 position,
                              vuint32 &v, vuint32 &w, vuint32 &x, vuint32 &y, vuint32 &z)
{
    z += (((( w | x) & y) | (w & x)) + sha1Word(chunk, position) + 0x8F1BBCDC + vrtol(v, 5));
    w = vrtol(w, 30);
}

inline void vcryptosha1::round4(vuint32 *chunk, const vuint32 position,
                              vuint32 &v, vuint32 &w, vuint32 &x, vuint32 &y, vuint32 &z)
{
    z += ((w ^ x ^ y) + sha1Word(chunk, position) + 0xCA62C1D6 + vrtol(v, 5));
    w = vrtol(w, 30);
}


}   //fcpp
