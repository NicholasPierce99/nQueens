//Nicholas Pierce
//N Queens problem using 2d matrix and stack
//csci 362

#include <iostream>
#include <stack>
#include "Queen.h"
#define N 8

//declare stack of type "Queen" using made queen object
//queen objects have both x and y coordinates
std::stack <Queen> stack;
//filled integer to keep track of amount of filled queens
static int filled = 0;

//print the found solution
void printSolution(int gameBoard[N][N]) {
	//specifically print x and y coordinates of top member of stack and matrix coordinates
	for (int i = 0; i < N; i++) {
		std::cout << " ( " << stack.top().x << ", " << stack.top().y<< " ) ";
		stack.pop();
		for (int j = 0; j < N; j++) {
			std::cout << gameBoard[i][j];
		}
		std::cout << std::endl;
	}
}
//check if queen is safe to place
bool safePlace(int gameBoard[N][N], int x, int y) {
	int i, j;
	//check for row conflicts
	for(i = 0; i < y; i++) {
		if(gameBoard[x][i]) {
			return false;
		}
	}
	//this mess checks for upper diagonal conflicts
	for(i = x, j = y; i >= 0 && j >= 0; i--, j--) {
		if(gameBoard[i][j]) {
			return false;
		}
	}
	//this mess checks for lower diagonal conflicts
	for (i = x, j = y; j >= 0 && i < N; i++, j--) {
		if(gameBoard[i][j]) {
			return false;
		}
	}
	return true;
}
//function that "solves" the problem, by repeatedly checking the placement of queens in the board
//specifically, place a queen, check if it works using the matrix as logic, push to stack and if it doesn't work, pop and try again
bool solveProblem(int gameBoard[N][N], int y) {
	if (filled == N) {
		return true;
	}
	//places queen, in stack, increment filled by 1
	for(int i = 0; i < N; i++) {
		if (safePlace(gameBoard, i, y)) {
			
			//place queen in board
			//push queen to stack
			gameBoard[i][y] = 1;
			
			stack.push(Queen(y, i));
			
			filled = filled + 1;
			
			if(solveProblem(gameBoard, y + 1)) {
				return true;
			}
			//if placing queen doesn't work, backtrack
			//place 0 in game board matrix
			//pop queen from stack
			gameBoard[i][y] = 0;
			stack.pop();
			filled = filled - 1;
		}
		
	}
	return false;
}
//run solveProblem function, check for invalid N and creates empty board 
bool solveNQueens() {
	//2d empty matrix
	int gameBoard[N][N] = { {0, 0, 0, 0},
        					{0, 0, 0, 0},
       						{0, 0, 0, 0},
        					{0, 0, 0, 0}
	};
	//check if N is defined to be less than 4, because n queens doesn't work for N less than 4
	if(solveProblem(gameBoard, filled) == false) {
		std::cout << "n queens doesn't work for N less than 4";
		return false;
	}
	printSolution(gameBoard);
	return true;

}
//initialize the stack, and push a queen to position 1
void initializeStack(std::stack <Queen> x) {
	stack.push(Queen(0, 0));
	
}
//main function, runs stack initializer and recursive solution to n queens problem
int main() {
	initializeStack(stack);
	solveNQueens();
	return 0;
}