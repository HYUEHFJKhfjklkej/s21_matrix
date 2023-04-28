#ifndef S21_MATRIX
#define S21_MATRIX

#include <algorithm>
#include <cmath>
#include <stdexcept>

class S21Matrix {
public:
  S21Matrix();
  ~S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);

  int Get_Rows() const noexcept;
  int Get_Cols() const noexcept;

  void Set(int cols, int rows);
  void Set_Cols(int cols);
  void Set_Rows(int rows);

  double &operator()(const int rows, const int columns);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double &other);
  [[nodiscard]] S21Matrix operator+(const S21Matrix &other) const;
  [[nodiscard]] S21Matrix operator-(const S21Matrix &other) const;
  [[nodiscard]] S21Matrix operator*(const S21Matrix &other) const;
  bool operator==(const S21Matrix &other) const;
  bool operator!=(const S21Matrix &other) const;

  friend S21Matrix operator*(const double &, const S21Matrix &);
  friend S21Matrix operator*(const S21Matrix &, const double &);

  void SumMatrix(const S21Matrix &other);
  bool EqMatrix(const S21Matrix &other) const;
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);

  [[nodiscard]] S21Matrix Transpose() const;
  [[nodiscard]] S21Matrix CalcComplements() const;

  double Determinant() const;

  S21Matrix InverseMatrix() const;

private:
  int rows_, cols_;
  double **matrix_;
  void remove();
  void allocateMatrix(int rows, int cols);
  [[nodiscard]] S21Matrix Submatrix(int excluded_row, int excluded_col) const;
  void CheckMatrixSize(const S21Matrix &other) const;
};

#endif // S21_MATRIX