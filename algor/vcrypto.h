#ifndef VCRYPTO_H
#define VCRYPTO_H

#include "vbytes.h"
#include "vstring.h"

namespace  fcpp{

class vcrypto
{
public:
    vcrypto();

    virtual ~vcrypto();

    static vstring Base64Encode(const vbytes&b);
    static vstring Base64Encode(const vstring&s);

    static vbytes Base64Decode(const vstring&s);

private:

};

}
#endif // VCRYPTO_H
