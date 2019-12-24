#include <stdio.h>
#include <stdlib.h>
#include "aes256.h"
int main(int argc, char * argv[]) {
    FILE* in,*out;
    in=fopen(argv[1],"rb");
    out=fopen(argv[2],"a");
    char s[256]={0};
    uint8_t buf[16];
    uint8_t key[32];
    uint8_t cnt=0,i;
    aes256_context ctx;
    for (i = 0; i < sizeof(key);i++) key[i] = i;
    while(!feof(in))
    {

        uint8_t c=fgetc(in);
        buf[cnt]=c;
        if(cnt==15)
        {
            aes256_init(&ctx,key);
            aes256_encrypt_ecb(&ctx,buf);
            for(i=0;i<sizeof(buf);i++)
            {
                sprintf(s,"%02X",buf[i]);
                fputs(s,out);
            }
            cnt=0;
        }
        else 
        {
            cnt++;
        }
    } 
    if(cnt!=0){
        for(cnt;cnt<sizeof(buf);cnt++)
        {
            buf[cnt]=0;
        }
        aes256_init(&ctx,key);
        aes256_encrypt_ecb(&ctx,buf);
        for(i=0;i<sizeof(buf);i++)
        {
            sprintf(s,"%02X",buf[i]);
            fputs(s,out);
        }
    }
    return 0;
}