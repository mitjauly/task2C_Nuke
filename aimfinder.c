#include <stdio.h>
#include <math.h>
#include "aimfinder.h"

/* Решение 1, использует метод беребора через целые координаты*/
int aimfinder(struct coordinate *aims, int aimsCount, int radius, coordinate *bestaim){
  int maxkills=0;
  int bestrange=radius*aimsCount;;
  float range;
  for(int x=0;x<100;x++)
    for(int y=0;y<100;y++) {
      int kills=0, rangesum =0;;
      for(int i=0;i<aimsCount;i++){
        range=sqrt(pow(x-aims[i].x,2)+pow(y-aims[i].y,2)); /*расстояние от цели до проверяемой координаты*/
        if(range<=radius){
          kills++;
          rangesum+=range; /*сумма расстояний до объектов при попадании*/
        }
      }
      if(kills>maxkills) { /*выбираем лучшего*/
        maxkills=kills;
        bestaim->x=x;bestaim->y=y;
        bestrange=rangesum;
      }
      else if((kills==maxkills)&&(rangesum<bestrange)){ /*выбираем лучшего из лучших*/
        maxkills=kills;                                 /*стараемся чтобы выстрел попал как можно ближе к целям, а не просто задел краешком*/
        bestrange=rangesum;
        bestaim->x=x;bestaim->y=y;
      }
    }
    return maxkills;
}
