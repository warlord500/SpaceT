#include <iostream>
#include <tetris/Well.h>

Well::Well()
{
	height = BOARD_HEIGHT;
	width = BOARD_WIDTH;

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			board[y][x] = Empty;
}

bool Well::tetriminoFit(const Tetrimino willItFit) const
{
	bool doesFit = true;
	int tempGrid[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];
	willItFit.getGrid(tempGrid);
	tetriminoLocation tempLocation = willItFit.getLocation();
	for (int y = 0; y < TETRIMINO_GRID_SIZE; y++)
	{
		for (int x = 0; x < TETRIMINO_GRID_SIZE; x++)
		{
			// Tests to see if the piece would be outside of the well
			if (tempGrid[y][x] == 1 &&
				(tempLocation.row + y >= BOARD_HEIGHT
					|| tempLocation.col + x >= BOARD_WIDTH
					|| tempLocation.col + x < 0))
				doesFit = false;
			// Tests to see if there is already a block occupying the target square
			if (tempGrid[y][x] == 1 && board[tempLocation.row + y][tempLocation.col + x] != Empty)
				doesFit = false;
		}
	}
	return doesFit;
}

void Well::addTetriminoToWell(const Tetrimino toBeAdded)
{
	int tempGrid[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];
	toBeAdded.getGrid(tempGrid);
	tetriminoLocation tempLocation = toBeAdded.getLocation();
	BlockColors tempColor = toBeAdded.getColor();
	for (int y = 0; y < TETRIMINO_GRID_SIZE; y++)
		for (int x = 0; x < TETRIMINO_GRID_SIZE; x++)
			if (tempGrid[y][x] == 1)
				board[tempLocation.row + y][tempLocation.col + x] = tempColor;
}

int Well::clearFullRows()
{
	int rowsCleared = 0;

	for (int y = 0; y < height; y++)
	{
		if (rowIsFull(y))
		{
			moveRowsDown(y - 1);
			rowsCleared++;
		}
	}

	return rowsCleared;
}

bool Well::rowIsFull(int row)
{
	bool rowFull = true;
	for (int col = 0; col < width; col++)
		if (board[row][col] == ' ')
			rowFull = false;
	return rowFull;
}

void Well::moveRowsDown(int firstRowToMove)
{
	for (;firstRowToMove >= 0; firstRowToMove--)
	{
		for (int col = 0; col < width; col++)
			board[firstRowToMove + 1][col] = board[firstRowToMove][col];
	}

	// Fills top row with blanks.
	for (int col = 0; col < width; col++)
		board[0][col] = Empty;
}

bool Well::topReached() const
{
	bool isReached = false;
	for (int x = 0; x < width; x++)
		if (board[0][x] != ' ')
			isReached = true;

	return isReached;
}

void Well::getBoard(BlockColors boardCopy[][BOARD_WIDTH]) const
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			boardCopy[y][x] = board[y][x];
}
