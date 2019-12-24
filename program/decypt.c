#include <stdlib.h>
#include <stdio.h>
#include "aes256.h"
#define MAXLEN 2

uint8_t hextodec(unsigned char* buf){
    uint8_t i,m,temp=0,n;
    for(i=0;i<2;i++)
    {
    if(buf[i]>='A'&&buf[i]<='F')
    n=buf[i]-'A'+10;
    else if(buf[i]>='a'&&buf[i]<='f')
    n=buf[i]-'a'+10;
    else n=buf[i]-'0';
    temp=temp*16+n;
    }
    return temp;
}
int main(int argc, char * argv[]){
    FILE *infile,*outfile;
    infile = fopen(argv[1],"rb");
    outfile = fopen(argv[2],"wb");
    uint8_t decimial;
    uint8_t rc;
    unsigned char buf[MAXLEN]; 
    char s[256]={0};
    uint8_t buffer[16];
    uint8_t key[32];
    uint8_t cnt=0,i;
    aes256_context ctx;
    for (i = 0; i < sizeof(key);i++) key[i] = i; 
    while( (rc = fread(buf,sizeof(unsigned char), MAXLEN,infile)) != 0 )

    {
        decimial=hextodec(buf);
        buffer[cnt]=decimial;
        if(cnt==15)
        {
            aes256_init(&ctx,key);
            aes256_decrypt_ecb(&ctx,buffer);
            for(i=0;i<sizeof(buffer);i++)
            {
                sprintf(s,"%02X",buffer[i]);
                fputs(s,outfile);
            }
            cnt=0;
        }
        else 
        {
            cnt++;
        }
       // fwrite( &decimial, sizeof( uint8_t ), rc, outfile );

    } 
    fclose(infile);
    fclose(outfile);
    return 0;
}