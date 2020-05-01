#ifndef _MINILOGO_H_
#define _MINILOGO_H_
/*
 * WARNING: Do not change lines below!
 * RES: Bpp16
 * WIDTH: 5
 * HEIGHT: 3
 * TYPE: IMAGE
 * DISTINCT_COLORS: 3
*/

//PREDEFINED COLORS:
#define _ 0xffff
#define X 0xe8e4
#define B 0x0000
//END

 static const uint16_t data[15] = {
	B,_,_,X,B
    ,_,X,X,X,_
    ,B,X,_,_,B
 }

#undef _ 0xffff
#undef X 0xe8e4
#undef B 0x0000


#endif
