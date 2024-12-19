#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../matrix.cpp"

TEST(S21Matrix, operatorEq) {
  s21::S21Matrix matrix1(3, 3);
  s21::S21Matrix matrix2;
 EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(S21Matrix, operatorEq2) {
  s21::S21Matrix matrix1(3, 2);
  s21::S21Matrix matrix2;
 EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(S21Matrix, operatorEq3) {
  s21::S21Matrix matrix1(3, 3);
  s21::S21Matrix matrix2;
  matrix1(0,0) = 2;
  matrix1(0,1) = 5;
  matrix2(0,0) = 2;
  matrix2(0,1) = 2;
 EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}
TEST(S21Matrix, ExceptionDeterminant) {
  s21::S21Matrix matrix1(2, 0);
  double *pen;
  EXPECT_THROW(matrix1.Determinant(), std::invalid_argument);
}

TEST(S21Matrix, CalcComplements) {
  s21::S21Matrix matrix1;
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 9;

  // Вычисляем дополнительные матрицы
  s21::S21Matrix result = matrix1.CalcComplements();

  ASSERT_EQ(result.getRows(), 3);
  ASSERT_EQ(result.getCols(), 3);
  // Каждый элемент дополнительной матрицы - это определитель
  // минора, вычисленный для соответствующего элемента исходной матрицы
  ASSERT_EQ(result(0, 0), -3);
  ASSERT_EQ(result(0, 1), 6);
  ASSERT_EQ(result(0, 2), -3);
  ASSERT_EQ(result(1, 0), 6);
  ASSERT_EQ(result(1, 1), -12);
  ASSERT_EQ(result(1, 2), 6);
  ASSERT_EQ(result(2, 0), -3);
  ASSERT_EQ(result(2, 1), 6);
  ASSERT_EQ(result(2, 2), -3);
}


TEST(S21Matrix, Mulmatrix3x3){
  s21::S21Matrix matrix1(3, 3);
  //int value_1  = rv.getRows()
  s21::S21Matrix matrix2;
  matrix1(0,0) = 2;
  matrix1(0,1) = 5;
  matrix2(0,0) = 2;
  matrix2(0,1) = 2;
  matrix1.MulMatrix(matrix2);
  double value0 = matrix1(0,0);
  double value1 = matrix1(0,1);
  ASSERT_TRUE (value0 == 4 && value1 == 4);
}

TEST(S21Matrix, ThrowsInvalidArgument) {
  s21::S21Matrix matrix1(3, 2);
  s21::S21Matrix matrix2;
  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}


// TEST(S21Matrix, MulNumber_ValidInput) {
//   s21::S21Matrix rv;
//   rv(0,0) = 1;
//   double value  = rv(0,0);
//   ASSERT_TRUE( value == 1);
// }



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
