#pragma once
#include <string.h>
#include <math.h>

std::string convHex(int n)
{


    std::string ret="";
    if(n<0)
        n=n+256;
    char lista[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    if(n < 16)
    {

        ret += lista[n];

    }
    else
    {

        int cociente = n/16;

        int resto = n%16;

        ret+=convHex(cociente);

        ret+=convHex(resto);

    }

    return ret;


}

int cov(std::string c){
int num=0;
for(int i=0;i<c.size();i++)
    num=(num*10)+((int)c[i]-48);

return num;
}

int* convBin(int n )
{
    int k=7;
    int* p =  new int  [8];
    for(int i=0; i<8; i++)
        p[i]=0;

    if(n<=1)
    {
        if(n!=0)
            p[k]=1;
        return p;
    }


    while((n/2)!=1)
    {
        p[k]=n%2;

        n=(n/2);

        k--;


    }
    p[k]=n%2;
    p[k-1]=1;
    if(k-1>0)



        return p;
}
int convHDec(char Hex)
{
    int num=(int)Hex;
    int k=1;
    std::string aux;

    if(num<0)
        num=256+num;

    aux =convHex(num);

    if(aux.length()>1)
        k=0;
    num=0;
    for(int i =0; i<aux.length(); i++)
    {

        switch(aux[i])
        {

        case 'A':
            num=num+10*pow(16,1-k);


            break;

        case 'B':
            num=num+11*pow(16,1-k);


            break;

        case 'C':

            num=num+12*pow(16,1-k);

            break;

        case 'D':
            num=num+13*pow(16,1-k);


            break;

        case 'E':
            num=num+14*pow(16,1-k);

            break;

        case 'F':
            num=num+15*pow(16,1-k);
            break;
        case '0':
            num=num;
            break;
        default:

            num=num+((((int)aux[i])-48)*pow(16,1-k));

            break;
        }
        k++;
    }



    return num;
}

// CONV_H_INCLUDED
