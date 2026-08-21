/* Giovanni Cadau © */

#include "stdio.h"
#include <math.h>
#include "coordinata.h"
#include "distanza.h"

double distanza(coordinata a , coordinata b)
{
    return sqrt( pow( (getAscissa(a)-getAscissa(b)), 2) + pow( (getOrdinata(a)-getOrdinata(b)), 2) );
}