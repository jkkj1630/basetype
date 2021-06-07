#ifndef VENDIAN_H
#define VENDIAN_H

#include "vtypes.h"

vuint32 endianLittleToBig32(vuint32 little) {
    return __builtin_bswap32(little);
}

vuint64 endianLittleToBig64(vuint64 little) {

    return __builtin_bswap64(little);
}

vuint32 endianBigToLittle32(vuint32 big) {
    return __builtin_bswap32(big);
}

vuint64 eendianBigToLittle64(vuint64 big) {

    return __builtin_bswap64(big);
}

#endif // VENDIAN_H
