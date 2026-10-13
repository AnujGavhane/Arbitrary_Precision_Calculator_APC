#include "apc.h"

/* Find the remainder by bringing down one dividend digit at a time. */
int modulus(Dlist *dividend, Dlist *divisor, Dlist **remainder)
{
    Dlist *rem = NULL, *tail = NULL;

    /* Modulus by zero is undefined. */
    if (!divisor || (divisor->data == 0 && !divisor->next))
        return FAILURE;

    for (Dlist *digit = dividend; digit; digit = digit->next)
    {
        /* Bring down the next digit into the current remainder. */
        if (list_append(&rem, &tail, digit->data) == FAILURE)
            goto error;

        /* Keep subtracting the divisor until the remainder is smaller. */
        while (list_compare(rem, divisor) >= 0)
        {
            Dlist *new_rem = NULL;
            Dlist *divisor_tail = divisor;
            while (divisor_tail->next)
                divisor_tail = divisor_tail->next;

            if (list_subtract(&rem, &tail, &divisor, &divisor_tail,
                              &new_rem) == FAILURE)
                goto error;

            list_free(&rem, &tail);
            rem = new_rem;
            tail = rem;
            while (tail && tail->next)
                tail = tail->next;
        }
    }

    *remainder = rem;
    return SUCCESS;

error:
    list_free(&rem, &tail);
    return FAILURE;
}
