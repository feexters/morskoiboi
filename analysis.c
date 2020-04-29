#include <stdio.h>
#include "stdlib.h"
#include "functions/morskoiboi.h"

/*Полный анализ поля на возможные расстановки
        Значения клетки:
6 - можно поставить по по горизонтали
7 - можно поставить по вертикали
8 - все два варианта расстановки
9 - поставить корабль нельзя*/
int intelligenceAnalysis(int field[][10], int typeShip){
    /*Анализ по горизонтали*/
    for(int y = 0; y < 10; y++){
        for(int x = 0; x <= 10 - typeShip; x++){
            /*Пропускаяем неподходящие*/
            if(field[y][x] == 0 || (field[y][x] >= 6 && field[y][x] <= 8)){
                 int i = 0;
                /*Проверяем всю строчку*/
                while ((field[y][x + i] == 0 || (field[y][x + i] >= 6 && field[y][x + i] <= 8)) && i < typeShip){
                    /*Фиксируем результат проверки, если можно поставить*/
                    if (i == typeShip - 1) field[y][x] = 6;
                    i++;
                }
            }
        }
    }
    /*Анализ по вертикали*/
     for(int x = 0; x < 10; x++){
        for(int y = 0; y <= 10 - typeShip; y++){
            /*Пропускаяем неподходящие*/
            if(field[y][x] == 0 || (field[y][x] >= 6 && field[y][x] <= 8)){
                int i = 0;
                while ((field[y + i][x] == 0 || (field[y + i][x] >= 6 && field[y + i][x] <= 8)) && i < typeShip){
                    /*Фиксируем результат проверки, если можно поставить*/
                    if (i == typeShip - 1){
                        if (field[y][x] == 6) field[y][x] += 2;
                        else field[y][x] = 7;
                    }
                    i++;
                }
            }
        }
    }
}
/*Анализ поля вокруг корабля после первого попадания*/
int AnalysisForShot(int field[][10],int routes[], int minTypeShip, int maxTypeShip, int x, int y){
    /*Обнуляем значения*/
    int positions = 0; // По какой оси располжен
    for (int i = 0; i < 4; i++) routes[i] = 0; 
    /*Проверяем количество доступных для стрельбы клеток в 4-х направлениях*/
    for (int i = y + 1; i < y + maxTypeShip && field [i][x] != 5 && field[i][x] != 9 && i <= 9; i++) routes[0] ++; //вниз
    for (int i = y - 1; i > y - maxTypeShip && field [i][x] != 5 && field[i][x] != 9 && i >= 0; i--) routes[1] ++; //вверх
    for (int i = x + 1; i < x + maxTypeShip && field [y][i] != 5 && field[y][i] != 9 && i <= 9; i++) routes[2] ++; //вправо
    for (int i = x - 1; i > x - maxTypeShip && field [y][i] != 5 && field[y][i] != 9 && i >= 0; i--) routes[3] ++; //влево
    /*Проверям возможные направления размещения корабля*/
    if (routes[0] + routes[1] >= minTypeShip - 1) positions ++;
    if (routes[2] + routes[3] >= minTypeShip - 1) positions += 2;
    #ifdef TEST_AI
        printf("\nВозможные направления: %i, %i, %i, %i", routes[0], routes[1], routes[2], routes[3]);
    #endif
    return positions;
}