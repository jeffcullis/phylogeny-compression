#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include "tokens.hpp"

// Go from Newick String to Array of Tokens, and back.

std::vector<std::size_t> & Tokens::newick2tokens (std::string & newick)
{
    size_t i, k;
    std::string x;
    char c;
    std::vector<std::size_t> & tokens = *(new std::vector<std::size_t>);
    for (i=0; i<newick.length(); ++i) {
        c = newick[i];
		switch(c) {
			case '(' :
				tokens.push_back(LB);
				break;
			case ')' :
				tokens.push_back(RB);
				break;
			case ',' :
				tokens.push_back(COMMA);
				break;
			case ';' :
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				if ( isdigit(c) ) {
                    x.push_back(c);
                }
                if ( !isdigit(newick[i+1]) ) {
                    tokens.push_back(std::stoi(x.c_str()));
                    x.clear();
                }
				break;
			default :
				std::cerr << "Error: found illegal char " << c << " in input Newick string." << std::endl;
				exit(-1);
				break;
		}
	}
	return tokens;
}

std::string & Tokens::tokens2newick(std::vector<std::size_t> & tokens)
{
    std::string & newick = *(new std::string);
    for (size_t i=0; i<tokens.size(); ++i) {
        size_t tok = tokens[i];
        switch(tok) {
            case LB:
                newick.push_back('(');
                break;
            case RB:
                newick.push_back(')');
                break;
            case COMMA:
                newick.push_back(',');
                break;
            default:
                newick.append(std::to_string(tok));
                break;
        }
    }
    newick.push_back(';');
    return newick;
}

/*int main() {
    std::cout << "Hello World!" << std::endl;
    
    std::vector<size_t> x {LB, LB, LB, 2, COMMA, 1, RB, COMMA, 3, RB, COMMA, 4, RB};
    std::string & y = tokens2newick(x);
    std::cout << y << std::endl;
    
    std::string n("((0,1),(2,(3,4)));");
    std::vector<size_t> & toks = newick2tokens(n);
    for (size_t i=0; i<toks.size(); ++i) {
        std::cout << toks[i] << std::endl;
    }
    return 0;
}*/









	
