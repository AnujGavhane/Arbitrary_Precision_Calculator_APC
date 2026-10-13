#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1
typedef int data_t;
typedef struct node { struct node *prev; data_t data; struct node *next; } Dlist;

int addition(Dlist **, Dlist **, Dlist **, Dlist **, Dlist **);
int subtraction(Dlist **, Dlist **, Dlist **, Dlist **, Dlist **);
int multiplication(Dlist **, Dlist **, Dlist **, Dlist **, Dlist **);
int division(Dlist **, Dlist **, Dlist **, Dlist **, Dlist **);
int modulus(Dlist *dividend, Dlist *divisor, Dlist **remainder);
int power(Dlist *base, int exponent, Dlist **result);
int list_append(Dlist **head, Dlist **tail, int digit);
void list_free(Dlist **head, Dlist **tail);
int list_compare(Dlist *a, Dlist *b);
int list_subtract(Dlist **a, Dlist **ta, Dlist **b, Dlist **tb, Dlist **r);
void list_print(Dlist *head);
int list_from_text(const char *text, Dlist **head, Dlist **tail);
int list_copy(Dlist *src, Dlist **head, Dlist **tail);

#endif
