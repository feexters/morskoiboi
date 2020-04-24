#include <stdio.h>
#include "stdlib.h"

/*Проверяет можно ли поставить здесь корабль*/
int checkShip(int field[][10], int lastField[][10], int x, int y, int typeShip, int position);

/*Проверяет уничтожен ли корабль*/
int checkKill(int field[][10], int fakeField[][10], int x, int y);

/*Рисует уничтоженный корабль*/
void kill(int fakeField[][10], int side, int backSide, int line, int x, int y);

/*Рисует одно поле*/
void printField(int field[][10]);

/*Рисует игровое поле*/
void drawField(int firstField[][10], int secondField[][10]);

/*Очистка поля от "мусора"*/
void clearField(int field[][10]);