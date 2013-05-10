
#include <iostream>
#include <string>
#include <GL/glut.h>

#include "Objeto.h"
#include "Escena.h"

#define USER_ID 1
#define AI_ID 2

Escena board;
Escena pieces;

int board_p[3][3];
extern bool game_over;
extern int n_rmplace;
extern std::string str_winner;

bool checkWin(int id);
bool checkNotOver();

void inicia(void) {
	if (!board.Load("board.txt")) 
	{
		std::cerr << "No se ha podido cargar la escena. No puedo seguir." << std::endl;
		exit(-1);
	}
	if (!pieces.Load("pieces.txt")){
		std::cerr << "No se ha podido cargar la escena. No puedo seguir." << std::endl;
		exit(-1);
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board_p[i][j] = 0;
		}
	}
}

void dibuja() {
	board.Draw();
	pieces.Draw();
}

// Esta función debe implementar el picking, actualizando el estado del 
// tablero después de atender el evento (el usuario ha hecho clic sobre 
// el pixel (x, y)
void click(int x, int y) {
//Draw the picking scene 
	board.Draw(true);
	//Read the pixel
	unsigned char id[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, id);
	//"Translate" between color and position
	//position:
	//0 1 2 | 20 120 40
	//3 4 5 | 140 60 160
	//6 7 8 | 80 180 100
	int pos;
	switch (id[0]/20)
	{
	case 1:
		pos = 0;
		break;
	case 6:
		pos = 1;
		break;
	case 2:
		pos = 2;
		break;
	case 7:
		pos = 3;
		break;
	case 3:
		pos = 4;
		break;
	case 8:
		pos = 5;
		break;
	case 4:
		pos = 6;
		break;
	case 9:
		pos = 7;
		break;
	case 5:
		pos = 8;
		break;
	default:
		return;
	}
	//Check if the position is already taken
	if (board_p[pos/3][pos%3] == 0)
	{
		board_p[pos/3][pos%3] = USER_ID;
		//Addinstance to pieces
		vertice s;
		s.x =  0.6;
		s.y = 0.6;
		s.z = 0.6;
		float ang = 45;
		vertice ora;
		ora.x = 0;
		ora.y = 1;
		ora.z = 0;
		vertice tran;/*
		tran.x = (-0.6 + (float)(pos%3)/2)/s.x;
		tran.z = (-0.6 + (float)(pos/3)/2)/s.z;
		tran.y = 0.35;*/
		tran.x=0.9*(pos%3-1);
				tran.z=0.9*(pos/3-1);
				tran.y=0.3;

		pieces.AddInstance(USER_ID-1, s, ang, ora, tran);
		n_rmplace--;
	//Check if the player has won
		bool player_win = checkWin(USER_ID);
	//If not, check if the game is over
		if (!player_win)
		{
			if (checkNotOver())
			{
			//Implement the game logic (IA)
				int ia_i, ia_j;
				bool flag_tmp = false;
				for (ia_i = 0; ia_i < 3; ia_i++)
				{
					for (ia_j = 0; ia_j < 3; ia_j++)
					{
						if (board_p[ia_i][ia_j] == 0)
						{
							board_p[ia_i][ia_j] = AI_ID;
							flag_tmp = true;
							break;
						}
					}
					if (flag_tmp)
						break;
				}
			//Addinstance to pieces
				ang = 30;
				pos = ia_i*3 + ia_j;
				/*tran.x = (-0.6 + (float)(pos%3)/2)/s.x;
		tran.z = (-0.6 + (float)(pos/3)/2)/s.z;
		tran.y = 0.35;*/
		tran.x=0.9*(pos%3-1);
				tran.z=0.9*(pos/3-1);
				tran.y=0.3;
				pieces.AddInstance(AI_ID-1, s, ang, ora, tran);
				n_rmplace--;
			//Check if IA has won
				bool ai_win = checkWin(AI_ID);
				if (!ai_win)
				{
					if (!checkNotOver())
					{
						game_over = true;
					}
				}
				else
				{
					str_winner = "Computer.";
					game_over = true;
				}
			}
			else
			{
				game_over = true;
			}
		}
		else
		{
			str_winner = "Player.";
			game_over = true;

		}
	}
	//pieces.Draw();
}

bool checkWin(int id)
{
	bool flag = false;
	for (int i = 0; i < 3; i++)
	{
		if ((board_p[i][0] == board_p[i][1]) && (board_p[i][0] != 0))
		{
			if (board_p[i][1] == board_p[i][2])
			{
				flag = true;
				return flag;
			}
		}
	}
	for (int j = 0; j < 3; j++)
	{
		if ((board_p[0][j] == board_p[1][j]) && (board_p[0][j] != 0))
		{
			if (board_p[1][j] == board_p[2][j])
			{
				flag = true;
				return flag;
			}
		}
	}
	if (((board_p[0][0] == board_p[1][1]) && (board_p[1][1] == board_p[2][2]) && (board_p[0][0] != 0)) 
		|| ((board_p[0][2] == board_p[1][1]) && (board_p[1][1] == board_p[2][0]) && (board_p[0][2] != 0)))
	{
		flag = true;
		return flag;
	}
	return flag;
}

bool checkNotOver()
{
	bool flag = false;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board_p[i][j] == 0)
			{
				flag = true;
				return flag;
			}
		}
	}
	return flag;
}