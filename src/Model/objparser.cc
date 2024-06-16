#include "objparser.h"

#include <fstream>
#include <sstream>

std::pair<std::vector<double>, std::vector<unsigned>>
s21::ObjParser::Parse() noexcept {
  std::fstream fp;
  fp.open(filename_);

  if (fp.is_open()) {
    std::string buffer;

    while (std::getline(fp, buffer)) {
      if (buffer[0] == 'v') {
        GetV(buffer);
      } else if (buffer[0] == 'f') {
        GetF(buffer);
      }
    }
  }

  fp.close();

  auto vector_v_f_pair = std::make_pair(vector_v_, vector_f_);

  return vector_v_f_pair;
}

void s21::ObjParser::GetV(const std::string &buffer) noexcept {
  double number1, number2, number3;

  std::stringstream iss(buffer);
  char v;

  if (iss >> v >> number1 >> number2 >> number3) {
    vector_v_.push_back(number1);
    vector_v_.push_back(number2);
    vector_v_.push_back(number3);
  }
}

void s21::ObjParser::GetF(const std::string &buffer) noexcept {
  std::stringstream iss(buffer);
  std::string token;
  unsigned first = 0, first_index = 0, index = 0;

  while (std::getline(iss, token, ' ')) {
    sscanf(token.c_str(), "%d", &index);

    if (index <= 0 || token.find('\r') != std::string::npos) continue;
    --index;

    if (first == 0) {
      vector_f_.push_back(index);
      first_index = index;
      first = 1;
    } else {
      vector_f_.insert(vector_f_.end(), {index, index});
    }
  }
  vector_f_.push_back(first_index);
}
