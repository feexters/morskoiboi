#include <stdio.h>
#include "stdlib.h"

/*Хранит информацию об игроках*/
struct player{
    int field[10][10];      // Поле с кораблями
    int fakeField[10][10];  // Выводимое поле
    int allShips;           // кол-во расставленных кораблей
};

/*Структура для хранения информациии
для вычисления расположения корабля и его убийства*/
struct memory{
    int lastShot;       // Результат последнего выстрела
    int routes[4];      // Возможные места отностельно места попадания 
    int position;       // По какой оси может располагаться корабль
    int firstHit[2];    // Первое попадание
    int allHits;        // Всего попаданий
    int typeShip[4];    //Оставшиеся типы кораблей у противника
    int minTypeShip;    // Минимальный размер корабля
    int maxTypeShip;    // Максимальный размер корабля
} memoryAI;

/*Проверяет можно ли поставить здесь корабль*/
int checkShip(int field[][10], int lastField[][10], int x, int y, int typeShip, int position);

/*Проверяет уничтожен ли корабль*/
int checkKill(int field[][10], int fakeField[][10], int x, int y);

/*Рисует уничтоженный корабль*/
void kill(int fakeField[][10], int side, int backSide, int line, int x, int y);

/*Рисует одно поле*/
void printField(int field[][10]);

/*Рисует игровое поле*/
void drawField(int firstField[][10], int secondField[][10], int firstAllShips, int secondAllShips);

/*Очистка поля от "мусора"*/
void clearField(int field[][10]);

/*Рисует невидимые символы*/
void printInvisibleSymbols(int field[][10], int typeShip, int x, int y);

/*Анализ поля вокруг корабля после первого попадания*/
int AnalysisForShot(int field[][10],int routes[], int minTypeShip, int maxTypeShip, int x, int y);

/*Полный анализ поля на возможные расстановки
        Значения клетки:
6 - можно поставить по по горизонтали
7 - можно поставить по вертикали
8 - все два варианта расстановки
9 - поставить корабль нельзя*/
int intelligenceAnalysis(int field[][10], int typeShip);

/*Ставит корабль*/
void intelligencePutShip(int field[][10], int typeShip);

/*Удаление корабля из списка*/
void remainingShips(struct memory *memoryAI, int killTypeShip);

/*Если попадание было не смертельным, 
то функция будет добивать, пытаясь угадать расположение корабля*/
int intelligenceRoadToKill(struct memory *memoryAI, struct player players[], int x, int y);

/*Стрельба ИИ*/
int intelligenceShot(struct memory *memoryAI, struct player players[], int x, int y);

/*Выбор корабля*/
void intelligenceShips(struct player players[]);
int shot(int field[][10], int fakeField[][10], int *allShips, int x, int y);