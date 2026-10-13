#include "apc.h"
int subtraction(Dlist **h1,Dlist **t1,Dlist **h2,Dlist **t2,Dlist **hr)
{
    /* This operation is the magnitude subtraction: first operand must be >= second. */
    return list_subtract(h1,t1,h2,t2,hr);
}
