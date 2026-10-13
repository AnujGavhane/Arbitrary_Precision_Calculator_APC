#include "apc.h"

int list_append(Dlist **head, Dlist **tail, int digit)
{
    Dlist *n = malloc(sizeof(*n));
    if (!n) return FAILURE;
    n->data = digit; n->next = NULL; n->prev = *tail;
    if (*tail) (*tail)->next = n; else *head = n;
    *tail = n;
    return SUCCESS;
}

void list_free(Dlist **head, Dlist **tail)
{
    Dlist *p = *head;
    while (p) { Dlist *next = p->next; free(p); p = next; }
    *head = *tail = NULL;
}

int list_from_text(const char *s, Dlist **h, Dlist **t)
{
    *h = *t = NULL;
    while (*s == '0' && s[1]) s++; /* Remove leading zeroes. */
    for (; *s; s++) if (list_append(h, t, *s - '0') == FAILURE) { list_free(h,t); return FAILURE; }
    return *h ? SUCCESS : FAILURE;
}

int list_copy(Dlist *p, Dlist **h, Dlist **t)
{
    *h = *t = NULL;
    for (; p; p=p->next) if (list_append(h,t,p->data)==FAILURE) { list_free(h,t); return FAILURE; }
    return SUCCESS;
}

int list_compare(Dlist *a, Dlist *b)
{
    int na=0, nb=0; Dlist *p;
    for(p=a;p;p=p->next) na++;
    for(p=b;p;p=p->next) nb++;
    if (na != nb) return na > nb ? 1 : -1;
    while(a && b) { if(a->data!=b->data) return a->data>b->data?1:-1; a=a->next; b=b->next; }
    return 0;
}

void list_print(Dlist *p)
{
    while (p && p->data == 0 && p->next) p=p->next;
    if (!p) { putchar('0'); return; }
    for (;p;p=p->next) printf("%d",p->data);
}

/* Compute a-b; callers must ensure a is at least b. */
int list_subtract(Dlist **ah,Dlist **at,Dlist **bh,Dlist **bt,Dlist **rh)
{
    int borrow=0; Dlist *a=*at,*b=*bt,*rt=NULL; *rh=NULL;
    while(a) {
        int v=a->data-borrow-(b?b->data:0); borrow=0;
        if(v<0){v+=10;borrow=1;}
        if(list_append(rh,&rt,v)==FAILURE){list_free(rh,&rt);return FAILURE;}
        a=a->prev; if(b)b=b->prev;
    }
    while(rt && rt->data==0 && rt->prev){ Dlist *old=rt;rt=rt->prev;rt->next=NULL;free(old); }
    /* Reverse the temporary least-significant-first result. */
    for(a=*rh;a;){ Dlist *next=a->next; a->next=a->prev; a->prev=next; a=next; }
    a=*rh; *rh=rt; (void)ah;(void)bh;(void)bt; return SUCCESS;
}
