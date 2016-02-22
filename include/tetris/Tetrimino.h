#ifndef TETRIS_TETRIMINO
#define TETRIS_TETRIMINO

#include <tetris/Enums.h>


namespace Tetris
{
const int TETRIMINO_GRID_SIZE = 4;

struct tetriminoLocation
{
	int row;
	int col;
};

class Tetrimino
{
public:
	// The ‘type’ parameter will determine which piece we initialize grid to
	Tetrimino(BlockShapes type = random_shape);

	BlockColors getColor() const;
	tetriminoLocation getLocation() const;
	void getGrid(int gridOut[][TETRIMINO_GRID_SIZE]) const;

	void setLocation(tetriminoLocation newLocation);
	void setLocation(int row, int col);

	void rotateLeft();
	void rotateRight();
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveUp();

	void dataDump() const;
	void printGrid(const int toBePrinted[][TETRIMINO_GRID_SIZE]) const;

private:
	int grid[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];
	BlockColors color;
	tetriminoLocation location;
	int getRandomNumber(int low, int high);
};
}

#endif
