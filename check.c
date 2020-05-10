#include <stdio.h>
#include "stdlib.h"
#include "functions/morskoiboi.h"


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
/*��।���� ���� �� ���������*/
int shot(int field[][10], int fakeField[][10], int *allShips, int x, int y){
    /*�஬��*/
    int result = 0; // १���� ����५�
    if (field[y][x] == 0 || field[y][x] >= 6){
        field[y][x] = 5;
        fakeField[y][x] = 5;
        return result;
    }
    /*�����*/
    else if (field[y][x] == 1) {
        field[y][x] = 3;
        fakeField[y][x] = field[y][x];
        /*�஢�ઠ �� 㡨��⢮*/
        result = checkKill(field, fakeField, x, y);
        /*����頥� ���-�� ��ࠡ���*/
        --*(allShips);
        return result + 1;
    }
    else {
        printf ("\n   �� 㦥 ��५﫨 � �� ����,");
        printf ("\n�롥�� ��㣮� � ������ ������.\n\n");
        result = 2;
        return result;
    }
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