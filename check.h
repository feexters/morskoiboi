#include <stdio.h>

int checkShip(int field[][10], int lastField[][10], int x, int y, int typeShip, int position);
int checkKill(int field[][10], int fakeField[][10], int x, int y);
void kill(int fakeField[][10], int side, int backSide, int line, int x, int y);