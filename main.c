#include "apc.h"

/* Build a list from a signed decimal string and report its sign separately. */
static int parse_number(char *s,Dlist **h,Dlist **t,int *sign)
{
    *sign=1;
    if(*s=='-' || *s=='+'){if(*s=='-')*sign=-1;s++;}
    if(!*s)return FAILURE;
    for(char *p=s;*p;p++)if(!isdigit((unsigned char)*p))return FAILURE;
    if (list_from_text(s,h,t) == FAILURE)
        return FAILURE;

    /* Treat -0 and +0 as ordinary zero so signs do not affect operations. */
    if ((*h)->data == 0 && !(*h)->next)
        *sign = 1;

    return SUCCESS;
}

int main(void)
{
    char left[4096],right[4096],op;
    puts("Arbitrary Precision Calculator (decimal integers)");
    puts("Operators: +  -  *  /  %  ^ (power exponent must be 0..10000)");
    for(;;){
        Dlist *h1=NULL,*t1=NULL,*h2=NULL,*t2=NULL,*result=NULL;
        int s1,s2,result_sign=1,status=SUCCESS;
        printf("Enter expression (example: -123 * 45): ");
        if(scanf("%4095s %c %4095s",left,&op,right)!=3)break;
        if(parse_number(left,&h1,&t1,&s1)==FAILURE || parse_number(right,&h2,&t2,&s2)==FAILURE){
            puts("Invalid integer input."); goto cleanup;
        }
        if(op=='+'){
            if(s1==s2){status=addition(&h1,&t1,&h2,&t2,&result);result_sign=s1;}
            else {int c=list_compare(h1,h2); if(c==0){Dlist *rt=NULL;status=list_append(&result,&rt,0);}
                else if(c>0){status=subtraction(&h1,&t1,&h2,&t2,&result);result_sign=s1;}
                else {status=subtraction(&h2,&t2,&h1,&t1,&result);result_sign=s2;}}
        } else if(op=='-'){
            if(s1!=s2){status=addition(&h1,&t1,&h2,&t2,&result);result_sign=s1;}
            else {int c=list_compare(h1,h2);if(c==0){Dlist *rt=NULL;status=list_append(&result,&rt,0);}
                else if(c>0){status=subtraction(&h1,&t1,&h2,&t2,&result);result_sign=s1;}
                else {status=subtraction(&h2,&t2,&h1,&t1,&result);result_sign=-s1;}}
        } else if(op=='*') {status=multiplication(&h1,&t1,&h2,&t2,&result);result_sign=s1*s2;}
        else if(op=='/') {status=division(&h1,&t1,&h2,&t2,&result);result_sign=s1*s2;}
        else if(op=='%') {status=modulus(h1,h2,&result);result_sign=s1;}
        else if(op=='^') {
            if(s2<0){status=FAILURE;}
            else { long e=0;for(Dlist *p=h2;p;p=p->next){e=e*10+p->data;if(e>10000)break;}
                if(e>10000)status=FAILURE;else {status=power(h1,(int)e,&result);result_sign=(s1<0 && (e%2))?-1:1;}}
        } else status=FAILURE;
        if(status==FAILURE)puts("Operation failed (check operator, division by zero, or exponent range).");
        else {printf("Result: "); if(result_sign<0 && !(result&&result->data==0&&!result->next))putchar('-');list_print(result);putchar('\n');}
cleanup:
        list_free(&h1,&t1);list_free(&h2,&t2);list_free(&result,&t1);
        printf("Continue? [y/N]: ");char answer[8];if(scanf("%7s",answer)!=1 || (answer[0]!='y'&&answer[0]!='Y'))break;
    }
    return 0;
}
