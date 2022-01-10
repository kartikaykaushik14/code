package main.java;

import java.util.Arrays;

public class SudokuSolver {

    public static void main(String[] args) {
        char[][] board = new char[][]{{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};
        solveSudoku(board);
        System.out.println(Arrays.deepToString(board));
    }

    public static void solveSudoku(char[][] board) {
        if(board == null || board.length == 0)
            return; //Invalid Test Case
        solver(board);
    }

    public static boolean solver(char[][] board){
        for(int i = 0; i < board.length; i++){
            for(int j = 0; j < board[0].length; j++){
                if(board[i][j] == '.'){
                    // Brute Force Approach, Check for all possibilities.
                    for(char k = '1'; k <= '9'; k++){
                        if(isValid(board, i, j, k)){
                            board[i][j] = k;
                            if(solver(board))
                                //If the trial value works, continue to use the same solution
                                return true;
                            else
                                //Else reset it
                                board[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    private static boolean isValid(char[][] board, int row, int col, char c){
        for(int i = 0; i < 9; i++) {

            //Check validity of columns
            if(board[row][i] != '.' && board[row][i] == c) {
                return false;
            }

            //Check validity of rows
            if(board[i][col] != '.' && board[i][col] == c) {
                return false;
            }

            //Check validity of the block
            if(board[3 * (row / 3) + i / 3][ 3 * (col / 3) + i % 3] != '.' &&
                    board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) {
                return false;
            }
        }
        return true;
    }
}
