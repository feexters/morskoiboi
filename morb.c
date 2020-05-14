/*gcc morb.c check.c draw.c analysis.c computer.c moving.c -o MorskoiBoi - компиляция игры*/
/*gcc morb.c check.c draw.c analysis.c computer.c moving.c -D TEST -o TEST - компиляция игры в режиме тестирования*/
/*gcc morb.c check.c draw.c analysis.c computer.c moving.c -D TEST_AI -o TEST_AI - компиляция игры в режиме тестирования ИИ*/

/*Библиотека с функциями для игры*/
#include "functions/morskoiboi.h"

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
        int choosePoint = 0; // выбранный пункт
        /*Меню игры*/
        char points[4][55] = {{"1. Однопалубник. Осталось:"},
                            {"2. Двухпалубник. Осталось:"},
                            {"3. Трехпалубник. Осталось:"},
                            {"4. Четырехпалубник. Осталось:"}};
        /*Рисуем меню*/
        system("cls");
        printf("    Выберите тип корабля\n\n");
        for (int i = 0; i < 4; i++){
            printf ("%s %i", points[i], ships[i]);
            if (i == choosePoint) printf ("  <--------");
            printf("\n");
        }
        /*Выбираем нужный пункт*/
        while(menuNavigation(4, &choosePoint)){
            system("cls");
            printf("    Выберите тип корабля\n\n");
            for (int i = 0; i < 4; i++){
                printf ("%s %i", points[i], ships[i]);
                /*Указывает на выбранный пункт*/
                if (i == choosePoint) printf ("  <--------");
                printf("\n");
            }
        }
        /*Если такой корабль остался, то переход к расстановке*/
            if (ships[choosePoint] != 0){
                putShip(field, choosePoint + 1);
                ships[choosePoint]--;
                result += choosePoint + 1;
            }
            else {
            printf ("Такие корабли закончились, выберите другой тип корабля.\n\n");
            system("pause");
        }
    }
}
/*Заполняет массив стандартными значениями*/
void startGame(int gameMode){
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            player = 0;
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
        printf ("Победил ВТОРОЙ игрок!!!\n");
        printf ("    КОНЕЦ ИГРЫ\n\n");
        system("pause");
        main();
    }
    else{
        printf ("Победил ПЕРВЫЙ игрок!!!\n");
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
    printf("\n       Для начала игры\n");
    printf("  вы должны расставить свои корабли.\n\n\n");
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
    x = 4;
    y = 4;
    lastSymbol = players[1].fakeField[y][x];
    players[1].fakeField[y][x] = 2;
    draw();
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
                players[1].fakeField[y][x] = 2;
                draw();
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
    int choosePoint = 0; // выбранный пункт
    /*Меню игры*/
    char points[4][35] = {{"1. Одиночная игра"},
                          {"2. Два игрока"},
                          {"3. Правила игры"},
                          {"4. Выход"}};
    /*Рисуем меню*/
    system("cls");
    printf ("     МОРСКОЙ БОЙ\n\n");
    printf (" Выберите режим игры:\n\n");
    for (int i = 0; i < 4; i++){
        printf ("%s", points[i]);
        if (i == choosePoint) printf ("  <--------");
        printf("\n");
    }
    /*Выбираем нужный пункт*/
    while(menuNavigation(4, &choosePoint)){
        system("cls");
        printf ("     МОРСКОЙ БОЙ\n\n");
        printf (" Выберите режим игры:\n\n");
        for (int i = 0; i < 4; i++){
            printf ("%s", points[i]);
            /*Указывает на выбранный пункт*/
            if (i == choosePoint) printf ("  <--------");
            printf("\n");
        }
    }
    switch (++choosePoint){
        /*Одиночная игра*/
        case 1: 
            onePlayer();
            break;
        /*Два игрока*/
        case 2: 
            twoPlayers();
            break;
        /*Правила игра*/
        case 3:
            rules();
            break;
        /*Выход из игры*/
        case 4:
            system("cls");
            printf ("   До новых встреч!!!\n\n\n");
            system("pause");
            exit(1);
            return 0;
            break;
        default: 
            main();
            break;
    }
    system("pause");
}