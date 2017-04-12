#include "stdafx.h"
#include "Point.h"
#include <random>
#include <iostream>
using namespace std;

lifegame::lifegame(){}

lifegame::~lifegame(){}

void lifegame::init_world(point world[][__WORLD_HEIGHT__]) //Инициализация первого поколения игры псевдослучайными значениями
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 10000);

	unsigned int i, j;

	for (i = 0; i < __WORLD_WIDTH__; i++) {
		for (j = 0; j < __WORLD_HEIGHT__; j++) {
			unsigned int num = dis(gen);
			if (num % 2 == 0) {
				world[i][j].is_live = 1;
			}
			else {
				world[i][j].is_live = 0;
			}
		}
	}
}

unsigned int lifegame::get_live_count(point world[][__WORLD_HEIGHT__]) //Количество живых клеток на игровом поле
{
	unsigned int count = 0;
	unsigned i, j;
	for (i = 0; i < __WORLD_WIDTH__; i++) {
		for (j = 0; j < __WORLD_HEIGHT__; j++) {
			if (world[i][j].is_live == 1) {
				count++;
			}
		}
	}
	return count;
}

void lifegame::read_point_neighbors(signed int nb[][2], unsigned int x, unsigned int y) //Получение координат соседей точки (окрестность мура 1 порядка)
{
	unsigned int i, j;
	unsigned int k = 0;

	for (i = x - 1; i <= x + 1; i++) {
		for (j = y - 1; j <= y + 1; j++) {
			if (i == x && j == y) {
				continue;
			}
			nb[k][0] = i;
			nb[k][1] = j;
			k++;
		}
	}
}

unsigned int lifegame::count_live_neighbors(point world[][__WORLD_HEIGHT__], unsigned int x, unsigned int y) //Количество живых соседей у клетки с координатами x, y
{
	unsigned int count = 0;
	unsigned int i;
	signed int nb[8][2];
	signed int _x, _y;

	read_point_neighbors(nb, x, y);

	for (i = 0; i < 8; i++) {
		_x = nb[i][0];
		_y = nb[i][1];

		if (_x < 0 || _y < 0) {
			continue;
		}
		if (_x >= __WORLD_WIDTH__ || _y >= __WORLD_HEIGHT__) {
			continue;
		}

		if (world[_x][_y].is_live == 1) {
			count++;
		}
	}

	return count;
}

void lifegame::next_generation(point world[][__WORLD_HEIGHT__], point prev_world[][__WORLD_HEIGHT__]) //Сгенерировать следующее поколение игрового мира
{
	unsigned int i, j;
	unsigned int live_nb;
	point p;

	for (i = 0; i < __WORLD_WIDTH__; i++) {
		for (j = 0; j < __WORLD_HEIGHT__; j++) {
			p = prev_world[i][j];
			live_nb = count_live_neighbors(prev_world, i, j);

			if (p.is_live == 0) {
				if (live_nb == 3) {
					world[i][j].is_live = 1;
				}
			}
			else {
				if (live_nb < 2 || live_nb > 3) {
					world[i][j].is_live = 0;
				}
			}
		}
	}
}

void lifegame::copy_world(point src[][__WORLD_HEIGHT__], point dest[][__WORLD_HEIGHT__]) // Копирование игрового мира. Используется для сохранения предыдущего поколения
{
	unsigned int i, j;
	for (i = 0; i < __WORLD_WIDTH__; i++) {
		for (j = 0; j < __WORLD_HEIGHT__; j++) {
			dest[i][j] = src[i][j];
		}
	}
}

int lifegame::cmp_world(point w1[][__WORLD_HEIGHT__], point w2[][__WORLD_HEIGHT__]) //Сравнение игровых миров текущего и предыдущего поколения
{
	unsigned int i, j;
	for (i = 0; i < __WORLD_WIDTH__; i++) {
		for (j = 0; j < __WORLD_HEIGHT__; j++) {
			if (w1[i][j].is_live != w2[i][j].is_live) {
				return -1;
			}
		}
	}
	return 0;
}

void lifegame::print_world(point world[][__WORLD_HEIGHT__])	//Вывести на экран игровое поле
{
	unsigned int i, j;
	for (i = 0; i < __WORLD_WIDTH__; i++) {
		for (j = 0; j < __WORLD_HEIGHT__; j++) {
			if (world[i][j].is_live == 1) {
				cout << '*';
			}
			else {
				cout << ' ';
			}
			cout << ' ';
		}
		cout << endl;
	}
}
