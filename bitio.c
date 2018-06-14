#include <stdio.h>

int main()
{
printf("#ifndef _BITIO_H_" "\n"
"#define _BITIO_H_" "\n");
for(unsigned n=0;n<=0xF;++n)printf(
"const unsigned char %c%c%c%c = 0x%X;\n"
,n&0x8?'I':'O',n&0x4?'I':'O',n&0x2?'I':'O',n&0x1?'I':'O',n);
for(unsigned n=0;n<=0xFF;++n)printf(
"const unsigned char %c%c%c%c%c%c%c%c = 0x%2X;\n"
,n&0x80?'I':'O',n&0x40?'I':'O',n&0x20?'I':'O',n&0x10?'I':'O'
,n&0x08?'I':'O',n&0x04?'I':'O',n&0x02?'I':'O',n&0x01?'I':'O',n);
printf("#endif" "\n");
return 0;
}


