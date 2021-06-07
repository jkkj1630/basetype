#ifndef VCRYPTOSHA1_H
#define VCRYPTOSHA1_H

#include "vcrypto.h"

namespace  fcpp{

class vcryptosha1 : public vcrypto
{
public:
    vcryptosha1();

    virtual ~vcryptosha1();

    vbytes compute();

    void appendData(const vbytes&);
    void appendData(const vptr data, vint32 len);

private:

    inline void round0(vuint32 *chunk, const uint position, vuint32 &v, vuint32 &w, vuint32 &x, vuint32 &y, vuint32 &z);
    inline void round1(vuint32 *chunk, const uint position, vuint32 &v, vuint32 &w, vuint32 &x, vuint32 &y, vuint32 &z);
    inline void round2(vuint32 *chunk, const uint position, vuint32 &v, vuint32 &w, vuint32 &x, vuint32 &y, vuint32 &z);
    inline void round3(vuint32 *chunk, const uint position, vuint32 &v, vuint32 &w, vuint32 &x, vuint32 &y, vuint32 &z);
    inline void round4(vuint32 *chunk, const uint position, vuint32 &v, vuint32 &w, vuint32 &x, vuint32 &y, vuint32 &z);

    inline vuint32 vrtol(vuint32 val, vuint32 shift);
    inline vuint32 sha1Word(vuint32 *chunk, const vuint32 position);

    void chunk();

    vbytes _encodeBuffer;

    vuint32 _h[5];

    vuint64 _msgSz;
};

}
#endif // VBYTES_H
