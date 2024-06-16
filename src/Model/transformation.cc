#include "transformation.h"

void s21::Transformation::Scale(double value) {
  if (value != 0) {
    value /= 100;

    for (double &iter : vector_v_) {
      iter *= value;
    }
  }
}

void s21::Transformation::MoveX(double value) {
  value /= 100;

  for (auto iter = 0; iter < vector_v_.size(); iter += 3) {
    vector_v_[iter] += value;
  }
}

void s21::Transformation::MoveY(double value) {
  value /= 100;

  for (auto iter = 1; iter < vector_v_.size(); iter += 3) {
    vector_v_[iter] += value;
  }
}

void s21::Transformation::MoveZ(double value) {
  value /= 100;

  for (auto iter = 2; iter < vector_v_.size(); iter += 3) {
    vector_v_[iter] += value;
  }
}

void s21::Transformation::RotateX(double angle) {
  angle /= 100;

  for (auto iter = 0; iter < vector_v_.size(); iter += 3) {
    double temp = vector_v_[iter + 1];

    vector_v_[iter + 1] =
        vector_v_[iter + 1] * cos(angle) + vector_v_[iter + 2] * sin(angle);
    vector_v_[iter + 2] =
        -1 * temp * sin(angle) + vector_v_[iter + 2] * cos(angle);
  }
}

void s21::Transformation::RotateY(double angle) {
  angle /= 100;

  for (auto iter = 1; iter < vector_v_.size(); iter += 3) {
    double temp = vector_v_[iter - 1];

    vector_v_[iter - 1] =
        vector_v_[iter - 1] * cos(angle) + vector_v_[iter + 1] * sin(angle);
    vector_v_[iter + 1] =
        -1 * temp * sin(angle) + vector_v_[iter + 1] * cos(angle);
  }
}
