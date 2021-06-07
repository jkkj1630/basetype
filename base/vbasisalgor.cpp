#include "vbasisalgor.h"
#include "vtypes.h"
#include <stdlib.h>

vint32 vrandom32(vint32 seed)
{
    srand(seed);
    return rand();
}

