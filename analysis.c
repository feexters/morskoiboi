#include <stdio.h>
#include "stdlib.h"
#include "functions/morskoiboi.h"

/*����� ������ ���� �� �������� ���⠭����
        ���祭�� ���⪨:
6 - ����� ���⠢��� �� �� ��ਧ��⠫�
7 - ����� ���⠢��� �� ���⨪���
8 - �� ��� ��ਠ�� ���⠭����
9 - ���⠢��� ��ࠡ�� �����*/
int intelligenceAnalysis(int field[][10], int typeShip){
    /*������ �� ��ਧ��⠫�*/
    for(int y = 0; y < 10; y++){
        for(int x = 0; x <= 10 - typeShip; x++){
            /*�ய�᪠塞 �����室�騥*/
            if(field[y][x] == 0 || (field[y][x] >= 6 && field[y][x] <= 8)){
                 int i = 0;
                /*�஢��塞 ��� �����*/
                while ((field[y][x + i] == 0 || (field[y][x + i] >= 6 && field[y][x + i] <= 8)) && i < typeShip){
                    /*�����㥬 १���� �஢�ન, �᫨ ����� ���⠢���*/
                    if (i == typeShip - 1) field[y][x] = 6;
                    i++;
                }
            }
        }
    }
    /*������ �� ���⨪���*/
     for(int x = 0; x < 10; x++){
        for(int y = 0; y <= 10 - typeShip; y++){
            /*�ய�᪠塞 �����室�騥*/
            if(field[y][x] == 0 || (field[y][x] >= 6 && field[y][x] <= 8)){
                int i = 0;
                while ((field[y + i][x] == 0 || (field[y + i][x] >= 6 && field[y + i][x] <= 8)) && i < typeShip){
                    /*�����㥬 १���� �஢�ન, �᫨ ����� ���⠢���*/
                    if (i == typeShip - 1){
                        if (field[y][x] == 6) field[y][x] += 2;
                        else field[y][x] = 7;
                    }
                    i++;
                }
            }
        }
    }
}
/*������ ���� ����� ��ࠡ�� ��᫥ ��ࢮ�� ���������*/
int AnalysisForShot(int field[][10],int routes[], int minTypeShip, int maxTypeShip, int x, int y){
    /*����塞 ���祭��*/
    int positions = 0; // �� ����� �� �ᯮ����
    for (int i = 0; i < 4; i++) routes[i] = 0; 
    /*�஢��塞 ������⢮ ����㯭�� ��� ��५�� ���⮪ � 4-� ���ࠢ������*/
    for (int i = y + 1; i < y + maxTypeShip && field [i][x] != 5 && field[i][x] != 9 && i <= 9; i++) routes[0] ++; //����
    for (int i = y - 1; i > y - maxTypeShip && field [i][x] != 5 && field[i][x] != 9 && i >= 0; i--) routes[1] ++; //�����
    for (int i = x + 1; i < x + maxTypeShip && field [y][i] != 5 && field[y][i] != 9 && i <= 9; i++) routes[2] ++; //��ࠢ�
    for (int i = x - 1; i > x - maxTypeShip && field [y][i] != 5 && field[y][i] != 9 && i >= 0; i--) routes[3] ++; //�����
    /*�஢��� �������� ���ࠢ����� ࠧ��饭�� ��ࠡ��*/
    if (routes[0] + routes[1] >= minTypeShip - 1) positions ++;
    if (routes[2] + routes[3] >= minTypeShip - 1) positions += 2;
    #ifdef TEST_AI
        printf("\n�������� ���ࠢ�����: %i, %i, %i, %i", routes[0], routes[1], routes[2], routes[3]);
    #endif
    return positions;
}