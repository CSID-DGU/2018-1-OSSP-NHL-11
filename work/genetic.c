#include <stdlib.h>
#include <stdio.h>
#include "tetris.h"
#include <math.h>


/* Randomizes a 0.001 float number between lowerbound and upperbound */
float randomHundredth(float lowerBound, float upperBound) {
 float x;

 /* Random number between lowerBound and upperBound */
 x = (float)rand() / (float)(RAND_MAX / (float)(upperBound - lowerBound));
 x += (float)lowerBound;

 /* Rounding to the first tenth number */
 x *= 100.0;
 //x = floorf(x);
 x = ((float)(int)(x*10)/10);
 x /= 100.0;
 return x;
}

/* Randomizes a float 0.01 number between lowerbound and upperbound */
float randomTenth(short lowerBound, short upperBound) {
 float x;

 /* Random number between lowerBound and upperBound */
 x = (float)rand() / (float)(RAND_MAX / (float)(upperBound - lowerBound));
 x += (float)lowerBound;

 /* Rounding to the first tenth number */
 x *= 10.0;
 //x = floorf(x);
 x = ((float)(int)(x*10)/10);
 x /= 10.0;
 return x;
}

/* Randomizes a float number between lowerbound and upperbound, without rounding it */
float randomFloat(short lowerBound, short upperBound) {
 float x;

 /* Random number between lowerBound and upperBound */
 x = (float)rand() / (float)(RAND_MAX / (float)(upperBound - lowerBound));
 x += (float)lowerBound;

 return x;
}

/* Creates an initial population for Genetic Algorithm */
Population* initialPopulation() {
 Population* pop = malloc(sizeof(Population));
 short i, j;

 for (i = 0; i<GENES_NB; i++) { // 인디비주얼의 개수
  pop->genes[i].score = 0;
  for (j = 0; j<COEF_NB; j++) // 가중치 개수
   pop->genes[i].coefs[j] = -1 * randomFloat(0, 1);
  pop->genes[i].coefs[0] = -1 * pop->genes[i].coefs[0]; // all negative except the first one
 }

 pop->genesNumber = GENES_NB;

 return pop;
}

/* Makes individuals play gamesNb games in Population pop */
void fitness(Population* pop, short gamesNb, int piecesSize) {

 short piecesArray[piecesSize];

 int i, j;

 for (i = 0; i<gamesNb; i++) {
  //generatePiecesFile(piecesSize);
  //readPiecesFile("pieces", piecesArray, piecesSize);
  for (j = 0; j < piecesSize; j++)
  {
	piecesArray[i] = rand() % 7;
  }
  for (j = 0; j<pop->genesNumber; j++) 
  {
	printf("Gene %d, game %d\n", j, i);
	pop->genes[j].score += playAIGame(piecesArray, piecesSize, pop->genes[j].coefs);
  }
 }

 fitnessCalculation(pop, piecesSize, gamesNb);
}


/* Generates the next population */
Population* nextPopulation(Population* parent, int piecesSize, short gamesNb) {
 int i;

 /* Initializing new population */
 Population* nextPop = malloc(sizeof(Population));
 nextPop->genesNumber = parent->genesNumber;

 for (i = 0; i<nextPop->genesNumber; i++) { // 인디비주얼을 다음 세대꺼로 바꿔주는데
  nextPop->genes[i].score = 0;
  reproduction(parent, nextPop, selection(parent), selection(parent), i); // 가중치값을 부모와 비슷하게 바꿔버림
  mutation(nextPop, i); // 돌연변이 : 랜덤으로 새로운 값을 만든다.
 }
 return nextPop;

}

/* Calculate the fitness of each individual in parent */
void fitnessCalculation(Population* parent, int piecesSize, short gamesNb) {
 int i;
 /* the max score for 1 game is 1 * piecesSize + 4 *  piecesSize, because for every 10 pieces, we can gain 20 points by removing a row + 10 points by adding 10 pieces */
 float maxScore = 5 * piecesSize * gamesNb;
 for (i = 0; i<parent->genesNumber; i++) {
  parent->genes[i].fitness = parent->genes[i].score / maxScore;
 }
}

/* Performs a weighted selection of an individual in parent */
short selection(Population* parent) {
 short parentRandomlySelected;
 float randomlyGeneratedNumber = randomFloat(parent->genes[searchLowestFitness(parent)].fitness, 1.0);
 short counter = 0;

 do {
  parentRandomlySelected = rand() % parent->genesNumber;
  counter++;

 } while (randomlyGeneratedNumber > parent->genes[parentRandomlySelected].fitness && counter < GENES_NB);
 return parentRandomlySelected;
}

/* Reproducts 2 given parents to create 1 child */
void reproduction(Population* parent, Population* next, short parentA, short parentB, short child) { // 랜덤하게 윗세대 중 두 개의 individual(곧 부모)를 가져옴
 short i;
 short parentSelectedToGiveCoef;
 short variationToCoef;
 for (i = 0; i<COEF_NB; i++) { // 가중치의 개수
  parentSelectedToGiveCoef = rand() % 2; // 0 혹은 1 생성
  next->genes[child].coefs[i] = (parentSelectedToGiveCoef == 0 ? parent->genes[parentA].coefs[i] : parent->genes[parentB].coefs[i]); // 부모 a와 b를 선택
  variationToCoef = rand() % 3; // 0 혹은 1 혹은 2 생성
  if (variationToCoef == 1) // 1이면 부모값에서 아주 약간 증가(+0.001)
   next->genes[child].coefs[i] += PRECISION;
  else if (variationToCoef == 2) // 1이면 부모값에서 아주 약간 감소(-0.001)
   next->genes[child].coefs[i] -= PRECISION;
  // 0이면 부모값 그대로 감(변화 없음)
 }
}

/* Mutates a child */
void mutation(Population* next, short genomeToMutate) {
 short i;
 if (randomHundredth(0, 1) <= MUT_FACTOR) { // 0.05보다 작으면 돌연변이 시작
  for (i = 0; i<COEF_NB; i++) // 가중치의 개수
   next->genes[genomeToMutate].coefs[i] = -1 * randomFloat(0, 1); // 정말 아주 랜덤하게 바꿔버림
  next->genes[genomeToMutate].coefs[0] = -1 * next->genes[genomeToMutate].coefs[0];
 }
}

/* Performs the global genetic algorithm */
void geneticAlgorithm(short generationNb, short gamesNb, int piecesSize) {
 Population* parent = initialPopulation(); // 처음 individual을 만든다.("GEN000.txt") 그니까 처음 가중치값을 랜덤으로 생성
 Population* child;
 short bestGene;
 char filename[] = "GEN001.txt";
 FILE* resultFile;
 short i;

 for (i = 0; i<generationNb; i++) {

  /* Modifying the filename */
  filename[3] = i / 100 + '0';
  filename[4] = (i / 10) % 10 + '0';
  filename[5] = i % 10 + '0';

  resultFile = fopen(filename, "w");
  fprintf(resultFile, "\n#####Generation n° %d#####\n", i);
  printf("\n#####Generation n° %d#####\n", i);


  fitness(parent, gamesNb, piecesSize); // 게임을 진행함
  printAllGenesCoefsAndFitness(resultFile, parent); // 가중치값을 txt에 출력
  child = nextPopulation(parent, piecesSize, gamesNb); // 다음 individual을 만든다.

  fprintf(resultFile, "\nBEST GENE\n"); // 최고의 가중치값을 파일에 작성
  bestGene = searchBestGene(parent);
  printGeneCoefficients(resultFile, parent->genes[bestGene]);

  free(parent);
  parent = child; // 아까 만든 individual을 parent에 넣어줌
  fclose(resultFile);
 }

 free(child);
}

/* Prints the coefficient of an individual */
void printGeneCoefficients(FILE* file, Gene gene) {
 short i;
 for (i = 0; i<COEF_NB; i++)
  fprintf(file, "%f ", gene.coefs[i]);
}

/* Prints all individuals coefficients */
void printAllGenesCoefsAndFitness(FILE* file, Population* pop) {
 short i;
 for (i = 0; i<pop->genesNumber; i++) {
  printGeneCoefficients(file, pop->genes[i]);
  fprintf(file, "fitness: %f, score %d\n", pop->genes[i].fitness, pop->genes[i].score);
 }
}

/* Searches for the most fit individual */
short searchBestGene(Population* pop) {
 float maxFitness = pop->genes[0].fitness;
 short bestGene = 0;
 short i;

 /* Finding the gene that has the best fitness */
 for (i = 1; i<pop->genesNumber; i++) {
  if (pop->genes[i].fitness > maxFitness) {
   bestGene = i;
   maxFitness = pop->genes[i].fitness;
  }
 }

 return bestGene;
}

/* Searches for the lowest fitness */
short searchLowestFitness(Population* pop) {
 float minFitness = pop->genes[0].fitness;
 short worstGene = 0;
 short i;

 /* Finding the gene that has the best fitness */
 for (i = 1; i<pop->genesNumber; i++) {
  if (pop->genes[i].fitness < minFitness) {
   worstGene = i;
   minFitness = pop->genes[i].fitness;
  }
 }

 return worstGene;
}

 
