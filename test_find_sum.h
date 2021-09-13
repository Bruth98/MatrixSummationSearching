// Copyright 2021 CSCE240
//
#ifndef HW3_INC_TEST_FIND_SUM_H_
#define HW3_INC_TEST_FIND_SUM_H_

#include <hw3/inc/find_sum.h>  // test file interface

#include <cassert>  // assert
#include <cstddef>  // size_t
#include <cstdlib>  // atoi
#include <cmath>  // abs, log10
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


// TestFindSum: tests a matrix with the provided search_sum; looks for the
//              expected indices found and indices found size.
//
bool TestFindSum(const int** matrix,
                 const size_t* matrix_size,
                 int search_sum,
                 const size_t expected_indices_found[][kIndices_size],
                 size_t expected_indices_found_size);


// TestFindSum: tests a very large matrix with many expected summations to
//              ensure the correct number of summations are found.
//
bool TestFindSum(const int** matrix,
                 const size_t* matrix_size,
                 int search_sum,
                 size_t expected_indices_found_size);


// ReadMatrixFile: Reads file param, creates 2D heap array and populates with
//                 file contents.
//
// Preconditions: file exists, is readable, is in correct format. No
//                error-checking done.
//
const int** ReadMatrixFile(const char* file_name, size_t* matrix_size);


// Delete: overloads to delete the two heap memory allocations
//
void Delete(const int** matrix, size_t rows);  // for input int matrix
void Delete(const size_t** indices, size_t size);  // for return size_t matrix


// IndicesEqual: Compare two sets of indices to ensure they are equal.
//
// Preconditions: two input parameters are allocated as arrays, each containing
//                four elements
//
bool IndicesEqual(const size_t expected[][kIndices_size],
                  size_t expected_size,
                  const size_t** actual,
                  size_t size);


// MatrixToString: Converts matrix to a string for printing.
//
// Preconditions: matrix_size parameter is accurate
//
const std::string MatrixToString(const int** matrix,
                                 const size_t* matrix_size);


// IndicesToString: Converts a set of indices to a string for printing.
//
// Preconditions: input parameter must be allocated as an array with four
//                elements
//
const std::string IndicesToString(const size_t*);


// used for input matrix print
//
const std::string FoundIndicesToString(const size_t**, size_t);

// used for return size_t matrix print
//
const std::string FoundIndicesToString(const size_t[][kIndices_size], size_t);

#endif  // HW3_INC_TEST_FIND_SUM_H_
