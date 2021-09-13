/* Copyright Brady Ruth 2021
 */

#include <cstddef>  // size_t
#ifndef HW3_INC_FIND_SUM_H_
#define HW3_INC_FIND_SUM_H_
// FindSum
//
// Traverses a two-dimensional heap-based array of integers representing a
// matrix. The function accumulates the entries of the matrix seeking a given
// sum. The function returns all such summations by providing a beginning and
// ending entry, given by indices. The number found is stored in the provided
// output parameter.
//
// Searches the columns, diagonals (ascending and descending), and rows of the
// matrix for a sequence of integers which sum to the value provided.  Note
// that diagonal and row indices must be in the direction of increasing column
// index, column indices must be in order of increasing row index. Said another
// way, sequences are left-to-right and top-to-bottom.
//
// Preconditions:
//  - matrix dimensions are correctly represented by matrix_size
//  - sums_found output parameter exists (but may contain garbage values)
//
// Parameters:
//  - matrix: a two-dimension integer array
//  - matrix_size: a two-element size_t array storing sizes of matrix
//    NOTE: See kMatrix_size_rows_idx and kMatrix_size_cols_idx below.
//  - search_sum: the integer value for which the function seeks sums
//  - sums_found: an OUTPUT PARAMETER pointing to a size_t
//
// Postconditions:
//  - sums_found stores number of summations found
//  - sums_found holds zero if no summations found
//
// Returns:
//  - Returns a two-dimensional unsigned integral of size
//      sums_found x kIndices_size
//    where n is the value in sums_found.
//  - Return type is of the form {
//      {
//        start row : size_t,
//        start col : size_t,
//        end row : size_t,
//        end col : size_t
//      }
//    }
//  - Returns the nullptr if no summations were found and sets sums_found to 0
//
const size_t** FindSum(const int** matrix,
                       const size_t* matrix_size,
                       int search_sum,
                       size_t* sums_found);


const size_t kMatrix_size_rows_idx = 0;  // row index in matrix_size
const size_t kMatrix_size_cols_idx = 1;  // col index in matrix_size

const size_t kIndices_size = 4;  // size of indices array
const size_t kIndices_start_row_idx = 0;  // starting row index in indices array
const size_t kIndices_start_col_idx = 1;  // starting column index in indices
const size_t kIndices_end_row_idx = 2;  // ending row index in indices
const size_t kIndices_end_col_idx = 3;  // ending colum index in indices
#endif  // HW3_INC_FIND_SUM_H_
