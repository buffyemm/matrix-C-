#include <iostream>
namespace s21 {

class Car {
 public:
  int door;
  int wheels;
  std::string model;

  void print() {
    std::cout << model << "\t" << door << "\t" << wheels << std::endl;
  }
  Car(std::string model, int door, int wheels) {
    this->door = door;
    this->wheels = wheels;
    this->model = model;
    std::cout << "Car has been created" << std::endl;
  }

  Car(std::string model) : door(1), wheels(1) {
    std::cout << "PISOS" << std::endl;
    this->model = model;
  }
};

class S21Matrix {
  private:
  int rows_, cols_;
  double** matrix_;

 public:
  S21Matrix(int rows, int cols) : rows_(rows), cols_(cols), matrix_(nullptr) {
    create_matrix();
  }
  S21Matrix() : rows_(3), cols_(3), matrix_(nullptr) { create_matrix(); }
  S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    create_matrix();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  // конструктор переноса, зачищает старую переменную, и переносит в нее
  // значения
  S21Matrix(S21Matrix&& other) noexcept
      : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }

      double& operator()(int a, int b) {
        if (a < 0 || a >= rows_ || b < 0 || b >= cols_) {
            throw std::out_of_range("Index out of range");
        }
        return matrix_[a][b];
    }

        const double& operator()(int a, int b) const {
        if (a < 0 || a >= rows_ || b < 0 || b >= cols_) {
            throw std::out_of_range("Index out of range");
        }
        return matrix_[a][b];
    }

  // деструктор
  ~S21Matrix() {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }

  void setCols(int a) {
    this->cols_ = a;
  }
  void setRows(int a) {
    this->rows_ = a;
  }
    int getCols() {
    return cols_;
  }
  int getRows() {
    return rows_;
  }

  void create_matrix() {
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

  bool EqMatrix(const S21Matrix& other) {
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

  void SumMatrix(const S21Matrix& other) {
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

  void SubMatrix(const S21Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_)
      throw std::invalid_argument("Wrong matrix size");
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }

  void printfMatrix() {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        std::cout << matrix_[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  void MulNumber(const double num) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] *= num;
      }
    }
  }

  void MulMatrix(const S21Matrix& other) {
    if (cols_ != other.rows_) {  // количество столбцов матрицы A равно
      // количеству строк матрицы B
      // throw "incorrect matrix";
      throw std::invalid_argument(
          "Number of columns in the first matrix must equal the number of rows "
          "in the second matrix.");
    } else {
      // S21Matrix tempMatrix(this->cols_, this->rows_);
      S21Matrix temp(rows_, other.cols_);
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
          temp.matrix_[i][j] = 0;
          for (int k = 0; k < cols_; k++) {
            temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
          }
        }
      }

      // temp.printfMatrix();
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
          this->matrix_[i][j] = temp.matrix_[i][j];
        }
      }
      // temp.matrix_ = matrix_;
    }
  }

  S21Matrix Transpose() {
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

  void create_minor(S21Matrix &result, int exception_row,
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

    double Determinant() {
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
                return 0; // Определитель равен 0
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

     S21Matrix CalcComplements() {
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

  S21Matrix operator+(const S21Matrix& rv) {
    if (rows_ != rv.rows_ || cols_ != rv.cols_)
      throw std::invalid_argument("Wrong matrix size");

    S21Matrix result(*this);
    result.SumMatrix(rv);

    return (result);
  }

  S21Matrix operator-(const S21Matrix& rv) {
    if (rows_ != rv.rows_ || cols_ != rv.cols_)
      throw std::invalid_argument("Wrong matrix size");

    S21Matrix result(*this);
    result.SubMatrix(rv);

    return (result);
  }

  S21Matrix operator*(const S21Matrix& rv) {
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

  S21Matrix operator*(const double num) {
    S21Matrix result(*this);
    result.MulNumber(num);

    return result;
  }

  bool operator==(const S21Matrix& rv) {
    return EqMatrix(rv);
  }
  //    S21Matrix operator+(const S21Matrix& rv)  {
  //   if(rows_ != rv.rows_ || cols_ != rv.cols_)
  // throw std:: invalid_argument("Wrong matrix size");

  // S21Matrix result(*this);
  // result.SumMatrix(rv);

  //     return (result);
  // }
};

//int main() {

  //S21Matrix matrix1(3, 3);
  //int value_1  = rv.getRows()
  // S21Matrix matrix2;
  // matrix1(0,0) = 2;
  // matrix1(0,1) = 5;
  // matrix2(0,0) = 2;
  // matrix2(0,1) = 2;
  // matrix1.MulMatrix(matrix2);
  // matrix1.printfMatrix();
//   S21Matrix arr(3, 3);
//   S21Matrix bar(3, 2);

//   int a = arr.getCols();
//   arr.setCols(3);

//   arr.matrix_[0][0] = 1;
//   arr.matrix_[1][0] = 1;
//   arr.matrix_[2][0] = 1;
//   bar.matrix_[0][0] = 1;
//   bar.matrix_[1][0] = 1;
//   bar.matrix_[2][0] = 1;
//   // arr.SubMatrix(bar);
//    double pin = 3;
//   // arr.MulNumber(pin);

//   // arr.printfMatrix();
//   // bar.printfMatrix();
//   // arr.SumMatrix(bar);
//   // arr.MulMatrix(bar);
//   if (arr == bar) {
//     std::cout << "Матрицы равны!" << std::endl;
// } else {
//     std::cout << "Матрицы не равны!" << std::endl;
// }
//   // arr.Transpose();
//   //res.printfMatrix();

//   S21Matrix mat1(2, 2);
//   mat1.matrix_[0][0] = 1;
//   S21Matrix mat2(2, 2);
//   mat2.matrix_[0][0] = 2;

//   // Заполнение матриц значениями
//   // ...

//   //   try {
//   // S21Matrix result = mat1 + mat2;
//   // result.printfMatrix(); // Использование оператора сложения
//   // } catch (const std::exception& e) {
//   //     std::cerr << "Error: " << e.what() << std::endl;
//   // }

//   // S21Matrix matrix = arr.Transpose();
//   // matrix.printfMatrix();
 // return 0;
//}
}