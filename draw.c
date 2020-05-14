#include "functions/morskoiboi.h"

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
    printf("  ��⠫��� ���������: %i", firstAllShips);
    printf("       ��⠫��� ���������: %i\n\n", secondAllShips);
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

/*����� ��६�饭�� ��楫�*/
int paintMove (int fakeField[][10], char choose, int *lastSymbol, int *x, int *y){
    /*�஢��塞 ���ࠢ����� � ������⢨� ��室� �� �।��� ����*/
    /*�����*/
    if (choose == 'w' && *y != 0) {
        fakeField[*y][*x] = *lastSymbol;
        --(*y);
        }
    /*�����*/
    else if (choose == 'a' && *x != 0) {
        fakeField[*y][*x] = *lastSymbol;
        --(*x);
        }
    /*����*/
    else if (choose == 's' && *y != 9) {
        fakeField[*y][*x] = *lastSymbol;
        ++(*y);}
    /*��ࠢ�*/
    else if (choose == 'd' && *x != 9) {
        fakeField[*y][*x] = *lastSymbol;
        ++(*x);
        }
    /*��室 �� �।��� ����*/
    else return 0;
    *lastSymbol = fakeField[*y][*x];
    fakeField[*y][*x] = 2;
    draw();
}
