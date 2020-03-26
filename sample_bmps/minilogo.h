#ifndef _MINILOGO_H_
#define _MINILOGO_H_

// mini logo 5x3 16bpp w konwencji 5-6-5 (rrrrrggggggbbbbb)

#define _ 0xffff
#define X 0xe8e4
#define B 0x0000

  const struct {
     const uint16_t width;
     const uint16_t height;
     const uint16_t data[5 * 3];
  } s_minilogo16 = { 5, 3 ,
     {
         B,_,_,X,B
        ,_,X,X,X,_
        ,B,X,_,_,B
     }
  };
#undef _ 0xffff
#undef X 0xe8e4
#undef B 0x0000


#endif