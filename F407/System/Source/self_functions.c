#include"self_functions.h"

uint16_t pow(uint8_t num, uint8_t i)
{
    if(i==0)
    {
        return 1;
    }
    else
    {
        return num*pow(num, i-1);
    }
}

void num2str(uint16_t num, uint8_t* str, uint8_t str_len)
{
    uint16_t num_len = num;
    uint8_t len_dif;
    uint8_t i;
    if(!num_len)
    {
        num_len = 1;
    }
    else
    {
        for(i=0; num_len!=0; i++)
        {
            num_len/=10;
        }
        num_len = i;
    }
    if(str_len >= num_len)
    {
        len_dif = str_len-num_len;
        if(len_dif)
        {
            for(i=0; i<len_dif; i++)
            {
                *(str+i)='0';
            }
        }
        for(i=len_dif; i<str_len; i++, num_len--)
        {
            *(str+i) = '0'+ (num/pow(10, num_len-1))%10;
        }
        *(str+str_len) = '\0';
    }
}

uint8_t month_days(uint16_t year, uint8_t month)
{
    uint8_t run_tag = 0;
    if(((year%4 == 0)&&(year%100 != 0)) || ((year%100 == 0)&&(year%400 == 0)))
        run_tag = 1;
    else
        run_tag = 0;

    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
        break;
    case 2:
        if(run_tag)return 29;
        else return 28;
        break;
    
    default:
        break;
    }
    return 0;
}

