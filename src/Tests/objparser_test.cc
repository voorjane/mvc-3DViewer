#include "../Model/objparser.h"

#include <gtest/gtest.h>

#include <vector>

TEST(ObjParser, ObjParserNormalBehaviour) {
s21::ObjParser parser("./cub.obj");
std::pair<std::vector<double>, std::vector<unsigned>> vectors =
        parser.Parse();

std::vector<double> test_vector_d = {
        0.000000, 1.000000, 1.000000, 0.000000, 0.000000, 1.000000,
        1.000000, 0.000000, 1.000000, 1.000000, 1.000000, 1.000000,
        0.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000,
        1.000000, 0.000000, 0.000000, 1.000000, 1.000000, 0.000000};
std::vector<unsigned> test_vector_u = {1, 2, 3, 8, 7, 6, 4, 3, 7,
                                       5, 1, 4, 5, 6, 2, 2, 6, 7};

for (size_t i = 0; i < vectors.first.size(); ++i) {
EXPECT_NEAR(vectors.first[i], test_vector_d[i], 1e-6);
}

for (size_t i = 0; i < vectors.second.size(); ++i) {
EXPECT_NEAR(vectors.second[i], test_vector_u[i], 1e-6);
}
}