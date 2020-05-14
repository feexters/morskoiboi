#include "functions/morskoiboi.h"

char skins [] = {'.', '#', '+', '*', 'X', 'O', '.', '.', '.', '.'}; // Скины

/*Рисуем невидимые символы, недающие поставить корабль на это место*/
void printInvisibleSymbols(int field[][10], int typeShip, int x, int y){
        /*Высчитываем прямоугольник вокруг корабля,
    затем заполням невидимыми символами*/
    int j = y, i = x, firstMaxCheck, secondMaxCheck; 
    /*По горизонтали
    определяем начальные и конечные координаты*/
    if (field[y][x+1] == 1 || field[y][x+1] == 3 || field[y][x+1] == 4){
        firstMaxCheck = 1 + y;
        secondMaxCheck = typeShip + x;
    }
    /*По вертикали
    определяем начальные и конечные координаты*/
    else {
        firstMaxCheck = typeShip + y;
        secondMaxCheck = x + 1;
    }
    /*Проверяем есть ли рядом стена*/
    if (j != 0) j--;
    int last_j = j; // Сохраняем начальное значение
    if (i != 0) i--;
    /*Проверка клеток*/
    while(i <= secondMaxCheck && i <= 9){
        while(j <= firstMaxCheck && j <= 9){
            if (field[j][i] == 0 || (field[j][i] >= 6 && field[j][i] < 9)) field[j][i] = 9;
            j++;
        }
        i++;
        /*Возвращаем начальное значение*/
        j = last_j;
    } 
}
/*Очистка поля от "мусора"*/
void clearField(int field[][10]){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j <= 10; j++){
            if(field[i][j] <=8 && field[i][j] >= 6) field[i][j] = 0;
        }
    }
}
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
        /*Замена на символы*/
        for(int j = 0; j < 10; j++){
            printf ("%c ", skins[field[i][j]]);
        }
        printf ("|\n");
    }
    printf ("   ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-\n");
}
/*Рисует игровое поле*/
void drawField(int firstField[][10], int secondField[][10], int firstAllShips, int secondAllShips){
    system("cls");
        printf ("      ПЕРВЫЙ ИГРОК");
    printf ("                  ВТОРОЙ ИГРОК\n   ");
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
            #ifdef TEST
                printf ("%i ", firstField[i][j]);
            #elif TEST_AI
                printf ("%i ", firstField[i][j]);
            #else
                /*Замена значений на символы*/
                printf ("%c ", skins[firstField[i][j]]);
            #endif
        }
        printf ("|     ");
        printf ("%2.i|", i + 1);
        for(int j = 0; j < 10; j++){
            #ifdef TEST
                printf ("%i ", secondField[i][j]);
            #elif TEST_AI
                printf ("%i ", secondField[i][j]);
            #else
                /*Замена значений на символы*/
                printf ("%c ", skins[secondField[i][j]]);
            #endif
            }
        printf ("|\n");
    }
    printf ("   ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-          ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-\n");
    printf("  Осталось попаданий: %i", firstAllShips);
    printf("       Осталось попаданий: %i\n\n", secondAllShips);
}
/*Рисует уничтоженный корабль*/
void kill(int fakeField[][10], int side, int backSide, int position, int x, int y){
    /*Если однопалубник*/
    if (!position) {
        fakeField[y][x] = 4;
        /*Рисуем вокруг невидимые символы*/
        printInvisibleSymbols(fakeField, 1, x, y);
    }
    /*Горизонтальный корабль*/
    else if (position == 1){
        for (int i = x - backSide; i <= x + side; i++){
            fakeField[y][i] = 4;
        }
        /*Рисуем вокруг невидимые символы*/
        printInvisibleSymbols(fakeField, backSide + 1 + side, x - backSide, y);
    }
    /*Вертикальный корабль*/
    else{ 
        for (int i = y - backSide; i <= y + side; i++){
            fakeField[i][x] = 4;
        }
        /*Рисуем вокруг невидимые символы*/
        printInvisibleSymbols(fakeField, backSide + 1 + side, x, y - backSide);
    }
}

/*Рисует перемещение прицела*/
int paintMove (int fakeField[][10], char choose, int *lastSymbol, int *x, int *y){
    /*Проверяем направление и отсутствие выхода за пределы поля*/
    /*Вверх*/
    if (choose == 'w' && *y != 0) {
        fakeField[*y][*x] = *lastSymbol;
        --(*y);
        }
    /*Влево*/
    else if (choose == 'a' && *x != 0) {
        fakeField[*y][*x] = *lastSymbol;
        --(*x);
        }
    /*Вниз*/
    else if (choose == 's' && *y != 9) {
        fakeField[*y][*x] = *lastSymbol;
        ++(*y);}
    /*Вправо*/
    else if (choose == 'd' && *x != 9) {
        fakeField[*y][*x] = *lastSymbol;
        ++(*x);
        }
    /*Выход за пределы поля*/
    else return 0;
    *lastSymbol = fakeField[*y][*x];
    fakeField[*y][*x] = 2;
    draw();
}
