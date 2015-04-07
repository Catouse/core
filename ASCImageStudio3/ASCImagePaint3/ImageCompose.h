// ImageCompose.h : Declaration of the composition constants

#pragma once

/////////////////////////////////////////////////////////////////
// Constants

// dost
const BYTE c_byPatternDots[8][8] = 
{
	{1,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{1,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0}
};

// dots dense
const BYTE c_byPatternDotsDense[8][8] = 
{
	{1,0,1,0,1,0,1,0},
	{0,0,0,0,0,0,0,0},
	{1,0,1,0,1,0,1,0},
	{0,0,0,0,0,0,0,0},
	{1,0,1,0,1,0,1,0},
	{0,0,0,0,0,0,0,0},
	{1,0,1,0,1,0,1,0},
	{0,0,0,0,0,0,0,0}
};

// grid
const BYTE c_byPatternGrid[8][8] = 
{
	{1,1,1,1,1,1,1,1},
	{1,0,0,0,1,0,0,0},
	{1,0,0,0,1,0,0,0},
	{1,0,0,0,1,0,0,0},
	{1,1,1,1,1,1,1,1},
	{1,0,0,0,1,0,0,0},
	{1,0,0,0,1,0,0,0},
	{1,0,0,0,1,0,0,0}
};

// grid rotated
const BYTE c_byPatternGridRotated[8][8] = 
{
	{1,0,0,0,0,0,0,1},
	{0,1,0,0,0,0,1,0},
	{0,0,1,0,0,1,0,0},
	{0,0,0,1,1,0,0,0},
	{0,0,0,1,1,0,0,0},
	{0,0,1,0,0,1,0,0},
	{0,1,0,0,0,0,1,0},
	{1,0,0,0,0,0,0,1}
};

// line vertical
const BYTE c_byPatternLineVertical[8][8] = 
{
	{1,0,0,0,1,0,0,0},
	{1,0,0,0,1,0,0,0},
	{1,0,0,0,1,0,0,0},
	{1,0,0,0,1,0,0,0},
	{1,0,0,0,1,0,0,0},
	{1,0,0,0,1,0,0,0},
	{1,0,0,0,1,0,0,0},
	{1,0,0,0,1,0,0,0}
};

// line horizontal
const BYTE c_byPatternLineHorizontal[8][8] = 
{
	{1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0}
};

// line diagonal
const BYTE c_byPatternLineDiagonal[8][8] = 
{
	{0,0,0,1,0,0,0,0},
	{0,0,1,0,0,0,0,0},
	{0,1,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,1,0},
	{0,0,0,0,0,1,0,0},
	{0,0,0,0,1,0,0,0}
};

// line diagonal rotated
const BYTE c_byPatternLineDiagonalRotated[8][8] =
{
	{0,0,0,0,1,0,0,0},
	{0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0},
	{0,0,0,1,0,0,0,0}
};

// chess board
const BYTE c_byPatternChessBoard[8][8] =
{
	{1,1,1,1,0,0,0,0},
	{1,1,1,1,0,0,0,0},
	{1,1,1,1,0,0,0,0},
	{1,1,1,1,0,0,0,0},
	{0,0,0,0,1,1,1,1},
	{0,0,0,0,1,1,1,1},
	{0,0,0,0,1,1,1,1},
	{0,0,0,0,1,1,1,1}
};

// dashes
const BYTE c_byPatternDashes[8][8] =
{
	{1,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0},
	{0,0,0,0,0,1,0,0},
	{0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,0,0}
};

// spiner
const BYTE c_byPatternSpiner[8][8] =
{
	{0,0,0,1,0,1,0,0},
	{0,0,0,0,1,1,0,0},
	{1,1,0,0,1,0,0,0},
	{0,1,1,1,1,0,0,1},
	{1,0,0,1,1,1,1,0},
	{0,0,0,1,0,0,1,1},
	{0,0,1,1,0,0,0,0},
	{0,0,1,0,1,0,0,0}
};

// thatches
const BYTE c_byPatternThatches[8][8] =
{
	{1,1,1,1,1,0,0,0},
	{0,1,1,1,0,1,0,0},
	{0,0,1,0,0,0,1,0},
	{0,1,0,0,0,1,1,1},
	{1,0,0,0,1,1,1,1},
	{0,0,0,1,0,1,1,1},
	{0,0,1,0,0,0,1,0},
	{0,1,1,1,0,0,0,1}
};

// empty
const BYTE c_byPatternEmpty[8][8] =
{
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0}
};

/////////////////////////////////////////////////////////
// Mosaic patterns

// spiral in
const BYTE c_byMosaicSpiralIn[8][8] = 
{
	{ 0, 1, 2, 3, 4, 5, 6, 7},
	{27,28,29,30,31,32,33, 8},
	{26,47,48,49,50,51,34, 9},
	{25,45,59,60,61,52,35,10},
	{24,45,58,63,62,53,36,11},
	{23,44,57,56,55,54,37,12},
	{22,43,42,41,40,39,38,13},
	{21,20,19,18,17,16,15,14}
};

// spiral out
const BYTE c_byMosaicSpiralOut[8][8] = 
{
	{42,43,44,45,46,47,48,49},
	{41,20,21,22,23,24,25,50},
	{40,19, 6, 7, 8, 9,26,51},
	{39,18, 5, 0, 1,10,27,52},
	{38,17, 4, 3, 2,11,28,53},
	{37,16,15,14,13,12,29,54},
	{36,35,34,33,32,31,30,55},
	{63,62,61,60,59,58,57,56}
};

// strips
const BYTE c_byMosaicStrips[8][8] = 
{
	{ 7,15,23,31,39,47,55,63},
	{63,55,47,39,31,23,15, 7},
	{ 7,15,23,31,39,47,55,63},
	{63,55,47,39,31,23,15, 7},
	{ 7,15,23,31,39,47,55,63},
	{63,55,47,39,31,23,15, 7},
	{ 7,15,23,31,39,47,55,63},
	{63,55,47,39,31,23,15, 7}
};

// dissolve
const BYTE c_byMosaicDissolve[8][8] = 
{
	{35,55,19,59,35,55,19,59},
	{47,23,63,31,47,23,63,31},
	{27,51,39,11,27,51,39,11},
	{43,15, 7, 3,43,15, 7, 3},
	{35,55,19,59,35,55,19,59},
	{47,23,63,31,47,23,63,31},
	{27,51,39,11,27,51,39,11},
	{43,15, 7, 3,43,15, 7, 3}
};

// random
const BYTE c_byMosaicRandom[8][8] = 
{
	{ 0,54,48,13,61, 5,51,45},
	{24,29, 4,33,44,25, 9,20},
	{43,63,37,55,17,30,40,56},
	{21,14,23,10,27,12, 2,32},
	{38,53,34,47, 1,62,46, 8},
	{59, 7,57,22,39,18,36,41},
	{15,42,16,60,11,50,31,19},
	{49,28, 3,35,58,26, 6,52}
};

// diagonal left-bottom
const BYTE c_byMosaicDiagonalLeftBottom[8][8] = 
{
	{ 0, 4, 8,13,17,21,26,30},
	{ 4, 8,13,17,21,26,30,34},
	{ 8,13,17,21,26,30,34,39},
	{13,17,21,26,30,34,39,43},
	{17,21,26,30,34,39,43,48},
	{21,26,30,34,39,43,48,52},
	{26,30,34,39,43,48,52,57},
	{30,34,39,43,48,52,57,63}
};

// diagonal left-top
const BYTE c_byMosaicDiagonalLeftTop[8][8] = 
{
	{31,35,39,44,49,53,58,63},
	{27,31,35,39,44,49,53,58},
	{21,27,31,35,39,44,49,53},
	{17,21,27,31,35,39,44,49},
	{13,17,21,27,31,35,39,44},
	{ 9,13,17,21,27,31,35,39},
	{ 4, 9,13,17,21,27,31,35},
	{ 0, 4, 9,13,17,21,27,31}
};

// diagonal right-bottom
const BYTE c_byMosaicDiagonalRightBottom[8][8] = 
{
	{31,27,21,17,13, 9, 4, 0},
	{35,31,27,21,17,13, 9, 4},
	{39,35,31,27,21,17,13, 9},
	{44,39,35,31,27,21,17,13},
	{49,44,39,35,31,27,21,17},
	{53,49,44,39,35,31,27,21},
	{59,53,49,44,39,35,31,27},
	{63,59,53,49,44,39,35,31}
};

// diagonal right-top
const BYTE c_byMosaicDiagonalRightTop[8][8] = 
{
	{63,59,53,49,44,39,35,31},
	{59,53,49,44,39,35,31,27},
	{53,49,44,39,35,31,27,21},
	{49,44,39,35,31,27,21,17},
	{44,39,35,31,27,21,17,13},
	{39,35,31,27,21,17,13, 9},
	{35,31,27,21,17,13, 9, 4},
	{31,27,21,17,13, 9, 4, 0}
};

// wall left
const BYTE c_byMosaicWallLeft[8][8] = 
{
	{ 0,15,16,31,32,47,48,63},
	{ 1,14,17,30,33,46,49,62},
	{ 2,13,18,29,34,45,50,61},
	{ 3,12,19,28,35,44,51,60},
	{ 4,11,20,27,36,43,52,59},
	{ 5,10,21,26,37,42,53,58},
	{ 6, 9,22,25,38,41,54,57},
	{ 7, 8,23,24,39,40,55,56}
};

// wall right
const BYTE c_byMosaicWallRight[8][8] = 
{
	{63,48,47,32,31,16,15, 0},
	{62,49,46,33,30,17,14, 1},
	{61,50,45,34,29,18,13, 2},
	{60,51,44,35,28,19,12, 3},
	{59,52,43,36,27,20,11, 4},
	{58,53,42,37,26,21,10, 5},
	{57,54,41,38,25,22, 9, 6},
	{56,55,40,39,24,23, 8, 7}
};

// wall bottom
const BYTE c_byMosaicWallBottom[8][8] = 
{
	{ 0, 1, 2, 3, 4, 5, 6, 7},
	{15,14,13,12,11,10, 9, 8},
	{16,17,18,19,20,21,22,23},
	{31,30,29,28,27,26,25,24},
	{32,33,34,35,36,37,38,39},
	{47,46,45,44,43,42,41,40},
	{48,49,50,51,52,53,54,55},
	{63,62,61,60,59,58,57,56}
};

// wall top
const BYTE c_byMosaicWallTop[8][8] = 
{
	{63,62,61,60,59,58,57,56},
	{48,49,50,51,52,53,54,55},
	{47,46,45,44,43,42,41,40},
	{32,33,34,35,36,37,38,39},
	{31,30,29,28,27,26,25,24},
	{16,17,18,19,20,21,22,23},
	{15,14,13,12,11,10, 9, 8},
	{ 0, 1, 2, 3, 4, 5, 6, 7}
};

// chess left
const BYTE c_byMosaicChessLeft[8][8] = 
{
	{ 0,36, 8,44,16,52,24,60},
	{32, 4,40,12,48,20,56,28},
	{ 1,37, 9,45,17,53,25,61},
	{33, 5,41,13,49,21,57,29},
	{ 2,38,10,46,18,54,26,62},
	{34, 6,42,14,50,22,59,30},
	{ 3,39,11,47,19,55,27,63},
	{35, 7,43,15,51,23,59,31}
};

// chess right
const BYTE c_byMosaicChessRight[8][8] = 
{
	{60,24,52,16,44, 8,36, 0},
	{28,56,20,48,12,40, 4,32},
	{61,25,53,17,45, 9,37, 1},
	{29,57,21,49,13,41, 5,33},
	{62,26,54,18,46,10,38, 2},
	{30,59,22,50,14,42, 6,34},
	{63,27,55,19,47,11,39, 3},
	{31,59,23,51,15,43, 7,35}
};

// chess top
const BYTE c_byMosaicChessTop[8][8] = 
{
	{60,28,61,29,62,30,63,31},
	{24,56,25,57,26,58,27,59},
	{52,20,53,21,54,22,55,23},
	{16,48,17,49,18,50,19,51},
	{44,12,45,13,46,14,47,15},
	{ 8,40, 9,41,10,42,11,43},
	{36, 4,37, 5,38, 6,39, 7},
	{ 0,32, 1,33, 2,34, 3,35}
};

// chess bottom
const BYTE c_byMosaicChessBottom[8][8] = 
{
	{ 0,32, 1,33, 2,34, 3,35},
	{36, 4,37, 5,38, 6,39, 7},
	{ 8,40, 9,41,10,42,11,43},
	{44,12,45,13,46,14,47,15},
	{16,48,17,49,18,50,19,51},
	{52,20,53,21,54,22,55,23},
	{24,56,25,57,26,58,27,59},
	{60,28,61,29,62,30,63,31}
};

// counterclockwise
const BYTE c_byMosaicCounterClockwise[8][8] = 
{
	{60,61,63, 3, 5, 6, 9,12},
	{57,59,62, 2, 4, 8,11,13},
	{55,56,58, 1, 7,10,15,16},
	{54,53,52, 0,14,17,18,19},
	{51,50,48,34,24,22,20,21},
	{49,46,43,37,31,27,25,23},
	{47,44,41,38,35,32,28,26},
	{45,42,40,39,36,33,30,29}
};

// clockwise
const BYTE c_byMosaicClockwise[8][8] = 
{
	{ 9, 6, 5, 3,64,63,60,58},
	{10, 8, 4, 2,62,59,57,55},
	{13,12, 7, 1,61,56,54,53},
	{15,14,11, 0,48,49,50,51},
	{16,17,19,26,36,45,46,47},
	{18,20,22,29,34,39,42,44},
	{21,23,27,30,32,37,40,43},
	{24,25,28,31,33,35,38,41}
};

/////////////////////////////////////////////////////////////////