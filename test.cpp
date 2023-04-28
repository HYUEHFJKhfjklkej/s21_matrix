#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Basic, default_constructor) {
  S21Matrix basic;
  EXPECT_EQ(basic.Get_Rows(), 3);
  EXPECT_EQ(basic.Get_Cols(), 3);
}
TEST(Basic, default_constructor_Exception) {
  EXPECT_ANY_THROW(S21Matrix exception(1, 0));
}

TEST(Basic, default_constructor_Exception2) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 4;
  matrix1(0, 1) = 4;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;
  S21Matrix matrix3 = matrix1 + matrix2;
  EXPECT_EQ(matrix3(0, 0), 5);
}

TEST(Basic, default_constructor_Exception3) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 4;
  matrix1(0, 1) = 4;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;
  S21Matrix matrix3 = matrix1 * matrix2;
  EXPECT_EQ(matrix3(0, 0), 8);
}

TEST(Basic, default_constructor_Exception4) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 4;
  matrix1(0, 1) = 4;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;
  S21Matrix matrix3 = matrix1 - matrix2;
  EXPECT_EQ(matrix3(0, 0), 3);
}

TEST(Basic, default_constructor_Exception5) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 4;
  matrix1(0, 1) = 4;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 4;
  EXPECT_EQ(matrix1.Determinant(), 0);
}

TEST(Basic, parameterized_constructor_Exception) {
  EXPECT_ANY_THROW(S21Matrix exception(0, -2));
}
TEST(Basic, parameterized_constructor) {
  S21Matrix basic(2, 2);
  EXPECT_EQ(basic.Get_Rows(), 2);
  EXPECT_EQ(basic.Get_Cols(), 2);
}
TEST(functionalTest, operators_over) {
  S21Matrix m1(1, 1);
  m1(0, 0) = 2;
  int num = 2;
  S21Matrix res = num * m1;
  S21Matrix res2 = m1 * num;
  S21Matrix res3 = res * res2;
  EXPECT_EQ(res(0, 0), 4);
  EXPECT_EQ(res2(0, 0), 4);
  EXPECT_EQ(res3(0, 0), 16);
}

TEST(functionalTest, EqMatrix) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 2;
  m1(0, 1) = 2;
  m1(1, 0) = 2;
  m1(1, 1) = 2;

  S21Matrix m2(2, 2);
  m2(0, 0) = 2;
  m2(0, 1) = 2;
  m2(1, 0) = 2;
  m2(1, 1) = 2;

  EXPECT_TRUE(m1.EqMatrix(m2));
}

TEST(GetterAndSetter, set) {
  S21Matrix basic(2, 3);
  basic(1, 1) = 2.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic.Get_Rows(), 2);
  EXPECT_EQ(basic.Get_Cols(), 3);
  basic.Set_Rows(4);
  basic.Set_Cols(4);
  basic.Set(4, 3);
  basic(3, 2) = 1.2;
  EXPECT_EQ(basic(1, 1), 2.2);
  EXPECT_EQ(basic(3, 2), 1.2);
  EXPECT_EQ(basic.Get_Rows(), 4);
  EXPECT_EQ(basic.Get_Cols(), 3);
}

TEST(assignmentOperator, brakets) {
  S21Matrix basic(2, 3);
  basic(1, 1) = 3;
  EXPECT_EQ(basic(1, 1), 3);
}

TEST(functionalTest, mult_Matrix_Exception) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix result = a * b);
}

TEST(functionalFuncTest, inverse_matrix) {
  S21Matrix basic(3, 3);

  basic(0, 0) = 4;
  basic(0, 1) = -2;
  basic(0, 2) = 1;

  basic(1, 0) = 1;
  basic(1, 1) = 6;
  basic(1, 2) = -2;

  basic(2, 0) = 1;
  basic(2, 1) = 0;
  basic(2, 2) = 0;

  basic = basic.InverseMatrix();

  EXPECT_EQ(basic(0, 1), 0);
  EXPECT_EQ(basic(0, 2), 1);

  EXPECT_EQ(basic(1, 0), 1);
  EXPECT_EQ(basic(2, 0), 3);

  EXPECT_EQ(basic(2, 1), 1);
  EXPECT_EQ(basic(2, 2), -13);
}

TEST(Basic, copy_constructor) {
  S21Matrix basic(2, 3);
  S21Matrix result(basic);
  EXPECT_EQ(result.Get_Rows(), 2);
  EXPECT_EQ(result.Get_Cols(), 3);
  EXPECT_EQ(basic == result, true);
  EXPECT_EQ(basic != result, false);
}

TEST(Basic, move_constructor) {
  S21Matrix basic(2, 3);
  S21Matrix result(std::move(basic));
  EXPECT_EQ(result.Get_Rows(), 2);
  EXPECT_EQ(result.Get_Cols(), 3);
  EXPECT_EQ(basic.Get_Rows(), 3);
  EXPECT_EQ(basic.Get_Cols(), 3);
}

TEST(assignmentOperator, brakets_Exception) {
  S21Matrix exception(2, 3);
  EXPECT_ANY_THROW(exception(1, 5));
}

TEST(functionalFuncTest, braket_Exception2) {
  S21Matrix exception(1, 1);
  EXPECT_ANY_THROW(exception(5, 0) = 5);
}

TEST(supportFunction, set_zero_Matrix) {
  S21Matrix basic;
  EXPECT_EQ(basic.Get_Rows(), 3);
  EXPECT_EQ(basic.Get_Cols(), 3);
}

TEST(assignmentOperator, moveConst) {
  S21Matrix basic(2, 3);
  S21Matrix basic2 = std::move(basic);
  EXPECT_EQ(basic.Get_Rows(), 3);
  EXPECT_EQ(basic.Get_Cols(), 3);
  EXPECT_EQ(basic2.Get_Rows(), 2);
  EXPECT_EQ(basic2.Get_Cols(), 3);
}

TEST(functionalTest, copy) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a = b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, plus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  S21Matrix result = a + b;
  EXPECT_DOUBLE_EQ(result(1, 1), 3.3);
}

TEST(functionalTest, plus2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a += b;
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(functionalTest, plus3) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SumMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(functionalTest, plus_Exception) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix result = a + b);
}

TEST(functionalTest, plus_Exception2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a += b);
}

TEST(functionalTest, plus_Exception3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SumMatrix(b));
}

TEST(functionalTest, minus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  S21Matrix result = a - b;
  EXPECT_DOUBLE_EQ(result(1, 1), -1.1);
}

TEST(functionalTest, minus2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a -= b;
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(functionalTest, minus3) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SubMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(functionalTest, minus_Exception) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix result = a + b);
}

TEST(functionalTest, minus_Exception2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a -= b);
}

TEST(functionalTest, minus_Exception3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SubMatrix(b));
}

TEST(functionalTest, mult_Matrix) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  S21Matrix result = a * b;
  EXPECT_DOUBLE_EQ(result(1, 1), 2.2);
}

TEST(functionalTest, mult_Matrix2) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a *= b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, mult_Matrix3) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a.MulMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, mult_MatrixTotal) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 4);
  S21Matrix res(3, 4);

  for (int i = 0, value = 0; i < a.Get_Rows(); i++)
    for (int j = 0; j < a.Get_Cols(); j++)
      a(i, j) = value++;

  for (int i = 0, value = 0; i < b.Get_Rows(); i++)
    for (int j = 0; j < b.Get_Cols(); j++)
      b(i, j) = value++;

  res(0, 0) = 4, res(0, 1) = 5, res(0, 2) = 6, res(0, 3) = 7;
  res(1, 0) = 12, res(1, 1) = 17, res(1, 2) = 22, res(1, 3) = 27;
  res(2, 0) = 20, res(2, 1) = 29, res(2, 2) = 38, res(2, 3) = 47;

  S21Matrix answer = a * b;
  EXPECT_TRUE(res == answer);
}

TEST(functionalTest, mult_Matrix_Exception2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a *= b);
}

TEST(functionalTest, mult_Matrix_Exception3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.MulMatrix(b));
}

TEST(functionalTest, mult_MatrixNum) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  S21Matrix result = a * 2;
  EXPECT_DOUBLE_EQ(result(1, 1), 2.2);
}

TEST(functionalTest, mult_MatrixNum2) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  a *= 2;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, mult_MatrixNum3) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  a.MulNumber(2);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, mult_MatrixNum4) {
  S21Matrix a(3, 2);
  a.MulNumber(NAN);
  EXPECT_EQ(std::isnan(a(1, 1)), 1);
  EXPECT_EQ(std::isnan(a(2, 1)), 1);
  EXPECT_EQ(std::isnan(a(1, 0)), 1);
}

TEST(functionalTest, equal) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  EXPECT_EQ(a == b, false);
  b.Set(2, 3);
  a(1, 1) = 1.3;
  b(1, 1) = 1.3;
  EXPECT_EQ(a == b, true);
  b(1, 2) = 1.3;
  EXPECT_EQ(a == b, false);
}

TEST(functionalTest, equal2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  EXPECT_EQ(a == b, true);
  a(1, 1) = 1.3;
  EXPECT_EQ(a == b, false);
  b(1, 1) = 1.3;
  EXPECT_EQ(a == b, true);
}

TEST(functionalFuncTest, determinant) {
  S21Matrix basic(4, 4);
  basic(0, 0) = 9;
  basic(0, 1) = 2;
  basic(0, 2) = 2;
  basic(0, 3) = 4;

  basic(1, 0) = 3;
  basic(1, 1) = 4;
  basic(1, 2) = 4;
  basic(1, 3) = 4;

  basic(2, 0) = 4;
  basic(2, 1) = 4;
  basic(2, 2) = 9;
  basic(2, 3) = 9;

  basic(3, 0) = 1;
  basic(3, 1) = 1;
  basic(3, 2) = 5;
  basic(3, 3) = 1;
  EXPECT_DOUBLE_EQ(basic.Determinant(), -578);
}

TEST(functionalFuncTest, determinant2) {
  S21Matrix basic(1, 1);
  basic(0, 0) = 10;
  EXPECT_DOUBLE_EQ(basic.Determinant(), 10);
}

TEST(functionalFuncTest, determinant3) {
  S21Matrix basic(2, 2);
  basic(0, 0) = 1.1;
  basic(0, 1) = 3.5;

  basic(1, 0) = -2;
  basic(1, 1) = 4;
  EXPECT_DOUBLE_EQ(basic.Determinant(), 11.4);
}

TEST(functionalFuncTest, determinantException) {
  S21Matrix exception(4, 3);
  EXPECT_ANY_THROW(exception.Determinant());
}

TEST(functionalFuncTest, inverse_matrix2) {
  S21Matrix basic(3, 3);

  basic(0, 0) = 2;
  basic(0, 1) = 2;
  basic(0, 2) = 123;

  basic(1, 0) = 12;
  basic(1, 1) = 6;
  basic(1, 2) = 5;

  basic(2, 0) = 1;
  basic(2, 1) = 2;
  basic(2, 2) = 8;

  basic = basic.InverseMatrix();

  EXPECT_DOUBLE_EQ(basic(0, 1), 0.10910815939278938);
  EXPECT_DOUBLE_EQ(basic(0, 2), -0.34535104364326374);

  EXPECT_DOUBLE_EQ(basic(1, 0), -0.043168880455407968);
  EXPECT_DOUBLE_EQ(basic(2, 0), 0.0085388994307400382);

  EXPECT_DOUBLE_EQ(basic(2, 1), -0.00094876660341555979);
  EXPECT_DOUBLE_EQ(basic(2, 2), -0.0056925996204933585);
}

TEST(functionalFuncTest, inverse_matrixException) {
  S21Matrix exception(3, 3);

  //  determ = 0
  exception(0, 0) = 1;
  exception(0, 1) = 1;
  exception(0, 2) = 3;
  exception(1, 0) = 4;
  exception(1, 1) = 4;
  exception(1, 2) = 6;
  exception(2, 0) = 4;
  exception(2, 1) = 4;
  exception(2, 2) = 9;
  EXPECT_EQ(exception.Determinant(), 0);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(functionalFuncTest, inverse_matrixException2) {
  S21Matrix exception(3, 3);

  exception(0, 0) = 1;
  exception(0, 1) = 4;
  exception(0, 2) = 1;
  exception(1, 0) = 3;
  exception(1, 1) = 7;
  exception(1, 2) = 2;
  exception(2, 0) = 3;
  exception(2, 1) = 2;
  exception(2, 2) = 1;
  EXPECT_EQ(exception.Determinant(), 0);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(functionalFuncTest, inverse_matrixException3) {
  S21Matrix exception(3, 2);
  EXPECT_ANY_THROW(exception.InverseMatrix());
}

TEST(functionalFuncTest, transpose) {
  S21Matrix result(2, 2);

  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 4;
  result(1, 1) = 3;
  result = result.Transpose();

  EXPECT_EQ(result(0, 0), 1);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(1, 0), 2);
  EXPECT_EQ(result(1, 1), 3);
}

TEST(functionalFuncTest, calc_complements) {
  S21Matrix result(2, 2);
  S21Matrix another(2, 2);

  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 4;
  result(1, 1) = 3;

  another(0, 0) = 1;
  another(0, 1) = 2;
  another(1, 0) = 13;
  another(1, 1) = 7;

  result -= another * result;
  result = result.CalcComplements();

  EXPECT_EQ(result(0, 0), -44);
  EXPECT_EQ(result(0, 1), 37);
  EXPECT_EQ(result(1, 0), 6);
  EXPECT_EQ(result(1, 1), -8);
}

TEST(Basic, defaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.Get_Rows(), 3);
  EXPECT_EQ(m.Get_Cols(), 3);
}

TEST(Basic, defaultConstructorEx) {
  S21Matrix m;
  EXPECT_ANY_THROW(m(5, 5));
}

TEST(Basic, parameterizedCconstructor) {
  S21Matrix m(2, 3);
  EXPECT_EQ(m.Get_Rows(), 2);
  EXPECT_EQ(m.Get_Cols(), 3);
}

TEST(Basic, parameterizedCconstructorEx) {
  EXPECT_ANY_THROW(S21Matrix ex(0, -2));
}

TEST(Basic, parameterizedCconstructorEx2) {
  EXPECT_ANY_THROW(S21Matrix m(0, 1););
}

TEST(Basic, copyConstructor) {
  S21Matrix m(2, 3);
  S21Matrix res(m);
  EXPECT_EQ(res.Get_Rows(), 2);
  EXPECT_EQ(res.Get_Cols(), 3);
  EXPECT_EQ(m == res, true);
}

TEST(assignmentOperator, braketsTrow) {
  S21Matrix m(2, 3);
  EXPECT_ANY_THROW(m(1, 5));
}

TEST(functionalTest, Plus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  S21Matrix res = a + b;
  EXPECT_DOUBLE_EQ(res(1, 1), 3.3);
}

TEST(functionalTest, PlusEx) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix res = a + b);
}

TEST(functionalTest, Plus2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a += b;
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(functionalTest, PlusEx2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a += b);
}

TEST(functionalTest, Plus3) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SumMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 3.3);
}

TEST(functionalTest, PlusEx3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SumMatrix(b));
}

TEST(functionalTest, Minus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  S21Matrix res = a - b;
  EXPECT_DOUBLE_EQ(res(1, 1), -1.1);
}

TEST(functionalTest, MinusEx) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix res = a + b);
}

TEST(functionalTest, Minus2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a -= b;
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(functionalTest, MinusEx2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a -= b);
}

TEST(functionalTest, Minus3) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  a.SubMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), -1.1);
}

TEST(functionalTest, MinusEx3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.SubMatrix(b));
}

TEST(functionalTest, MultMatrix) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  S21Matrix res = a * b;
  EXPECT_DOUBLE_EQ(res(1, 1), 2.2);
}

TEST(functionalTest, MultMatrixEx) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(S21Matrix res = a * b);
}

TEST(functionalTest, MultMatrix2) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a *= b;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, MultMatrixEx2) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a *= b);
}

TEST(functionalTest, MultMatrix3) {
  S21Matrix a(3, 2);
  S21Matrix b(2, 3);
  a(1, 1) = 1.1;
  b(1, 1) = 2;
  a.MulMatrix(b);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, MultMatrixEx3) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  a(1, 1) = 1.1;
  b(1, 1) = 2.2;
  EXPECT_ANY_THROW(a.MulMatrix(b));
}

TEST(functionalTest, MultMatrixNum) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  S21Matrix res = a * 2;
  EXPECT_DOUBLE_EQ(res(1, 1), 2.2);
}

TEST(functionalTest, MultMatrixNum2) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  a *= 2;
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, MultMatrixNum3) {
  S21Matrix a(3, 2);
  a(1, 1) = 1.1;
  a.MulNumber(2);
  EXPECT_DOUBLE_EQ(a(1, 1), 2.2);
}

TEST(functionalTest, equalFunc) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);
  EXPECT_EQ(a.EqMatrix(b), false);
  b.Set_Rows(3);
  a(1, 1) = 1.1;
  b(1, 1) = 1.1;
  EXPECT_EQ(a.EqMatrix(b), true);
  b(1, 2) = 1.1;
  EXPECT_EQ(a.EqMatrix(b), false);
}

TEST(functionalFuncTest, determinantEx) {
  S21Matrix m(4, 3);

  EXPECT_ANY_THROW(m.Determinant());
}

TEST(functionalFuncTest, calcComplementsEx) {
  S21Matrix m(4, 3);
  EXPECT_ANY_THROW(m.CalcComplements());
}

TEST(functionalFuncTest, inverseMatrix) {
  S21Matrix m(3, 3);
  // var 1
  m(0, 0) = 4;
  m(0, 1) = -2;
  m(0, 2) = 1;
  m(1, 0) = 1;
  m(1, 1) = 6;
  m(1, 2) = -2;
  m(2, 0) = 1;
  m(2, 1) = 0;
  m(2, 2) = 0;

  m = m.InverseMatrix();

  EXPECT_EQ(m(0, 1), 0);
  EXPECT_EQ(m(0, 2), 1);
  EXPECT_EQ(m(1, 0), 1);
  EXPECT_EQ(m(2, 0), 3);
  EXPECT_EQ(m(2, 1), 1);
  EXPECT_EQ(m(2, 2), -13);
}

TEST(functionalFuncTest, calcComplements) {
  S21Matrix result{2, 2};
  S21Matrix another{2, 2};

  result(0, 0) = 1;
  result(0, 1) = 2;
  result(1, 0) = 4;
  result(1, 1) = 3;

  another(0, 0) = 1;
  another(0, 1) = 2;
  another(1, 0) = 13;
  another(1, 1) = 7;

  result -= another * result;
  result = result.CalcComplements();

  EXPECT_EQ(result(0, 0), -44);
  EXPECT_EQ(result(0, 1), 37);
  EXPECT_EQ(result(1, 0), 6);
  EXPECT_EQ(result(1, 1), -8);
}

TEST(functionalFuncTest, inverseMatrixEx) {
  S21Matrix m(3, 3);

  //  determ = 0
  m(0, 0) = 1;
  m(0, 1) = 1;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 4;
  m(1, 2) = 6;
  m(2, 0) = 4;
  m(2, 1) = 4;
  m(2, 2) = 9;
  EXPECT_EQ(m.Determinant(), 0);
  EXPECT_ANY_THROW(m.InverseMatrix());
}

TEST(functionalFuncTest, inverseMatrixEx2) {
  S21Matrix m(3, 3);

  m(0, 0) = 1;
  m(0, 1) = 4;
  m(0, 2) = 1;
  m(1, 0) = 3;
  m(1, 1) = 7;
  m(1, 2) = 2;
  m(2, 0) = 3;
  m(2, 1) = 2;
  m(2, 2) = 1;
  EXPECT_EQ(m.Determinant(), 0);
  EXPECT_ANY_THROW(m.InverseMatrix());
}

TEST(functionalFuncTest, inverseMatrixEx3) {
  S21Matrix m(3, 2);
  EXPECT_ANY_THROW(m.InverseMatrix());
}

TEST(functionalFuncTest, braketEx) {
  S21Matrix m(1, 1);
  EXPECT_ANY_THROW(m(5, 0) = 5);
}
int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}