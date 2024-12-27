#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  S21Matrix();

  S21Matrix(int rows, int cols);

  S21Matrix(const S21Matrix &other);

  S21Matrix(S21Matrix &&other) noexcept;

  ~S21Matrix();

  //  void setCols(int a);
  //
  //  void setRows(int a);

  int getCols();

  int getRows();

  bool EqMatrix(const S21Matrix &other);

  void SumMatrix(const S21Matrix &other);

  void SubMatrix(const S21Matrix &other);

  void MulNumber(const double num);

  void MulMatrix(const S21Matrix &other);



  void Allocate();

  void DeAllocate();

  void SwapMatrix(S21Matrix &other);

  S21Matrix Transpose();

  void create_minor(S21Matrix &result, int exception_row, int exception_column);

  double Determinant();

  S21Matrix CalcComplements();

  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix &rv);

  S21Matrix operator-(const S21Matrix &rv);

  S21Matrix operator*(const S21Matrix &rv);

  double &operator()(int a, int b) const;

  S21Matrix operator*(const double num);

  S21Matrix operator+=(const S21Matrix& other);

  S21Matrix operator-=(const S21Matrix& other);

  S21Matrix operator*=(const S21Matrix& other);

  S21Matrix operator*=(const double num);

  bool operator==(const S21Matrix &rv);

  S21Matrix operator=(const S21Matrix& other);

  S21Matrix operator=(S21Matrix&& other) noexcept;

  void create_matrix();

  void printfMatrix();
};

#endif  // SRC_MATRIX_H
