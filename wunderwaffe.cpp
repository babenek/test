#include <stdlib.h>
#include <cstdio>
#include <cstdint>
#include <vector>

#define bit0x01 if(n&0x01) {printf("\n true:%d",__COUNTER__ );} else {printf("\nfalse:%d",__COUNTER__ );}
#define bit0x02 if(n&0x02) {bit0x01;} else {bit0x01;}
#define bit0x04 if(n&0x04) {bit0x02;} else {bit0x02;}
#define bit0x08 if(n&0x08) {bit0x04;} else {bit0x04;}
#define bit0x10 if(n&0x10) {bit0x08;} else {bit0x08;}
#define bit0x20 if(n&0x20) {bit0x10;} else {bit0x10;}
#define bit0x40 if(n&0x40) {bit0x20;} else {bit0x20;}
#define bit0x80 if(n&0x80) {bit0x40;} else {bit0x40;}

int main()
{
	for(int n =0;n<256;++n){
		bit0x80;
	}
	printf("%d",__COUNTER__ );
	printf("%d",__COUNTER__ );
	return 0;
}

//------------------------------------------------------------------------------
