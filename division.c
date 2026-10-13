#include "apc.h"
int division(Dlist **h1,Dlist **t1,Dlist **h2,Dlist **t2,Dlist **hr)
{
    /* Long division: bring down one digit, then subtract divisor at most 9 times. */
    (void)t1; /* The algorithm walks the dividend from its head. */
    if(!*h2 || ((*h2)->data==0 && !(*h2)->next)) return FAILURE;
    Dlist *rem=NULL,*rt=NULL,*q=NULL,*qt=NULL,*p;
    for(p=*h1;p;p=p->next){
        if(list_append(&rem,&rt,p->data)==FAILURE) goto fail;
        int digit=0,cmp;
        do { cmp=list_compare(rem,*h2); if(cmp>=0){Dlist *newh=NULL;
                if(list_subtract(&rem,&rt,h2,t2,&newh)==FAILURE)goto fail;
                /* Free old remainder and rebuild its tail after subtraction. */
                list_free(&rem,&rt); rem=newh; rt=rem; while(rt&&rt->next)rt=rt->next; digit++;
            }} while(cmp>=0);
        if(list_append(&q,&qt,digit)==FAILURE)goto fail;
    }
    while(q && q->data==0 && q->next){Dlist *old=q;q=q->next;q->prev=NULL;free(old);}
    *hr=q; list_free(&rem,&rt); return SUCCESS;
fail: list_free(&rem,&rt); list_free(&q,&qt); return FAILURE;
}
