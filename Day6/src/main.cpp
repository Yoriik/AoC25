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

std::vector<std::string> transpose_and_clean_input() {
  std::vector<std::string> lines;
  std::string line;

  // Read all input lines
  while (std::getline(std::cin, line)) {
    if (!line.empty())
      lines.push_back(line);
  }
  if (lines.empty())
    return {};

  // Find max line length to pad
  size_t max_len = 0;
  for (auto &l : lines)
    if (l.size() > max_len)
      max_len = l.size();
  for (auto &l : lines)
    l.resize(max_len, ' '); // pad with spaces

  // Transpose
  std::vector<std::string> transposed(max_len);
  for (size_t r = 0; r < lines.size(); ++r) {
    for (size_t c = 0; c < max_len; ++c) {
      transposed[c].push_back(lines[r][c]);
    }
  }

  // Collapse columns into numbers (remove "inside" whitespace)
  std::vector<std::string> cleaned_columns;
  for (auto &col : transposed) {
    std::string s;
    bool has_digit = false;
    for (char ch : col) {
      if (!isspace(ch)) {
        s.push_back(ch);
        has_digit = true;
      }
    }
    if (has_digit)
      cleaned_columns.push_back(s);
  }

  return cleaned_columns;
}

std::vector<operation> extract_ops_from_line(const std::string &op_line,
                                             size_t num_columns) {
  std::vector<operation> ops;
  for (char ch : op_line) {
    if (ch == '+' || ch == '*')
      ops.push_back(char_to_op(ch));
  }
  // If there are more columns than operators, just stop
  if (ops.size() > num_columns)
    ops.resize(num_columns);
  return ops;
}

template <typename T>
Matrix<T> read_transposed_matrix(std::vector<operation> &out_ops,
                                 std::vector<operation> &out_ops2) {
  std::vector<std::string> lines;
  std::string line;

  // Read all input lines
  while (std::getline(std::cin, line)) {
    if (!line.empty())
      lines.push_back(line);
  }

  if (lines.empty())
    return Matrix<T>{};

  // The last line contains operators
  std::string op_line = lines.back();
  lines.pop_back();

  // Pad lines to max length
  size_t max_len = 0;
  for (const auto &l : lines)
    if (l.size() > max_len)
      max_len = l.size();
  for (auto &l : lines)
    l.resize(max_len, ' ');

  // Transpose lines into columns
  std::vector<std::string> transposed(max_len);
  for (size_t r = 0; r < lines.size(); ++r)
    for (size_t c = 0; c < max_len; ++c)
      transposed[c].push_back(lines[r][c]);

  // Parse columns into numbers, row by row
  std::vector<std::vector<T>> temp_columns;
  for (auto &col : transposed) {
    std::vector<T> column;
    std::string current_number;
    for (char ch : col) {
      if (!isspace(ch)) {
        current_number.push_back(ch);
      } else if (!current_number.empty()) {
        std::istringstream iss(current_number);
        T value;
        iss >> value;
        column.push_back(value);
        current_number.clear();
      }
    }
    // push last number if present
    if (!current_number.empty()) {
      std::istringstream iss(current_number);
      T value;
      iss >> value;
      column.push_back(value);
    }

    if (!column.empty())
      temp_columns.push_back(std::move(column));
  }

  if (temp_columns.empty())
    return Matrix<T>{};

  // Ensure all columns have the same number of rows
  size_t num_rows = temp_columns[0].size();
  for (auto &col : temp_columns)
    if (col.size() != num_rows)
      throw std::runtime_error("Inconsistent column count.");

  // Build the matrix
  size_t num_cols = temp_columns.size();
  Matrix<T> M(num_rows, num_cols);
  for (size_t c = 0; c < num_cols; ++c)
    for (size_t r = 0; r < num_rows; ++r)
      M(r, c) = temp_columns[c][r];

  // Extract operators in order from operator line
  out_ops.clear();
  for (char ch : op_line) {
    if (ch == '+' || ch == '*')
      out_ops.push_back(char_to_op(ch));
    if (out_ops.size() >= num_cols)
      break; // stop once we have enough operators
  }
  out_ops2 = out_ops;

  // Pad with ADD if fewer operators than columns
  while (out_ops.size() < temp_columns.size())
    out_ops.push_back(operation::ADD);

  return M;
}

template <typename T>
std::vector<T>
process_columns_right_to_left(const Matrix<T> &M,
                              const std::vector<operation> &ops) {
  std::vector<T> results(M.cols());

  size_t op_count = ops.size(); // may be less than M.cols()

  for (size_t idx = 0; idx < M.cols(); ++idx) {
    // Map idx so 0 -> rightmost column
    size_t c = M.cols() - 1 - idx;

    if (idx < op_count) {
      // Only apply operator if present
      switch (ops[c]) {
      case operation::ADD: {
        T sum = 0;
        for (size_t r = 0; r < M.rows(); ++r)
          sum += M(r, c);
        results[idx] = sum;
        break;
      }
      case operation::MULT: {
        T prod = 1;
        for (size_t r = 0; r < M.rows(); ++r)
          prod *= M(r, c);
        results[idx] = prod;
        break;
      }
      }
    } else {
      // No operator available: just copy the first row? sum? choose behavior
      // Here we sum by default
      T sum = 0;
      for (size_t r = 0; r < M.rows(); ++r)
        sum += M(r, c);
      results[idx] = sum;
    }
  }

  return results;
}

template <typename T>
std::vector<T> process_problems(const std::vector<std::vector<T>> &problems,
                                const std::vector<operation> &ops) {
  if (ops.size() != problems.size())
    throw std::runtime_error("Operator count does not match problem count.");

  std::vector<T> results(problems.size());

  for (size_t i = 0; i < problems.size(); ++i) {
    const auto &numbers = problems[i];
    switch (ops[i]) {
    case operation::ADD: {
      T sum = 0;
      for (T v : numbers)
        sum += v;
      results[i] = sum;
      break;
    }
    case operation::MULT: {
      T prod = 1;
      for (T v : numbers)
        prod *= v;
      results[i] = prod;
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
    std::vector<operation> operators, operators2;
    Matrix<long long> M =
        read_transposed_matrix<long long>(operators, operators2);

    auto results = process_columns_right_to_left(M, operators);

    for (auto v : operators2) {
      if (v == operation::ADD)
        std::cout << '+';
      if (v == operation::MULT)
        std::cout << '*';
    }
    std::cout << "\n";

    for (auto v : results)
      std::cout << v << " ";
    std::cout << "\n";

    long long r = results.size() / operators2.size();
    long long multTerm = 1, addTerm = 0, sum = 0;
    for (long long i = 0; i < operators2.size(); i++) {
      multTerm = 1, addTerm = 0;
      for (long long j = r * (i + 1) - 1; j >= i * r; --j) {
        if (operators2[i] == operation::MULT) {
          std::cout << "adding: " << results[i + j] << std::endl;
          addTerm += results[i + j];
        }
        if (operators2[i] == operation::ADD) {
          std::cout << "multing: " << results[i + j] << std::endl;
          multTerm *= results[i + j];
        }
      }
      if (operators2[i] == operation::MULT) {
        std::cout << "term for grand total " << addTerm << std::endl;
        sum += addTerm;
      }
      if (operators2[i] == operation::ADD) {
        std::cout << "term for grand total " << multTerm << std::endl;
        sum += multTerm;
      }
      std::cout << "grand total after op " << i << " " << sum << std::endl;
    }

    std::cout << sum << '\n';
    return 0;
  }
}
