#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <utility>
#include <vector>

namespace s21 {
class ObjParser {
 public:
  const int kMAX_LENGTH = 256;
  explicit ObjParser(std::string filename) : filename_(std::move(filename)) {}
  std::pair<std::vector<double>, std::vector<unsigned>> Parse() noexcept;

 private:
  std::string filename_;
  std::vector<double> vector_v_ = {};
  std::vector<unsigned> vector_f_ = {};
  void GetV(const std::string &buffer) noexcept;
  void GetF(const std::string &buffer) noexcept;
};
}  // namespace s21

#endif  // PARSER_H
