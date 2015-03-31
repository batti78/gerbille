#ifndef HAAR_H
#define HAAR_H

#include<stdio.h>
#include<stdlib.h>

//Structure contenue dans la liste de Haar-feature obtenue par la fonction to list. 

struct haar{
  long result;
  unsigned  x,y;
  unsigned size_w, size_h;
  int haar;
};

//structure déffinissant le rectangle dans lequel sont composé les haar-features. 

struct rect{
  unsigned x; 
  unsigned y;
  unsigned size_w;
  unsigned size_h; 
  unsigned img_w;
  unsigned img_h;
  unsigned long integ[img_h][img_w];
};


//Deffinition des différents entiers qui compose de réctangle dans lequel sont calculé les haar-features. 

unsigned long A(struct rect *rect)
  return rect->integ[rect->x -1][rect->y -1];

unsigned long B(struct rect *rect)
  return rect->integ[rect->y -1][rect->x + rect->size_w -1];

unsigned long C(struct rect *rect)
  return rect->integ[rect->y + rect->size_h -1][rect->x + rect->size_w -1];

unsigned long D(struct rect *rect)
  return rect->integ[rect->y + rect->size_h -1][rect->x-1];

unsigned long E(struct rect *rect)
  return rect->integ[rect->y-1][rect->x + (rect->size_w)/2 -1];

unsigned long F(struct rect *rect)
  return rect->integ[rect->y + (rect->size_h)/2 -1][rect->x + rect->size_w -1];

unsigned long G(struct rect *rect)
  return rect->integ[rect->y + rect->size_h -1][rect->x + (rect->size_w)/2 -1];

unsigned long H(struct rect *rect)
  return rect->integ[rect->y + (rect->size_h)/2 -1][rect->x-1];

unsigned long I(struct rect *rect)
  return rect->integ[rect->y-1][rect->x + (rect->size_w)/3 -1];

unsigned long J(struct rect *rect)
  return rect->integ[rect->y-1][rect->x + 2*(rect->size_w)/3 -1];

unsigned long K(struct rect* rect)
  return rect->integ[rect->y + (rect->size_h)/3 -1][rect->x + rect->size_w -1];

unsigned long L(struct rect *rect)
  return rect->integ[rect->y + 2*(rect->size_h)/ -1][rect->x + rect->size_w -1];

unsigned long M(struct rect *rect)
  return rect->integ[rect->y + rect->size_h -1][rect->x + 2*(rect->size_w)/3 -1];

unsigned long N(struct rect *rect)
  return rect->integ[rect->y + rect->size_h -1][rect->x + (rect->size_w)/3 -1];

unsigned long O(struct rect *rect)
  return rect->integ[rect->y + 2*(rect->size_h)/3 -1][rect->x-1];

unsigned long P(struct rect *rect)
  return rect->integ[rect->y + (rect->size_h)/3 -1][rect->x-1];

unsigned long X(struct rect *rect)
  return rect->integ[rect->y + (rect->size_h)/2 -1][rect->x + (rect->size_w)/2 -1];

//On passe au calcule des haar feature à l'aide des valeur intégrales ci-dessus. 

long haar1(struct rect *rect)
  return (- A(rect) + B(rect) + C(rect) - D(rect) + 2*H(rect) + 2*E(rect));

long haar2(struct rect *rect)
  return (-C(rect) - 2*E(rect) + 2*G(rect) + B(rect) + A(rect) - D(rect));

long haar3(struct rect *rect)
  return (3*N(rect) + A(rect) - 3*I(rect) - D(rect) + L(rect) + 3*J(rect) - B(rect) - 3*M(rect));

long haar4(struct rect *rect) 
  return (- 3*L(rect) - 3*P(rect) + 3*O(rect) + 3*K(rect) - B(rect) + A(rect) - D(rect) + C(rect));

long haar5(struct rect *rect)
  return (- 4*X(rect) + 2*H(rect) + 2*E(rect) + 2*F(rect) + 2*G(rect) - A(rect) - B(rect) - C(rect) - D(rect);





struct haar *result(unsigned x, unsigned y, unsigned size_w, unsigned size_h, int haar, unsigned img_w, unsigned img_h, unsigned long integ[img_h][img_w]);





struct haar *array(unsigned img_w, unsigned img_h, unsigned long integ[h][w]); 

#endif
