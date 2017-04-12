// LifeGame.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "Point.h"
#include <random>
#include <iostream>
using namespace std;


int main()
{
	point world[__WORLD_WIDTH__][__WORLD_HEIGHT__];
	point prev_world[__WORLD_WIDTH__][__WORLD_HEIGHT__];

	lifegame a;
	a.init_world(world);
	unsigned int live_points = -1;
	bool is_optimal = false;

	do {
		a.print_world(world);
		a.copy_world(world, prev_world);
		a.next_generation(world, prev_world);

		is_optimal = a.cmp_world(world, prev_world) == 0;
		live_points = a.get_live_count(world);

		if (is_optimal) {
			cout << "Optimal configuration detected" << endl;
		}

		if (live_points == 0) {
			cout << "All points died" << endl;
		}
		msleep(1000);
	} while (live_points != 0 && !is_optimal);

	return 0;
}
