#include <iostream>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "tokens.hpp"

namespace {
TEST(TokensTest, TestNewick) {
  std::string newick_str = "((0,1),(2,(3,4)));";
  std::vector<size_t> & toks = Tokens::newick2tokens(newick_str);

  for (size_t i=0; i<toks.size(); ++i) {
    std::cout << toks[i] << std::endl;
  }

  std::vector<size_t> expected_tok = {
  	LB, LB, 0, COMMA, 1, RB, COMMA, LB, COMMA, 2, COMMA, LB, 3, COMMA, 4, RB, RB, RB
  };



/*int main() {
    std::cout << "Hello World!" << std::endl;
    
    std::vector<size_t> x {LB, LB, LB, 2, COMMA, 1, RB, COMMA, 3, RB, COMMA, 4, RB};
    std::string & y = tokens2newick(x);
    std::cout << y << std::endl;
    
    std::string n("((0,1),(2,(3,4)));");
    std::vector<size_t> & toks = newick2tokens(n);

    return 0;
}*/

}

}