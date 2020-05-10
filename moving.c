#include <stdio.h>
#include "stdlib.h"
#include "functions/morskoiboi.h"

/*����⠢��� ��ࠡ��*/
void putShip(int field[][10], int typeShip){
    int result = 0;
    int position = 0;//1 - ��ਧ��⠫쭮, 0 - ���⨪��쭮
    int lastField[10][10];
    /*������� ����� ����*/
    for (int i = 0; i < 10; i++){
         for (int j = 0; j < 10; j++) lastField[i][j] = field[i][j];
    }
    int x = 4, y = 4; // �⠢�� �� �।��� ����
    /*���㥬 ��ࠡ��*/
    for(int i = 0; i < typeShip; i++) field[y + i][x] = 1;
    /*���㥬 ����*/
    printField(field);
    while(!result){
        switch(getch()){
            case 'w'://�����
                /*��࠭�祭�� ����*/
                if (y == 0) break;
                /*�� ���⨪���*/
                else if (!position){
                    field[y + typeShip - 1][x] = lastField[y + typeShip - 1][x];
                    y--;
                    for(int i = 0; i < typeShip; i++){
                        field[y + i][x] = 1;
                    }
                }
                /*�� ��ਧ��⠫�*/
                else{
                    y--;
                    for(int i = 0; i < typeShip; i++){
                        field[y][x + i] = 1;
                        field[y + 1][x + i] = lastField[y + 1][x + i];
                    }
                }
                printField(field);
                break;
             case 'a'://�����
                /*��࠭�祭�� ����*/
                if (x == 0) break;
                /*�� ��ਧ��⠫�*/
                else if (position){
                        field[y][x + typeShip - 1] = lastField[y][x + typeShip - 1];
                        x--;
                        for(int i = 0; i < typeShip; i++){
                            field[y][x + i] = 1;
                        }
                    }
                /*�� ���⨪���*/
                else{
                    x--;
                    for(int i = 0; i < typeShip; i++){
                        field[y + i][x] = 1;
                        field[y + i][x + 1] = lastField[y + i][x +1];
                    }
                }
                printField(field);
                break;
                
            case 's'://����
                /*�� ���⨪���*/
                if (!position){
                    /*��࠭�祭�� ����*/
                    if (y + typeShip - 1 == 9) break;
                    field[y][x] = lastField[y][x];
                    y++;
                    for(int i = 0; i < typeShip; i++){
                        field[y + i][x] = 1;
                    }
                }
                /*�� ��ਧ��⠫�*/
                else{
                    /*��࠭�祭�� ����*/
                    if (y == 9) break;
                    y++;
                    for(int i = 0; i < typeShip; i++){
                        field[y][x + i] = 1;
                        field[y - 1][x + i] = lastField[y - 1][x + i];
                    }
                }
                printField(field);
                break;
            case 'd'://��ࠢ�
                /*�� ��ਧ��⠫�*/
                if (position){
                    /*��࠭�祭�� ����*/
                    if (x + typeShip - 1 == 9) break;
                    field[y][x] = lastField[y][x];
                    x++;
                    for(int i = 0; i < typeShip; i++){
                        field[y][x + i] = 1;
                    }
                }
                /*�� ���⨪���*/
                else{
                    /*��࠭�祭�� ����*/
                    if (x == 9) break;
                    x++;
                    for(int i = 0; i < typeShip; i++){
                        field[y + i][x] = 1;
                        field[y + i][x - 1] = lastField[y + i][x - 1];
                    }
                }
                printField(field);
                break;
            case 'f'://ᬥ�� ���ࠢ����� ��ࠡ��
                /*�� ��ਧ��⠫쭮�*/
                if (!position) {
                    /*��࠭�祭�� ����*/
                    if (x + typeShip - 1 > 9){
                        printf ("\n         ������ ����������!\n ��ࠡ�� �㤥� ��室��� �� �।��� ����!\n"); 
                    break;
                    }
                    position = 1;
                    /*���ࠥ� ��譨� ᨬ���� �� ���⨪���*/
                    for (int i = 1; i < typeShip; i++){
                        field[y + i][x] = lastField[y + i][x];
                        field[y][x + i] = 1;
                    }
                    printField(field);
                }
                /*�� ���⨪��쭮�*/
                else {
                    /*��࠭�祭�� ����*/
                    if (y + typeShip - 1 > 9){
                        printf ("\n         ������ ����������!\n ��ࠡ�� �㤥� ��室��� �� �।��� ����!\n"); 
                    break;
                    }
                    position = 0;
                     /*���ࠥ� ��譨� ᨬ���� �� ��ਧ��⠫�*/
                    for (int i = 1; i < typeShip; i++){
                        field[y][x + i] = lastField[y][x + i];
                        field[y + i][x] = 1;
                    }
                    printField(field);
                }
                break;
            case 'e'://���⠢��� ��ࠡ��
                result = checkShip(field, lastField, x, y, typeShip, position);
                if (result == 0){
                    printf ("\n   �訡��!!! ��ࠡ�� �� ������ ������� ��� � ��㣮�.\n");
                    printf ("                  �롥�� ��㣮� ����.\n\n\n");
                }
                system("pause");
                printField(field);
                break;
        }
    }
}

/*��ࠢ����� �� �६� ��५��*/
void move(int field[][10], int fakeField[][10], int *allShips, int *lastSymbol, int *x, int *y, int *player, struct player players[]){
    int hit = 0; // ������� ��५��
    if (kbhit()){
        char choose = getch();
        /*������ ��६�饭�� ��楫�*/
        if (choose == 'w' || choose == 'a' || choose == 's' || choose == 'd') paintMove(fakeField, choose, lastSymbol, x, y);
        /*�믮��塞 ��५��*/
        else if (choose = 'e'){
            hit = shot(field, fakeField, allShips, *x, *y);
            if (hit != 2) *lastSymbol = fakeField[*y][*x];
            /*���塞 ��ப�*/
            if (!hit){
                if (*player == 0) *player = 1;
                else *player = 0;
                /*�����頥� ��砫�� ���祭�� ���न��⠬*/
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