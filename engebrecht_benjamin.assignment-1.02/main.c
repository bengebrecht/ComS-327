#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gen.h"
#include "io.h"

typedef enum command {
	gen_file,
	save_file,
	load_file,
	save_load_file
} command_t;



int main(int argc, char *argv[])
{

	command_t command;

	int seed = (int)time(NULL);

	if (argc == 1) {
		command = gen_file;
	} else if (argc == 2){
		if (!strcmp(argv[1], "--load")) {
			command = load_file;
		} else if (!strcmp(argv[1], "--save")) {
			command = save_file;
		} else {
			fprintf(stderr, "Bad argument\n");
		}
	} else if (argc == 3) {
		if (((!strcmp(argv[1], "--load")) && (!strcmp(argv[2], "--save"))) || ((!strcmp(argv[1], "--save")) && (!strcmp(argv[2], "--load")))) {
			command = save_load_file;
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
		case gen_file:

			srand(seed);

			init(screen);

			draw_rooms(screen, rooms);

			draw_corridors(screen, rooms);

			//print_hardness(screen);

			break;

		case load_file:

			load(screen);

			print(screen);

			break;

		case save_file:

			srand(seed);

			init(screen);

			draw_rooms(screen, rooms);

			draw_corridors(screen, rooms);

			save(screen, rooms);

			print(screen);			

			break;

		case save_load_file:

			srand(seed);

			load(screen);

			print(screen);

			init(screen);

			draw_rooms(screen, rooms);

			draw_corridors(screen, rooms);

			save(screen, rooms);

			break;
	}

	return 0;
}