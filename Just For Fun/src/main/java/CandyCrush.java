package main.java;

import java.util.Arrays;

public class CandyCrush {

    public static void main(String[] args) {
        int[][] board = new int[][]{{110,5,112,113,114},{210,211,5,213,214},{310,311,3,313,314},{410,411,412,5,414},{5,1,512,3,3},{610,4,1,613,614},{710,1,2,713,714},{810,1,2,1,1},{1,1,2,2,2},{4,1,4,4,1014}};
        candyCrush(board);
        System.out.println(Arrays.deepToString(board));
    }

    public static int[][] candyCrush(int[][] board) {
        int rows = board.length;
        int columns = board[0].length;

        boolean found = true;

        while (found) {
            found = false;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    int val = Math.abs(board[i][j]);
                    if (val == 0) continue;
                    if (j < columns - 2 && Math.abs(board[i][j + 1]) == val && Math.abs(board[i][j + 2]) == val) {
                        found = true;
                        int ind = j;
                        while (ind < columns && Math.abs(board[i][ind]) == val) board[i][ind++] = -val;
                    }
                    if (i < rows - 2 && Math.abs(board[i + 1][j]) == val && Math.abs(board[i + 2][j]) == val) {
                        found = true;
                        int ind = i;
                        while (ind < rows && Math.abs(board[ind][j]) == val) board[ind++][j] = -val;
                    }
                }
            }
            if (found) {
                // All positive entries are moved to bottom and are padded with 0s on top
                for (int j = 0; j < columns; j++) {
                    int storeInd = rows - 1;
                    for (int i = rows - 1; i >= 0; i--) {
                        if (board[i][j] > 0) {
                            board[storeInd--][j] = board[i][j];
                        }
                    }
                    for (int k = storeInd; k >= 0; k--) board[k][j] = 0;
                }
            }
        }
        return board;
    }

}
