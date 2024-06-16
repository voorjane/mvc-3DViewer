#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

#include "objparser.h"

namespace s21 {
class Transformation {
 public:
  explicit Transformation(std::vector<double> vector_v)
      : vector_v_(std::move(vector_v)) {}

  void Scale(double value);
  void MoveX(double value);
  void MoveY(double value);
  void MoveZ(double value);
  void RotateX(double angle);
  void RotateY(double angle);
  const std::vector<double>& GetVector() const { return vector_v_; }

 private:
  std::vector<double> vector_v_;
};

class TransformationFacade {
 public:
  explicit TransformationFacade(std::vector<double> vector_v)
      : transformation_(std::move(vector_v)) {}

  void Scale(double value) { transformation_.Scale(value); }

  void Move(double x, double y, double z) {
    transformation_.MoveX(x);
    transformation_.MoveY(y);
    transformation_.MoveZ(z);
  }

  void Rotate(double x, double y) {
    transformation_.RotateX(x);
    transformation_.RotateY(y);
  }

  const std::vector<double>& GetVector() const {
    return transformation_.GetVector();
  }

 private:
  Transformation transformation_;
};
}  // namespace s21

#endif  // TRANSFORMATION_H
