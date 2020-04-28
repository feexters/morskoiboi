#include <stdio.h>
#include "stdlib.h"
#include "functions/CheckAndDraw.h"

char skins [] = {'.', '#', '+', '*', 'X', 'O', '.', '.', '.', '.'}; // �����

/*���㥬 �������� ᨬ����, �����騥 ���⠢��� ��ࠡ�� �� �� ����*/
void printInvisibleSymbols(int field[][10], int typeShip, int x, int y){
        /*�����뢠�� ��אַ㣮�쭨� ����� ��ࠡ��,
    ��⥬ ������� �������묨 ᨬ������*/
    int j = y, i = x, firstMaxCheck, secondMaxCheck; 
    /*�� ��ਧ��⠫�
    ��।��塞 ��砫�� � ������ ���न����*/
    if (field[y][x+1] == 1 || field[y][x+1] == 3 || field[y][x+1] == 4){
        firstMaxCheck = 1 + y;
        secondMaxCheck = typeShip + x;
    }
    /*�� ���⨪���
    ��।��塞 ��砫�� � ������ ���न����*/
    else {
        firstMaxCheck = typeShip + y;
        secondMaxCheck = x + 1;
    }
    /*�஢��塞 ���� �� �冷� �⥭�*/
    if (j != 0) j--;
    int last_j = j; // ���࠭塞 ��砫쭮� ���祭��
    if (i != 0) i--;
    /*�஢�ઠ ���⮪*/
    while(i <= secondMaxCheck && i <= 9){
        while(j <= firstMaxCheck && j <= 9){
            if (field[j][i] == 0 || (field[j][i] >= 6 && field[j][i] < 9)) field[j][i] = 9;
            j++;
        }
        i++;
        /*�����頥� ��砫쭮� ���祭��*/
        j = last_j;
    } 
}
/*���⪠ ���� �� "����"*/
void clearField(int field[][10]){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j <= 10; j++){
            if(field[i][j] <=8 && field[i][j] >= 6) field[i][j] = 0;
        }
    }
}
/*����� ���� ����*/
void printField(int field[][10]){
    system("cls");
    printf ("   ");
    for (int i = 0; i < 10; i++) printf ("%c ", 'A' + i);
    printf ("\n   ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-\n");
    for (int i = 0; i < 10; i++){
        printf ("%2.i|", i + 1);
        /*������ �� ᨬ����*/
        for(int j = 0; j < 10; j++){
            printf ("%c ", skins[field[i][j]]);
        }
        printf ("|\n");
    }
    printf ("   ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-\n");
}
/*����� ��஢�� ����*/
void drawField(int firstField[][10], int secondField[][10], int firstAllShips, int secondAllShips){
    system("cls");
        printf ("      ������ �����");
    printf ("                  ������ �����\n   ");
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
                /*������ ���祭�� �� ᨬ����*/
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
                /*������ ���祭�� �� ᨬ����*/
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
    printf("��⠫��� �ᥣ� ���������: %i", firstAllShips);
    printf("       ��⠫��� �ᥣ� ���������: %i", secondAllShips);
}
/*����� 㭨�⮦���� ��ࠡ��*/
void kill(int fakeField[][10], int side, int backSide, int position, int x, int y){
    /*�᫨ �������㡭��*/
    if (!position) {
        fakeField[y][x] = 4;
        /*���㥬 ����� �������� ᨬ����*/
        printInvisibleSymbols(fakeField, 1, x, y);
    }
    /*��ਧ��⠫�� ��ࠡ��*/
    else if (position == 1){
        for (int i = x - backSide; i <= x + side; i++){
            fakeField[y][i] = 4;
        }
        /*���㥬 ����� �������� ᨬ����*/
        printInvisibleSymbols(fakeField, backSide + 1 + side, x - backSide, y);
    }
    /*���⨪���� ��ࠡ��*/
    else{
        for (int i = y - backSide; i <= y + side; i++){
            fakeField[i][x] = 4;
        }
        /*���㥬 ����� �������� ᨬ����*/
        printInvisibleSymbols(fakeField, backSide + 1 + side, x, y - backSide);
    }
}
/*�஢���� 㭨�⮦�� �� ��ࠡ��*/
int checkKill(int field[][10], int fakeField[][10], int x, int y){
    /*��।��塞 �� ����� �� �ᯮ����� ��ࠡ�� � �� ���� �� �� �������㡭�*/
    if ((field[y][x - 1] < 5 && field[y][x - 1] != 0 && x != 0) || (field[y][x + 1] != 0 && field[y][x + 1] < 5 && x != 9)){
        int left = 0, right = 0;// �ࠩ ��ࠡ�� �⭮��⥫쭮 �窨 ���������
        /*�஢���, ���⮦��� �� ���� ��� ��ࠡ��*/
        while (x - left >= 0 && field[y][x - left] != 0 && field[y][x - left] < 5){
            if (field[y][x - left] == 1) return 0;
            left++;
        }
        /*�஢���, ���⮦��� �� �ࠢ� ��� ��ࠡ��*/
        while (x + right <= 9 && field[y][x + right] != 0 && field[y][x + right] < 5){
            if (field[y][x + right] == 1) return 0;
            right++;
        }
        /*���㥬 㡨�� ��ࠡ��*/
        kill(fakeField, --right, --left, 1, x, y);
    }
    /*��।��塞 �� ����� �� �ᯮ����� ��ࠡ�� � �� ���� �� �� �������㡭�*/
    else if ((field[y - 1][x] < 5 && field[y - 1][x] != 0 && y != 0) || (field[y + 1][x] != 0 && field[y + 1][x] < 5 && y != 9)){
        int up = 0, down = 0;// �ࠩ ��ࠡ�� �⭮��⥫쭮 �窨 ���������
        /*�஢���, ���⮦��� �� ���孨� ��� ��ࠡ��*/
        while (y - up >= 0 && field[y - up][x] != 0 && field[y - up][x] < 5){
            if (field[y - up][x] == 1) return 0;
            up++;
        }
        /*�஢���, ���⮦��� �� ������ ��� ��ࠡ��*/
        while (y + down <= 9 && field[y + down][x] != 0 && field[y + down][x] < 5){
            if (field[y + down][x] == 1) return 0;
            down++;
        }
        /*���㥬 㡨�� ��ࠡ��*/
        kill(fakeField, --down, --up, 2, x, y);
    }
    /*�᫨ �� �������㡭��*/
    else kill(fakeField, 0, 0, 0, x, y);
    return 2;
}
/*�஢���� ����� �� ���⠢��� ����� ��ࠡ��*/
int checkShip(int field[][10], int lastField[][10], int x, int y, int typeShip, int position){
    /*�����뢠�� ��אַ㣮�쭨�,
    ����� ������ ���� ᢮����� ��� ࠧ��饭�� ��ࠡ��,
    ��⥬ �஢��塞 ������ �����*/
    int j, i, firstMaxCheck, secondMaxCheck; 
    /*�� ��ਧ��⠫�
    ��।��塞 ��砫�� � ������ ���न����*/
    if (position){
        j = y; 
        firstMaxCheck = 1 + y;
        i = x; 
        secondMaxCheck = typeShip + x;
    }
    /*�� ���⨪���
    ��।��塞 ��砫�� � ������ ���न����*/
    else {
        j = y; 
        firstMaxCheck = typeShip + y;
        i = x; 
        secondMaxCheck = x + 1;
    }
    /*�஢��塞 ���� �� �冷� �⥭�*/
        if (j != 0) j--;
        int last_j = j; // ���࠭塞 ��砫쭮� ���祭��
        if (i != 0) i--;
        /*�஢�ઠ ���⮪*/
        while(i <= secondMaxCheck && i <= 9){
            while(j <= firstMaxCheck && j <= 9){
                if (lastField[j][i] == 1 ) return 0;
                j++; 
            }
            i++;
            /*�����頥� ��砫쭮� ���祭��*/
            j = last_j;
        } 
    return 1;
}