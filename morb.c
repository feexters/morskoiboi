/*gcc morb.c check.c draw.c- компиляция*/
#include <stdio.h>
#include "ctype.h"
#include "time.h"
#include "stdlib.h" //Для функции system(), rand()
#include "conio.h" // getch(), khbit()
/*Библиотека с функциями для игры*/
#include "functions/morskoiboi.h"
//#define TEST //- запус программы в режиме тестирования
//#define TEST_AI //- запус программы в режиме тестирования ИИ

struct player players[2];
struct memory memoryAI;

int x = 4, y = 4; //Координаты для перемещения
int player = 0; //Номер ходящего игрока 
int lastSymbol = 0; // Начальное значение для последнего символа поля

int main();
int shot(int field[][10], int fakeField[][10], int *allShips, int x, int y);
/*Рисует игровое поле*/
void draw(){
    drawField(players[0].fakeField, players[1].fakeField, players[0].allShips, players[1].allShips);
}
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
/*Выбор корабля для последующей расстановки*/
void ships(int field[][10]){
    int ships[] = {4, 3, 2, 1}; // всего кораблей каждого вида
    int result = 0;
    #ifdef TEST
        for (int i = 0; i < 4; i++){
            ships[i] = 1;
        }
        result = 10;
    #endif
    while (result < 20){
        system("cls");
        printf("    Выберите тип корабля\n\n");
        printf("1. Однопалубник. Осталось: %i\n", ships[0]);
        printf("2. Двухпалубник. Осталось: %i\n", ships[1]);
        printf("3. Трехпалубник. Осталось: %i\n", ships[2]);
        printf("4. Четырехпалубник. Осталось: %i\n", ships[3]);
        char choose = getch();
        if (choose <= '4' && choose >= '1'){
            /*Если такой корабль остался то переход к расстановке*/
                if (ships[choose - '0' - 1] != 0){
                    putShip(field, choose - '0');
                    ships[choose - '0' - 1]--;
                    result += choose - '0';
                }
                else {
                printf ("Такие корабли закончились, выберите другой тип корабля.\n\n");
                system("pause");
            }
        }
    }
}
/*Заполняет массив стандартными значениями*/
void startGame(int gameMode){
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            players[0].field[i][j] = 0;
            players[1].field[i][j] = 0;
            players[0].fakeField[i][j] = 0;
            players[1].fakeField[i][j] = 0;
        }
    }
    if (gameMode){
        memoryAI.lastShot = 0; // Результат последнего выстрела
        memoryAI.position;
        memoryAI.firstHit[2];
        memoryAI.typeShip[0] = 4;
        memoryAI.typeShip[1] = 3;
        memoryAI.typeShip[2] = 2;
        memoryAI.typeShip[3] = 1;
        memoryAI.minTypeShip = 1;
        memoryAI.maxTypeShip = 4;
    }
}
/*Определяет есть ли попадание*/
int shot(int field[][10], int fakeField[][10], int *allShips, int x, int y){
    /*Промах*/
    int result = 0; // результат выстрела
    if (field[y][x] == 0 || field[y][x] >= 6){
        field[y][x] = 5;
        fakeField[y][x] = 5;
        return result;
    }
    /*Попал*/
    else if (field[y][x] == 1) {
        field[y][x] = 3;
        fakeField[y][x] = field[y][x];
        /*Проверка на убийство*/
        result = checkKill(field, fakeField, x, y);
        /*Сокращаем кол-во кораблей*/
        --*(allShips);
        return result + 1;
    }
    else {
        printf ("\n   Вы уже стреляли в это место,");
        printf ("\nвыберите другое и повторите попытку.\n\n");
        result = 2;
        return result;
    }
}
/*Рисует перемещение прицела*/
int paintMove (int fakeField[][10], char choose){
    /*Проверяем направление и отсутствие выхода за пределы поля*/
    /*Вверх*/
    if (choose == 'w' && y != 0) {
        fakeField[y][x] = lastSymbol;
        y--;
        }
    /*Влево*/
    else if (choose == 'a' && x != 0) {
        fakeField[y][x] = lastSymbol;
        x--;
        }
    /*Вниз*/
    else if (choose == 's' && y != 9) {
        fakeField[y][x] = lastSymbol;
        y++;}
    /*Вправо*/
    else if (choose == 'd' && x != 9) {
        fakeField[y][x] = lastSymbol;
        x++;
        }
    /*Выход за пределы поля*/
    else return 0;
    lastSymbol = fakeField[y][x];
    fakeField[y][x] = 2;
    draw();
}
/*Управление во время стрельбы*/
void move(int field[][10], int fakeField[][10], int *allShips){
    int hit = 0; // Результат стрельбы
    if (kbhit()){
        char choose = getch();
        /*Делаем перемещение прицела*/
        if (choose == 'w' || choose == 'a' || choose == 's' || choose == 'd') paintMove(fakeField, choose);
        /*Выполняем стрельбу*/
        else if (choose = 'e'){
            hit = shot(field, fakeField, allShips, x, y);
            if (hit != 2) lastSymbol = fakeField[y][x];
            /*Меняем игрока*/
            if (!hit){
                if (player == 0) player = 1;
                else player = 0;
                    /*Возвращаем начальные значения координатам*/
                    x = 4;
                    y = 4; 
                    lastSymbol = players[player].fakeField[y][x];
                draw();
            }
         }
    }
}
/*Режим для двух игроков*/
void twoPlayers(){
    /*Обнуление полей и вывод информации*/
    startGame(0);
    system("cls");
    printf("         ПЕРВЫЙ игрок расставляет корабли.\n");
    printf("Проследите, чтобы второй игрок не смотрел на монитор, \n");
    printf(" иначе он будет знать, где расположены ваши корабли.\n\n\n");
    system ("pause");
    /*Расстановка кораблей для первого игрока*/
    ships(players[0].field);
    players[0].allShips = 20;
    system("cls");
    #ifdef TEST
        players[0].allShips = 10;
    #else 
        printf("         ВТОРОЙ игрок расставляет корабли.\n");
        printf("Проследите, чтобы первый игрок не смотрел на монитор, \n");
        printf(" иначе он будет знать, где расположены ваши корабли.\n\n\n");
        system ("pause");
        /*Расстановка кораблей для второго игрока*/
        ships(players[1].field);
    #endif
    players[1].allShips = 20;
    #ifdef TEST
        /*Показываем расположения кораблей*/
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                players[0].fakeField[i][j] = players[0].field[i][j];
            }
        }
    #endif
    draw();
    lastSymbol = 0;
    /*Игра продолжается пока не закончатся корабли*/
    while (players[0].allShips && players[1].allShips){
        /*Ход игрока*/
        move(players[!player].field, players[!player].fakeField, &players[!player].allShips);
    }
    system("pause");
    system ("cls");
    /*Завершение игры и вывод результатов*/
    if (!players[0].allShips){
        printf ("Победил ПЕРВЫЙ игрок!!!\n");
        printf ("    КОНЕЦ ИГРЫ\n\n");
        system("pause");
        main();
    }
    else{
        printf ("Победил Второй игрок!!!\n");
        printf ("    КОНЕЦ ИГРЫ\n\n");
        system("pause");
        main();
    }
}
/*Одиночная игра для компьтера*/
void onePlayer(){
    /*Обнуление полей и вывод информации*/
    startGame(1);
    system("cls");
    printf("\n\n\n           Для начала игры\n");
    printf("      вы должны расставить свои корабли.\n\n\n");
    system ("pause");
    /*Расстановка кораблей игроком*/
    ships(players[0].field);
    players[0].allShips = 20;
    system("cls");
    /*Расстановка кораблей компьютером*/
    intelligenceShips(players);
    players[1].allShips = 20;
    #ifdef TEST
        /*Показываем расположения кораблей*/
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                players[1].fakeField[i][j] = players[1].field[i][j];
            }
        }
        players[0].allShips = 10;
    #elif TEST_AI
        /*Показываем расположения кораблей*/
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                players[1].fakeField[i][j] = players[1].field[i][j];
            }
        }
        players[0].allShips = 20;
    #endif
    draw();
    system("pause");
    lastSymbol = 0;
    x = 4;
    y = 4;
    /*Игра продолжается пока не закончатся корабли*/
    while (players[0].allShips && players[1].allShips){
        /*Ход игрока*/
        if (!player) {
            #ifdef TEST_AI
                player = 1;
            #else 
                move(players[!player].field, players[!player].fakeField, &players[!player].allShips);
            #endif
        }
        /*Ход компьютера*/
        else {
            if (!intelligenceShot(&memoryAI, players, x, y)){
                player = 0; // Сменяем игроков
                /*Возвращаем начальные значения координатам*/
                x = 4;
                y = 4; 
                lastSymbol = players[1].fakeField[y][x]; 
            }
        }
   }
    system ("pause");
    system ("cls");
    /*Завершение игры и вывод результатов*/
    if (!players[1].allShips){
        printf ("     ПОБЕДА!!!\n");
        printf ("    КОНЕЦ ИГРЫ\n\n");
        system("pause");
        main();
    }
    else{
        printf ("   ПОРАЖЕНИЕ!!!\n");
        printf ("    КОНЕЦ ИГРЫ\n\n");
        system("pause");
        main();
    }
}
int main(){
    srand(time(NULL));// Для генерации псевдо случайных чисел
    /*Меню игры*/
    system("cls");
    printf ("     МОРСКОЙ БОЙ\n\n");
    printf (" Выберите режим игры:\n\n");
    printf ("1. Одиночная игра\n");
    printf ("2. Два игрока\n");
    printf ("3. Выход\n");
    switch (getchar()){
        case '1': 
            onePlayer();
            break;
        case '2': 
            twoPlayers();
            break;
        case '3':
            printf ("До новых встреч!!!\n");
            system("pause");
            return 0;
            break;
        default: 
            printf ("Вы ввели неверное значение! Попробуйте еще раз!\n");
            main();
            break;
    }
    system("pause");
}