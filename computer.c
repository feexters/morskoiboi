#include <stdio.h>
#include "stdlib.h"
#include "functions/morskoiboi.h"

/*Выбор корабля*/
void intelligenceShips(struct player players[]){
    /*Корабли для расстановки расположены в порядке упрощения поиска места*/
    int ships [] ={4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; 
    /*Расстановка кораблей*/
    for (int i = 0; i < 10; i++){
        printf("%i", i);
        intelligenceAnalysis(players[1].field, ships[i]);
        #ifdef TEST_AI
        drawField(players[0].fakeField, players[1].field, players[0].allShips, players[1].allShips);
        system("pause");
        #endif
        intelligencePutShip(players[1].field, ships[i]);
        #ifdef TEST_AI
        drawField(players[0].fakeField, players[1].field, players[0].allShips, players[1].allShips);
        system("pause");
        #endif
        clearField(players[1].field);
    }
}
/*Если попадание было не смертельным, 
то функция будет добивать, пытаясь угадать расположение корабля*/
int intelligenceRoadToKill(struct memory *memoryAI, struct player players[], int x, int y){
    int canShot[4];// места для стрельбы
    int allPlaces = 0; // всего ест для стрельбы
    int chosePlace, result; // выбранное место, результат стрельбы
    #ifdef TEST_AI
        printf("\nВозможные направления:");
        for (int i = 0; i < 4; i++) printf(" %i", memoryAI->routes[i]);
        printf("\n");
    #endif
    /*Определяем доступные направления для стрельбы*/
    if (memoryAI->position == 1 || memoryAI->position == 3){
        /*вниз*/
        if(memoryAI->routes[0]) 
            canShot[allPlaces++] = 1;
        /*вверх*/
        if(memoryAI->routes[1]) 
            canShot[allPlaces++] = 2;
    }
    if (memoryAI->position == 2 || memoryAI->position == 3){
        /*вправо*/
        if(memoryAI->routes[2]) 
            canShot[allPlaces++] = 3;
        /*влево*/
        if(memoryAI->routes[3]) 
            canShot[allPlaces++] = 4;
    }
    /*Выбираем направление и задаем начальные координаты*/
    chosePlace = canShot[rand()%allPlaces];
    y = memoryAI->firstHit[0];
    x = memoryAI->firstHit[1]; 
    /*стреляем вниз*/
    if(chosePlace == 1){
        while(players[0].fakeField[++y][x] == 3);
    }
    /*стреляем вверх*/
    else if(chosePlace == 2){
        while(players[0].fakeField[--y][x] == 3);
    }
    /*стреляем вправо*/
    else if(chosePlace == 3){
        while(players[0].fakeField[y][++x] == 3);
    }
    /*стреляем влево*/
    else {
        while(players[0].fakeField[y][--x] == 3);
    }
    #ifdef TEST_AI
        printf("\nДоступные направления: ");
        for(int i = 0; i < allPlaces; i++)
            printf("%i ", canShot[i]);
        printf("\nВыбранное направление: %i", chosePlace);
        printf("\nВыбранное место: y = %i, x = %i", y, x);
        system("pause");
        drawField(players[0].field, players[1].fakeField, players[0].allShips, players[1].allShips);
    #endif
    result = shot(players[0].field, players[0].fakeField, &players[0].allShips, x, y);
    /*Промах*/
    if (!result) {
        memoryAI->routes[chosePlace - 1] = 0;
    }
    /*Убил*/
    else if (result == 3){
            memoryAI->lastShot = 0;
            memoryAI->position = 0;
            remainingShips(memoryAI, ++memoryAI->allHits);
            memoryAI->allHits == 0;
            for (int i = 0; i < 4; i++) memoryAI->routes[i] = 0;;
    }
    /*Попал*/
    else if (result == 1) {
        memoryAI->allHits++;
        memoryAI->routes[chosePlace - 1]--;
        if(chosePlace - 1 == 0 || chosePlace - 1 == 1) memoryAI->position = 1;
        else memoryAI->position = 2;
    }
    return result;
}
/*Стрельба ИИ*/
int intelligenceShot(struct memory *memoryAI, struct player players[], int x, int y){
    int result; //результат выстрела
    /*Если есть недобитый корабль*/
    if (memoryAI->lastShot == 1) result = intelligenceRoadToKill(memoryAI, players, x, y);
    /*Расположение корабля неизвестно*/
    else {
        /*Полный анализ поля*/
        intelligenceAnalysis(players[0].fakeField, memoryAI->minTypeShip);
        #ifdef TEST_AI
            drawField(players[0].fakeField, players[1].fakeField, players[0].allShips, players[1].allShips);
            system("pause");
        #endif
        int canShot[99];// Возможные места для стрельбы
        int allPlaces = 0;//кол-во доступных мест
        int chosePlace; //выбранное место для стрельбы
        /*Поиск доступных мест*/
        for (int i = 0; i < 100; i++){
            if (players[0].fakeField[i/10][i%10] >= 6 && players[0].fakeField[i/10][i%10] <= 8) {
                canShot[allPlaces++] = i;
            }
        }
        /*Выбор места рандомно*/
        chosePlace = canShot[rand()%allPlaces];
        x = chosePlace % 10;
        y = chosePlace / 10;
        /*Результат стрельбы*/
        result = shot(players[0].field, players[0].fakeField, &players[0].allShips, x, y);
        if (!result) {
        }
        /*Фиксируем попадание*/
        else if (result == 1){
            memoryAI->firstHit[0] = y;
            memoryAI->firstHit[1] = x;
            memoryAI->lastShot = 1;
            memoryAI->allHits = 1;
            memoryAI->position = AnalysisForShot(players[0].fakeField, memoryAI->routes, memoryAI->minTypeShip, memoryAI->maxTypeShip, x, y);
        }
        /*Убил*/
        else remainingShips(memoryAI, 1);
        clearField(players[0].fakeField);
    }
    return result;
}
/*Удаление корабля из списка*/
void remainingShips(struct memory *memoryAI, int killTypeShip){
    /*удаляем корабль*/
    memoryAI->typeShip[killTypeShip - 1]--;
    int i = 0, j = 3;
    /*Поиск максимальных и минимальных кораблей*/
    while(!memoryAI->typeShip[i] && i < 4) i++;
    while(!memoryAI->typeShip[j] && j >= 0) j--;
    memoryAI->minTypeShip = ++i;
    memoryAI->maxTypeShip = ++j;
}
/*Ставит корабль*/
void intelligencePutShip(int field[][10], int typeShip){
    int i = 0;
    int allPositions = 0, chosePosition, route; 
    int canPut[100]; //Содержит доступные места для расстановки 
    /*Выбираем подходящие места*/
    #ifdef TEST_AI
        printf("\nДоступные координаты: ");
    #endif
    while(i < 100){
        if (field[i/10][i%10] >= 6 && field[i/10][i%10] <= 8) {
            canPut[allPositions++] = i;
            #ifdef TEST_AI
            printf("%i ", canPut[allPositions - 1]);
            #endif
        }
        i++;
    }
    /*Рандомно выбираем места из доступного списка*/
    chosePosition = canPut[rand()%(allPositions)];
    /*Выбираем по вертикали или горизонтали*/
    int x = chosePosition % 10;
    int y = chosePosition / 10;
    if (field[y][x] == 8) route = rand()%2;
    else route = field[y][x] - 6;
    /*Рисуем корабль*/
    if (route){
        for(int j = y; j < y + typeShip; j++) field[j][x] = 1;
    } 
    else {
        for(int j = x; j < x + typeShip; j++) field[y][j] = 1;
    }
    printInvisibleSymbols(field, typeShip, x, y);
    #ifdef TEST_AI
        printf("\nВыбранная позиция: %i\n", chosePosition);
        printf("x: %i\n", x);
        printf("y: %i\n", y);
        printf("Направление: %i\n", route);
        system("pause");
    #endif  
}