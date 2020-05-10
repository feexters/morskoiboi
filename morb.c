/*gcc morb.c check.c draw.c computer.c analysis.c - ���������*/
#include <stdio.h>
#include "ctype.h"
#include "time.h"
#include "stdlib.h" //��� �㭪樨 system(), rand()
/*������⥪� � �㭪�ﬨ ��� ����*/
#include "functions/morskoiboi.h"
//#define TEST //- ����� �ணࠬ�� � ०��� ���஢����
//#define TEST_AI //- ����� �ணࠬ�� � ०��� ���஢���� ��

struct player players[2];
struct memory memoryAI;

int x = 4, y = 4; //���न���� ��� ��६�饭��
int player = 0; //����� 室�饣� ��ப� 
int lastSymbol = 0; // ��砫쭮� ���祭�� ��� ��᫥����� ᨬ���� ����

int main();

/*����� ��஢�� ����*/
void draw(){
    drawField(players[0].fakeField, players[1].fakeField, players[0].allShips, players[1].allShips);
}
/*�뢮� �ࠢ�� ����*/
void rules(){
    system("cls");
    char symbol;
    /*����⨥ 䠩�� � �ࠢ�����*/
    FILE *rules;
    rules = fopen("rules.txt", "r");
    /*�뢮� �ࠢ��*/
    while ((symbol = fgetc(rules)) != EOF) printf ("%c", symbol);
    fclose(rules);
    printf("\n");
    system("pause");
    main();
}
/*�롮� ��ࠡ�� ��� ��᫥���饩 ���⠭����*/
void ships(int field[][10]){
    int ships[] = {4, 3, 2, 1}; // �ᥣ� ��ࠡ��� ������� ����
    int result = 0;
    #ifdef TEST
        for (int i = 0; i < 4; i++){
            ships[i] = 1;
        }
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
            /*�᫨ ⠪�� ��ࠡ�� ��⠫�� � ���室 � ���⠭����*/
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
/*�������� ���ᨢ �⠭����묨 ���祭�ﬨ*/
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
        /*������塞 �������� �⠭����묨 ���祭�ﬨ*/
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
/*����� ��� ���� ��ப��*/
void twoPlayers(){
    /*���㫥��� ����� � �뢮� ���ଠ樨*/
    startGame(0);
    system("cls");
    printf("         ������ ��ப ���⠢��� ��ࠡ��.\n");
    printf("��᫥���, �⮡� ��ன ��ப �� ᬮ�५ �� ������, \n");
    printf(" ���� �� �㤥� �����, ��� �ᯮ������ ��� ��ࠡ��.\n\n\n");
    system ("pause");
    /*����⠭���� ��ࠡ��� ��� ��ࢮ�� ��ப�*/
    ships(players[0].field);
    players[0].allShips = 20;
    system("cls");
    #ifdef TEST
        players[0].allShips = 10;
    #else 
        printf("         ������ ��ப ���⠢��� ��ࠡ��.\n");
        printf("��᫥���, �⮡� ���� ��ப �� ᬮ�५ �� ������, \n");
        printf(" ���� �� �㤥� �����, ��� �ᯮ������ ��� ��ࠡ��.\n\n\n");
        system ("pause");
        /*����⠭���� ��ࠡ��� ��� ��ண� ��ப�*/
        ships(players[1].field);
    #endif
    players[1].allShips = 20;
    #ifdef TEST
        /*�����뢠�� �ᯮ������� ��ࠡ���*/
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                players[0].fakeField[i][j] = players[0].field[i][j];
            }
        }
    #endif
    draw();
    lastSymbol = 0;
    /*��� �த�������� ���� �� ��������� ��ࠡ��*/
    while (players[0].allShips && players[1].allShips){
        /*��� ��ப�*/
        move(players[!player].field, players[!player].fakeField, &players[!player].allShips, &lastSymbol, &x, &y, &player, players);
    }
    draw();
    system("pause");
    system ("cls");
    /*�����襭�� ���� � �뢮� १���⮢*/
    if (!players[0].allShips){
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
/*�����筠� ��� ��� �������*/
void onePlayer(){
    /*���㫥��� ����� � �뢮� ���ଠ樨*/
    startGame(1);
    system("cls");
    printf("\n\n\n           ��� ��砫� ����\n");
    printf("      �� ������ ���⠢��� ᢮� ��ࠡ��.\n\n\n");
    system ("pause");
    /*����⠭���� ��ࠡ��� ��ப��*/
    ships(players[0].field);
    players[0].allShips = 20;
    system("cls");
    /*����⠭���� ��ࠡ��� �������஬*/
    intelligenceShips(players);
    players[1].allShips = 20;
    #ifdef TEST
        /*�����뢠�� �ᯮ������� ��ࠡ���*/
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                players[1].fakeField[i][j] = players[1].field[i][j];
            }
        }
        players[0].allShips = 10;
    #elif TEST_AI
        /*�����뢠�� �ᯮ������� ��ࠡ���*/
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
    x = 4;
    y = 4;
    /*��� �த�������� ���� �� ��������� ��ࠡ��*/
    while (players[0].allShips && players[1].allShips){
        /*��� ��ப�*/
        if (!player) {
            #ifdef TEST_AI
                player = 1;
            #else 
                move(players[!player].field, players[!player].fakeField, &players[!player].allShips, &lastSymbol, &x, &y, &player, players);
            #endif
        }
        /*��� ��������*/
        else {
            if (!intelligenceShot(&memoryAI, players, x, y)){
                player = 0; // ����塞 ��ப��
                /*�����頥� ��砫�� ���祭�� ���न��⠬*/
                x = 4;
                y = 4; 
                lastSymbol = players[1].fakeField[y][x]; 
            }
        }
    }
    draw();
    system ("pause");
    #ifdef TEST_AI
        draw();
        system("pause");
        printf("\n���������: %i\n", memoryAI.minTypeShip);
            printf("���ᨬ����: %i\n", memoryAI.maxTypeShip);
            printf ("��⠫��� ��ࠡ���: ");
            for(int i = 0; i < 4; i++) printf("%i ", memoryAI.typeShip[i]);
            system("pause");
    #endif
    system ("cls");
    /*�����襭�� ���� � �뢮� १���⮢*/
    if (!players[1].allShips){
        printf ("     ������!!!\n");
        printf ("    ����� ����\n\n");
        system("pause");
        main();
    }
    else{
        printf ("   ���������!!!\n");
        printf ("    ����� ����\n\n");
        system("pause");
        main();
    }
}
int main(){
    srand(time(NULL));// ��� �����樨 �ᥢ�� ��砩��� �ᥫ
    /*���� ����*/
    system("cls");
    printf ("     ������� ���\n\n");
    printf (" �롥�� ०�� ����:\n\n");
    printf ("1. �����筠� ���\n");
    printf ("2. ��� ��ப�\n");
    printf ("3. �ࠢ��� ����\n");
    printf ("4. ��室\n");
    switch (getchar()){
        case '1': 
            onePlayer();
            break;
        case '2': 
            twoPlayers();
            break;
        case '3':
            rules();
            break;
        case '4':
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