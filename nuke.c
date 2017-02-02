#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "aimfinder.h"
#include "betteraimfinder.h"

int main (int argc, char * argv[])
{
   coordinate *aims=( coordinate*) malloc(1);

   if(argc!=3) {
     printf("Wrong number of arguments");
     return -1;
     }
   int radius= atoi(argv[2]);
   int aimsCount=0;
   FILE *fl;
   /*Переносим координаты из файла в массив*/
   if((fl=fopen(argv[1],"r"))!=0){
      printf("\nRadius: %d\n",radius);

      char cc;
      while( !feof(fl) ) {
        aims = ( coordinate*) realloc(aims, (aimsCount+1)* sizeof( coordinate));
        if(fscanf(fl, "%d", &aims[aimsCount].x)==-1||fscanf(fl, "%c",&cc )==-1||fscanf(fl, "%d", &aims[aimsCount].y )==-1) {
          printf("Error reading file");
          return -1;
          }


        aimsCount++;
      }
      printf ("Aims count - %d, with coordinates: \n", aimsCount);
      for(int i=0;i<aimsCount;i++){
        printf ("%d, ", aims[i].x);
        printf ("%d\n", aims[i].y);
      }
      fclose(fl);

      /* Предположим, что координаты удара тоже должны быть целые числа,
      как скорей всего всего имелось в виду в задаче(т.к. все входыне данные целые),
      тогда можно легко решить задачу перебором всех координат
      и проверкой во сколько целей попадаем      */
      coordinate bestaim;
      int kills=aimfinder(aims, aimsCount, radius, &bestaim);

      /* Это решение будет неудачным если большая координатная сетка и целей не очень много*/
      printf ("\nSolution 1:\nCoordinate set is (%d, %d), with %d kills. \n\n", bestaim.x, bestaim.y, kills);


      /*Второе решение, как мне кажется намного правильней
      через составление подмножеств координат и проверку, есть ли для данного подмножества точка попадания, позволяющая убить все цели
      данного подмножества, запоминание точки с лучшим количеством убийств и лучшей кучностью,
      Преимущества по сравнению с предыдущем: алгоритм не зависит от разрешающей способности сетки координат, т.е. можно легко переделать для
      целей заданных не целыми координатами, скорость рассчета зависит только от количества возможных целей, больше шансов, что
      если радиус взрыва окажется меньше все цели окажутся поражены.
      */
      bestrange =aimsCount*radius;
      maxkills=0;
      /*конечно лучше бы не пользоваться глобальными переменными для возврата значений, но в данном случае это сильно упростит код*/
      betteraimfinder(aims, aimsCount, radius);
      if(maxkills!=0)
      printf ("Solution 2(more accurate):\nBest coodrinate set is (%f, %f), with %d kills. \n", bestaimD.x, bestaimD.y, maxkills);
      else
      printf ("Coordinate file has wrong fromat \n");


    }
  else{
    printf ("File error, ensure file with this name exist");
  }
}
