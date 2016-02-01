#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gen.h"
#include "io.h"

int main(int argc, char *argv[])
{

	int seed;

	if (argc == 1) {
		seed = (int)time(NULL);
	} else {
		seed = atoi(argv[1]);
	}


	//Set up random number seed
	srand(seed);

	char screen[80][21] = {{0}};

	int rooms[10][2] = {{0}};

	init(screen);

	draw_rooms(screen, rooms);

	draw_corridors(screen, rooms);

	print(screen);

	printf("Seed: %d argc: %d\n", seed, argc);

	return 0;
}