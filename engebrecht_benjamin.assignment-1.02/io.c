#include <stdio.h>
#include <stdlib.h>
#include <endian.h>
#include <string.h>
#include <stdint.h>

#include "gen.h"

void save(struct node screen[80][21], struct room_data rooms[]) {

	char * path;
	char * str;
	FILE * fp;
	uint8_t * room_buff;

	int s = strlen(getenv("HOME"));

	path = (char*) malloc(sizeof(char)*(s+17));

	snprintf(path, sizeof(char)*(s+17), "%s/.rlg327/dungeon", getenv("HOME"));
	printf("%s", path);

	fp = fopen(path, "w");

	if (fp == NULL) {
		printf("Error loading");
	}

	int i, j, k = 0;

	while(rooms[i].x != 0) {
		i++;
	}

	str = (char*) malloc(sizeof(char)*7);

	if (str == NULL) {
		fputs("str memory error", stderr);
		exit(3);
	}

	sprintf(str, "RLG327");

	//Write header
	fwrite(str,1,6,fp);

	int file_size = 0;

	fwrite(&file_size, 4, 1, fp);

	file_size = htobe32(((i*4)+1495));

	fwrite(&file_size, 4, 1, fp);

	uint8_t screen_buff[1482] = {0};

	//Write data
	for (i=1; i<20; i++) {
		for (j=1; j<79; j++) {
			screen_buff[k] = (uint8_t)screen[j][i].hardness;
			k++;
		}
	}

	fwrite(screen_buff,1482,1,fp);

	k=0;

	for(i=0; rooms[i].x != 0; i++) {
		k++;
	}

	room_buff = (uint8_t*) malloc(k*4);

	printf("Allocated %d to buffer\n", k*4);

	j=0;

	for(i=0; i<k*4; i+=4) {
		room_buff[i] = rooms[j].x;
		room_buff[i+1] = rooms[j].y;
		room_buff[i+2] = rooms[j].width;
		room_buff[i+3] = rooms[j].height;
		j++;
	}

	fwrite(room_buff, 1, k*4, fp);

	//close file
	fclose(fp);

	free(path);
	free(room_buff);
	free(str);

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

	path = (char*) malloc(sizeof(char)*(s+17));

	snprintf(path, sizeof(char)*(s+17), "%s/.rlg327/dungeon", getenv("HOME"));

	fp = fopen(path, "r");

	fseek(fp, 10, SEEK_SET);

	size = (int*) malloc(sizeof(int));

	fread(size,sizeof(int),1,fp);

	rewind(fp);

	int size_int = be32toh(*size);

	buffer = (uint8_t*) malloc (sizeof(uint8_t)*(size_int));

	if(buffer == NULL) {
		printf("Memory error");
	}

	fseek(fp, 14, SEEK_SET);

	init(screen);

	int i, j, k;

	for (i=1; i<20; i++) {
		for (j=1; j<79; j++) {
			screen[j][i].hardness = (int) fgetc(fp);
		}
	}
	free(buffer);

	//Draw rooms

	// fseek(fp, 10, SEEK_CUR);

	buffer = (uint8_t*) malloc (sizeof(uint8_t)*(size_int-1495));
	fread(buffer,sizeof(uint8_t),size_int-1495,fp);


	for(i=0; i< (size_int-1495); i+=4) {
		for(j=buffer[i]; j<(buffer[i+2]+buffer[i]); j++) {
			for(k=buffer[i+1]; k<(buffer[i+3]+buffer[i+1]); k++) {
				screen[j][k].c = '.';
			}
		}
	}

	//Draw corridors

	for (i = 1; i < 20; i++) {
		for (j = 1; j < 79; j++) {
			if (screen[j][i].c == ' ' && screen[j][i].hardness == 0) {
				screen[j][i].c = '#';
			}
		}
	}

	//close file
	fclose(fp);

	free(buffer);
	free(size);
	free(path);

}
