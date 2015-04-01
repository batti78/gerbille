#ifndef ADABOOST_H
#define ADABOOST_H

#include<stdio.h>
#include<stdlib.h>
#include"haar.c"


struct ada{
  struct haar x;
  int y;
  float p; 
};

struct ada *boost(struct haar *array) 
{
  long nb = sizeof(array)/sizeof(struct haar);
  struct ada *boost = NULL;
  long n = 0; 
  while (array[0])
  {
    boost = realloc(boost, sizeof(boost) + sizeof(struct ada));
    boost[n]->x = array[n];
    boost->y = 1;
    boost->p = 1/nb;
  }
}



#endif
