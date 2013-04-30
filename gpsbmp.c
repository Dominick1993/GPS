#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "gpsbmp.h"

void intToString(int number, int zeros)
{
    int x = 1;
    for (int i = 1; i<zeros; i++) x*=10;
    for (int i = 0; i<zeros; i++){
        printf("%d",number/x);
        number = number%x;
        x/=10;
    }
}

int stringToInt(char * string)
{
    int zaporne = 0;
    int result = 0;
    for(size_t i = 0; i<strlen(string); i++)
    {
        if(string[i] == '-')
        {
            zaporne = 1;
            continue;
        }
        else if(string[i] == '+') continue;
        result*=10;
        result+=(string[i]-'0');
    }
    if(zaporne && result != 0) return (-1)*result;
    return result;
}

void vypis(int cislo, int nuly, bool neg, bool lon)
{
    if (neg && cislo) putchar('-');
    if ((cislo%100)/60 >=1)
        intToString(cislo/100 + 1,nuly+lon);
    else
        intToString(cislo/100,nuly+lon);
    putchar(' ');
    if ((cislo%100)/60 >=1)
        intToString((cislo%100)%60,nuly);
    else
        intToString(cislo%100,nuly);
    if (lon) putchar('\n');
    else printf(", ");
}

void nacitanie(int commaPosition, int* lon, int* lat, int* nmeas, short* zmena)
{
    char c;
    int counter = 0;
    while(counter<commaPosition)
        if((c=getchar()) == ',')
            counter++;
    scanf("%d",lat);
    while((c=getchar()) != 'N' && c != 'S'){}
    if(c == 'S')
    {
        vypis(*lat,2,true,false);
        *lat*=-1;
    }
    else {
        vypis(*lat,2,false,false);
    }
    getchar();
    scanf("%d",lon);
    while((c=getchar()) != 'E' && c != 'W'){}
    if(c == 'W')
    {
        vypis(*lon,2,true,true);
        *lon*=-1;
    }
    else {
        vypis(*lon,2,false,true);
    }
    (*zmena)++;
    (*nmeas)++;
}
