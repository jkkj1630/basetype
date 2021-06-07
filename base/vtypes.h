#ifndef VTYPES_H
#define VTYPES_H

#include "vdefines.h"

using vchar = char;
using vuchar = unsigned char;

using vint16 = short ;
using vint32 = int;
using vlong = long;
using vint64 = long long;
using vuint16 = unsigned short;
using vuint32 = unsigned int;
using vulong = unsigned long;
using vuint64 = unsigned long long;

using vfloat32 = float;

using vchar_ptr = char*;
using vchar_const_ptr = char const *;
using vptr = void*;
using vconst_ptr = const void*;

using vsocket = int;
using vsocklen = unsigned int;

#endif // VTYPES_H
