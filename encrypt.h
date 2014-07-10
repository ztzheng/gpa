#ifndef ENCRYPT_H
#define ENCRYPT_H
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#define MAX_LEN 1024
void encrypt(char*   cSrc,char*   cDest)
{
    char   c;
    int   i,h,l,j=0;
    for   (i=0;i<(int)strlen(cSrc);i++)
    {
        c=cSrc[i];
        h=(c>>4)&0xf;
        l=c&0xf;
        cDest[j]=h+'x';
        cDest[j+1]=l+'z';
        j+=2;
    }
    cDest[j]='\0';
}
void decrypt(char*   cSrc,char*   cDest)
{
    int   i,h,l,m,n,j=0;
    for   (i=0;i<(int)strlen(cSrc);i=i+2)
    {
        h=(cSrc[i]-'x');
        l=(cSrc[i+1]-'z');
        m=(h<<4);
        n=(l&0xf);
        cDest[j]=m   +   n;
        j++;
    }
    cDest[j]='\0';

}
#endif // ENCRYPT_H
