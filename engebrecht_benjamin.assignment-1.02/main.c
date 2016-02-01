#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gen.h"
#include "io.h"

typedef enum command {
	read,
	write,
	rw
} command_t;

int main(int argc, char *argv[])
{

	command_t command;

	int seed;

	if (argc == 1) {
		seed = (int)time(NULL);
	} else if (argc == 2){
		if (!strcmp(argv[1], "--load")) {
			command = read;
		} else if (!strcmp(argv[1], "--save")) {
			command = save;
		} else {
			fprintf(stderr, "Bad argument\n");
		}
	} else if (argc == 3) {
		if ((!strcmp(argv[1], "--load") && !strcmp(argv[2], "--save") || (!strcmp(argv[1], "--save") && !strcmp(argv[2], "--load")) {
			command = rw;
		} else {
			fprintf(stderr, "Bad argument\n");			
		}
	} else {
		fprintf(stderr, "Too many arguments\n");		
	}


	// } else {
	// 	seed = atoi(argv[1]);
	// }


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