/*gcc morb.c CheckAndDraw.c - ���������*/
#include <stdio.h>
#include "ctype.h"
#include "time.h"
#include "stdlib.h" //��� �㭪樨 system(), rand()
#include "conio.h" // getch(), khbit()
/*������⥪� � �㭪�ﬨ ��� �ᮢ���� �����
� �஢�ப �᫮���*/
#include "functions/CheckAndDraw.h"
//#define TEST //- ����� �ணࠬ�� � ०��� ���஢����
//#define TEST //- ����� �ணࠬ�� � ०��� ���஢���� ��

struct player{
    int field[10][10];// ���� � ��ࠡ�ﬨ
    int fakeField[10][10];// �뢮����� ����
    int allShips;// ���-�� ���⠢������ ��ࠡ���
} players[2];
int x = 4, y = 4; //���न���� ��� ��६�饭��
int player = 0; //����� 室�饣� ��ப� 
int lastSymbol = 0; // ��砫쭮� ���祭�� ��� ��᫥����� ᨬ���� ����

int main();
void draw(){
    drawField(players[0].field, players[1].field);
}
/*���㥬 �������� ᨬ����, �����騥 ���⠢��� ��ࠡ�� �� �� ����*/
void printInvisibleSymbols(int field[][10], int typeShip){
        /*�����뢠�� ��אַ㣮�쭨� ����� ��ࠡ��,
    ��⥬ ������� �������묨 ᨬ������*/
    int j, i, firstMaxCheck, secondMaxCheck; 
    /*�� ��ਧ��⠫�
    ��।��塞 ��砫�� � ������ ���न����*/
    if (field[y][x+1] == 1){
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
            if (field[j][i] != 1) field[j][i] = 9;
            j++;
        }
        i++;
        j = last_j;
    } 
}
/*�⠢�� ��ࠡ��*/
void intelligencePutShip(int field[][10], int typeShip){
    int i = 0;
    int allPositions = 0, choosePosition, route; 
    int canPut[100]; //����ন� ����㯭� ���� ��� ���⠭���� 
    /*�롨ࠥ� ���室�騥 ����*/
    #ifdef TEST_AI
        printf("\n����㯭� ���न����: ");
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
    /*�������� �롨ࠥ� ���� �� ����㯭��� ᯨ᪠*/
    choosePosition = canPut[rand()%(allPositions)];
    /*�롨ࠥ� �� ���⨪��� ��� ��ਧ��⠫�*/
    x = choosePosition % 10;
    y = choosePosition / 10;
    if (field[y][x] == 8) route = rand()%2;
    else route = field[y][x] - 6;
    /*���㥬 ��ࠡ��*/
    if (route){
        for(int j = y; j < y + typeShip; j++) field[j][x] = 1;
    } 
    else {
        for(int j = x; j < x + typeShip; j++) field[y][j] = 1;
    }
    printInvisibleSymbols(field, typeShip);
    #ifdef TEST_AI
        printf("\n��࠭��� ������: %i\n", choosePosition);
        printf("x: %i\n", x);
        printf("y: %i\n", y);
        printf("���ࠢ�����: %i\n", route);
        system("pause");
    #endif  
}
/*����� ������ ���� �� �������� ���⠭����
        ���祭�� ���⪨:
6 - ����� ���⠢��� �� �� ��ਧ��⠫�
7 - ����� ���⠢��� �� ���⨪���
8 - �� ��� ��ਠ�� ���⠭����
9 - ���⠢��� ��ࠡ�� �����*/
int intelligenceAnalysis(int field[][10], int typeShip){
    /*������ �� ��ਧ��⠫�*/
    for(y = 0; y < 10; y++){
        for(x = 0; x <= 10 - typeShip; x++){
            /*�ய�᪠塞 �����室�騥*/
            if(field[y][x] != 9 && field[y][x] != 9){
                /*�����㥬 १���� �஢�ન*/
                if (checkShip(field, field, x, y, typeShip, 1))
                    field[y][x] = 6;
            }
        }
    }
    /*������ �� ���⨪���*/
     for(int x = 0; x < 10; x++){
        for(int y = 0; y <= 10 - typeShip; y++){
            /*�ய�᪠塞 �����室�騥*/
            if(field[y][x] != 9 && field[y][x] != 9){
                /*�����㥬 १���� �஢�ન*/
                if (checkShip(field, field, x, y, typeShip, 0)){
                    if (field[y][x] == 6) field[y][x] += 2;
                    else field[y][x] = 7;
                }
            }
        }
    }
}
/*�롮� ��ࠡ��*/
void intelligenceShips(int field[][10]){
    /*��ࠡ�� ��� ���⠭���� �ᯮ������ � ���浪� ��饭�� ���᪠ ����*/
    int ships [] ={4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; 
    /*����⠭���� ��ࠡ���*/
    for (int i = 0; i < 10; i++){
        printf("%i", i);
        intelligenceAnalysis(field, ships[i]);
        #ifdef TEST_AI
        draw();
        system("pause");
        #endif
        intelligencePutShip(field, ships[i]);
        #ifdef TEST_AI
        draw();
        system("pause");
        #endif
        clearField(field);
    }
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
void ships(int field[][10]){
    int ships[] = {4, 3, 2, 1}; // �ᥣ� ��ࠡ��� ������� ����
    #ifdef TEST
        for (int i = 0; i < 4; i++){
            ships[i] = 1;
        }
    #endif
    int result = 0;
    #ifdef TEST
        result = 10;
    #elif TEST_AI
        result = 20;
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
    draw();
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
                draw();
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
        move(players[player].field, players[player].fakeField, &players[player].allShips);
    }
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
    startGame();
    system("cls");
    printf("         ��� ��砫� ���� �� ������ ���⠢��� ᢮� ��ࠡ��.\n");
    system ("pause");
    /*����⠭���� ��ࠡ��� ��ப��*/
    ships(players[0].field);
    players[0].allShips = 20;
    system("cls");
    #ifdef TEST
        players[0].allShips = 10;
    #endif
    /*����⠭���� ��ࠡ��� �������஬*/
    intelligenceShips(players[1].field);
    players[1].allShips = 20;
    #ifdef TEST
        /*�����뢠�� �ᯮ������� ��ࠡ���*/
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                players[0].fakeField[i][j] = players[0].field[i][j];
                players[1].fakeField[i][j] = players[1].field[i][j];
            }
        }
    #elif TEST_AI
        /*�����뢠�� �ᯮ������� ��ࠡ���*/
        for (int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                players[1].fakeField[i][j] = players[1].field[i][j];
            }
        }
    #endif
    draw();
    system("pause");
    lastSymbol = 0;
    /*��� �த�������� ���� �� ��������� ��ࠡ��*/
    //while (players[0].allShips && players[1].allShips){
        /*��� ��ப�*/
        //if (!player) move(players[player].field, players[player].fakeField, &players[player].allShips);
        /*��� ��������*/
        //else intelligenceShot(player[player]);
   // }
    system ("cls");
    /*�����襭�� ���� � �뢮� १���⮢*/
    if (!players[0].allShips){
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