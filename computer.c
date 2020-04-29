#include <stdio.h>
#include "stdlib.h"
#include "functions/morskoiboi.h"

/*�롮� ��ࠡ��*/
void intelligenceShips(struct player players[]){
    /*��ࠡ�� ��� ���⠭���� �ᯮ������ � ���浪� ��饭�� ���᪠ ����*/
    int ships [] ={4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; 
    /*����⠭���� ��ࠡ���*/
    for (int i = 0; i < 10; i++){
        printf("%i", i);
        intelligenceAnalysis(players[1].field, ships[i]);
        #ifdef TEST_AI
        drawField(players[0].fakeField, players[1].field, players[0].allShips, players[1].allShips);
        system("pause");
        #endif
        intelligencePutShip(players[1].field, ships[i]);
        #ifdef TEST_AI
        drawField(players[0].fakeField, players[1].field, players[0].allShips, players[1].allShips);
        system("pause");
        #endif
        clearField(players[1].field);
    }
}
/*�᫨ ��������� �뫮 �� ᬥ�⥫��, 
� �㭪�� �㤥� ��������, ������ 㣠���� �ᯮ������� ��ࠡ��*/
int intelligenceRoadToKill(struct memory *memoryAI, struct player players[], int x, int y){
    int canShot[4];// ���� ��� ��५��
    int allPlaces = 0; // �ᥣ� ��� ��� ��५��
    int chosePlace, result; // ��࠭��� ����, १���� ��५��
    #ifdef TEST_AI
        printf("\n�������� ���ࠢ�����:");
        for (int i = 0; i < 4; i++) printf(" %i", memoryAI->routes[i]);
        printf("\n");
    #endif
    /*��।��塞 ����㯭� ���ࠢ����� ��� ��५��*/
    if (memoryAI->position == 1 || memoryAI->position == 3){
        /*����*/
        if(memoryAI->routes[0]) 
            canShot[allPlaces++] = 1;
        /*�����*/
        if(memoryAI->routes[1]) 
            canShot[allPlaces++] = 2;
    }
    if (memoryAI->position == 2 || memoryAI->position == 3){
        /*��ࠢ�*/
        if(memoryAI->routes[2]) 
            canShot[allPlaces++] = 3;
        /*�����*/
        if(memoryAI->routes[3]) 
            canShot[allPlaces++] = 4;
    }
    /*�롨ࠥ� ���ࠢ����� � ������ ��砫�� ���न����*/
    chosePlace = canShot[rand()%allPlaces];
    y = memoryAI->firstHit[0];
    x = memoryAI->firstHit[1]; 
    /*��५塞 ����*/
    if(chosePlace == 1){
        while(players[0].fakeField[++y][x] == 3);
    }
    /*��५塞 �����*/
    else if(chosePlace == 2){
        while(players[0].fakeField[--y][x] == 3);
    }
    /*��५塞 ��ࠢ�*/
    else if(chosePlace == 3){
        while(players[0].fakeField[y][++x] == 3);
    }
    /*��५塞 �����*/
    else {
        while(players[0].fakeField[y][--x] == 3);
    }
    #ifdef TEST_AI
        printf("\n����㯭� ���ࠢ�����: ");
        for(int i = 0; i < allPlaces; i++)
            printf("%i ", canShot[i]);
        printf("\n��࠭��� ���ࠢ�����: %i", chosePlace);
        printf("\n��࠭��� ����: y = %i, x = %i", y, x);
        system("pause");
        drawField(players[0].field, players[1].fakeField, players[0].allShips, players[1].allShips);
    #endif
    result = shot(players[0].field, players[0].fakeField, &players[0].allShips, x, y);
    /*�஬��*/
    if (!result) {
        memoryAI->routes[chosePlace - 1] = 0;
    }
    /*����*/
    else if (result == 3){
            memoryAI->lastShot = 0;
            memoryAI->position = 0;
            remainingShips(memoryAI, ++memoryAI->allHits);
            memoryAI->allHits == 0;
            for (int i = 0; i < 4; i++) memoryAI->routes[i] = 0;;
    }
    /*�����*/
    else if (result == 1) {
        memoryAI->allHits++;
        memoryAI->routes[chosePlace - 1]--;
        if(chosePlace - 1 == 0 || chosePlace - 1 == 1) memoryAI->position = 1;
        else memoryAI->position = 2;
    }
    return result;
}
/*��५졠 ��*/
int intelligenceShot(struct memory *memoryAI, struct player players[], int x, int y){
    int result; //१���� ����५�
    /*�᫨ ���� �������� ��ࠡ��*/
    if (memoryAI->lastShot == 1) result = intelligenceRoadToKill(memoryAI, players, x, y);
    /*��ᯮ������� ��ࠡ�� �������⭮*/
    else {
        /*����� ������ ����*/
        intelligenceAnalysis(players[0].fakeField, memoryAI->minTypeShip);
        #ifdef TEST_AI
            drawField(players[0].fakeField, players[1].fakeField, players[0].allShips, players[1].allShips);
            system("pause");
        #endif
        int canShot[99];// �������� ���� ��� ��५��
        int allPlaces = 0;//���-�� ����㯭�� ����
        int chosePlace; //��࠭��� ���� ��� ��५��
        /*���� ����㯭�� ����*/
        for (int i = 0; i < 100; i++){
            if (players[0].fakeField[i/10][i%10] >= 6 && players[0].fakeField[i/10][i%10] <= 8) {
                canShot[allPlaces++] = i;
            }
        }
        /*�롮� ���� ࠭�����*/
        chosePlace = canShot[rand()%allPlaces];
        x = chosePlace % 10;
        y = chosePlace / 10;
        /*������� ��५��*/
        result = shot(players[0].field, players[0].fakeField, &players[0].allShips, x, y);
        if (!result) {
        }
        /*�����㥬 ���������*/
        else if (result == 1){
            memoryAI->firstHit[0] = y;
            memoryAI->firstHit[1] = x;
            memoryAI->lastShot = 1;
            memoryAI->allHits = 1;
            memoryAI->position = AnalysisForShot(players[0].fakeField, memoryAI->routes, memoryAI->minTypeShip, memoryAI->maxTypeShip, x, y);
        }
        /*����*/
        else remainingShips(memoryAI, 1);
        clearField(players[0].fakeField);
    }
    return result;
}
/*�������� ��ࠡ�� �� ᯨ᪠*/
void remainingShips(struct memory *memoryAI, int killTypeShip){
    /*㤠�塞 ��ࠡ��*/
    memoryAI->typeShip[killTypeShip - 1]--;
    int i = 0, j = 3;
    /*���� ���ᨬ����� � ���������� ��ࠡ���*/
    while(!memoryAI->typeShip[i] && i < 4) i++;
    while(!memoryAI->typeShip[j] && j >= 0) j--;
    memoryAI->minTypeShip = ++i;
    memoryAI->maxTypeShip = ++j;
}
/*�⠢�� ��ࠡ��*/
void intelligencePutShip(int field[][10], int typeShip){
    int i = 0;
    int allPositions = 0, chosePosition, route; 
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
    chosePosition = canPut[rand()%(allPositions)];
    /*�롨ࠥ� �� ���⨪��� ��� ��ਧ��⠫�*/
    int x = chosePosition % 10;
    int y = chosePosition / 10;
    if (field[y][x] == 8) route = rand()%2;
    else route = field[y][x] - 6;
    /*���㥬 ��ࠡ��*/
    if (route){
        for(int j = y; j < y + typeShip; j++) field[j][x] = 1;
    } 
    else {
        for(int j = x; j < x + typeShip; j++) field[y][j] = 1;
    }
    printInvisibleSymbols(field, typeShip, x, y);
    #ifdef TEST_AI
        printf("\n��࠭��� ������: %i\n", chosePosition);
        printf("x: %i\n", x);
        printf("y: %i\n", y);
        printf("���ࠢ�����: %i\n", route);
        system("pause");
    #endif  
}