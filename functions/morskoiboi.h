#include <stdio.h>
#include "stdlib.h"
#include "conio.h"
#include "time.h"
#include "ctype.h"

/*�࠭�� ���ଠ�� �� ��ப��*/
struct player{
    int field[10][10];      // ���� � ��ࠡ�ﬨ
    int fakeField[10][10];  // �뢮����� ����
    int allShips;           // ���-�� ���⠢������ ��ࠡ���
};

/*������� ��� �࠭���� ���ଠ樨�
��� ���᫥��� �ᯮ������� ��ࠡ�� � ��� 㡨��⢠*/
struct memory{
    int lastShot;       // ������� ��᫥����� ����५�
    int routes[4];      // �������� ���� �⭮�⥫쭮 ���� ��������� 
    int position;       // �� ����� �� ����� �ᯮ�������� ��ࠡ��
    int firstHit[2];    // ��ࢮ� ���������
    int allHits;        // �ᥣ� ���������
    int typeShip[4];    //��⠢訥�� ⨯� ��ࠡ��� � ��⨢����
    int minTypeShip;    // ��������� ࠧ��� ��ࠡ��
    int maxTypeShip;    // ���ᨬ���� ࠧ��� ��ࠡ��
} memoryAI;

////////////////////////       main.c       ////////////////////////////////////////////

/*���饭�� �맮� drawField � �⠭����묨 ���祭�ﬨ*/
void draw();

////////////////////////       moving.c       ////////////////////////////////////////////

/*����⠢��� ��ࠡ��*/
void putShip(int field[][10], int typeShip);

/*��ࠢ����� �� �६� ��५��*/
void move(int field[][10], int fakeField[][10], int *allShips, int *lastSymbol, int *x, int *y, int *player, struct player players[]);

/*��६�饭�� � ����*/
int menuNavigation(int totalPoints, int *choosePoint);

////////////////////////       draw.c       ////////////////////////////////////////////

/*����� ���� ����*/
void printField(int field[][10]);

/*����� 㭨�⮦���� ��ࠡ��*/
void kill(int fakeField[][10], int side, int backSide, int line, int x, int y);

/*����� ��६�饭�� ��楫�*/
int paintMove (int fakeField[][10], char choose, int *lastSymbol, int *x, int *y);

/*����� ��஢�� ����*/
void drawField(int firstField[][10], int secondField[][10], int firstAllShips, int secondAllShips);

/*���⪠ ���� �� "����"*/
void clearField(int field[][10]);

/*����� �������� ᨬ����*/
void printInvisibleSymbols(int field[][10], int typeShip, int x, int y);

////////////////////////       check.c       ////////////////////////////////////////////

/*�஢���� ����� �� ���⠢��� ����� ��ࠡ��*/
int checkShip(int field[][10], int lastField[][10], int x, int y, int typeShip, int position);

/*�஢���� 㭨�⮦�� �� ��ࠡ��*/
int checkKill(int field[][10], int fakeField[][10], int x, int y);

/*�஢���� ���� �� ���������*/
int shot(int field[][10], int fakeField[][10], int *allShips, int x, int y);

////////////////////////       analysis.c       ////////////////////////////////////////////

/*������ ���� ����� ��ࠡ�� ��᫥ ��ࢮ�� ���������*/
int AnalysisForShot(int field[][10],int routes[], int minTypeShip, int maxTypeShip, int x, int y);

/*����� ������ ���� �� �������� ���⠭����
        ���祭�� ���⪨:
6 - ����� ���⠢��� �� �� ��ਧ��⠫�
7 - ����� ���⠢��� �� ���⨪���
8 - �� ��� ��ਠ�� ���⠭����
9 - ���⠢��� ��ࠡ�� �����*/
int intelligenceAnalysis(int field[][10], int typeShip);

////////////////////////       computer.c       ////////////////////////////////////////////

/*�⠢�� ��ࠡ��*/
void intelligencePutShip(int field[][10], int typeShip);

/*�������� ��ࠡ�� �� ᯨ᪠*/
void remainingShips(struct memory *memoryAI, int killTypeShip);

/*�᫨ ��������� �뫮 �� ᬥ�⥫��, 
� �㭪�� �㤥� ��������, ������ 㣠���� �ᯮ������� ��ࠡ��*/
int intelligenceRoadToKill(struct memory *memoryAI, struct player players[], int x, int y);

/*��५졠 ��*/
int intelligenceShot(struct memory *memoryAI, struct player players[], int x, int y);

/*�롮� ��ࠡ��*/
void intelligenceShips(struct player players[]);