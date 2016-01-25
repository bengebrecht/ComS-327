#include <stdlib.h>
#include <stdio.h>

//Define maximum length and width
#define MAX_LENGTH 7
#define MAX_WIDTH 7


void init(char arr[][21]) {
	
	int i,j;

	//Write all cells to the "space" character
	for (i = 0; i < 80; i++) {
		for (j = 0; j < 21; j++) {
			arr[i][j] = ' ';
		}
	}
}

void print(char arr[][21]) {

	int i,j;

	//Print entire screen buffer
	for (i = 0; i < 21; i++) {
		for (j = 0; j < 80; j++) {
			printf("%c", arr[j][i]);
		}

		printf("\n");
	}
}

int is_valid(char screen[][21], int x, int y, int width, int length) {

	int i, j;

	//Check for intersection with other room
	for (i = x; i < x+width; i++) {

		for (j = y; j < y+length; j++) {

			if (screen[i][j] != ' ') {

				return 0;

			}
		}
	}

	//Check for one 1 cell of non-room between proposed room and other rooms
	
	//Area to check runs from x-1 to x+width+1, scan all y values 
	for (i = x-1; i < x+width+1; i++) {
		
		if (screen[i][y-1] != ' ') {return 0;}

		if (screen[i][y+length+1] != ' ') {return 0;}
	}

	for (j = y; j < y+length; j++) {

		if (screen[x-1][j] != ' ') {return 0;}

		if (screen[x+width+1][j] != ' ') {return 0;}
	}

	return 1;
}

/**
 * Generates the rooms on the screen buffer, placing them 
 * into a 80x21 matrix (2D array) and also placing the 
 * midpoints of each room into a separate matrix for line 
 * drawing purposes
 *
 * @param  screen a matrix representation of the screen
 * @param  room   a matrix for storing data for corridors
*/


void draw_rooms(char screen[][21], int room[][2]) {

	int area = 0;
	int roomnum = 0;

	while (((double)area/1680) < 0.10 || roomnum < 5) {
		//Get random number between 3 and 3+MAX_*
		int width = (rand() % (MAX_WIDTH)) + 3;
		int length = (rand() % (MAX_LENGTH)) + 3;

		//Get random number between 1-(80-MAX_LENGTH)
		int x = (rand() % (80-MAX_WIDTH-5)) + 1;
		//Get random number between 1-(21-MAX_WIDTH)
		int y = (rand() % (21-MAX_LENGTH-5)) + 1;

		//Check if the proposed area is valid or not
		if (is_valid(screen, x, y, width, length)) {

			int i, j;
			
			//Write proposed area to screen buffer as periods
			for (i = x; i < x+width; i++) {
				for (j = y; j < y+length; j++) {

					screen[i][j] = '.';
				
				}
			}

			//Add proposed area to total area
			area = area + (width*length);

			//Add midpoint of each room to "room" array
			room[roomnum][0] = x+(width/2);
			room[roomnum][1] = y+(length/2);

			roomnum++;

		}

	}

}



/* 
Origionally this method used the index of the rooms array
for all of the calculations, but it got rather difficult to read.
For the sake of whoever grades this I decided to use the extra memory
to make it mush less confusing. 

Also, the code under the comment "Geometry" exists since Bresenham's
algorithm doesn't allow graphing in the second or third quadrants
relative to (x0, y0). Switching points 0 & 1 in that case allows
a lot of cases to be ignored and saved a lot of code.
*/

void drawing_helper(char screen[][21], int rooms[][2], int i, int j) {

	//clarity > memory
	int x1 = rooms[i][0];
	int y1 = rooms[i][1];
	int x0 = rooms[j][0];
	int y0 = rooms[j][1];

	//Geometry
	//Switch order of pairs to work with line algorithm
	if (x0 > x1) {

		int temp = x0;
		x0 = x1;
		x1 = temp;

		temp = y0;
		y0 = y1;
		y1 = temp;

	}

	//Calculate slope of line
	double slope = ((double) y1 - y0) / ((double) x1 - x0);

	int index;

	//If the slope of the line is less than 1
	if (abs((int)slope) < 1) {

		int prev_height = 0;
		int change = 0;

		//For each x value between x0 and x1
		for (index = x0; index < x1; index++) {

			//Calculate y value for (x,y) coordinates
			int height = (int)(slope * (index - x0)) + y0;

			//Detect change in height for contiuous line algorithm
			if (height != prev_height) {

				change = 1;

			}

			//Continuous line algorithm
			if (change == 1) {

				//If the line changes height and the next index is blank...
				if (screen[index-1][height] == ' ') {

					//Write another hash mark to make it continuous
					screen[index-1][height] = '#';

					change = 0;

				}
			}
			//If the proposed cell doesn't have anything in it...
			if (screen[index][height] == ' ') {

				//Write hash there
				screen[index][height] = '#';



			}

			prev_height = height;
		}

	//If the slope of the line is not < 1
	} else {

			int prev_height = 0;
			int change = 0;

		//More geometry to make line drawing work
		if (y0 > y1) {

			int temp = x0;
			x0 = x1;
			x1 = temp;

			temp = y0;
			y0 = y1;
			y1 = temp;

		}

		//For each y value between y0 and y1
		for (index = y0; index < y1; index++) {

			//Calculate x value for (x,y) pair
			int height = (int)((1.0/slope) * (index - y0)) + x0;

			//If height changes, make note
			if (height != prev_height) {
				change = 1;
			}

			//If the height has changed...
			if (change == 1) {

				//If the cell is clear.. (had to include prev_height to fix bug)
				if (screen[prev_height][index] == ' ' && prev_height != 0) {

					//Write hash to empty cell
					screen[prev_height][index] = '#';

					change = 0;
				}
				
			}

			//If the proposed cell is clear...
			if (screen[height][index] == ' ') {

				//Write hash symbol
				screen[height][index] = '#';

			}

			prev_height = height;
		}	
	}
}

void draw_corridors(char screen[][21], int rooms[][2]) {

	int i;

	//For all rooms that have a valid value
	for (i = 1; rooms[i][0] != 0; i++) {
		//Draw a line between current room and previous room
		drawing_helper(screen, rooms, i, i-1);
	}

	//Draw a line between rooms 1 and n
	drawing_helper(screen, rooms, 0, i-1);
}



