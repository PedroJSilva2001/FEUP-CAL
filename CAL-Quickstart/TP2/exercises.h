// By: Gonçalo Leão

#ifndef CAL_TP2_CLASSES_EXERCISES_H
#define CAL_TP2_CLASSES_EXERCISES_H

#include <vector>

// Ex 1
#define MAZE_WALL 0
#define MAZE_PATH 1
#define MAZE_EXIT 2

class Labyrinth {
public:
    Labyrinth(int values[10][10]);
    void print() const;
    bool findGoal(int x, int y);
private:
    int labyrinth[10][10];
    bool visited[10][10];
    void initializeVisited();
    bool findGoalRecursive(int x, int y);
        //TODO: Add other methods if needed
};

// Ex 2
#define IllegalArgumentException -1

class Sudoku
{
public:
    /**
     * Creates an empty puzzle
     */
    Sudoku();
    /**
     * Initializes a puzzle with initial content.
     * Throws an IllegalArgumentException if any cell has a value out of range or
     * a number is repeated in the same line, column or 3x3 block.
     *
     * @param nums Matrix with the initial cell values (0 for empty cell)
     */
    Sudoku(int nums[9][9]);
    /**
     * Checks if the puzzle has been completely solved.
     */
    bool isComplete() const;
    /**
     * Solves the puzzle.
     * Returns a boolean indicating if the puzzle is possible.
     */
    bool solve();
    /**
     * Determines the multiplicity of the puzzle's solutions.
     * It is a variant of the solve method.
     * Does not change the game's state.
     * Returns:
     *   0 if the puzzle has no solution,
     *   1 if the puzzle has a unique solution,
     *   >1 if the puzzle has two or more solutions (for efficiency reasnos, it does not count all of the solutions and stops on the second one)
     */
    int countSolutions();
    /**
     * Generates a puzzle with a unique solution and filled with as least cells as possible that ensure that the solution is unique.
     */
    void generate();
    /**
	 * Obtains the current of the puzzle (only for reading, not writing!).
	 */
    int **getNumbers();
    /**
     * Prints the solution.
     */
    void print() const;
private:
    /**
     * numbers[i][j] - number that occupies line i, column j (from 0 to 8)
     * 0 means the cell is empty.
     */
    int numbers[9][9];
    /**
     * Information derivable from numbers. Used to accelerate the computations.
     */
    int countFilled;
    bool columnHasNumber[9][10];
    bool lineHasNumber[9][10];
    bool block3x3HasNumber[3][3][10];

    void initialize();
    /**
     * Checks if the cell at line i, column j accepts number n
     */
    bool accepts(int i, int j, int n);
    /**
     * Fills in the cell at line i, column j with number n.
     * Also updates the cell counter.
     */
    void place(int i, int j, int n);
    /**
     * Clears the cell at line i, column j.
     * Returns the previous contents.
     * Also updates the cell counter.
     */
    int clear(int i, int j);
    /**
     * Clears the whole puzzle
     */
    void clear();
	//TODO: Add other methods if needed
    void solveAllSolutions();

    bool canFindBestCell(int &row, int &col);

    unsigned solutions;
};

// Ex 3
bool changeMakingBacktracking(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]);

// Ex 4
class Activity {
public:
    unsigned int start;
    unsigned int finish;
    Activity(unsigned int s, unsigned int f): start(s), finish(f){};
    bool operator==(const Activity &a2) const;
    bool overlaps(const Activity &a2) const;
};
std::vector<Activity> activitySelectionBacktracking(std::vector<Activity> A);

#endif //CAL_TP2_CLASSES_EXERCISES_H
