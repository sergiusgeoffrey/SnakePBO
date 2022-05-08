#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;
void gotoxy(int a, int b)
{
	COORD k = { a, b };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), k);
}
class CSegment
{
public:
	int X, Y;
	char Alphabet;
	CSegment(int a = 0, int b = 0, char c = NULL)
	{
		X = a;
		Y = b;
		Alphabet = c;
	}
	void setX(int x)
	{
		X = x;
	}
	void setY(int y)
	{
		Y = y;
	}
	void setAlphabet(char x)
	{
		Alphabet = x;
	}
	int getX()
	{
		return X;
	}
	int getY()
	{
		return Y;
	}
	char getAlphabet()
	{
		return Alphabet;
	}
	void Draw()
	{
		gotoxy(X, Y); cout << Alphabet;
	}
};
class CSnake
{
public:
	CSegment *snake;
	int length, DX, DY;
	CSnake(int index = 1,int dx=0,int dy=0,int x=0,int y=0,char alp='O')
	{
		length = index;
		snake = new CSegment[length];
		DX = dx;
		DY = dy;
		snake[length-1].X=x;
		snake[length-1].Y=y;
		snake[length-1].Alphabet=alp;
	}
	void Move(int direction)
	{
		if (direction == 4)
		{
			if (DX != -1||length==1) {
				DX = 1;
				DY = 0;
			}
		}
		else if (direction == 2)
		{
			if (DX != 1||length==1) {
				DX = -1;
				DY = 0;
			}

		}
		else if (direction == 1)
		{
			if (DY != -1||length==1) {
				DX = 0;
				DY = 1;
			}

		}
		else if (direction == 3)
		{
			if (DY != -1||length==1) {
				DX = 0;
				DY = -1;
			}
		}
	}
	void Updates()
	{
		CSegment* temp;
		temp = new CSegment[length];
		temp[0] = snake[0];
		for (int i = 1; i < length; i++)
			temp[i]= snake[i - 1];
		temp[0].setX(snake[0].getX()+DX);
		temp[0].setY(snake[0].getY()+DY);
		delete[]snake;
		snake = temp;
		if (snake[0].X > 119)
			snake[0].X = 1;
		if (snake[0].X < 1)
			snake[0].X = 119;
		if (snake[0].Y> 29)
			snake[0].Y=1;
		if (snake[0].Y < 0)
			snake[0].Y=29;
	}
	
	void Plus(char x,int posx,int posy)
	{	
		length++;
		CSegment* temp;
		temp = new CSegment[length];
		for (int i = 0; i < length; i++)
		{
			temp[i].Alphabet = snake[i].Alphabet;
			temp[i].X = posx;
			temp[i].Y = posy;
		}
		temp[0].Alphabet = x;
		delete[]snake;
		snake = temp;
	}
	int getX()
	{
		return snake[0].X;
	}
	int getY()
	{
		return snake[0].Y;
	}
	void setX(int x)
	{
		snake[length-1].X = x;
	}
	void setY(int y)
	{
		snake[length-1].Y = y;
	}
	bool Collision()
	{
		for (int i = 1; i < length; i++)
		{
			if (snake[0].X == snake[i].X && snake[0].Y == snake[i].Y)
			{
				return true;
			}
		}
		return false;
	}
	void Draw()
	{
		for (int i = 0; i < length; i++)
		{
			gotoxy(snake[i].getX(), snake[i].getY());
			cout << snake[0].Alphabet;
		}
	}
	~CSnake()
	{
		delete[]snake;
	}
};
class CFood
{
public:
	int X, Y, DX, DY;
	char Alphabet;
	CFood(int a=0,int b=0,int c=0,int d=0,char inp=NULL,int x=0,int y=0)
	{
		X = a;
		Y = b;
		DX = c;
		DY = d;
		Alphabet = inp;
	}
	void setX(int a)
	{
		X = a;
	}
	void setY(int a)
	{
		Y = a;
	}
	void setAlphabet(char a)
	{
		Alphabet = a;
	}
	void setDX(int a)
	{
		DX = a;
	}
	void setDY(int a)
	{
		DY = a;
	}
	int getX()
	{
		return X;
	}
	int getY()
	{
		return Y;
	}
	char getAlphabet()
	{
		return Alphabet;
	}
	int getDX()
	{
		return DX;
	}
	int getDY()
	{
		return DY;
	}
	void SetDirection(int direction)
	{
		if (direction == 1) //KANAN
		{
				DX = 1;
				DY = 0;
		}
		else if (direction == 2) //KIRI
		{
				DX = -1;
				DY = 0;
		}
		else if (direction == 3) //ATAS
		{
				DX = 0;
				DY = 1;			
		}
		else if (direction == 4) //BAWAH
		{
				DX = 0;
				DY = -1;
		}
	}
	void Updates()
	{
		X += DX;
		Y += DY;
		if (X > 119)
			DX = -1;
		if (X < 1)
			DX = 1;
		if (Y > 29)
			DY = -1;
		if (Y < 0)
			DY = 1;
	}
	void Draw()
	{
		gotoxy(X, Y); cout << Alphabet;
	}
};
class CGameSnake
{
	CSnake snake;
	CFood food[5];
	char inp;
	int direct;
public:
	void Initialize()
	{
		int x, y, dir;
		srand(time(NULL));
		for (int i = 0; i < 5; i++)
		{
			char a = rand() % 26 + 65;
			if (food[i].Alphabet == NULL)
			{
				food[i].Alphabet = a;
			}
		}
		for (int i = 0; i < 5; i++)
		{
			 x = rand() % 120, y = rand() % 30, dir = rand() % 4 + 1;
			food[i].setX(x);
			food[i].setY(y);
			food[i].SetDirection(dir);
		}
	}
	void isiUlang()
	{

		srand(time(NULL));
		for (int i = 0; i < 5; i++)
		{
			char a = rand() % 26 + 65;
			int x = rand() % 120, y = rand() % 30, dir = rand() % 4 + 1;
			if (food[i].Alphabet == NULL)
			{
				food[i].Alphabet = a;
				food[i].setX(x);
				food[i].setY(y);
				food[i].SetDirection(dir);
			}
		}
	}
	void Updates()
	{
		for (int i = 0; i < 5; i++) {
			char temp;
			if (direct==1)
			{ 
				if (snake.snake[0].getX() == food[i].getX() && snake.snake[0].getY() == food[i].getY())
				{
					temp = food[i].getAlphabet();
					snake.Plus(temp,food[i].getX(),food[i].getY());
					food[i] = NULL;
					isiUlang();
				}
				if (snake.snake[0].getX()==food[i].getX()&& snake.snake[0].getY()-1 == food[i].getY())
				{
					temp = food[i].getAlphabet();
					snake.Plus(temp, food[i].getX(), food[i].getY());
					food[i] = NULL;
					isiUlang();
				}
			}
			if (direct==2)
			{
				if (snake.snake[0].getX() == food[i].getX() && snake.snake[0].getY() == food[i].getY())
				{
					temp = food[i].getAlphabet();
					snake.Plus(temp, food[i].getX(), food[i].getY());
					food[i] = NULL;
					isiUlang();
				}
				if(snake.snake[0].getX()+1==food[i].getX()&&snake.snake[0].getY()==food[i].getY())
				{
					temp = food[i].getAlphabet();
					snake.Plus(temp, food[i].getX(), food[i].getY());
					food[i] = NULL;
					isiUlang();
				}
			}
			if (direct==3)
			{
				if (snake.snake[0].getX() == food[i].getX() && snake.snake[0].getY() == food[i].getY())
				{
					temp = food[i].getAlphabet();
					snake.Plus(temp, food[i].getX(), food[i].getY());
					food[i] = NULL;
					isiUlang();
				}
				if (snake.snake[0].getX() == food[i].getX() && snake.snake[0].getY()+1 == food[i].getY())
				{
					temp = food[i].getAlphabet();
					snake.Plus(temp, food[i].getX(), food[i].getY());
					food[i] = NULL;
					isiUlang();
				}
			}
			if (direct==4)
			{
				if (snake.snake[0].getX() == food[i].getX() && snake.snake[0].getY() == food[i].getY())
				{
					temp = food[i].getAlphabet();
					snake.Plus(temp, food[i].getX(), food[i].getY());
					food[i] = NULL;
					isiUlang();
				}
				if (snake.snake[0].getX() -1== food[i].getX() && snake.snake[0].getY() == food[i].getY())
				{
					temp = food[i].getAlphabet();
					snake.Plus(temp, food[i].getX(), food[i].getY());
					food[i] = NULL;
					isiUlang();
				}
			}
		}
		snake.Updates();
		for (int i = 0; i < 5; i++)
			food[i].Updates();
	}
	void ProcessInput()
	{

		if (_kbhit())
		{
			inp = _getch();
			if (inp == 'W' || inp == 'w')
			{
				direct = 3;
	
			}
			if (inp == 'A' || inp == 'a')
			{
				direct = 2;
			
			}
			if (inp == 'S' || inp == 's')
			{
				direct = 1;
			
			}
			if (inp == 'D' || inp == 'd')
			{
				direct = 4;
			
			}
			snake.Move(direct);
		}
	}
	void Draw()
	{
		system("cls");
		snake.Draw();
		for (int i = 0; i < 5; i++)
			food[i].Draw();
	}
	void Run()
	{
		while (inp!=27)
		{
			Draw();
			ProcessInput();
			Sleep(10);
			Updates();
			if (snake.Collision()) {
				gotoxy(15, 15); cout << "You Died";
				break;
			}
		}
	}
};
void main()
{
	CGameSnake game;
	game.Initialize();
	game.Run();
	system("pause");
}
