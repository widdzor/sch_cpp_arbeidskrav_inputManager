#include <stdlib.h>
#include "util.h"

int iRandRange(int low, int high)
{
    return rand() % ((high + 1) - low) + low;
}
