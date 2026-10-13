#include "apc.h"

/* Calculate base^exponent by multiplying by base repeatedly. */
int power(Dlist *base, int exponent, Dlist **result)
{
    Dlist *answer = NULL, *answer_tail = NULL;
    Dlist *base_copy = NULL, *base_tail = NULL;

    if (exponent < 0 || !base)
        return FAILURE;

    /* Any number to the power zero is 1. */
    if (list_append(&answer, &answer_tail, 1) == FAILURE)
        return FAILURE;

    if (list_copy(base, &base_copy, &base_tail) == FAILURE)
    {
        list_free(&answer, &answer_tail);
        return FAILURE;
    }

    for (int i = 0; i < exponent; i++)
    {
        Dlist *next_answer = NULL;
        Dlist *next_tail = NULL;

        /* multiplication returns the head; find its tail for the next pass. */
        if (multiplication(&answer, &answer_tail, &base_copy, &base_tail,
                           &next_answer) == FAILURE)
        {
            list_free(&answer, &answer_tail);
            list_free(&base_copy, &base_tail);
            return FAILURE;
        }

        list_free(&answer, &answer_tail);
        answer = next_answer;
        next_tail = answer;
        while (next_tail && next_tail->next)
            next_tail = next_tail->next;
        answer_tail = next_tail;
    }

    list_free(&base_copy, &base_tail);
    *result = answer;
    return SUCCESS;
}
