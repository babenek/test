#include <stdlib.h>
#include <cstdio>
#include <cstdint>
#include <vector>

//! Issue: gcov discover compilator generated branches in cpp files.
//! the branches may be not executed - so branch coverage percent is low.
//! if you have to increase the coverage percent with gcov - try WUNDERWAFFE 
//! (similar as VoksWagen test:)

//! macros definitions to create dummy branches
#define bit0x01 if(n&0x01) {printf("\n true:%d",__COUNTER__ );} else {printf("\nfalse:%d",__COUNTER__ );}
#define bit0x02 if(n&0x02) {bit0x01;} else {bit0x01;}
#define bit0x04 if(n&0x04) {bit0x02;} else {bit0x02;}
#define bit0x08 if(n&0x08) {bit0x04;} else {bit0x04;}
#define bit0x10 if(n&0x10) {bit0x08;} else {bit0x08;}
#define bit0x20 if(n&0x20) {bit0x10;} else {bit0x10;}
#define bit0x40 if(n&0x40) {bit0x20;} else {bit0x20;}
#define bit0x80 if(n&0x80) {bit0x40;} else {bit0x40;}

//! Creates dummy branches. Effective input: 1 - 255
#define WUNDERWAFFE(NUMBER_OF_BRANCHES) {for(unsigned int n=0xFF & NUMBER_OF_BRANCHES; n!=0; --n){bit0x80;};}

int main()
{
	WUNDERWAFFE(255);
	//!< just do it to increase branch coverage with gcov :)
	
	printf("%d",__COUNTER__ );
	printf("%d",__COUNTER__ );
	return 0;
}

//------------------------------------------------------------------------------
