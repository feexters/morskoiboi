/*gcc morb.c CheckAndDraw.c - компиляция*/
#include <stdio.h>
#include "ctype.h"
#include "time.h"
#include "stdlib.h" //Для функции system(), rand()
#include "conio.h" // getch(), khbit()
/*Библиотека с функциями для рисования полей
и проверок условий*/
#include "functions/CheckAndDraw.h"
//#define TEST //- запус программы в режиме тестирования
//#define TEST //- запус программы в режиме тестирования ИИ

struct player{
    int field[10][10];// Поле с кораблями
    int fakeField[10][10];// Выводимое поле
    int allShips;// кол-во расставленных кораблей
} players[2];
/*Структура для хранения информациии
для вычисления расположения корабля и его убийства*/
struct memory{
    int lastShot; // Результат последнего выстрела
    int routes[4]; // Возможные места отностельно места попадания 
    int position; // По какой оси может располагаться корабль
    int firstHit[2]; // Первое попадание
    int allHits; // Всего попаданий
    int typeShip[4]; //Оставшиеся типы кораблей у противника
    int minTypeShip; // Минимальный размер корабля
    int maxTypeShip; // Максимальный размер корабля
} memoryAI;
int x = 4, y = 4; //Координаты для перемещения
int player = 0; //Номер ходящего игрока 
int lastSymbol = 0; // Начальное значение для последнего символа поля

int main();
int intelligenceAnalysis(int field[][10], int typeShip);
int shot(int field[][10], int fakeField[][10], int *allShips);
/*Рисует игровое поле*/
void draw(){
    drawField(players[0].fakeField, players[1].fakeField);
}
/*Проверяет оставшиеся корабли*/
void remainingShips(int killTypeShip){
    /*Фиксация убитого корабля*/
    memoryAI.typeShip[killTypeShip - 1]--;
    int i = 0, j = 3;
    /*Поиск минимального и наибольшего корабля*/
    while(!memoryAI.typeShip[i] && i < 4) i++;
    while(!memoryAI.typeShip[j] && j >= 0) j--;
    memoryAI.minTypeShip = ++i;
    memoryAI.maxTypeShip = ++j;
}
/*Анализ поля вокруг корабля после первого попадания*/
int AnalysisForShot(int field[][10],int routes[], int minTypeShip, int maxTypeShip, int x, int y){
    /*Обнуляем значения*/
    int positions = 0; // По какой оси располжен
    for (int i = 0; i < 4; i++) routes[i] = 0; 
    /*Проверяем количество доступных для стрельбы клеток в 4-х направлениях*/
    for (int i = y + 1; i < y + maxTypeShip && field [i][x] != 5 && field[i][x] && i <= 9; i++) routes[0] ++; //вниз
    for (int i = y - 1; i > y - maxTypeShip && field [i][x] != 5 && field[i][x] && i >= 0; i--) routes[1] ++; //вверх
    for (int i = x + 1; i < x + maxTypeShip && field [y][i] != 5 && field[y][i] && i <= 9; i++) routes[2] ++; //вправо
    for (int i = x - 1; i > x - maxTypeShip && field [y][i] != 5 && field[y][i] && i >= 0; i--) routes[3] ++; //влево
    /*Проверям возможные направления размещения корабля*/
    if (routes[0] + routes[1] >= minTypeShip - 1) positions ++;
    if (routes[2] + routes[3] >= minTypeShip - 1) positions += 2;
    #ifdef TEST_AI
        printf("\nВозможные направления: %i, %i, %i, %i", routes[0], routes[1], routes[2], routes[3]);
    #endif
    return positions;
}
/*Если попадание было не смертельным, 
то функция будет добивать, пытаясь угадать расположение корабля*/
int intelligenceRoadToKill(int routes[], int position, int field[][10]){
    int canShot[4];// места для стрельбы
    int allPlaces = 0; // всего ест для стрельбы
    int chosePlace, result; // выбранное место, результат стрельбы
    #ifdef TEST_AI
        printf("\nВозможные направления: %i, %i, %i, %i", routes[0], routes[1], routes[2], routes[3]);
    #endif
    /*Определяем доступные направления для стрельбы*/
    if (position == 1 || position == 3){
        /*вниз*/
        if(routes[0]) 
            canShot[allPlaces++] = 1;
        /*вверх*/
        if(routes[1]) 
            canShot[allPlaces++] = 2;
    }
    if (position == 2 || position == 3){
        /*вправо*/
        if(routes[2]) 
            canShot[allPlaces++] = 3;
        /*влево*/
        if(routes[3]) 
            canShot[allPlaces++] = 4;
    }
    /*Выбираем направление и задаем начальные координаты*/
    chosePlace = canShot[rand()%allPlaces];
    y = memoryAI.firstHit[0];
    x = memoryAI.firstHit[1]; 
    /*стреляем вниз*/
    if(chosePlace == 1){
        while(field[++y][x] == 3);
    }
    /*стреляем вверх*/
    else if(chosePlace == 2){
        while(field[--y][x] == 3);
    }
    /*стреляем вправо*/
    else if(chosePlace == 3){
        while(field[y][++x] == 3);
    }
    /*стреляем влево*/
    else {
        while(field[y][--x] == 3);
    }
    #ifdef TEST_AI
        printf("\nДоступные направления: ");
        for(int i = 0; i < allPlaces; i++)
            printf("%i ", canShot[i]);
        printf("\nВыбранное направление: %i", chosePlace);
        printf("\nВыбранное место: y = %i, x = %i", y, x);
        system("pause");
        drawField(players[0].field, players[1].fakeField);
    #endif
    result = shot(players[0].field, field, &players[0].allShips);
    /*Промах*/
    if (!result) {
        routes[chosePlace - 1] = 0;
        player = 0; // Сменяем игроков
        /*Возвращаем начальные значения координатам*/
        x = 4;
        y = 4; 
        lastSymbol = players[player].fakeField[y][x];
    }
    /*Убил*/
    else if (result == 3){
            memoryAI.lastShot = 0;
            memoryAI.position = 0;
            remainingShips(++memoryAI.allHits);
            memoryAI.allHits == 0;
            for (int i = 0; i < 4; i++) routes[i] = 0;;
    }
    /*Попал*/
    else if (result == 1) {
        memoryAI.allHits++;
        routes[chosePlace - 1]--;
        if(chosePlace - 1 == 0 || chosePlace - 1 == 1) position = 1;
        else position = 2;
    }
    return result;
}
/*Стрельба ИИ*/
int intelligenceShot(int field[][10]){
    int result; //результат выстрела
    /*Если есть недобитый корабль*/
    if (memoryAI.lastShot == 1) result = intelligenceRoadToKill(memoryAI.routes, memoryAI.position, field);
    /*Расположение корабля неизвестно*/
    else {
        /*Полный анализ поля*/
        intelligenceAnalysis(field, memoryAI.minTypeShip);
        #ifdef TEST_AI
            draw();
            system("pause");
        #endif
        int canShot[99];// Возможные места для стрельбы
        int allPlaces = 0;//кол-во доступных мест
        int chosePlace; //выбранное место для стрельбы
        /*Поиск доступных мест*/
        for (int i = 0; i < 100; i++){
            if (field[i/10][i%10] >= 6 && field[i/10][i%10] <= 8) {
                canShot[allPlaces++] = i;
            }
        }
        /*Выбор места рандомно*/
        chosePlace = canShot[rand()%allPlaces];
        x = chosePlace % 10;
        y = chosePlace / 10;
        /*Результат стрельбы*/
        result = shot(players[0].field, field, &players[0].allShips);
        if (!result) {
            player = 0; // Сменяем игроков
            /*Возвращаем начальные значения координатам*/
            x = 4;
            y = 4; 
            lastSymbol = players[player].fakeField[y][x];    
        }
        /*Фиксируем попадание*/
        else if (result == 1){
            memoryAI.firstHit[0] = y;
            memoryAI.firstHit[1] = x;
            memoryAI.lastShot = 1;
            memoryAI.allHits = 1;
            memoryAI.position = AnalysisForShot(field, memoryAI.routes, memoryAI.minTypeShip, memoryAI.maxTypeShip, x, y);
        }
        /*Убил*/
        else remainingShips(1);
        clearField(field);
    }
    return result;
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
    x = chosePosition % 10;
    y = chosePosition / 10;
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
/*Полный анализ поля на возможные расстановки
        Значения клетки:
6 - можно поставить по по горизонтали
7 - можно поставить по вертикали
8 - все два варианта расстановки
9 - поставить корабль нельзя*/
int intelligenceAnalysis(int field[][10], int typeShip){
    /*Анализ по горизонтали*/
    for(y = 0; y < 10; y++){
        for(x = 0; x <= 10 - typeShip; x++){
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
/*Выбор корабля*/
void intelligenceShips(int field[][10]){
    /*Корабли для расстановки расположены в порядке упрощения поиска места*/
    int ships [] ={4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; 
    /*Расстановка кораблей*/
    for (int i = 0; i < 10; i++){
        printf("%i", i);
        intelligenceAnalysis(field, ships[i]);
        #ifdef TEST_AI
        drawField(players[0].fakeField, players[1].field);
        system("pause");
        #endif
        intelligencePutShip(field, ships[i]);
        #ifdef TEST_AI
        drawField(players[0].fakeField, players[1].field);
        system("pause");
        #endif
        clearField(field);
    }
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
            /*Если такой корабль остался то перход к расстановке*/
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
int shot(int field[][10], int fakeField[][10], int *allShips){
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
            hit = shot(field, fakeField, allShips);
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
    printf("         \n\n\nДля начала игры вы должны расставить свои корабли.\n\n\n");
    system ("pause");
    /*Расстановка кораблей игроком*/
    ships(players[0].field);
    players[0].allShips = 20;
    system("cls");
    /*Расстановка кораблей компьютером*/
    intelligenceShips(players[1].field);
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
        else intelligenceShot(players[!player].fakeField);
   }
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