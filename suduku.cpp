#include <iostream>
#include <chrono>

const int WIDTH = 9;
const int HEIGHT = 9;

class Board {
	public:
		Board(int board[WIDTH][HEIGHT]) {
			// Initialize the board
			for(int i = 0; i < WIDTH; i++) {
				for(int j = 0; j < HEIGHT; j++) {
					_board[i][j] = board[i][j];
				}
			}
		}

		int get(int row, int col) { return _board[row][col]; }
		int set(int row, int col, int val) { _board[row][col] = val; }

		void printBoard() {
			for(int i = 0; i < WIDTH; i++) {
				for(int j = 0; j < HEIGHT; j++) {
					std::cout << _board[i][j] << " ";
					if(j != 0 && j != WIDTH-1 && ((j+1) % 3) == 0) std::cout << "| ";
				}
				std::cout << std::endl;
				if(i != 0 && i != HEIGHT -1 && ((i+1) % 3) == 0) std::cout << "---------------------\n";
			}
			std::cout << std::endl;
		}
			
	private:
		int _board[WIDTH][HEIGHT];
};


class Solver {
	public:
		Solver(Board& board) : _board(board) {}

		virtual bool isSolved() = 0;
		virtual bool isValid(int row, int col) = 0;

		virtual bool solve() = 0;
	protected:
		Board _board;

};


class BruteForceSolver : public Solver {
	public :
		BruteForceSolver(Board& board) : Solver(board) {}

		bool isSolved() override { return false; }

		bool solve() { 
			return solve(0,0);
		}
		
		bool solve(int row, int col) {
		
			// If x,y == number
				// Go on to next index
				// Return recursive call
			// Else (If x,y, == blank)
				// Using 1...9:
					// Put val in board, call solve recursively. Returns bool
						// True: That number was correct, return true
						// False: That number was incorrect, try the next
				// Set x,y to 0
				// Return false
			
			if(row == WIDTH && col == 0)
				return true; // Solved board

			// If blank
			if(_board.get(row,col) == 0) {
				// Find the correct number
				for(int i = 1; i < 10; i++) {
					_board.set(row,col,i);
					if(isValid(row,col)) {
					    	auto res = [&]() {
						if(col == WIDTH-1) {
					        	return solve(row+1,0);
						} else {
				         	   	return solve(row,col+1);
						}}();
						if(res) {
							return true;
						} 
					}
				}
				_board.set(row,col,0);
				return false;
			} else { // Preset-Number
				// Keep going
				if(col == WIDTH-1) {
			 		return solve(row+1,0);
				} 
				return solve(row,col+1);
			}
		}

		void print() {
			_board.printBoard();	
		}

	private:
		bool isValid(int row, int col) override {
			int value = _board.get(row,col);
			// Row check
			for(int i = 0; i < HEIGHT; ++i) {
				if(row == i) continue;
				if(_board.get(i,col) == value)
					return false;
			}
			// Col check
			for(int i = 0; i < WIDTH; ++i) {
				if(col == i) continue;
				if(_board.get(row,i) == value) return false;
			}
			// Square check
			int upperLeftRow = 3*(row / 3); // Intentional floor
			int upperLeftCol = 3*(col / 3); // Intentional floor
			
			for(int squareRow = upperLeftRow; squareRow < upperLeftRow+3; squareRow++) {
				for(int squareCol = upperLeftCol; squareCol < upperLeftCol+3; squareCol++) {
					if(squareRow == row && squareCol == col) continue;
					if(_board.get(squareRow, squareCol) == value) return false;
				}
			}
					

			// Passed all checks
			return true;	
		}
};

int main() {
/*
	int int_board[WIDTH][HEIGHT] = {{3, 0, 6, 5, 0, 8, 4, 0, 1},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};
*/
	int int_board[WIDTH][HEIGHT] = 
                     {{8,0,0,0,0,0,0,0,0},
                      {0,0,3,6,0,0,0,0,0},
                      {0,7,0,0,9,0,2,0,0},
                      {0,5,0,0,0,7,0,0,0},
                      {0,0,0,0,4,5,7,0,0},
                      {0,0,0,1,0,0,0,3,0},
                      {0,0,1,0,0,0,0,6,8},
                      {0,0,8,5,0,0,0,1,0},
                      {0,9,0,0,0,0,4,0,0}};

	Board board(int_board);
	
	BruteForceSolver solver(board);


	solver.print();	
	auto start = std::chrono::system_clock::now();
	if(solver.solve()) {	
		auto end = std::chrono::system_clock::now();
		solver.print();	

		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		// convert manually because if we casted in milliseconds we would get 0 by rounding
	   	std::cout << "Solving took " <<  elapsed.count() / 100000.0 << " milliseconds.\n";	
		return 0;
	}
	std::cout << "Problem was not solvable!\n";


	return 0;
}
