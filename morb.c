/*gcc morb.c check.c draw.c computer.c analysis.c - компиляция*/
#include <stdio.h>
#include "ctype.h"
#include "time.h"
#include "stdlib.h" //Для функции system(), rand()
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

/*Рисует игровое поле*/
void draw(){
    drawField(players[0].fakeField, players[1].fakeField, players[0].allShips, players[1].allShips);
}
/*Вывод правил игры*/
void rules(){
    system("cls");
    char symbol;
    /*Открытие файла с правилами*/
    FILE *rules;
    rules = fopen("rules.txt", "r");
    /*Вывод правил*/
    while ((symbol = fgetc(rules)) != EOF) printf ("%c", symbol);
    fclose(rules);
    printf("\n");
    system("pause");
    main();
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
        /*заполняем структуру стандартными значениями*/
        memoryAI.lastShot = 0;
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
        move(players[!player].field, players[!player].fakeField, &players[!player].allShips, &lastSymbol, &x, &y, &player, players);
    }
    draw();
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
                move(players[!player].field, players[!player].fakeField, &players[!player].allShips, &lastSymbol, &x, &y, &player, players);
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
    draw();
    system ("pause");
    #ifdef TEST_AI
        draw();
        system("pause");
        printf("\nМинимальный: %i\n", memoryAI.minTypeShip);
            printf("Максимальный: %i\n", memoryAI.maxTypeShip);
            printf ("Остались кораблей: ");
            for(int i = 0; i < 4; i++) printf("%i ", memoryAI.typeShip[i]);
            system("pause");
    #endif
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
    printf ("3. Правила игры\n");
    printf ("4. Выход\n");
    switch (getchar()){
        case '1': 
            onePlayer();
            break;
        case '2': 
            twoPlayers();
            break;
        case '3':
            rules();
            break;
        case '4':
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