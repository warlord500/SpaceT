#ifndef ENUMS_H
#define ENUMS_H

	// the following enum uses the url below as refernce
    // http://mercurymasterpunk.ca/images/tetris.jpg
  enum BlockShapes
    {
        random,
        I_shape,
        J_shape,
        L_shape,
        O_shape,
        Z_shape,
        T_shape,
        S_shape
    };

    /*
        Enum: BlockColors
            the block colors that exist
    */
    enum BlockColors
    {
        Empty,
        Cyan,
        Yellow,
        Orange,
        Blue,
        Green,
        Red,
        Purple
    };

#endif // TETRISENUMS_HPP_INCLUDED
