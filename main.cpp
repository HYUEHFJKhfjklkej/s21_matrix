#include "s21_matrix_oop.h"

void S21Matrix::allocateMatrix(int rows, int cols) {
  if (cols <= 0 || rows <= 0) {
    throw std::invalid_argument("Invalid argument");
  }
  matrix_ = new double *[rows];
  for (int i = 0; i < rows; ++i) {
    matrix_[i] = new double[cols];
  }
}

S21Matrix::S21Matrix() : rows_(3), cols_(3) { allocateMatrix(rows_, cols_); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  allocateMatrix(rows_, cols_);
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-6) {
        return false;
      }
    }
  }
  return true;
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  allocateMatrix(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = std::exchange(other.rows_, 3);
  cols_ = std::exchange(other.cols_, 3);
  matrix_ = std::exchange(other.matrix_, nullptr);
  other.allocateMatrix(3, 3);
}

S21Matrix::~S21Matrix() { remove(); }

void S21Matrix::remove() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  rows_ = 0;
  cols_ = 0;
  delete[] matrix_;
  matrix_ = nullptr;
}

int S21Matrix::Get_Rows() const noexcept { return rows_; }

int S21Matrix::Get_Cols() const noexcept { return cols_; }

double &S21Matrix::operator()(const int rows, const int columns) {
  if (rows < 0 || rows >= rows_ || columns < 0 || columns >= cols_)
    throw std::out_of_range("Out of range");
  return matrix_[rows][columns];
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    S21Matrix tmp(other.rows_, other.cols_);
    for (int i = 0; i < other.rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        tmp.matrix_[i][j] = other.matrix_[i][j];
      }
    }
    *this = std::move(tmp);
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    remove();
    rows_ = std::exchange(other.rows_, 3);
    cols_ = std::exchange(other.cols_, 3);
    matrix_ = std::exchange(other.matrix_, nullptr);
    other.allocateMatrix(3, 3);
  }
  return *this;
}

void S21Matrix::Set_Cols(int cols) { Set(cols, rows_); }

void S21Matrix::Set_Rows(int rows) { Set(cols_, rows); }

void S21Matrix::Set(int rows, int cols) {
  S21Matrix tmp(rows, cols);
  for (int i = 0; i < std::min(rows, rows_); i++) {
    for (int j = 0; j < std::min(cols, cols_); j++) {
      tmp(i, j) = matrix_[i][j];
    }
  }
  *this = std::move(tmp);
}

void S21Matrix::CheckMatrixSize(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Wrong matrix, different Size");
  }
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  CheckMatrixSize(other);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  CheckMatrixSize(other);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Wrong matrix, different Size first matrix "
        "columns and second matrix rows");
  }
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        tmp(i, j) += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(tmp);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix tmp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp(j, i) = matrix_[i][j];
    }
  }
  return tmp;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
      result(i, j) = sign * this->Submatrix(i, j).Determinant();
    }
  }

  return result;
}

S21Matrix S21Matrix::Submatrix(int excluded_row, int excluded_col) const {
  S21Matrix submatrix(rows_ - 1, cols_ - 1);
  int row_offset = 0;

  for (int i = 0; i < rows_ - 1; i++) {
    if (i == excluded_row) {
      row_offset = 1;
    }

    int col_offset = 0;
    for (int j = 0; j < cols_ - 1; j++) {
      if (j == excluded_col) {
        col_offset = 1;
      }
      submatrix(i, j) = matrix_[i + row_offset][j + col_offset];
    }
  }
  return submatrix;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square");
  }
  if (rows_ == 1) {
    return matrix_[0][0];
  } else if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }
  double det = 0;
  for (int i = 0; i < cols_; i++) {
    det += (i % 2 == 0 ? 1.0 : -1.0) * matrix_[0][i] *
           Submatrix(0, i).Determinant();
  }
  return det;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (fabs(det) < 1e-6) {
    throw std::invalid_argument("Impossible inverse matrix, determinant is 0");
  }
  S21Matrix temp = CalcComplements().Transpose();
  return temp *= 1 / det;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  return SumMatrix(other), *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  return SubMatrix(other), *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  return MulMatrix(other), *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix res(*this);
  return res += other;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix res(*this);
  return res -= other;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix res(*this);
  return res *= other;
}

S21Matrix operator*(const double &num, const S21Matrix &other) {
  S21Matrix res(other);
  return res *= num;
}

S21Matrix operator*(const S21Matrix &other, const double &num) {
  S21Matrix res(other);
  return res *= num;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

bool S21Matrix::operator!=(const S21Matrix &other) const {
  return !EqMatrix(other);
}

S21Matrix &S21Matrix::operator*=(const double &other) {
  return MulNumber(other), *this;
}
