
struct node {
	char c;
	int hardness;
};

struct room_data {
	int x;
	int y;
	int mid_x;
	int mid_y;
	int width;
	int height;
};


void draw_rooms(struct node screen[80][21], struct room_data rooms[]);

void init(struct node screen[80][21]);

void init_border(struct node screen[80][21]);

void print(struct node screen[80][21]);

void print_hardness(struct node screen[80][21]);

void draw_corridors(struct node screen[80][21], struct room_data rooms[]);

void drawing_helper(struct node screen[80][21], struct room_data rooms[], int i, int j);