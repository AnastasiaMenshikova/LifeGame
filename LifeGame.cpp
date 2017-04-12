// LifeGame.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "Point.h"
#include <random>
#include <iostream>
using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");

	point world[__WORLD_WIDTH__][__WORLD_HEIGHT__];
	point prev_world[__WORLD_WIDTH__][__WORLD_HEIGHT__];

	lifegame a;
	unsigned int live_points = -1;
	bool is_optimal = false;
	bool gameOn = true;
	bool gameover = false;
	int decision;

	while (gameOn == true) 
	{

		while (gameover == true) 
		{
			for (;;) {
				cout << endl << "Нажмите 1 для продолжения или 0 для выхода." << endl;
				if ((cin >> decision) && (cin.good()))
				{
					break;
				}
				else
				{
					cout << "\n Некорректное значение. Для продолжения игры нажмите 1 или 0 для выхода." << endl;
					system("pause");
					cin.clear();
					cin.ignore();
					system("cls");
				}
			}
			if (decision == 1) {
				gameOn = true;
				gameover = false;
				live_points = -1;
				is_optimal = false;
			}
			if (decision == 0)
			{
				gameOn = false;
				break;
			}
		}

		if (gameOn == false) { break; }

		a.init_world(world);
		
		do {
			system("cls");
			a.print_world(world);
			a.copy_world(world, prev_world);
			a.next_generation(world, prev_world);
			is_optimal = a.cmp_world(world, prev_world) == 0;
			live_points = a.get_live_count(world);

				if (is_optimal) {
					cout << "Стабильная конфигурация" << endl;
					gameover = true;
				}

				if (live_points == 0) {
				cout << "Все клетки умерли" << endl;
				gameover = true;
				}
			msleep(1000);
		} while (live_points != 0 && !is_optimal);
		
	}
	return 0;
}
