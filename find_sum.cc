/* Copyright Brady Ruth 2021
 */
#include "hw3/inc/find_sum.h"

/*
searches the matrix horizontally for the correct sum
*/
size_t** horizontalSum(const int** matrix,
                       int rows,
                       int cols,
                       int needle,
                       size_t** indexes,
                       size_t* sums_found) {
    int sum;  // establish the sum
    int counter = 0;  // set num of sums found to 0
    for (int r=0; r < rows; r++) {  // span rows
        sum = 0;  // reset sum
        for (int c=0; c < cols; c++) {  // span columns
            sum = matrix[r][c];  // check to see if first index is a sum

            if (sum == needle) {  // sum found!
                size_t *sumFound = new size_t[kIndices_size];  // establish a 1D array with 4 elements
                sumFound[kIndices_start_row_idx] = r;   // set the first element to the current row
                sumFound[kIndices_start_col_idx] = c;  // set the second element to the current col
                sumFound[kIndices_end_row_idx] = r;  // set the third element to the current row, since it is still the first pass of the array
                sumFound[kIndices_end_col_idx] = c;  // set the fourth element to the current col, since it is still in the first loop over the array
                indexes[counter] = sumFound;  // set the current row of the 2D array to the 1D sumFound array
                counter++;  // adavance the counter by 1
                *sums_found = counter;  // set the number of sums found equal to the counter.
            }
            if (c <= cols - 1) {  // if there are still columns left in the current row of the matrix
                for (int k = c+1; k < cols; k++) {  // iterate through each col, and keep the row the same
                    sum += matrix[r][k];  // add the next index to the currnet sum
                    if (sum == needle) {  // sum found!
                        size_t *sumFound = new size_t[kIndices_size];  // establish a 1D array with 4 elements
                        sumFound[kIndices_start_row_idx] = r;  // set the first element to the current row
                        sumFound[kIndices_start_col_idx] = c;  // set the second element to the current col (c)
                        sumFound[kIndices_end_row_idx] = r;  // set the third element to the current row, since the horizontal sum will still have the same row
                        sumFound[kIndices_end_col_idx] = k;  // set the fourth element to the new col (k) since that is the end coordinate of the correct summation
                        indexes[counter] = sumFound;  // set the current row of the 2D array to the 1D sumFound array
                        counter++;  // adavance the counter by 1
                        *sums_found = counter;  // set the number of sums found equal to the counter.
                    }
                }
            }
        }
    }
    return indexes;  // return the 2D array of all sum combinations found
}

/*
Searches the matrix vertically for all correct summation combinations.
*/
size_t** verticalSum(const int** matrix,
                       int rows,
                       int cols,
                       int needle,
                       size_t** indexes,
                       size_t* sums_found) {
    int sum;
    int counter = 0;
    for (int c=0; c < cols; c++) {  // span cols first
        sum = 0;  // reset sum
        for (int r=0; r < rows; r++) {  // span rows second
            sum = matrix[r][c];  // check to see if first index is a sum

            if (sum == needle) {  // sum found!
                size_t *sumFound = new size_t[kIndices_size];  // establish a 1D array with 4 elements
                sumFound[kIndices_start_row_idx] = r;  // set the first element to the current row
                sumFound[kIndices_start_col_idx] = c;  // set the second element to the current col
                sumFound[kIndices_end_row_idx] = r;  // set the third element to the current row, since it is still the first pass of the array
                sumFound[kIndices_end_col_idx] = c;  // set the fourth element to the current col, since it is still in the first loop over the array
                indexes[counter] = sumFound;  // same as before
                counter++;
                *sums_found = counter;
            }
            for (int k = r+1; k < rows; k++) {  // iterate through each row
                sum += matrix[k][c];  // advance row, anchor column
                if (sum == needle) {  // sum found!
                    size_t *sumFound = new size_t[kIndices_size];
                    sumFound[kIndices_start_row_idx] = r;  // set the first element to the current row (r)
                    sumFound[kIndices_start_col_idx] = c;  // set the second element to the current col
                    sumFound[kIndices_end_row_idx] = k;  // set the third element to the new row (k)
                    sumFound[kIndices_end_col_idx] = c;  // set the fourth element to the current column, since the vertical sum will still have the same column
                    indexes[counter] = sumFound;  // same as before
                    counter++;
                    *sums_found = counter;
                }
            }
         }
    }
    return indexes;
}

/*
Searches the matrix diagonally, descending, for all correct summation combinations.
*/
size_t** dDiagSum(const int** matrix,
                   int rows,
                   int cols,
                   int needle,
                   size_t** indexes,
                   size_t* sums_found) {
    int counter = 0;
    for (int c = 0; c < cols; c++) {
        for (int r=0; r < rows; r++) {
            int sum = 0;
            int curRow = r;  // establish a variable to check rows "ahead" of the current row
            int curCol = c;  // establish a variable to check cols "ahead" of the current column
            while (curRow < rows && curCol < cols) {  // while the "advanced" rows and columns are less than actual number of rows and cols
                sum += matrix[curRow][curCol];  // add the current "advanced" row and col to the sum
                if (sum == needle) {  // sum found!
                    size_t *sumFound = new size_t[kIndices_size];
                    sumFound[kIndices_start_row_idx] = r;  // set the first index to the index of the original row
                    sumFound[kIndices_start_col_idx] = c;  // set the second index to the index of the original col
                    sumFound[kIndices_end_row_idx] = curRow;  // set the third index to the index of the "advanced" row
                    sumFound[kIndices_end_col_idx] = curCol;  // set the fourth index to the index of the "advanced" col
                    indexes[counter] = sumFound;  // same as before
                    counter++;
                    *sums_found = counter;
                }
                curRow++;  // sum was not found on this loop, "advance" the curRow and curCol by 1 to check the next descending diagonal
                curCol++;
            }
        }
    }
    return indexes;
}

/*
Searches the matrix diagonally, ascending, for all correct summation combinations.
*/
size_t** aDiagSum(const int** matrix,
                   int rows,
                   int cols,
                   int needle,
                   size_t** indexes,
                   size_t* sums_found) {
    int counter = 0;
    for (int c = 0; c < cols; c++) {  // start at the first column, loop through all columns
        for (int r=0; r < rows; r++) {  // start at the first row, loop through all rows
            int sum = 0;
            int curRow = r;
            int curCol = c;
            while (curRow >= 0 && curCol < cols) {  // while there are still rows above the current, and still columns to check past the current
                sum += matrix[curRow][curCol];  // add the value of the current row/column to the sum
                if (sum == needle) {  // sum found!
                    size_t *sumFound = new size_t[kIndices_size];
                    sumFound[kIndices_start_row_idx] = r;
                    sumFound[kIndices_start_col_idx] = c;
                    sumFound[kIndices_end_row_idx] = curRow;
                    sumFound[kIndices_end_col_idx] = curCol;
                    indexes[counter] = sumFound;
                    counter++;
                    *sums_found = counter;
                }
                curRow--;  // move the current row up by 1 to keep checking ascending diagonals
                curCol++;  // move the current row over by 1 to keep checking ascending diagonals
            }
        }
    }
    return indexes;
}

/*
This is the main function called upon by the testing code
*/
const size_t** FindSum(const int** matrix,
                       const size_t* matrix_size,
                       int search_sum,
                       size_t* sums_found) {
    int rows = matrix_size[kMatrix_size_rows_idx];  // establishes the number of rows needed to be searched through
    int cols = matrix_size[kMatrix_size_cols_idx];  // establishes the number of cols needed to be searched through
    *sums_found = 0;  // establish the output parameter to avoid any weird numbers auto generating, which did happen quite a lot before I figured this out
    size_t startSize = rows;
    size_t **indices = new size_t *[startSize];

    /*
    Find the indices that sum up correctly horizontally
    */
    indices = horizontalSum(matrix,
                            rows,
                            cols,
                            search_sum,
                            indices,
                            sums_found);

    /*
    Find the indices that sum up correctly vertically
    */
    indices = verticalSum(matrix,
                          rows,
                          cols,
                          search_sum,
                          indices,
                          sums_found);

    /*
    Find the indices that sum up correctly diagonally, descending across the matrix
    */
    indices = dDiagSum(matrix,
                          rows,
                          cols,
                          search_sum,
                          indices,
                          sums_found);

      /*
    Find the indices that sum up correctly diagonally, ascending across the matrix
    */
    indices = aDiagSum(matrix,
                          rows,
                          cols,
                          search_sum,
                          indices,
                          sums_found);

    /*
    return the matrix of indices found
    */
    return const_cast<const size_t **>(indices);
}
