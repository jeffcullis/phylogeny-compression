
#ifndef _edgelist2tokens_hpp
#define _edgelist2tokens_hpp

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include <cstdlib>
#include <climits>
#include "vertex.hpp"
#include "tokens.hpp"

class EdgeList2Tokens
{
  public:
    EdgeList2Tokens();
    std::vector<size_t> & getTokens (std::vector<size_t> & edges);

  private:
    std::vector<Vertex> treeVerts;
    std::vector<size_t> edgeRep;
    std::vector<size_t> tokens;

    void push_new_vertex();
    void initVerts ();
    void addTaxon(size_t edgeNo, size_t value);
    void buildTree();
    void buildTokens(size_t currVert, bool notFirst);
    std::vector<size_t> & createTokens();
    void cleanUp();
};

#endif
