#ifndef WELL_H
#define WELL_H

#include "Tetrimino.h"

const int BOARD_HEIGHT = 24;
const int BOARD_WIDTH = 8;

class Well
{
public:
	Well();
	bool tetriminoFit(const Tetrimino willItFit) const;
	void addTetriminoToWell(const Tetrimino toBeAdded);
	int clearFullRows();
	bool topReached() const;
	void getBoard(BlockColors boardCopy[][BOARD_WIDTH]) const;
	void boardDump() const;
private:
	int height;
	int width;
	BlockColors board[BOARD_HEIGHT][BOARD_WIDTH];
	bool rowIsFull(int row);
    void moveRowsDown(int firstRowToMove);
};

#endif
