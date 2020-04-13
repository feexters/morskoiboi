//gcc morb.c check.c - ���������
#include "stdio.h"
#include "ctype.h"
#include "check.h"// checkKill & checkShip
#include "stdlib.h" //��� �㭪樨 system()
#include "conio.h"// getch(), khbit()


//#define TEST_TWO_PLAYERS //- ����� �ணࠬ�� � ०��� ���஢���� ��� ���� ��ப��

struct player{
    int field[10][10];// ���� � ��ࠡ�ﬨ
    int fakeField[10][10];// �뢮����� ����
    int allShips;// ���-�� ���⠢������ ��ࠡ���
} players[2];
char skins [] = {'.', '#', '+', '*', 'X', 'O'}; // �����
int x = 4, y = 4; //���न���� ��� ��६�饭��
int player = 0; //����� 室�饣� ��ப� 

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
/*�롮� ��ࠡ�� ��� ��᫥���饩 ���⠭����*/
void ships(int field[][10], int palyer){
    int ships[] = {4, 3, 2, 1}; // �ᥣ� ��ࠡ��� ������� ����
    #ifdef TEST_TWO_PLAYERS
        for (int i = 0; i < 4; i++){
            ships[i] = 1;
        }
    #endif
    int result = 0;
    #ifdef TEST_TWO_PLAYERS
        result = 10;
    #endif
    while (result < 20){
        system("cls");
        printf("    �롥�� ⨯ ��ࠡ��\n\n");
        printf("1. �������㡭��. ��⠫���: %i\n", ships[0]);
        printf("2. ���寠�㡭��. ��⠫���: %i\n", ships[1]);
        printf("3. ��寠�㡭��. ��⠫���: %i\n", ships[2]);
        printf("4. �����寠�㡭��. ��⠫���: %i\n", ships[3]);
        char choose = getch();
        if (choose <= '4' && choose >= '1'){
                if (ships[choose - '0' - 1] != 0){
                    putShip(field, choose - '0');
                    ships[choose - '0' - 1]--;
                    result += choose - '0';
                }
                else {
                printf ("����� ��ࠡ�� �����稫���, �롥�� ��㣮� ⨯ ��ࠡ��.\n\n");
                system("pause");
            }
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
            printf ("%c ", skins[players[0].fakeField[i][j]]);
        }
        printf ("|     ");
        printf ("%2.i|", i + 1);
        for(int j = 0; j < 10; j++){
            /*������ ���祭�� �� ᨬ����*/
            printf ("%c ", skins[players[1].fakeField[i][j]]);
        }
        printf ("|\n");
    }
    printf ("   ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-          ");
    for (int i = 0; i < 9; i++) printf ("--");
    printf ("-\n");
    #ifdef TEST_TWO_PLAYERS
        printf("��⠫��� ���������: %i\n", players[0].allShips);
    #endif
}
/*�������� ���ᨢ �⠭����묨 ���祭�ﬨ*/
void startGame(){
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            players[0].field[i][j] = 0;
            players[1].field[i][j] = 0;
            players[0].fakeField[i][j] = 0;
            players[1].fakeField[i][j] = 0;
        }
    }
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
        checkKill(field, fakeField, x, y);
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
                if (player == 0) player = 1;
                else player = 0;
                    /*�����頥� ��砫�� ���祭�� ���न��⠬*/
                    x = 4;
                    y = 4; 
                    lastSymbol = players[player].fakeField[y][x];
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
    ships(players[0].field, 1);
    players[0].allShips = 20;
    system("cls");
    #ifdef TEST_TWO_PLAYERS
        players[0].allShips = 10;
    #else 
        printf("         ������ ��ப ���⠢��� ��ࠡ��.\n");
        printf("��᫥���, �⮡� ���� ��ப �� ᬮ�५ �� ������, \n");
        printf(" ���� �� �㤥� �����, ��� �ᯮ������ ��� ��ࠡ��.\n\n\n");
        system ("pause");
        /*����⠭���� ��ࠡ��� ��� ��ண� ��ப�*/
        ships(players[1].field, 2);
    #endif
    players[1].allShips = 20;
    #ifdef TEST_TWO_PLAYERS
        /*�����뢠�� �ᯮ������� ��ࠡ���*/
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                players[0].fakeField[i][j] = players[0].field[i][j];
            }
        }
    #endif
    drawField();
    lastSymbol = 0;
    /*��� �த�������� ���� �� ��������� ��ࠡ��*/
    while (players[0].allShips && players[1].allShips){
        /*��� ��ப�*/
        move(players[player].field, players[player].fakeField, &players[player].allShips);
    }
    system ("cls");
    /*�����襭�� ���� � �뢮� १���⮢*/
    if (!players[1].allShips){
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