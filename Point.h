#define __WORLD_HEIGHT__ 10	//Ширина игрового поля
#define __WORLD_WIDTH__ 10	//Высота игрового поля

#ifdef _WIN32
	#include <windows.h>
	#define msleep(x) Sleep(x)
#else
	#include <unistd.h>
	#define msleep(x) usleep(x * 1000)
#endif

struct point 
{
	unsigned is_live : 1;
};

class lifegame{

public:
	lifegame();
	~lifegame();

	void init_world(point world[][__WORLD_HEIGHT__]);
	unsigned int get_live_count(point world[][__WORLD_HEIGHT__]);
	void read_point_neighbors(signed int nb[][2], unsigned int x, unsigned int y);
	unsigned int count_live_neighbors(point world[][__WORLD_HEIGHT__], unsigned int x, unsigned int y);
	void next_generation(point world[][__WORLD_HEIGHT__], point prev_world[][__WORLD_HEIGHT__]);
	void copy_world(point src[][__WORLD_HEIGHT__], point dest[][__WORLD_HEIGHT__]);
	int cmp_world(point w1[][__WORLD_HEIGHT__], point w2[][__WORLD_HEIGHT__]);
	void print_world(point world[][__WORLD_HEIGHT__]);

};
