#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <vector>

enum class operation { ADD, MULT };

template <typename T> class Matrix {
public:
  Matrix() = default;
  Matrix(size_t rows, size_t cols)
      : numRows(rows), numCols(cols), data(rows * cols) {}

  T &operator()(size_t r, size_t c) { return data[r * numCols + c]; }
  const T &operator()(size_t r, size_t c) const {
    return data[r * numCols + c];
  }

  size_t rows() const { return numRows; }
  size_t cols() const { return numCols; }

private:
  size_t numRows = 0;
  size_t numCols = 0;
  std::vector<T> data;
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

// ------------------------
// Read transposed matrix (Part 2)
// ------------------------
template <typename T>
Matrix<T> read_transposed_matrix(std::vector<operation> &out_ops) {
  std::vector<std::string> lines;
  std::string line;

  while (std::getline(std::cin, line)) {
    if (!line.empty())
      lines.push_back(line);
  }

  if (lines.empty())
    return Matrix<T>{};

  std::string op_line = lines.back(); // last line = operators
  lines.pop_back();

  for (char ch : op_line) {
    if (ch == '+' || ch == '*')
      out_ops.push_back(char_to_op(ch));
  }

  size_t rows = lines.size();
  size_t cols = out_ops.size();

  Matrix<T> M(rows, cols);

  for (size_t r = 0; r < rows; ++r) {
    std::istringstream iss(lines[r]);
    for (size_t c = 0; c < cols; ++c) {
      T value;
      if (!(iss >> value)) {
        throw std::runtime_error("Invalid number in input");
      }
      M(r, c) = value;
    }
  }

  return M;
}

// ------------------------
// Process columns
// ------------------------
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
      T prod = 1;
      for (size_t r = 0; r < M.rows(); ++r)
        prod *= M(r, c);
      results[c] = prod;
      break;
    }
    }
  }

  return results;
}

// ------------------------
// Main
// ------------------------
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Expecting 1 argument (day number).\n";
    return -1;
  }

  if (*argv[1] == '2') {
    std::vector<operation> operators;
    Matrix<long long> M = read_transposed_matrix<long long>(operators);

    auto results = process_columns(M, operators);

    std::cout << "Column results: ";
    for (auto v : results)
      std::cout << v << " ";
    std::cout << "\n";

    long long total = std::accumulate(results.begin(), results.end(), 0LL);
    std::cout << "Grand total: " << total << "\n";

    return 0;
  }
}