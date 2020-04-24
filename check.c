#include <stdio.h>
#include "functions/check.h"

/*Рисует уничтоженный корабль*/
void kill(int fakeField[][10], int side, int backSide, int line, int x, int y){
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
int checkKill(int field[][10], int fakeField[][10], int x, int y){
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
        kill(fakeField, --right, --left, 1, x, y);
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
        kill(fakeField, --down, --up, 2, x, y);
    }
    /*Если это однопалубник*/
    else kill(fakeField, 0, 0, 0, x, y);
}
/*Проверяет можно ли поставить здесь корабль*/
int checkShip(int field[][10], int lastField[][10], int x, int y, int typeShip, int position){
    /*Высчитываем прямоугольник,
    который должен быть свободен для размещения корабля,
    затем проверяем каждую клетку*/
    int j, i, firstMaxCheck, secondMaxCheck; 
    /*По горизонтали
    определяем начальные и конечные координаты*/
    if (position){
        j = y; 
        firstMaxCheck = 1 + y;
        i = x; 
        secondMaxCheck = typeShip + x;
    }
    /*По вертикали
    определяем начальные и конечные координаты*/
    else {
        j = y; 
        firstMaxCheck = typeShip + y;
        i = x; 
        secondMaxCheck = x + 1;
    }
    /*Проверяем есть ли рядом стена*/
        if (j != 0) j--;
        int last_j = j; 
        if (i != 0) i--;
        /*Проверка клеток*/
        while(i <= secondMaxCheck && i <= 9){
            while(j <= firstMaxCheck && j <= 9){
                if (lastField[j][i] == 1) return 0;
                j++;
            }
            i++;
            j = last_j;
        } 
    return 1;
}