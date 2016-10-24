#ifndef _tokens_hpp
#define _tokens_hpp

#include <iostream>

const unsigned int LB = UINT_MAX-1;
const unsigned int RB = UINT_MAX-2;
const unsigned int COMMA = UINT_MAX-3;

class Tokens {
    public:
        static std::vector<std::size_t> & newick2tokens (std::string & newick);
        static std::string & tokens2newick(std::vector<std::size_t> & tokens);
};

#endif
