#include "apc.h"
int addition(Dlist **h1,Dlist **t1,Dlist **h2,Dlist **t2,Dlist **hr)
{
    Dlist *a=*t1,*b=*t2,*rh=NULL,*rt=NULL; int carry=0;
    while(a||b||carry){ int n=carry+(a?a->data:0)+(b?b->data:0);
        if(list_append(&rh,&rt,n%10)==FAILURE){list_free(&rh,&rt);return FAILURE;}
        carry=n/10; if(a)a=a->prev;if(b)b=b->prev; }
    *hr=rt; /* Reverse the least-significant-first temporary list. */
    for(a=rh;a;){Dlist *next=a->next;a->next=a->prev;a->prev=next;a=next;}
    (void)h1;(void)h2;(void)t1;(void)t2; return SUCCESS;
}
