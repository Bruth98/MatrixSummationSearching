// Copyright 2021 CSCE240
//
#include <hw3/inc/test_find_sum.h>


int main(int argc, char* argv[]) {
  const size_t kFileArgIdx = 1;
  const size_t kTestArgIdx = 2;

  size_t matrix_size[] = { 0, 0 };
  const int **matrix = ReadMatrixFile(argv[kFileArgIdx], matrix_size);

  int result = 0;
  switch (atoi(argv[kTestArgIdx])) {
    case 0: {
      std::cout << "TESTING ROW FindSum:" << std::endl;
      std::cout << MatrixToString(matrix, matrix_size) << std::endl;
      int search_sum = -87;
      const size_t expected_indices[][kIndices_size] = {
        {1, 0, 1, 2},
        {3, 1, 3, 3},
        {4, 2, 4, 4}
      };
      size_t expected_indices_size = 3;
      if (TestFindSum(matrix,
                      matrix_size,
                      search_sum,
                      expected_indices,
                      expected_indices_size)) {
        std::cout << "  PASSED" << std::endl;
        result = 0;
      } else {
        std::cout << "  FAILED" << std::endl;
        result = 1;
      }
      break;
    }

    case 1: {
      std::cout << "TESTING COLUMN FindSum:" << std::endl;
      std::cout << MatrixToString(matrix, matrix_size) << std::endl;
      int search_sum = -87;
      size_t expected_col_indices[][kIndices_size] = {
        {1, 0, 3, 0},
        {0, 2, 2, 2},
        {2, 4, 4, 4}
      };
      size_t expected_indices_size = 3;
      if (TestFindSum(matrix,
                      matrix_size,
                      search_sum,
                      expected_col_indices,
                      expected_indices_size)) {
        std::cout << "  PASSED" << std::endl;
        result = 0;
      } else {
        std::cout << "  FAILED" << std::endl;
        result = 1;
      }
      break;
    }

    case 2: {
      std::cout << "TESTING ASCENDING DIAGONAL FindSum:" << std::endl;
      std::cout << MatrixToString(matrix, matrix_size) << std::endl;
      int search_sum = -87;
      size_t expected_asc_indices[][kIndices_size] = {
        {2, 0, 0, 2},
        {2, 2, 0, 4},
        {4, 2, 2, 4}
      };
      size_t expected_indices_size = 3;
      if (TestFindSum(matrix,
                      matrix_size,
                      search_sum,
                      expected_asc_indices,
                      expected_indices_size)) {
        std::cout << "  PASSED" << std::endl;
        result = 0;
      } else {
        std::cout << "  FAILED" << std::endl;
        result = 1;
      }
      break;
    }

    case 3: {
      std::cout << "TESTING DESCENDING DIAGONAL FindSum:" << std::endl;
      std::cout << MatrixToString(matrix, matrix_size) << std::endl;
      int search_sum = -87;
      size_t expected_asc_indices[][kIndices_size] = {
        {0, 0, 2, 2},
        {0, 2, 2, 4},
        {2, 0, 4, 2}
      };
      size_t expected_indices_size = 3;
      if (TestFindSum(matrix,
                      matrix_size,
                      search_sum,
                      expected_asc_indices,
                      expected_indices_size)) {
        std::cout << "  PASSED" << std::endl;
        result = 0;
      } else {
        std::cout << "  FAILED" << std::endl;
        result = 1;
      }
      break;
    }

    case 4: {
      std::cout << "TESTING MISSING FindSum:" << std::endl;
      std::cout << MatrixToString(matrix, matrix_size) << std::endl;
      size_t expected_missing_indices[][kIndices_size] = { 0, 0, 0, 0 };
      if (TestFindSum(matrix, matrix_size, 0, expected_missing_indices, 0)) {
        std::cout << "  PASSED" << std::endl;
        result = 0;
      } else {
        std::cout << "  FAILED" << std::endl;
        result = 1;
      }
      break;
    }

    case 5: {
      std::cout << "TESTING Large Matrix:" << std::endl;
      std::cout << MatrixToString(matrix, matrix_size) << std::endl;
      size_t expected_indices_found_size
        = (matrix_size[kMatrix_size_rows_idx] - 1)
          * matrix_size[kMatrix_size_cols_idx]
        + matrix_size[kMatrix_size_rows_idx]
          * (matrix_size[kMatrix_size_cols_idx] - 1)
        + (matrix_size[kMatrix_size_rows_idx] - 1)
          * (matrix_size[kMatrix_size_cols_idx] - 1)
        + (matrix_size[kMatrix_size_rows_idx] - 1)
          * (matrix_size[kMatrix_size_cols_idx] - 1);

      if (TestFindSum(matrix, matrix_size, 2, expected_indices_found_size)) {
        std::cout << "  PASSED" << std::endl;
        result = 0;
      } else {
        std::cout << "  FAILED" << std::endl;
        result = 1;
      }
      break;
    }
  }

  Delete(matrix, matrix_size[kMatrix_size_rows_idx]);

  return result;
}



bool TestFindSum(const int** matrix,
                 const size_t* matrix_size,
                 int search_sum,
                 const size_t expected_found[][kIndices_size],
                 size_t expected_size) {
  size_t actual_size = static_cast<size_t>(-1);  // space for output param
  const size_t **actual_indices = FindSum(matrix,
                                          matrix_size,
                                          search_sum,
                                          &actual_size);
  bool passed = true;
  if (expected_size > 0 && (actual_size == 0 || !actual_indices)) {
    std::cout << "  No summation found for sum: " << search_sum << std::endl;
    passed = false;
  }

  if (actual_size != expected_size) {
    std::cout << "  Expected sums found: " << expected_size
        << ", Actual sums found: " << actual_size << std::endl;

    passed = false;
  }

  if (!IndicesEqual(expected_found, expected_size, actual_indices, actual_size))
    passed = false;

  Delete(actual_indices, actual_size);
  return passed;
}


bool TestFindSum(const int** matrix,
                 const size_t* matrix_size,
                 int search_sum,
                 size_t expected_size) {
  size_t actual_size = static_cast<size_t>(-1);

  const size_t **actual_indices = FindSum(matrix, matrix_size, 2, &actual_size);

  Delete(actual_indices, actual_size);

  if (expected_size != actual_size) {
    std::cout << "  Expected sums_found: " << expected_size
        << ", Actual: " << actual_size << std::endl;
    return false;
  } else {
    return true;
  }
}


const int** ReadMatrixFile(const char* file_name, size_t* matrix_size) {
  std::fstream fin(file_name, std::fstream::in);
  assert(fin.is_open());

  int rows, cols;
  fin >> rows >> cols;
  assert(rows > 0 && cols > 0);

  int **matrix = new int*[rows];
  for (size_t row = 0; row < static_cast<size_t>(rows); ++row) {
    matrix[row] = new int[cols];

    for (size_t col = 0; col < static_cast<size_t>(cols); ++col) {
      fin >> matrix[row][col];
    }
  }

  matrix_size[kMatrix_size_rows_idx] = rows;
  matrix_size[kMatrix_size_cols_idx] = cols;

  return const_cast<const int**>(matrix);
}


bool IndicesEqual(const size_t expected[][kIndices_size],
                  size_t expected_size,
                  const size_t** actual,
                  size_t size) {
  bool *found = new bool[size];  // found from expected
  for (size_t i = 0; i < size; ++i) {
    found[i] = false;
    for (size_t j = 0; j < size; ++j) {
      if (actual[i][kIndices_start_row_idx]
            == expected[j][kIndices_start_row_idx]
          && actual[i][kIndices_start_col_idx]
            == expected[j][kIndices_start_col_idx]
          && actual[i][kIndices_end_row_idx]
            == expected[j][kIndices_end_row_idx]
          && actual[i][kIndices_end_col_idx]
            == expected[j][kIndices_end_col_idx]) {
        found[i] = true;
        break;
      }
    }
  }

  bool passed = true;
  for (size_t i = 0; i < size; ++i)
    if (!found[i]) {
      std::cout << "  Expected Found Indices:\n"
        << "    " << FoundIndicesToString(expected, expected_size)
        << std::endl;
      std::cout << "  Actual Found Indices:\n"
        << "    " << FoundIndicesToString(actual, size) << std::endl;
      passed = false;  // one of the index pairs was not found
      break;
    }

  delete [] found;
  return passed;
}


const std::string MatrixToString(const int** matrix,
                                 const size_t* matrix_size) {
  std::stringstream sout;

  int largest_log10 = 0;  // ensures widths of all values are equal
  for (size_t row = 0; row < matrix_size[kMatrix_size_rows_idx]; ++row)
    for (size_t col = 0; col < matrix_size[kMatrix_size_cols_idx]; ++col) {
      int tmp_log10 = log10(abs(matrix[row][col]));
      if (tmp_log10 > largest_log10)
        largest_log10 = tmp_log10;
    }

  for (size_t row = 0; row < matrix_size[kMatrix_size_rows_idx]; ++row) {
    for (size_t col = 0; col < matrix_size[kMatrix_size_cols_idx]; ++col)
      sout << std::setw(largest_log10 + 3) << matrix[row][col];

    if (row < matrix_size[kMatrix_size_rows_idx] - 1)
      sout << '\n';
  }

  return sout.str();
}


const std::string IndicesToString(const size_t* indices) {
  std::stringstream sout;

  sout << "(" << indices[kIndices_start_row_idx] << ", " <<
    indices[kIndices_start_col_idx] << ") - (" << indices[kIndices_end_row_idx]
    << ", " << indices[kIndices_end_col_idx] << ")";

  return sout.str();
}


const std::string FoundIndicesToString(const size_t indices[][kIndices_size],
                                       size_t size) {
  std::stringstream sout;

  for (size_t i = 0; i < size; ++i) {
    sout << IndicesToString(indices[i]);
    if (i < size - 1)
      sout << ", ";
  }

  return sout.str();
}

const std::string FoundIndicesToString(const size_t** indices,
                                       size_t size) {
  std::stringstream sout;

  for (size_t i = 0; i < size; ++i) {
    sout << IndicesToString(indices[i]);
    if (i < size - 1)
      sout << ", ";
  }

  return sout.str();
}


void Delete(const int** matrix, size_t row) {
  if (matrix) {
    for (size_t i = 0; i < row; ++i)
      if (matrix[i])
        delete [] matrix[i];

    delete [] matrix;
  }
}

void Delete(const size_t** indices, size_t size) {
  if (indices) {
    for (size_t i = 0; i < size; ++i)
      if (indices[i])
        delete [] indices[i];

    delete [] indices;
  }
}
