#ifndef ENUMS_H
#define ENUMS_H

namespace Tetris
{
	// the following enum uses the url below as refernce
    // http://mercurymasterpunk.ca/images/tetris.jpg
enum BlockShapes
{
	random_shape,
	I_shape,
	J_shape,
	L_shape,
	O_shape,
	Z_shape,
	T_shape,
	S_shape
};

enum BlockColors
{
	Staging,
	Empty,
	Cyan,
	Yellow,
	Orange,
	Blue,
	Green,
	Red,
	Purple
};
}

#endif // TETRISENUMS_HPP_INCLUDED
