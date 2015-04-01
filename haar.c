#include<stdio.h>
#include<stdlib.h>
#include"haar.h"


//Structure contenue dans la liste de Haar-feature obtenue par la fonction to list. 

/*
struct haar{
  long result;
  unsigned  x,y;
  unsigned size_w, size_h;
  int haar;
};
*/

//structure déffinissant le rectangle dans lequel sont composé les haar-features. 

/*
struct rect{
  int x; 
  int y;
  int size_w;
  int size_h; 
  int img_w;
  int img_h;
  unsigned long integ[img_h][img_w];
};
*/

//Deffinition des différents entiers qui compose de réctangle dans lequel sont calculé les haar-features. 

unsigned long A(struct rect *rect) {
  if (rect->y != 0 && rect->x != 0)
    return rect->integ[rect->x -1][rect->y -1];
  else
    return 0;
}

unsigned long B(struct rect *rect) {
  if (rect->y != 0) 
    return rect->integ[rect->y -1][rect->x + rect->size_w -1];
  else
    return 0;
}

unsigned long C(struct rect *rect) {
  return rect->integ[rect->y + rect->size_h -1][rect->x + rect->size_w -1];
}

unsigned long D(struct rect *rect) {
  if (rect->x != 0)
    return rect->integ[rect->y + rect->size_h -1][rect->x-1];
  else
    return 0;
}

unsigned long E(struct rect *rect) {
  if (rect->y != 0)
    return rect->integ[rect->y-1][rect->x + (rect->size_w)/2 -1];
  else
    return 0;
}

unsigned long F(struct rect *rect) {
  return rect->integ[rect->y + (rect->size_h)/2 -1][rect->x + rect->size_w -1];
}

unsigned long G(struct rect *rect) {
  return rect->integ[rect->y + rect->size_h -1][rect->x + (rect->size_w)/2 -1];
}

unsigned long H(struct rect *rect) {
  if (rect->x != 0)
    return rect->integ[rect->y + (rect->size_h)/2 -1][rect->x-1];
  else
    return 0;
}

unsigned long I(struct rect *rect) {
  if (rect->y != 0)
    return rect->integ[rect->y-1][rect->x + (rect->size_w)/3 -1];
  else
    return 0;
}

unsigned long J(struct rect *rect) {
  if (rect->y != 0)
    return rect->integ[rect->y-1][rect->x + 2*(rect->size_w)/3 -1];
  else
    return 0;
}

unsigned long K(struct rect* rect) {
  return rect->integ[rect->y + (rect->size_h)/3 -1][rect->x + rect->size_w -1];
}

unsigned long L(struct rect *rect) {
  return rect->integ[rect->y + 2*(rect->size_h)/ -1][rect->x + rect->size_w -1];
}

unsigned long M(struct rect *rect) {
  return rect->integ[rect->y + rect->size_h -1][rect->x + 2*(rect->size_w)/3 -1];
}

unsigned long N(struct rect *rect) {
  return rect->integ[rect->y + rect->size_h -1][rect->x + (rect->size_w)/3 -1];
}

unsigned long O(struct rect *rect) {
  if (rect->x != 0)
    return rect->integ[rect->y + 2*(rect->size_h)/3 -1][rect->x-1];
  else
    return 0;
}

unsigned long P(struct rect *rect) {
  if (rect->x != 0)
    return rect->integ[rect->y + (rect->size_h)/3 -1][rect->x-1];
  else
    return 0;
}

unsigned long X(struct rect *rect) {
  return rect->integ[rect->y + (rect->size_h)/2 -1][rect->x + (rect->size_w)/2 -1];
}

//On passe au calcule des haar feature à l'aide des valeur intégrales ci-dessus. 

long haar1(struct rect *rect) {
  return (- A(rect) + B(rect) + C(rect) - D(rect) + 2*H(rect) + 2*E(rect));
}

long haar2(struct rect *rect) {
  return (-C(rect) - 2*E(rect) + 2*G(rect) + B(rect) + A(rect) - D(rect));
}

long haar3(struct rect *rect) {
  return (3*N(rect) + A(rect) - 3*I(rect) - D(rect) + L(rect) + 3*J(rect) - B(rect) - 3*M(rect));
}

long haar4(struct rect *rect) {
  return (- 3*L(rect) - 3*P(rect) + 3*O(rect) + 3*K(rect) - B(rect) + A(rect) - D(rect) + C(rect));
}

long haar5(struct rect *rect) {
  return (- 4*X(rect) + 2*H(rect) + 2*E(rect) + 2*F(rect) + 2*G(rect) - A(rect) - B(rect) - C(rect) - D(rect));
      }

//fonction retournant un tableau de haar-features et prenant en paramametre la matrice de l'image intégrale, sa largeur et sa hauteur) 

struct haar *array(int img_w, int img_h, unsigned long **integ)
{
  int x, y, w, h, haar;
  unsigned long n = 0; 
  struct haar *array = NULL; 
  struct rect *r  = malloc(sizeof(struct rect)); 
  r->integ = integ;
  for (y = 0; y < (img_h - 24); y++)
  {
    r->y = y; 
    for(x = 0; x < (img_w - 24); x++)
    {
      r->x = x; 
      for (h = 24; h < img_h; h = (h/4)*5)
      {
        r->size_h = h; 
        for(w = 24; h < img_w; w = (w/4)*5)
        {
          r->size_w = w; 
          for (haar = 0; haar < 5; haar++)
          {
            array = realloc(array, sizeof(array) + sizeof(struct haar));
            switch (haar)
            {
            case 0 :
              array[n]->result = haar1(r);
              array[n]->haar = 1; 
              break;
            case 1 :
              array[n]->result = haar2(r);
              array[n]->haar = 2; 
              break;
            case 3 :
              array[n]->result = haar3(r);
              array[n]->haar = 3; 
              break;
            case 4 :
              array[n]->result = haar4(r);
              array[n]->haar = 4; 
              break;
            case 5 :
              array[n]->result = haar5(r); 
              array[n]->haar = 5; 
              break;
            }
            array[n]->x = x;
            array[n]->y = y;
            array[n]->size_h = h;
            array[n]->size_w = w; 
            n++; 
          }
        }
      }
    }
  }
  return array;
}
