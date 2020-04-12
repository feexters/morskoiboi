#include "stdio.h"
#include "ctype.h"
#include "stdlib.h" //��� �㭪樨 system()
#include "conio.h"// getch(), khbit()

//#define TEST_TWO_PLAYERS - ����� �ணࠬ�� � ०��� ���஢���� ��� ���� ��ப��

char skins [] = {'.', '#', '+', '*', 'X', 'O'}; // �����
int firstField[10][10], fakeFirstField[10][10];
int secondField[10][10], fakeSecondField[10][10];
int x = 4, y = 4; //���न���� ��� ��६�饭��
int player = 1; //����� 室�饣� ��ப� 
int gameover = 0; //��।���� ����� ����
int allShips1 = 0;// ���-�� ���⠢������ ��ࠡ���
int allShips2 = 0;// ���-�� ���⠢������ ��ࠡ���

int main();

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
        int last_j = j; 
        if (i != 0) i--;
        /*�஢�ઠ ���⮪*/
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
/*����⠢��� ��ࠡ��*/
void putShip(int field[][10], int typeShip){
    int result = 0;
    int position = 0;//1 - ��ਧ��⠫쭮, 0 - ���⨪��쭮
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
            case 'w'://�����
                /*�� ���⨪���*/
                if (!position){
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
                /*�� ��ਧ��⠫�*/
                if (position){
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
                /*�� ���⨪���*/
            case 's'://����
                if (!position){
                    field[y][x] = lastField[y][x];
                    y++;
                    for(int i = 0; i < typeShip; i++){
                        field[y + i][x] = 1;
                    }
                }
                /*�� ��ਧ��⠫�*/
                else{
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
                    field[y][x] = lastField[y][x];
                    x++;
                    for(int i = 0; i < typeShip; i++){
                        field[y][x + i] = 1;
                    }
                }
                /*�� ���⨪���*/
                else{
                    x++;
                    for(int i = 0; i < typeShip; i++){
                        field[y + i][x] = 1;
                        field[y + i][x - 1] = lastField[y + i][x - 1];
                    }
                }
                printField(field);
                break;
            case 'f'://ᬥ�� ���ࠢ����� ��ࠡ��
                if (!position) {
                    position = 1;
                    /*���ࠥ� ��譨� ᨬ���� �� ���⨪���*/
                    for (int i = 1; i < typeShip; i++){
                        field[y + i][x] = lastField[y + i][x];
                        field[y][x + i] = 1;
                    }
                    printField(field);
                }
                else {
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
/*�롮� ��ࠡ�� ��� ��᫥���饩 ���⠭����*/
void ships(int field[][10], int palyer){
    int ship1 = 4, ship2 = 3, ship3 = 2, ship4 = 1; // �ᥣ� ��ࠡ��� ������� ����
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
        printf("    �롥�� ⨯ ��ࠡ��\n\n");
        printf("1. �������㡭��. ��⠫���: %i\n", ship1);
        printf("2. ���寠�㡭��. ��⠫���: %i\n", ship2);
        printf("3. ��寠�㡭��. ��⠫���: %i\n", ship3);
        printf("4. �����寠�㡭��. ��⠫���: %i\n", ship4);
        switch(getchar()){
            case '1':
                if (ship1 != 0) {
                    putShip(field, 1);
                    ship1--;
                    result++;
                }
                else {
                    printf ("����� ��ࠡ�� �����稫���, �롥�� ��㣮� ⨯ ��ࠡ��.\n\n");
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
                    printf ("����� ��ࠡ�� �����稫���, �롥�� ��㣮� ⨯ ��ࠡ��.\n\n");
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
                    printf ("����� ��ࠡ�� �����稫���, �롥�� ��㣮� ⨯ ��ࠡ��.\n\n");
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
                    printf ("����� ��ࠡ�� �����稫���, �롥�� ��㣮� ⨯ ��ࠡ��.\n\n");
                    system("pause");
                } 
                break;
        }
    }
}
/*����� ��஢�� ����*/
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
            /*������ ���祭�� �� ᨬ����*/
            printf ("%c ", skins[fakeFirstField[i][j]]);
        }
        printf ("|     ");
        printf ("%2.i|", i + 1);
        for(int j = 0; j < 10; j++){
            /*������ ���祭�� �� ᨬ����*/
            printf ("%c ", skins[fakeSecondField[i][j]]);
        }
        printf ("|\n");
    }
    printf ("   ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-          ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-\n");
    #ifdef TEST_TWO_PLAYERS
        printf("��⠫��� ���������: %i\n", allShips1);
    #endif
}
/*�������� ���ᨢ �⠭����묨 ���祭�ﬨ*/
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
/*����� 㭨�⮦���� ��ࠡ��*/
void kill(int fakeField[][10], int side, int backSide, int line){
    /*�᫨ �������㡭��*/
    if (!line) fakeField[y][x] = 4;
    /*��ਧ��⠫�� ��ࠡ��*/
    else if (line == 1){
        for (int i = x - backSide; i <= x + side; i++){
            fakeField[y][i] = 4;
        }
    }
    /*���⨪���� ��ࠡ��*/
    else{
        for (int i = y - backSide; i <= y + side; i++){
            fakeField[i][x] = 4;
        }
    }
}
/*�஢���� 㭨�⮦�� �� ��ࠡ��*/
int checkKill(int field[][10], int fakeField[][10]){
    /*��।��塞 �� ����� �� �ᯮ����� ��ࠡ�� � �� ���� �� �� �������㡭�*/
    if ((field[y][x - 1] != 5 && field[y][x - 1] != 0 && x != 0) || (field[y][x + 1] != 0 && field[y][x + 1] != 5 && x != 9)){
        int left = 0, right = 0;// �ࠩ ��ࠡ�� �⭮��⥫쭮 �窨 ���������
        /*�஢���, ���⮦��� �� ���� ��� ��ࠡ��*/
        while (x - left >= 0 && field[y][x - left] != 0 && field[y][x - left] != 5){
            if (field[y][x - left] == 1) return 0;
            left++;
        }
        /*�஢���, ���⮦��� �� �ࠢ� ��� ��ࠡ��*/
        while (x + right <= 9 && field[y][x + right] != 0 && field[y][x + right] != 5){
            if (field[y][x + right] == 1) return 0;
            right++;
        }
        /*���㥬 㡨�� ��ࠡ��*/
        kill(fakeField, --right, --left, 1);
    }
    /*��।��塞 �� ����� �� �ᯮ����� ��ࠡ�� � �� ���� �� �� �������㡭�*/
    else if ((field[y - 1][x] != 5 && field[y - 1][x] != 0 && y != 0) || (field[y + 1][x] != 0 && field[y + 1][x] != 5 && y != 9)){
        int up = 0, down = 0;// �ࠩ ��ࠡ�� �⭮��⥫쭮 �窨 ���������
        /*�஢���, ���⮦��� �� ���孨� ��� ��ࠡ��*/
        while (y - up >= 0 && field[y - up][x] != 0 && field[y - up][x] != 5){
            if (field[y - up][x] == 1) return 0;
            up++;
        }
        /*�஢���, ���⮦��� �� ������ ��� ��ࠡ��*/
        while (y + down <= 9 && field[y + down][x] != 0 && field[y + down][x] != 5){
            if (field[y + down][x] == 1) return 0;
            down++;
        }
        /*���㥬 㡨�� ��ࠡ��*/
        kill(fakeField, --down, --up, 2);
    }
    /*�᫨ �� �������㡭��*/
    else kill(fakeField, 0, 0, 0);
}
/*��।���� ���� �� ���������*/
int shot(int field[][10], int fakeField[][10], int *allShips){
    /*�஬��*/
    if (field[y][x] == 0){
        field[y][x] = 5;
        fakeField[y][x] = 5;
        return 0;
    }
    /*�����*/
    else if (field[y][x] == 1) {
        field[y][x] = 3;
        fakeField[y][x] = field[y][x];
        /*�஢�ઠ �� 㡨��⢮*/
        checkKill(field, fakeField);
        /*����頥� ���-�� ��ࠡ���*/
        --*(allShips);
        return 1;
    }
    else {
        printf ("\n   �� 㦥 ��५﫨 � �� ����,");
        printf ("\n�롥�� ��㣮� � ������ ������.\n\n");
        return 2;
    }
}
int lastSymbol = 0; // ��砫쭮� ���祭�� ��� ��᫥����� ᨬ���� ����
/*����� ��६�饭�� ��楫�*/
int paintMove (int fakeField[][10], char choose){
    /*�஢��塞 ���ࠢ����� � ������⢨� ��室� �� �।��� ����*/
    /*�����*/
    if (choose == 'w' && y != 0) {
        fakeField[y][x] = lastSymbol;
        y--;
        }
    /*�����*/
    else if (choose == 'a' && x != 0) {
        fakeField[y][x] = lastSymbol;
        x--;
        }
    /*����*/
    else if (choose == 's' && y != 9) {
        fakeField[y][x] = lastSymbol;
        y++;}
    /*��ࠢ�*/
    else if (choose == 'd' && x != 9) {
        fakeField[y][x] = lastSymbol;
        x++;
        }
    /*��室 �� �।��� ����*/
    else return 0;
    lastSymbol = fakeField[y][x];
    fakeField[y][x] = 2;
    drawField();
}
/*��ࠢ����� �� �६� ��५��*/
void move(int field[][10], int fakeField[][10], int *allShips){
    int hit = 0; // ������� ��५��
    if (kbhit()){
        char choose = getch();
        /*������ ��६�饭�� ��楫�*/
        if (choose == 'w' || choose == 'a' || choose == 's' || choose == 'd') paintMove(fakeField, choose);
        /*�믮��塞 ��५��*/
        else if (choose = 'e'){
            hit = shot(field, fakeField, allShips);
            if (hit != 2) lastSymbol = fakeField[y][x];
            /*���塞 ��ப�*/
            if (!hit){
                if (player == 1) {
                    player = 2;
                    /*�����頥� ��砫�� ���祭�� ���न��⠬*/
                    x = 4;
                    y = 4; 
                    lastSymbol = fakeSecondField[y][x];
                }
                else {
                    player = 1;
                    /*�����頥� ��砫�� ���祭�� ���न��⠬*/
                    x = 4;
                    y = 4; 
                    lastSymbol = fakeFirstField[y][x];
                }
                drawField();
            }
         }
    }
}
/*����� ��� ���� ��ப��*/
void twoPlayers(){
    /*���㫥��� ����� � �뢮� ���ଠ樨*/
    startGame();
    system("cls");
    printf("         ������ ��ப ���⠢��� ��ࠡ��.\n");
    printf("��᫥���, �⮡� ��ன ��ப �� ᬮ�५ �� ������, \n");
    printf(" ���� �� �㤥� �����, ��� �ᯮ������ ��� ��ࠡ��.\n\n\n");
    system ("pause");
    /*����⠭���� ��ࠡ��� ��� ��ࢮ�� ��ப�*/
    ships(firstField, 1);
    allShips1 = 20;
    system("cls");
    #ifdef TEST_TWO_PLAYERS
        allShips1 = 10;
    #else 
        printf("         ������ ��ப ���⠢��� ��ࠡ��.\n");
        printf("��᫥���, �⮡� ���� ��ப �� ᬮ�५ �� ������, \n");
        printf(" ���� �� �㤥� �����, ��� �ᯮ������ ��� ��ࠡ��.\n\n\n");
        system ("pause");
        /*����⠭���� ��ࠡ��� ��� ��ண� ��ப�*/
        ships(secondField, 2);
    #endif
    allShips2 = 20;
    #ifdef TEST_TWO_PLAYERS
        /*�����뢠�� �ᯮ������� ��ࠡ���*/
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                fakeFirstField[i][j] = firstField[i][j];
            }
        }
    #endif
    drawField();
    lastSymbol = 0;
    /*��� �த�������� ���� �� ��������� ��ࠡ��*/
    while (allShips1 && allShips2){
        /*��� ��ப�*/
        if (player == 1) move(firstField, fakeFirstField, &allShips1);
        else move(secondField, fakeSecondField, &allShips2);
    }
    system ("cls");
    /*�����襭�� ���� � �뢮� १���⮢*/
    if (!allShips2){
        printf ("������� ������ ��ப!!!\n");
        printf ("    ����� ����\n\n");
        system("pause");
        main();
    }
    else{
        printf ("������� ��ன ��ப!!!\n");
        printf ("    ����� ����\n\n");
        system("pause");
        main();
    }
}
void onePlayer(){
    printf ("����...");
    int main();
}
int main(){
    /*���� ����*/
    system("cls");
    printf ("     ������� ���\n\n");
    printf (" �롥�� ०�� ����:\n\n");
    printf ("1. �����筠� ���\n");
    printf ("2. ��� ��ப�\n");
    printf ("3. ��室\n");
    switch (getchar()){
        case '1': 
            onePlayer();
            break;
        case '2': 
            twoPlayers();
            break;
        case '3':
            printf ("�� ����� �����!!!\n");
            system("pause");
            return 0;
            break;
        default: 
            printf ("�� ����� ����୮� ���祭��! ���஡�� �� ࠧ!\n");
            main();
            break;
    }
    system("pause");
}