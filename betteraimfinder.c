#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "aimfinder.h"
#include "betteraimfinder.h"

/* Второе решение: - через подмножества */
int betteraimfinder(coordinate *aims, int aimsCount, int radius){
    coordinateD average,max,min;
    max.x=aims[0].x;max.y=aims[0].y;
    min.x=aims[0].x;min.y=aims[0].y;

    /* Находим точку удара для данного подмножества*/
    for(int i=0;i<aimsCount;i++){
      if(max.x<aims[i].x) max.x=aims[i].x;
      if(min.x>aims[i].x) min.x=aims[i].x;
      if(max.y<aims[i].y) max.y=aims[i].y;
      if(min.y>aims[i].y) min.y=aims[i].y;
    }
    /*находим мин. и макс. координаты, и вычисляем средину координат */
    average.x=min.x+(max.x-min.x)/2; average.y=min.y+(max.y-min.y)/2;

    float range,rangesum=0;
    int bestaimfound=1;
    for(int i=0;i<aimsCount;i++){ /*проверяем все ли цели доступы и средних координат*/
      range=sqrt(pow(average.x-aims[i].x,2)+pow(average.y-aims[i].y,2));
      if(range>radius){
        bestaimfound=0;
       break; /* нет смысла дальше проверять, переходим к подмножествам*/
      }
      else{
        rangesum+=range;
      }
   }

   if (bestaimfound==1){ // Решение найдено

     if((aimsCount>maxkills)||((rangesum<bestrange)&&(aimsCount==maxkills))) {
       // проверяем что оно лучшее с максимальным количеством попаданий или
       // таким же количеством попаданий но лучшей кучностью
       bestaimD.x= average.x;
       bestaimD.y= average.y;
       bestrange=rangesum;
       maxkills=aimsCount;
     }

     }
     else{
       /* Составляем подмножеста из наборов координат и ищем в них оптимальную точку удара и количество убийств,
        сохраняя лучшее найденное значение до тех пор пока не останутся одиночные элементы*/
       if(aimsCount-1>maxkills){ /*нет смысла проверять заведомо худшие решения*/

          for(int i=0;i<aimsCount;i++)
          {   coordinate *aimsCut=( coordinate*) calloc(aimsCount,sizeof(coordinate));
              memcpy(aimsCut,aims,i*sizeof(coordinate)); /*получаем подмножество*/
              memcpy(&aimsCut[i],&aims[i+1],(aimsCount-1-i)*sizeof(coordinate));
              betteraimfinder(aimsCut, aimsCount-1, radius); /*вызываем эту же функцию еще раз с уменьшеным подмножеством*/
              free(aimsCut);
          }
     }

  }

}
