#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<windows.h>
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y);
	printf(" <-0-> ");
}
void erase_ship(int x, int y)
{
	system("cls");
}
int main()
{
	char ch = ' ';
	int x = 38, y = 20;
	
	draw_ship(x, y);

	do {
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 'a' && x >= 1)
			{
				draw_ship(--x, y);
			}
			if (ch == 'd' && x <= 80)
			{
				draw_ship(++x, y);
			}
			if (ch == 's' && y <= 23)
			{
				erase_ship(x, y);
				draw_ship(x, ++y);
			}
			if (ch == 'w' && y >= 1)
			{
				erase_ship(x, y);
				draw_ship(x, --y);
			}
			fflush(stdin);
		}
		Sleep(10);
	} while (ch != 'x');


	return 0;
}