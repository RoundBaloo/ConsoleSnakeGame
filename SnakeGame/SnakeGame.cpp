#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
//EADIBLE OBJECTS MAY SPAWN JUST RIGHT IN WALLS!!!
using namespace std;

bool GameOver;
int width;
int height;
int sx, sy; // snake
int ex, ey; // eadible
int tailX[100], tailY[100];
int tail;
int score;
int tickrate;
enum class eDirection
{
	STOP = 0,
	UP,
	DOWN,
	RIGHT,
	LEFT
};
eDirection dir;

void Setup() {
    srand(time(NULL));
    cout << "HELLO, DO YOU WANT TO CUSTOMISE YOUR GAME?\nENTER \"YES\" OR \"NO\"" << endl;
    cout << "ENTER THE DIMENSIONS OF THE FIELD!\nHEIGHT: ";
    cin >> width;
    cout << "WIDTH: ";
    cin >> height;
    cout << "ENTER TICKRATE(150 RECOMMENDED): ";
    cin >> tickrate;
    GameOver = false;
    dir = eDirection::STOP;
    sx = width / 2 - 2;
    sy = height / 2 - 2;
    ex = 2 + rand() % (width - 2);
    ey= 2 + rand() % (height - 2);
    score = 0;
}

void Draw() {
    system("cls"); //system ("clear");
    /*for (int i = 0; i < width + 1; i++) {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) {
                cout << "#";
            }
            if (i == sy && j == sx) {
                cout << "0";
            }
            else if (i == ey && j == ex) {
                cout << "F";
            }
            else {
                cout << " ";
            }
        }
        cout << endl;

    }

    for (int i = 0; i < width + 1; i++) {
        cout << "#";
    }
    cout << endl;*/
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (i == 0 || i == width - 1 || (i > 0 && i < width && j == 0) || (i > 0 && i < width && j == height - 1))
            {
                cout << "#";
            }
            else if (i == sx && j == sy)
            {
                cout << "0";
            }
            else if (i == ex && j == ey)
            {
                cout << "F";
            }
            else {
                bool print = false;
                for (int k = 0; k < tail; k++) {
                    if (tailX[k] == j && tailY[k] == i) { 
                        print = true;
                        cout << "o";
                    }
                }
                if (!print) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
        cout << "SCORE: " << score;
        Sleep(tickrate);
}

void Input() {
    if (_kbhit()) {
        switch (_getch())
        {
        case('w'):
            dir = eDirection::UP;
            break;
        case('a'):
            dir = eDirection::LEFT;
            break;
        case('s'):
            dir = eDirection::DOWN;
            break;
        case('d'):
            dir = eDirection::RIGHT;
            break;
        case('x'):
            GameOver = true;
            break;
        }
    }
}

void Logic() {
    int preX = tailX[0];
    int preY = tailY[0];
    int preX_2, preY_2;
    tailX[0] = sy;
    tailY[0] = sx;
    for (int i = 1; i < tail; i++) {
        preX_2 = tailX[i];
        preY_2 = tailY[i];
        tailX[i] = preX;
        tailY[i] = preY;
        preX = preX_2;
        preY = preY_2;
    }
    switch (dir)
    {
    case eDirection::UP:
        sx--;
        break;
    case eDirection::DOWN:
        sx++;
        break;
    case eDirection::RIGHT:
        sy++;
        break;
    case eDirection::LEFT:
        sy--;
        break;
    }
    /*if (sx > width || sx < 0 || sy > height || sy < 0) {
        sx = 10;
        sy = 10;
    }*/

    if (sx >= width -1 ) 
        sx = 0;
    else if (sx < 0) 
        sx = width - 2;

    if (sy >= height - 1)
        sy = 0;
    else if (sy < 0)
        sy = height - 2;

    for (int i = 0; i < tail; i++) {
        if (tailX[i] == sy && tailY[i] == sx) { GameOver = true; }
    }

    if (sx == ex && sy == ey) {
        score++;
        ex = 2 + rand() % (width - 2);
        ey = 2 + rand() % (height - 2);
        tail++;
    }
    if (GameOver)
        cout << "\nGAME OVER" << endl;
}

int main() {
    Setup();
    while (!GameOver) {
        Draw();
        Input();
        Logic();
    }
    return 0;
}

//void Setup() {
//	srand(time(NULL));
//	GameOver = false;
//	dir = STOP;
//	sx = width / 2;
//	sy = height / 2;
//	ex = rand() % width;
//	ey = rand() % height;
//	score = 0;
//}
//
//void Draw(char *p_field[]) {
//	system("cls"); // очистка терминала при вызове Draw
//	for (int i = 1; i <= width; i++) {
//		for (int j = 1; j <= height; j++) {
//			cout << p_field[i][j];
//		}
//		cout << endl;
//	}
//}
//
//void Input() {
//
//}
//
//void Logic() {
//
//}
//
//int main() {
//
//	char field[30][30];
//	char* p_field[1000];
//	for (int i = 1; i <= width; i++) { p_field[i] = field[i]; }
//	for (int i = 1; i <= width; i++) {
//		for (int j = 1; j <= height; j++) {
//			field[i][j] = ' ';
//			if (i == sy && j == sx) {
//				cout << "0";
//			}
//			else if (i == ey && j == ex) {
//				cout << "F";
//			}
//			else {
//				cout << " ";
//			}
//		}
//	}
//
//	for (int i = 1; i <= width; i++) {
//		for (int j = 1; j <= height; j++) {
//			if (i == 1 || j == 1 || i == width || j == width) {
//				field[i][j] = '#';
//			}
//		}
//	}
//
//	Setup();
//	while (!GameOver) {
//		Draw(p_field);
//		//Input();
//		//Logic();
//	}
//}