#ifndef HAAR_H
#define HAAR_H

#include<stdio.h>
#include<stdlib.h>

struct haar{
  long result;
  unsigned  x,y;
  unsigned size_w, size_h;
  int haar;
};

long haar1(unsigned x, unsigned y, unsigned size_w, unsigned size_h, unsigned img_w, unsigned img_h, unsigned long integ[img_h][img_w]); 
long haar2(unsigned x, unsigned y, unsigned size_w, unsigned size_h, unsigned img_w, unsigned img_h, unsigned long integ[img_h][img_w]);
long haar3(unsigned x, unsigned y, unsigned size_w, unsigned size_h, unsigned img_w, unsigned img_h, unsigned long integ[img_h][img_w]); 
long haar4(unsigned x, unsigned y, unsigned size_w, unsigned size_h, unsigned img_w, unsigned img_h, unsigned long integ[img_h][img_w]); 
long haar5(unsigned x, unsigned y, unsigned size_w, unsigned size_h, unsigned img_w, unsigned img_h, unsigned long integ[img_h][img_w]); 
long haar6(unsigned x, unsigned y, unsigned size_w, unsigned size_h, unsigned img_w, unsigned img_h, unsigned long integ[img_h][img_w]); 




struct haar *result(long x, long y, unsigned size_w, unsigned size_h, int haar, unsigned img_w, unsigned img_h, unsigned long integ[img_h][img_w]);





struct haar *array(unsigned img_w, unsigned img_h, unsigned long integ[h][w]); 

#endif
