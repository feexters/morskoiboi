#include <stdio.h>
#include "stdlib.h"
#include "functions/morskoiboi.h"

/*Расставляет корабли*/
void putShip(int field[][10], int typeShip){
    int result = 0;
    int position = 0;//1 - горизонтально, 0 - вертикально
    int lastField[10][10];
    /*Создаем копию поля*/
    for (int i = 0; i < 10; i++){
         for (int j = 0; j < 10; j++) lastField[i][j] = field[i][j];
    }
    int x = 4, y = 4; // ставим на середину поля
    /*Рисуем корабль*/
    for(int i = 0; i < typeShip; i++) field[y + i][x] = 1;
    /*Рисуем поле*/
    printField(field);
    while(!result){
        switch(getch()){
            case 'w'://вверх
                /*Ограничение поля*/
                if (y == 0) break;
                /*по вертикали*/
                else if (!position){
                    field[y + typeShip - 1][x] = lastField[y + typeShip - 1][x];
                    y--;
                    for(int i = 0; i < typeShip; i++){
                        field[y + i][x] = 1;
                    }
                }
                /*по горизонтали*/
                else{
                    y--;
                    for(int i = 0; i < typeShip; i++){
                        field[y][x + i] = 1;
                        field[y + 1][x + i] = lastField[y + 1][x + i];
                    }
                }
                printField(field);
                break;
             case 'a'://влево
                /*Ограничение поля*/
                if (x == 0) break;
                /*по горизонтали*/
                else if (position){
                        field[y][x + typeShip - 1] = lastField[y][x + typeShip - 1];
                        x--;
                        for(int i = 0; i < typeShip; i++){
                            field[y][x + i] = 1;
                        }
                    }
                /*по вертикали*/
                else{
                    x--;
                    for(int i = 0; i < typeShip; i++){
                        field[y + i][x] = 1;
                        field[y + i][x + 1] = lastField[y + i][x +1];
                    }
                }
                printField(field);
                break;
                
            case 's'://вниз
                /*по вертикали*/
                if (!position){
                    /*Ограничение поля*/
                    if (y + typeShip - 1 == 9) break;
                    field[y][x] = lastField[y][x];
                    y++;
                    for(int i = 0; i < typeShip; i++){
                        field[y + i][x] = 1;
                    }
                }
                /*по горизонтали*/
                else{
                    /*Ограничение поля*/
                    if (y == 9) break;
                    y++;
                    for(int i = 0; i < typeShip; i++){
                        field[y][x + i] = 1;
                        field[y - 1][x + i] = lastField[y - 1][x + i];
                    }
                }
                printField(field);
                break;
            case 'd'://вправо
                /*по горизонтали*/
                if (position){
                    /*Ограничение поля*/
                    if (x + typeShip - 1 == 9) break;
                    field[y][x] = lastField[y][x];
                    x++;
                    for(int i = 0; i < typeShip; i++){
                        field[y][x + i] = 1;
                    }
                }
                /*по вертикали*/
                else{
                    /*Ограничение поля*/
                    if (x == 9) break;
                    x++;
                    for(int i = 0; i < typeShip; i++){
                        field[y + i][x] = 1;
                        field[y + i][x - 1] = lastField[y + i][x - 1];
                    }
                }
                printField(field);
                break;
            case 'f'://смена направления корабля
                /*На горизонтальное*/
                if (!position) {
                    /*Ограничение поля*/
                    if (x + typeShip - 1 > 9){
                        printf ("\n         Поворот невозможен!\n Корабль будет выходить за пределы поля!\n"); 
                    break;
                    }
                    position = 1;
                    /*Убираем лишние символы по вертикали*/
                    for (int i = 1; i < typeShip; i++){
                        field[y + i][x] = lastField[y + i][x];
                        field[y][x + i] = 1;
                    }
                    printField(field);
                }
                /*На вертикальное*/
                else {
                    /*Ограничение поля*/
                    if (y + typeShip - 1 > 9){
                        printf ("\n         Поворот невозможен!\n Корабль будет выходить за пределы поля!\n"); 
                    break;
                    }
                    position = 0;
                     /*Убираем лишние символы по горизонтали*/
                    for (int i = 1; i < typeShip; i++){
                        field[y][x + i] = lastField[y][x + i];
                        field[y + i][x] = 1;
                    }
                    printField(field);
                }
                break;
            case 'e'://поставить корабль
                result = checkShip(field, lastField, x, y, typeShip, position);
                if (result == 0){
                    printf ("\n   Ошибка!!! Корабли не должны касаться друг с другом.\n");
                    printf ("                  Выберите другое место.\n\n\n");
                }
                system("pause");
                printField(field);
                break;
        }
    }
}

/*Управление во время стрельбы*/
void move(int field[][10], int fakeField[][10], int *allShips, int *lastSymbol, int *x, int *y, int *player, struct player players[]){
    int hit = 0; // Результат стрельбы
    if (kbhit()){
        char choose = getch();
        /*Делаем перемещение прицела*/
        if (choose == 'w' || choose == 'a' || choose == 's' || choose == 'd') paintMove(fakeField, choose, lastSymbol, x, y);
        /*Выполняем стрельбу*/
        else if (choose = 'e'){
            hit = shot(field, fakeField, allShips, *x, *y);
            if (hit != 2) *lastSymbol = fakeField[*y][*x];
            /*Меняем игрока*/
            if (!hit){
                if (*player == 0) *player = 1;
                else *player = 0;
                /*Возвращаем начальные значения координатам*/
                *x = 4;
                *y = 4; 
                *lastSymbol = players[*player].fakeField[*y][*x];
                players[*player].fakeField[*y][*x] = 2;
                draw();
            }
         }
    }
}

int menuNavigation(int totalPoints, int *choosePoint){
    char move = getch();
    if (move == 'w'){
        if (*choosePoint != 0) --(*choosePoint);
        else *choosePoint = 3;
    }
    else if (move == 's'){
        if (*choosePoint != 3) ++(*choosePoint);
        else *choosePoint = 0;
    }
    else if (move == 'e') return 0;
    return 1;
}