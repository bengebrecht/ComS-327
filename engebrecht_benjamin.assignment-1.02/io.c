#include <stdio.h>
#include <stdlib.h>
#include <endian.h>
#include <string.h>
#include <stdint.h>

#include "gen.c"

void save(struct node screen[80][21], struct room_data rooms[]) {

	char * path;
	FILE * fp;
	uint8_t * room_buff;

	int s = strlen(getenv("HOME"));

	path = (char*) malloc(sizeof(char)*(s+16));

	snprintf(path, sizeof(char)*s, "%s/.rlg327/dungeon", getenv("HOME"));

	fp = fopen(path, "w");

	int i, j, k = 0;

	while(rooms[i].x != 0) {
		i++;
	}

	char str[15];

	sprintf(str, "RLG327");

	//Write header
	fwrite(str,6,1,fp);

	int file_size = 0;

	fwrite(&file_size, 4, 1, fp);

	file_size = ((i*4)+1495);

	fwrite(&file_size, 4, 1, fp);

	uint8_t screen_buff[1482] = {0};

	//Write data
	for (i=1; i<79; i++) {
		for (j=1; j<20; j++) {
			screen_buff[k] = (uint8_t)screen[i][j].hardness;
			k++;
		}
	}

	fwrite(screen_buff,1482,1,fp);

	k=0;

	for(i=0; i<10 || rooms[i].x != 0; i++) {
		k++;
	}

	room_buff = (uint8_t*) malloc(k*4);

	j=0;

	for(i=0; i<k*4; i+=4) {
		room_buff[i] = rooms[j].x;
		room_buff[i+1] = rooms[j].y;
		room_buff[i+2] = rooms[j].width;
		room_buff[i+3] = rooms[j].height;
		j++;
	}

	fwrite(room_buff, k*4, 1, fp);

	//close file
	fclose(fp);

	free(path);

}

//Normal Java logic dictates that a load statement should have no
//parameters and return the data, however, passing the array into
//the function eliminates a lot of problems that would arise from
//trying to point to a 2D array of structs
void load(struct node screen[80][21]) {

	FILE * fp;
	uint8_t * buffer;
	int * size;
	char * path;

	int s = strlen(getenv("HOME"));

	path = (char*) malloc(sizeof(char)*(s+16));

	snprintf(path, sizeof(char)*s, "%s/.rlg327/dungeon", getenv("HOME"));

	fp = fopen(path, "r");

	fseek(fp, 10, SEEK_SET);

	size = (int*) malloc(sizeof(int));

	fread(size,sizeof(int),1,fp);

	rewind(fp);

	int size_int = *size;

	buffer = (uint8_t*) malloc (sizeof(char)*(size_int));
	if(buffer == NULL) {
		printf("Memory error");
	}

	fseek(fp, 4, SEEK_SET);

	init_border(screen);

	int i, j, k;

	for (i=1; i<79; i++) {
		for (j=1; j<20; j++) {
			screen[i][j].hardness = (int) fgetc(fp);
		}
	}
	free(buffer);

	//Draw rooms

	buffer = (uint8_t*) malloc (sizeof(uint8_t)*(size_int-1495));
	fread(buffer,sizeof(uint8_t),size_int-1495,fp);

	for(i=0; i< (size_int-1495); i+=4) {
		for(j=buffer[i]; j<buffer[i+2]; j++) {
			for(k=buffer[i+1]; k<buffer[i+3]; k++) {
				screen[j][k].c = '.';
			}
		}
	}

	//Draw corridors

	for (i = 1; i < 79; i++) {
		for (j = 1; j < 20; j++) {
			if (screen[i][j].c == ' ' && screen[i][j].hardness == 0) {
				screen[i][j].c = '#';
			}
		}
	}

	//close file
	fclose(fp);

	free(buffer);
	free(size);
	free(path);

}
