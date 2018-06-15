#ifndef __TETRIS_H__
#define __TETRIS_H__


/* * * * * *
 * MACROS 
 * * * * * */
 /** Length of a generated pieces file */
#define LENGTH 1000

/** If set to 1, display the game board for every move played, if set to 0, displays only the final game board */
#define DISPLAY 1
 
/** Board Height */
#define T_HEIGHT 20 //24
/** Visible Board Height */
#define T_HEIGHT_VIS 18 //20
/** Board Width */
#define T_WIDTH 12 //10

/** Size of a Tetrimino */
#define TETRI_SIZE 4
/** Default number of rotations */
#define T_ROTATION 4

/** Constants for Tetriminos */
#define TETRI_O 0
#define TETRI_J 1
#define TETRI_L 2
#define TETRI_I 3
#define TETRI_Z 4
#define TETRI_S 5
#define TETRI_T 6
//추가
#define TETRI_P 7 //+ 블록
#define TETRI_N 8 //. 블록
#define TETRI_M 9 //작은 ㄱ 블록

/** Contsants for rotations */
#define ROT_0 0
#define ROT_1 1
#define ROT_2 2
#define ROT_3 3

/** Coefficient to apply to a cleared line */
#define ROW_VALUE_COEFF 10

/** Error code */
#define ERROR -1


/** Default depth of Depth-First Search */
#define DEPTH 2

/** Number fo Generations for Genetic Algorithm */
#define GENETIC_GENERATIONS_NB 70 //100
/** Number fo Generations for Genetic Algorithm */
#define GENETIC_GAMES_NB 10 //10
/** Number of pieces per game */
#define GENETIC_PIECES_LENGTH 10000
/** Number fo coefficients for Genetic ALgorithm */
#define COEF_NB 4
/** Number fo individuals in a population */
#define GENES_NB 25 //100
/** Mutation factor */
#define MUT_FACTOR 0.05

/** Defines the precision of heuristic's coefficients */
#define PRECISION 0.001

/** Number of games for hill climbing */
#define HILL_CLIMBING_GAMES_NB 10
/** Length of pieces file for hill climbing */
#define HILL_CLIMBING_GAME_LENGTH 10000


/* * * * * *
 * GLOBALS 
 * * * * * */
/** Array of predefined coefficients for heuristic */
extern float DEFAULT_COEFS[COEF_NB];


/* * * * * *
 * DATA STRUCTURES 
 * * * * * */
 
/** 
 * Tetrimino Structure
 * */
typedef struct Tetrimino {
	short array[TETRI_SIZE][TETRI_SIZE];
	short type;
} Tetrimino;

/** 
 * Game Structure
 * */
typedef struct Game {
	unsigned short array[T_HEIGHT];
	unsigned long long score;
} Game;

/** 
 * Move Structure
 * */
typedef struct Move {
	short x;
	short rotation;
	float heuristic;
} Move;

/** 
 * Gene Structure
 * */
typedef struct Gene {
	float coefs[COEF_NB];
	int score;
	float fitness;
} Gene;

/** 
 * Population Structure
 * */
typedef struct Population {
	Gene genes[GENES_NB];
	short genesNumber;
} Population;


/** 
 * Bitboard.c
 * */
unsigned short getBitboardValue(unsigned short bitboard, unsigned short indexToRetrieve);
unsigned short setBitboardValue(unsigned short bitboard, unsigned short indexToRetrieve, unsigned short value);

 
/* * * * * *
 * PROTOTYPES 
 * * * * * */
 
 /**
 *  Game.c
 * */
 
Game* createGame();
Game* copyGame(Game* game);
short addTetrimino(Game* game, Tetrimino* tet, short x);
short cancelAdding(Game* game, Tetrimino* tet, short x);
short canGoDown(Game* game, short x, short y, Tetrimino* tet);
short maxHeight(Game* game);
short removeRows(Game* game);
short maxTetX(Tetrimino* tet);
short tetUpperLeftCase(Tetrimino* tet);
short maxTetY(Tetrimino* tet);
void displayGameBoard(Game* game);
void freeGame(Game* game);

/** 
 * Tetrimino.c
 * */
Tetrimino* createTetrimino(short type);
void rotate(Tetrimino* tet, short rotation);
void rotateO(Tetrimino* tet, short rotation);
void rotateJ(Tetrimino* tet, short rotation);
void rotateL(Tetrimino* tet, short rotation);
void rotateI(Tetrimino* tet, short rotation);
void rotateZ(Tetrimino* tet, short rotation);
void rotateS(Tetrimino* tet, short rotation);
void rotateT(Tetrimino* tet, short rotation);
void rotateP(Tetrimino* tet, short rotation);
void rotateN(Tetrimino* tet, short rotation);
void rotateM(Tetrimino* tet, short rotation);
void displayTetrimino(Tetrimino* tetrimino);
void freeTetrimino(Tetrimino* tetrimino);

/** 
 * GameManager.c
 * */
void generatePiecesFile(int size);
void generateMovesFile(int size);
short playAMove(Game* game, Tetrimino* tet, short x, short rotation);
int playAGame(int numberOfTetriminos, short* piecesArray, int piecesSize, Move* movesArray, int movesSize);
int readPiecesFile(char* filename, short* piecesArray, int maxReadableSize);
int readMovesFile(char* filename, Move* movesArray, int maxReadableSize);

/** 
 * AI.c
 * */
unsigned long long playAIGame(short* piecesArray, unsigned long long piecesSize, float* coefs);
Move determineMove(Game* game, short depth, short* tetList, unsigned long long indexList, unsigned long long tetSize, float* coefs);
short possibleMoves(Game* game, Tetrimino* tet, Move* moves);
float heuristic(Game* game, float* coefs);
short countCompleteLines(Game* game);
short countHoles(Game* game);
short computeTotalHeight(Game* game);
short computeHollowness(Game* game);
short maxColumnHeight(Game* game, short columnNb);

/** 
 * Genetic.c
 * */
float randomTenth(short lowerBound, short upperBound);
float randomFloat(short lowerBound, short upperBound);
Population* initialPopulation();
void fitness(Population* pop, short gamesNb, int piecesSize);
Population* nextPopulation(Population* parent, int piecesSize, short gamesNb);
void fitnessCalculation(Population* parent, int piecesSize, short gamesNb);
short selection(Population* parent);
void reproduction(Population* parent, Population* next, short parentA, short parentB, short child);
void mutation(Population* next, short genomeToMutate);
void geneticAlgorithm(short generationNb, short gamesNb, int piecesSize);
void printGeneCoefficients(FILE* file, Gene gene);
void printAllGenesCoefsAndFitness(FILE* file, Population* pop);
short searchBestGene(Population* pop);
short searchLowestFitness(Population* pop);

/**
 * HillCLimbing.c
 * */
void hillClimbing();
short specificCoefHillClimbing(short** pieces, float* coefs, short* directions, short indexToHillClimb, FILE* f);
short determineDirection(float* coefs, short indexToDetermine);

#endif

