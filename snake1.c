#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <dos.h>

#define MAX_X 15
#define MAX_Y 15
#define MAX_SNAKE_LENGTH 6

typedef enum 
{
	UP,
	DOWN,
	LEFT,
	RIGHT
} Direction;

typedef struct tail_t
{
	int x;
	int y;
} tail_t;
	
typedef struct snake_t
{
	int x;
	int y;
	struct tail_t * tail;
	size_t tsize;
	Direction direction;
}  snake_t;
	
typedef struct food_t
{
	int x;
	int y;
	int isEaten;
} food_t;

// --> x
// || Y
// \/
// @**
struct snake_t initSnake(int x, int y, size_t tsize)
{
	struct snake_t snake;
	snake.x = x;
	snake.y = y;
	snake.tsize = tsize;
	snake.tail = (tail_t *) malloc (sizeof(tail_t) * 100);
	for (int i =0; i < tsize; ++i){
		snake.tail[i].x = x + i +1;
		snake.tail[i].y = y;
		}
		snake.direction = LEFT;
	return snake;
}

food_t initFood()
{
	food_t food;
	food.x = rand() % MAX_X;
	food.y = rand() % MAX_Y;
	food.isEaten = 0;
	return food;
}
	
// @**
void printSnake(struct snake_t snake, food_t food)
{
		char matrix[MAX_X][MAX_Y];
		for (int i = 0; i < MAX_X; ++i)
		{
			for (int j = 0; j < MAX_Y; ++j)
			{
				matrix[i][j] = ' ';
			}
		}
		matrix[food.x][food.y] = '$';
		
		matrix[snake.x][snake.y] = '@';
		for (int i = 0; i < snake.tsize; ++i)
		{
			matrix[snake.tail[i].x][snake.tail[i].y] = '*';
		}
		
		for (int j = 0; j < MAX_Y; ++j)
		{
			for (int i = 0; i < MAX_X; ++i)
			{
				printf("%c", matrix[i][j]);
			}
				printf("\n");
		}
}
	
// <--  @** tsize = 2
//     @**

//  @**      @***
//    * <--     *
//  ***        **
snake_t move(snake_t snake, food_t *food)
{
	for (int i = snake.tsize; i > 0; i--)
	{
		snake.tail[i] = snake.tail[i-1];
	}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
	switch(snake.direction)
	{
		case UP:
		{
			snake.y = snake.y - 1;
			if (snake.y < 0)
			{
				snake.y = MAX_Y -1;
			}
			break;
		}
		case DOWN:
		{
			snake.y = snake.y + 1;
			if (snake.y == MAX_Y)
			{
				snake.y = 0;
			}
			break;
		}
		case LEFT:
		{
			snake.x = snake.x - 1;
			if (snake.x < 0)
			{
				snake.x = MAX_X -1;
			}
			break;
		}
		case RIGHT:
		{
			snake.x = snake.x + 1;
			if (snake.x == MAX_X)
			{
				snake.x = 0;
			}
			break;
		}
	}
	if (snake.x == food->x && snake.y == food->y)
	{
		food->isEaten++;
		snake.tsize++;
	}
	
		
	return snake;
}
void printLevel(snake_t snake)
{
	int i=snake.tsize;
	printf("level is %d\n",i-1);
}

Direction input(snake_t snake){
	if (kbhit()){
		switch (getch()) {
			case 'w':
				return UP;
			case 's':
				return DOWN;
			case 'a':
				return LEFT;
			case 'd':
				return RIGHT;
		}
	}
	return snake.direction;
}

void speed(snake_t snake)
{
	float i=MAX_SNAKE_LENGTH-snake.tsize;
	
	sleep(i);
} 


		
int main()
{
	struct snake_t snake = initSnake( 10, 5, 2);
	food_t food = initFood();
	printSnake(snake, food);

	while(snake.tsize<MAX_SNAKE_LENGTH)
	{
		snake.direction = input(snake);
		snake = move(snake, &food);
		if (food.isEaten)
		{
			food = initFood();
		}
		
		speed(snake);
		system("cls");
		printSnake(snake, food);
		

	}
	printLevel(snake);
	getchar();
	return 0;
}

