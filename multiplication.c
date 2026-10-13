#include "apc.h"
int multiplication(Dlist **h1,Dlist **t1,Dlist **h2,Dlist **t2,Dlist **hr)
{
    int n=0,m=0,i=0,j=0; Dlist *p;
    for(p=*h1;p;p=p->next)
        n++;
    for(p=*h2;p;p=p->next)
        m++;
    int *x=calloc((size_t)n,sizeof(int)),*y=calloc((size_t)m,sizeof(int));
    int *z=calloc((size_t)(n+m+1),sizeof(int));
    if(!x||!y||!z){free(x);free(y);free(z);return FAILURE;}
    for(p=*t1;p;p=p->prev)x[i++]=p->data;
    i=0; for(p=*t2;p;p=p->prev)y[i++]=p->data; /* Collect from least significant digit. */
    for(i=0;i<n;i++) for(j=0;j<m;j++) z[i+j]+=x[i]*y[j];
    for(i=0;i<n+m;i++){z[i+1]+=z[i]/10;z[i]%=10;}
    Dlist *rh=NULL,*rt=NULL;
    for(i=n+m;i>0 && z[i]==0;i--) {}
    for(;i>=0;i--) if(list_append(&rh,&rt,z[i])==FAILURE){list_free(&rh,&rt);free(x);free(y);free(z);return FAILURE;}
    *hr=rh; free(x);free(y);free(z); return SUCCESS;
}
