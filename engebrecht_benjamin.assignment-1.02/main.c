#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gen.h"
#include "io.h"

typedef enum command {
	gen,
	save,
	load,
	save_load
} command_t;



int main(int argc, char *argv[])
{

	command_t command;

	int seed = (int)time(NULL);

	if (argc == 1) {
		command = gen;
	} else if (argc == 2){
		if (!strcmp(argv[1], "--load")) {
			command = load;
		} else if (!strcmp(argv[1], "--save")) {
			command = save;
		} else {
			fprintf(stderr, "Bad argument\n");
		}
	} else if (argc == 3) {
		if (((!strcmp(argv[1], "--load")) && (!strcmp(argv[2], "--save"))) || ((!strcmp(argv[1], "--save")) && (!strcmp(argv[2], "--load")))) {
			command = save_load;
		} else {
			fprintf(stderr, "Bad argument\n");			
		}
	} else {
		fprintf(stderr, "Too many arguments\n");		
	}


	// } else {
	// 	seed = atoi(argv[1]);
	// }

	struct node screen[80][21] = {{{0}}};

	struct room_data rooms[10] = {{0}};

	switch (command) {
		case gen:

			srand(seed);

			init(screen);

			draw_rooms(screen, rooms);

			draw_corridors(screen, rooms);

			print(screen);

			break;

		case load:

			screen = load();

			print(screen);

			break;

		case save:

			srand(seed);

			init(screen);

			draw_rooms(screen, rooms);

			draw_corridors(screen, rooms);

			save(screen, rooms);

			print(screen);			

			break;

		case save_load:

			srand(seed);

			screen = load();

			print(screen);

			init(screen);

			draw_rooms(screen, rooms);

			draw_corridors(screen, rooms);

			save(screen, rooms);

			break;
	}

	return 0;
}