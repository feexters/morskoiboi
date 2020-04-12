#include "stdio.h"
#include "ctype.h"
#include "stdlib.h" //Для функции system()
#include "conio.h"// getch(), khbit()

int firstField[10][10], fakeFirstField[10][10];
int secondField[10][10], fakeSecondField[10][10];
int x = 4, y = 4; //Координаты для перемещения
int player = 1; //Номер ходящего игрока 
int gameover = 0; //Определяет конец игры
int allShips1 = 0;// кол-во расставленных кораблей
int allShips2 = 0;// кол-во расставленных кораблей
/*
*/
int main();

/*Рисует одно поле*/
void printField(int field[][10]){
    system("cls");
    printf ("   ");
    for (int i = 0; i < 10; i++) printf ("%c ", 'A' + i);
    printf ("\n   ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-\n");
    for (int i = 0; i < 10; i++){
        printf ("%2.i|", i + 1);
        for(int j = 0; j < 10; j++){
            if (field[i][j] == 0) printf (". ");
            else printf ("# ");
        }
        printf ("|\n");
    }
    printf ("   ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-\n");
}
/*Проверяет можно ли поставить здесь корабль*/
int checkShip(int field[][10], int lastField[][10], int x, int y, int typeShip, int position){
    /*Проверка вертикального корабля*/
    if (!position){
        for(int i = 0; i < typeShip; i++){
            /**/
            if ((field[y + i][x + 1] == 1 && x != 9) || (field[y + i][x - 1] == 1 && x != 0) || lastField[y + i][x] == 1) return 0;
            if (i == 0) {
                if ((field[y - 1][x - 1] == 1 && x != 0) || field[y - 1][x] == 1 || (field[y - 1][x + 1] == 1 && x != 9)) return 0;
            }
            else if (i == typeShip - 1){
                if ((field[y + 1 + i][x + 1] == 1 && x != 9) || field[y + 1 + i][x] == 1 || (field[y + 1 + i][x - 1] == 1 && x != 0)) return 0;
            }
        }
    }
    /*Проверка горизонтального корабля*/
    else {
        for(int i = 0; i < typeShip; i++){
            if (field[y + 1][x + i] == 1 || field[y - 1][x + i] == 1) return 0;
            if (i == 0 && x != 0) {
                if (field[y + 1][x - 1] == 1 || field[y][x - 1] == 1 || field[y - 1][x - 1] == 1) return 0;
            }
            else if (i == typeShip - 1 && ( x + typeShip) <= 9){
                if (field[y + 1][x + 1 + i] == 1 || field[y][x + 1 + i] == 1 || field[y - 1][x + 1 + i] == 1) return 0;
            }
        }
    }
    return 1;
}
/*Расставляет корабли*/
void putShip(int field[][10], int typeShip){
    int result = 0;
    int position = 0;//1 - горизонтально, 0 - вертикально
    int lastField[10][10];
    for (int i = 0; i < 10; i++){
         for (int j = 0; j < 10; j++) lastField[i][j] = field[i][j];
    }
    int x = 4, y = 4;
    for(int i = 0; i < typeShip; i++)
        field[y + i][x] = 1;
    printField(field);
    while(!result){
        switch(getch()){
            case 'w'://вверх
                /*по вертикали*/
                if (!position){
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
                /*по горизонтали*/
                if (position){
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
                /*по вертикали*/
            case 's'://вниз
                if (!position){
                    field[y][x] = lastField[y][x];
                    y++;
                    for(int i = 0; i < typeShip; i++){
                        field[y + i][x] = 1;
                    }
                }
                /*по горизонтали*/
                else{
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
                    field[y][x] = lastField[y][x];
                    x++;
                    for(int i = 0; i < typeShip; i++){
                        field[y][x + i] = 1;
                    }
                }
                /*по вертикали*/
                else{
                    x++;
                    for(int i = 0; i < typeShip; i++){
                        field[y + i][x] = 1;
                        field[y + i][x - 1] = lastField[y + i][x - 1];
                    }
                }
                printField(field);
                break;
            case 'f'://смена направления корабля
                if (!position) {
                    position = 1;
                    /*Убираем лишние символы по вертикали*/
                    for (int i = 1; i < typeShip; i++){
                        field[y + i][x] = lastField[y + i][x];
                        field[y][x + i] = 1;
                    }
                    printField(field);
                }
                else {
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
void ships(int field[][10], int palyer){
    int ship1 = 4, ship2 = 3, ship3 = 2, ship4 = 1; // всего кораблей каждого вида
    #ifdef TEST_TWO_PLAYERS
        ship1 = 1; 
        ship2 = 1; 
        ship3 = 1; 
        ship4 = 1;
    #endif
    int result = 0;
    #ifdef TEST_TWO_PLAYERS
        result = 10;
    #endif
    while (result < 20){
        system("cls");
        printf("    Выберите тип корабля\n\n");
        printf("1. Однопалубник. Осталось: %i\n", ship1);
        printf("2. Двухпалубник. Осталось: %i\n", ship2);
        printf("3. Трехпалубник. Осталось: %i\n", ship3);
        printf("4. Четырехпалубник. Осталось: %i\n", ship4);
        switch(getchar()){
            case '1':
                if (ship1 != 0) {
                    putShip(field, 1);
                    ship1--;
                    result++;
                }
                else {
                    printf ("Такие корабли закончились, выберите другой тип корабля.\n\n");
                    system("pause");
                } 
                break;
            case '2':
                if (ship2 != 0) {
                    putShip(field, 2);
                    ship2--;
                    result += 2;
                }
                else {
                    printf ("Такие корабли закончились, выберите другой тип корабля.\n\n");
                    system("pause");
                } 
                break;
            case '3':
                if (ship3 != 0) {
                    putShip(field, 3);
                    ship3--;
                    result += 3;
                }
                else {
                    printf ("Такие корабли закончились, выберите другой тип корабля.\n\n");
                    system("pause");
                } 
                break;
            case '4':
                if (ship4 != 0) {
                    putShip(field, 4);
                    ship4--;
                    result += 4;
                }
                else {
                    printf ("Такие корабли закончились, выберите другой тип корабля.\n\n");
                    system("pause");
                } 
                break;
        }
    }
}
/*Рисует игровое поле*/
void drawField (){
    system("cls");
    printf ("   ");
    for (int i = 0; i < 10; i++) printf ("%c ", 'A' + i);
    printf ("         ");
    for (int i = 0; i < 10; i++) printf ("%c ", 'A' + i);
    printf ("\n   ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-          ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-\n");
    for (int i = 0; i < 10; i++){
        printf ("%2.i|", i + 1);
        for(int j = 0; j < 10; j++){
            /*Замена значений на символы*/
            if (fakeFirstField[i][j] == 0) printf (". ");
            else if (fakeFirstField[i][j] == 1) printf ("# ");
            else if (fakeFirstField[i][j] == 2) printf ("+ ");
            else if (fakeFirstField[i][j] == 3) printf ("* ");
            else if (fakeFirstField[i][j] == 4) printf ("X ");
            else printf ("O ");
        }
        printf ("|     ");
        printf ("%2.i|", i + 1);
        for(int j = 0; j < 10; j++){
            /*Замена значений на символы*/
            if (fakeSecondField[i][j] == 0) printf (". ");
            else if (fakeSecondField[i][j] == 1) printf ("# ");
            else if (fakeSecondField[i][j] == 2) printf ("+ ");
            else if (fakeSecondField[i][j] == 3) printf ("* ");
            else if (fakeSecondField[i][j] == 4) printf ("X ");
            else printf ("O ");
        }
        printf ("|\n");
    }
    printf ("   ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-          ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-\n");
    #ifdef TEST_TWO_PLAYERS
        printf("Осталось попаданий: %i\n", allShips1);
        printf("Осталось попаданий: %i", allShips2);
    #endif
}
/*Заполняет массив стандартными значениями*/
void startGame(){
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            firstField[i][j] = 0;
            secondField[i][j] = 0;
            fakeFirstField[i][j] = 0;
            fakeSecondField[i][j] = 0;
        }
    }
}
/*Рисует уничтоженный корабль*/
void kill(int fakeField[][10], int side, int backSide, int line){
    /*Если однопалубник*/
    if (!line) fakeField[y][x] = 4;
    /*Горизонтальный корабль*/
    else if (line == 1){
        for (int i = x - backSide; i <= x + side; i++){
            fakeField[y][i] = 4;
        }
    }
    /*Вертикальный корабль*/
    else{
        for (int i = y - backSide; i <= y + side; i++){
            fakeField[i][x] = 4;
        }
    }
}
/*Проверяет уничтожен ли корабль*/
int checkKill(int field[][10], int fakeField[][10]){
    /*Определяем по какой оси расположен корабль и не является ли он однопалубным*/
    if ((field[y][x - 1] != 5 && field[y][x - 1] != 0 && x != 0) || (field[y][x + 1] != 0 && field[y][x + 1] != 5 && x != 9)){
        int left = 0, right = 0;// край корабля отностительно точки попадания
        /*Проверям, учичтожены ли левые части корабля*/
        while (x - left >= 0 && field[y][x - left] != 0 && field[y][x - left] != 5){
            if (field[y][x - left] == 1) return 0;
            left++;
        }
        /*Проверям, учичтожены ли правые части корабля*/
        while (x + right <= 9 && field[y][x + right] != 0 && field[y][x + right] != 5){
            if (field[y][x + right] == 1) return 0;
            right++;
        }
        /*Рисуем убитый корабль*/
        kill(fakeField, --right, --left, 1);
    }
    /*Определяем по какой оси расположен корабль и не является ли он однопалубным*/
    else if ((field[y - 1][x] != 5 && field[y - 1][x] != 0 && y != 0) || (field[y + 1][x] != 0 && field[y + 1][x] != 5 && y != 9)){
        int up = 0, down = 0;// край корабля отностительно точки попадания
        /*Проверям, учичтожены ли верхние части корабля*/
        while (y - up >= 0 && field[y - up][x] != 0 && field[y - up][x] != 5){
            if (field[y - up][x] == 1) return 0;
            up++;
        }
        /*Проверям, учичтожены ли нижние части корабля*/
        while (y + down <= 9 && field[y + down][x] != 0 && field[y + down][x] != 5){
            if (field[y + down][x] == 1) return 0;
            down++;
        }
        /*Рисуем убитый корабль*/
        kill(fakeField, --down, --up, 2);
    }
    /*Если это однопалубник*/
    else kill(fakeField, 0, 0, 0);
}
/*Определяет есть ли попадание*/
int shot(int field[][10], int fakeField[][10], int *allShips){
    /*Промах*/
    if (field[y][x] == 0){
        field[y][x] = 5;
        fakeField[y][x] = 5;
        return 0;
    }
    /*Попал*/
    else if (field[y][x] == 1) {
        field[y][x] = 3;
        fakeField[y][x] = field[y][x];
        /*Проверка на убийство*/
        checkKill(field, fakeField);
        /*Сокращаем кол-во кораблей*/
        --*(allShips);
        return 1;
    }
    else {
        printf ("\n   Вы уже стреляли в это место,");
        printf ("\nвыберите другое и повторите попытку.\n\n");
        return 2;
    }
}
int lastSymbol = 0; // Начальное значение для последнего символа поля
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
    drawField();
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
                if (player == 1) {
                    player = 2;
                    /*Возвращаем начальные значения координатам*/
                    x = 4;
                    y = 4; 
                    lastSymbol = fakeSecondField[y][x];
                }
                else {
                    player = 1;
                    /*Возвращаем начальные значения координатам*/
                    x = 4;
                    y = 4; 
                    lastSymbol = fakeFirstField[y][x];
                }
                drawField();
            }
         }
    }
}
/*Режим для двух игроков*/
void twoPlayers(){
    /*Обнуление полей и вывод информации*/
    startGame();
    system("cls");
    printf("         ПЕРВЫЙ игрок расставляет корабли.\n");
    printf("Проследите, чтобы второй игрок не смотрел на монитор, \n");
    printf(" иначе он будет знать, где расположены ваши корабли.\n\n\n");
    system ("pause");
    /*Расстановка кораблей для первого игрока*/
    ships(firstField, 1);
    allShips1 = 20;
    system("cls");
    #ifdef TEST_TWO_PLAYERS
        allShips1 = 10;
    #else 
        printf("         ВТОРОЙ игрок расставляет корабли.\n");
        printf("Проследите, чтобы первый игрок не смотрел на монитор, \n");
        printf(" иначе он будет знать, где расположены ваши корабли.\n\n\n");
        system ("pause");
        /*Расстановка кораблей для второго игрока*/
        ships(secondField, 2);
    #endif
    allShips2 = 20;
    #ifdef TEST_TWO_PLAYERS
        /*Показываем расположения кораблей*/
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                fakeFirstField[i][j] = firstField[i][j];
            }
        }
    #endif
    drawField();
    lastSymbol = 0;
    /*Игра продолжается пока не закончатся корабли*/
    while (allShips1 && allShips2){
        /*Ход игрока*/
        if (player == 1) move(firstField, fakeFirstField, &allShips1);
        else move(secondField, fakeSecondField, &allShips2);
    }
    system ("cls");
    /*Завершение игры и вывод результатов*/
    if (!allShips2){
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
void onePlayer(){
    printf ("Скоро...");
    int main();
}
int main(){
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