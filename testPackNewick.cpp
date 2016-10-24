#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include "tokens.hpp"

boost::dynamic_bitset<> & packTokens (std::vector<size_t> & tok)
{
    boost::dynamic_bitset<> & packedTokens = *(new boost::dynamic_bitset<>);
    size_t bit_width = 8; // BUG: THIS SHOULD BE SET IN THE CONSTRUCTOR
    // size_t branch_count = 0; // Used to infer position of comma
    for (size_t i=0; i<tok.size(); ++i) {
        switch (tok) {
            case LB:
                packedTokens.push_back(1);
                packedTokens.push_back(0);
                break;
            case RB:
                packedTokens.push_back(1);
                packedTokens.push_back(1);
            case COMMA:
                // No need to store the comma; comma positions can be inferred from tree structure
                break;
            default:
                packedTokens.push_back(0); // Leading 0 for the packed tokens; note therefore need bit_width+1 bits when unpacking (or start at idx=1);
                boost::dynamic_bitset<> temp(bit_width, tok);
                for (size_t i=0; i<bit_width; ++i) {
                    packedTokens.push_back(temp[i]);
                }
                break;
        }
    }
    return packedTokens;
}

std::vector<size_t> & unpackTokens (boost::dynamic_bitset<> & packedTokens)
{
    std::vector<size_t> tokens = *(new std::vector<size_t>);
    size_t bit_width = 8;
    size_t i = 0;
    size_t commaPlacement = 0;
    while (i < packedTokens.size()) {
        if (packedTokens[i] == 0) {
            ++i;
            if (commaPlacement == 1) {
                tokens.push_back(COMMA);
                //commaPlacement = 0;
            }
            
            // parse a node id
            boost::dynamic_bitset<> node(bit_width, 0ul);
            for (size_t bidx=0; bidx<bit_width; ++bidx) {
                node[bidx] = packedTokens[i+bidx];
            }
            i = i + bit_width;
            std::size_t val = node.to_ulong();  // BUG: NEED TO CATCH POSSIBLE ULONG OVERFLOW ERROR HERE - see boost docs.
            
            /*
            From: http://www.boost.org/doc/libs/1_56_0/libs/dynamic_bitset/example/example3.cpp
            bool fits_in_ulong = true;
            unsigned long ul = 0;
            try {
                ul = x.to_ulong();
            } catch(std::overflow_error &) {
            */
            
            tokens.push_back(val);

        } else {
            // parse a left or right bracket
            ++i;
            if (packedTokens[i] == 0) {
                if (commaPlacement == 1) {
                    tokens.push_back(COMMA);
                    commaPlacement = 0;
                }
                tokens.push_back(LB);
            } else {
                tokens.push_back(RB);
                commaPlacement = 1;
            }
       }
       ++i;
   }
   return tokens;
}


int main() {
    std::cout << "HW!" << std::endl;
    return 0;
}




