#include "matrix.h"

S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  create_matrix();
}

S21Matrix::S21Matrix() : rows_(3), cols_(3), matrix_(nullptr) {
  create_matrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  create_matrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

double& S21Matrix::operator()(int a, int b) const {
  if (a < 0 || a >= rows_ || b < 0 || b >= cols_) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[a][b];
}

// void S21Matrix::setCols(int a) { this->cols_ = a; }
// void S21Matrix::setRows(int a) { this->rows_ = a; }
int S21Matrix::getCols() { return cols_; }
int S21Matrix::getRows() { return rows_; }

void S21Matrix::create_matrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }

  // for (int i = 0; i < rows_; i++) {
  //   for (int j = 0; j < cols_; j++) {
  //     matrix_[i][j] = 2;
  //   }
  // }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (matrix_[i][j] != other.matrix_[i][j]) {
          return false;
        }
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (matrix_ == nullptr || other.matrix_ == nullptr) {
    std::cerr << "Matrix not initialized!" << std::endl;
    return;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Wrong matrix size");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::printfMatrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::invalid_argument("The matrices are incompatible.");
  }

  S21Matrix matrix_mul(this->rows_, other.cols_);

  for (int i = 0; i < matrix_mul.rows_; i++) {
    for (int j = 0; j < matrix_mul.cols_; j++) {
      matrix_mul.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        matrix_mul.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  rows_ = matrix_mul.rows_;
  cols_ = matrix_mul.cols_;

  this->DeAllocate();
  this->Allocate();

  this->SwapMatrix(matrix_mul);
}
void S21Matrix::Allocate() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

void S21Matrix::DeAllocate() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}
void S21Matrix::SwapMatrix(S21Matrix& other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix temp(cols_, rows_);
  for (int i = 0; i < temp.cols_; i++) {
    for (int j = 0; j < temp.cols_; j++) {
      temp.matrix_[i][j] = matrix_[j][i];
      // this->matrix_[i][j] = temp.matrix_[i][j];
    }
  }
  // this->cols_ = temp.cols_;
  // this->rows_ = temp.rows_;
  return temp;
}

void S21Matrix::create_minor(S21Matrix& result, int exception_row,
                             int exception_column) {
  for (int i = 0, m = 0, k = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (i != exception_row && j != exception_column) {
        result.matrix_[m][k] = this->matrix_[i][j];
        if (k == result.cols_ - 1) {
          m++;
          k = 0;
        } else {
          k++;
        }
      }
    }
  }
}

double S21Matrix::Determinant() {
  if (!matrix_) {
    throw std::runtime_error("Matrix is not initialized.");
  }
  if (rows_ != cols_) {
    throw std::runtime_error("Matrix is not square.");
  }
  if (rows_ == 1) {
    return matrix_[0][0];
  }

  double result = 1.0;
  S21Matrix triangle(rows_, cols_);

  // Копируем матрицу в треугольную матрицу
  for (int i = 0; i < triangle.rows_; i++) {
    for (int j = 0; j < triangle.cols_; j++) {
      triangle.matrix_[i][j] = matrix_[i][j];
    }
  }

  for (int i = 0; i < triangle.rows_; i++) {
    int hook = i;
    for (int j = i + 1; j < triangle.rows_; j++) {
      if (triangle.matrix_[j][i] > triangle.matrix_[hook][i]) {
        hook = j;
      }
    }
    if (hook != i) {
      result *= -1;
      for (int j = i; j < triangle.rows_; j++) {
        std::swap(triangle.matrix_[i][j], triangle.matrix_[hook][j]);
      }
    }
    if (triangle.matrix_[i][i] == 0) {
      return 0;  // Определитель равен 0
    } else {
      result *= triangle.matrix_[i][i];
    }
    for (int j = i + 1; j < triangle.rows_; j++) {
      double ratio = triangle.matrix_[j][i] / triangle.matrix_[i][i];
      for (int k = i; k < triangle.rows_; k++) {
        triangle.matrix_[j][k] -= ratio * triangle.matrix_[i][k];
      }
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (!matrix_) {
    throw std::runtime_error("Matrix is not initialized.");
  }
  if (rows_ != cols_) {
    throw std::runtime_error("Matrix is not square.");
  }

  S21Matrix result(rows_, cols_);
  S21Matrix minor_matrix(rows_ - 1, cols_ - 1);
  double determinant = 0;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      create_minor(minor_matrix, i, j);
      determinant = minor_matrix.Determinant();
      result.matrix_[i][j] = pow(-1, i + j) * determinant;
    }
  }

  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix& rv) {
  if (rows_ != rv.rows_ || cols_ != rv.cols_)
    throw std::invalid_argument("Wrong matrix size");

  S21Matrix result(*this);
  result.SumMatrix(rv);

  return (result);
}

S21Matrix S21Matrix::operator-(const S21Matrix& rv) {
  if (rows_ != rv.rows_ || cols_ != rv.cols_)
    throw std::invalid_argument("Wrong matrix size");

  S21Matrix result(*this);
  result.SubMatrix(rv);

  return (result);
}

S21Matrix S21Matrix::operator*(const S21Matrix& rv) {
  if (cols_ != rv.rows_) {
    throw std::invalid_argument(
        "Number of columns in the first matrix must equal the number of rows "
        "in the second matrix.");
  } else {
    S21Matrix result(*this);
    result.MulMatrix(rv);

    return (result);
  }
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);

  return result;
}

bool S21Matrix::operator==(const S21Matrix& rv) { return EqMatrix(rv); }
