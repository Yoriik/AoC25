#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

enum class operation { ADD, MULT };

template <typename T> class Matrix {
public:
  Matrix() = default;

  Matrix(size_t rows, size_t cols, const T &value = T{})
      : numRows(rows), numCols(cols), data(rows * cols, value) {}

  T &operator()(size_t r, size_t c) {
    check_bounds(r, c);
    return data[r * numCols + c];
  }

  const T &operator()(size_t r, size_t c) const {
    check_bounds(r, c);
    return data[r * numCols + c];
  }

  size_t rows() const noexcept { return numRows; }
  size_t cols() const noexcept { return numCols; }

private:
  size_t numRows = 0;
  size_t numCols = 0;
  std::vector<T> data;

  void check_bounds(size_t r, size_t c) const {
    if (r >= numRows || c >= numCols)
      throw std::out_of_range("Matrix index out of range");
  }
};

inline operation char_to_op(char c) {
  switch (c) {
  case '+':
    return operation::ADD;
  case '*':
    return operation::MULT;
  default:
    throw std::runtime_error("Invalid operator in operator row.");
  }
}

template <typename T>
Matrix<T> read_matrix_and_ops(std::vector<operation> &out_ops) {
  std::vector<std::vector<T>> temp;
  std::string line;

  while (std::getline(std::cin, line)) {
    bool is_ops =
        !line.empty() && line.find_first_not_of("*+ ") == std::string::npos;

    if (is_ops) {
      for (char ch : line)
        if (ch == '+' || ch == '*')
          out_ops.push_back(char_to_op(ch));
      break;
    }

    std::istringstream iss(line);
    T value;
    std::vector<T> row;

    while (iss >> value)
      row.push_back(value);

    if (!row.empty())
      temp.push_back(std::move(row));
  }

  if (temp.empty())
    return Matrix<T>{};

  size_t rows = temp.size();
  size_t cols = temp[0].size();
  Matrix<T> M(rows, cols);

  for (size_t r = 0; r < rows; ++r) {
    if (temp[r].size() != cols)
      throw std::runtime_error("Inconsistent column count.");
    for (size_t c = 0; c < cols; ++c)
      M(r, c) = temp[r][c];
  }

  return M;
}

template <typename T>
std::vector<T> process_columns(const Matrix<T> &M,
                               const std::vector<operation> &ops) {
  if (ops.size() != M.cols())
    throw std::runtime_error("Operator count does not match column count.");

  std::vector<T> results(M.cols());

  for (size_t c = 0; c < M.cols(); ++c) {
    switch (ops[c]) {
    case operation::ADD: {
      T sum = 0;
      for (size_t r = 0; r < M.rows(); ++r)
        sum += M(r, c);
      results[c] = sum;
      break;
    }
    case operation::MULT: {
      long long prod = 1;
      for (size_t r = 0; r < M.rows(); ++r) {
        if (M(r, c) != 0 &&
            prod > std::numeric_limits<long long>::max() / M(r, c)) {
          throw std::overflow_error("Column multiplication overflow");
        }
        prod *= M(r, c);
      }
      results[c] = prod;
      break;
    }
    }
  }

  return results;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Expecting 1 argument (day number).\n";
    return -1;
  }

  if (*argv[1] == '1') {
    std::vector<operation> operators;
    Matrix<long long> M = read_matrix_and_ops<long long>(operators);
    auto results = process_columns(M, operators);
    std::cout << std::accumulate(results.begin(), results.end(), 0LL) << '\n';
    return 0;
  }

  if (*argv[1] == '2') {
    return 0;
  }
}
