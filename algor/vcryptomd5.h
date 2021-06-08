#ifndef VCRYPTOMD5_H
#define VCRYPTOMD5_H

#include "vcrypto.h"

namespace  fcpp{

class vcryptomd5 : public vcrypto
{
public:
    vcryptomd5();

    virtual ~vcryptomd5();

    vbytes compute();

    void appendData(const vbytes&);
    void appendData(const vchar_const_ptr data, vuint32 len);

private:

    void byteSwap(vuint32 *buf, unsigned words);

    void computeStep(vuint32 const in[16]);

    vuint32 _buf[4];
    union {
        vint64 length64;
        vint32 length32[2];
    } _bytes;

    vuint32 _in[16];
};

}
#endif // VCRYPTOMD5_H
