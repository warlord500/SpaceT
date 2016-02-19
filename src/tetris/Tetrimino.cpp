#include <tetris/Tetrimino.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

Tetrimino::Tetrimino(BlockShapes type)
{
	location.row = 0;
	location.col = 0;

	// Initialize grid elements to zero
	for(int x = 0; x < TETRIMINO_GRID_SIZE; x++)
		for(int y = 0; y < TETRIMINO_GRID_SIZE; y++)
			grid[x][y] = 0;

	if(type == random_shape)
		type = static_cast<BlockShapes>(getRandomNumber(1, 7));

	// I've chosen to use a co-ordinate plane for the grid with
	// the orgin (0,0) in the top-left corner, and so that the left indice refers
	// to the y-component, and the right indice refers to the x-component.
	switch(type)
	{
	case I_shape:
		grid[2][0] = 1;
		grid[2][1] = 1;
		grid[2][2] = 1;
		grid[2][3] = 1;
		color = Cyan;
		break;
	case J_shape:
		grid[1][1] = 1;
		grid[2][1] = 1;
		grid[2][2] = 1;
		grid[2][3] = 1;
		color = Orange;
		break;
	case L_shape:
		grid[2][0] = 1;
		grid[2][1] = 1;
		grid[2][2] = 1;
		grid[1][2] = 1;
		color = Blue;
		break;
	case O_shape:
		grid[2][1] = 1;
		grid[1][1] = 1;
		grid[2][2] = 1;
		grid[1][2] = 1;
		color = Yellow;
		break;
	case Z_shape:
		grid[1][1] = 1;
		grid[1][2] = 1;
		grid[2][2] = 1;
		grid[2][3] = 1;
		color = Red;

		break;
	case T_shape:
		grid[2][0] = 1;
		grid[2][1] = 1;
		grid[1][1] = 1;
		grid[2][2] = 1;
		color = Purple;

		break;
	case S_shape:
		grid[2][0] = 1;
		grid[2][1] = 1;
		grid[1][1] = 1;
		grid[1][2] = 1;
		color = Green;
	};
}

BlockColors Tetrimino::getColor() const
{
	return color;
}

tetriminoLocation Tetrimino::getLocation() const
{
	return location;
}

void Tetrimino::getGrid(int gridOut[][TETRIMINO_GRID_SIZE]) const
{
	for(int y = 0; y < TETRIMINO_GRID_SIZE; y++)
		for(int x = 0; x < TETRIMINO_GRID_SIZE; x++)
		gridOut[y][x] = grid[y][x];
}

void Tetrimino::setLocation(tetriminoLocation newLocation)
{
	location = newLocation;
}

void Tetrimino::setLocation(int row, int col)
{
	location.row = row;
	location.col = col;
}

void Tetrimino::rotateLeft()
{
	int tempGrid[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];

	// Transposes the array
	for(int y = 0; y < TETRIMINO_GRID_SIZE; y++)
		for(int x = 0; x < TETRIMINO_GRID_SIZE; x++)
			tempGrid[x][y] = grid[y][x];

	// Reverses the columns putting the result in grid[][]
	for(int x = 0; x < TETRIMINO_GRID_SIZE; x++)
	{
		for(int y = 0; y < TETRIMINO_GRID_SIZE; y++)
			grid[TETRIMINO_GRID_SIZE - y - 1][x] = tempGrid[y][x];
	}
}

void Tetrimino::rotateRight()
{
	int tempGrid[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];

	// Transposes the array
	for (int y = 0; y < TETRIMINO_GRID_SIZE; y++)
		for (int x = 0; x < TETRIMINO_GRID_SIZE; x++)
			tempGrid[x][y] = grid[y][x];

	// Reverses the rows putting the result in grid[][]
	for(int y = 0; y < TETRIMINO_GRID_SIZE; y++)
	{
		for(int x = 0; x < TETRIMINO_GRID_SIZE; x++)
			grid[y][TETRIMINO_GRID_SIZE - x - 1] = tempGrid[y][x];
	}
}

void Tetrimino::moveLeft()
{
	location.col -= 1;
}

void Tetrimino::moveRight()
{
	location.col += 1;
}

void Tetrimino::moveDown()
{
	location.row += 1;
}

void Tetrimino::moveUp()
{
	location.row -= 1;
}

int Tetrimino::getRandomNumber(int low, int high)
{
	static bool firstTime=true;
	int randNum;

	//if first time called, seed random number generator
	if (firstTime)
	{
		srand( static_cast<unsigned int>(time(NULL)) );
		firstTime=false;
	}

	//generate random number between given low and high values (inclusive)
	randNum = rand() % (high-low+1) + low;

	return randNum;
}
