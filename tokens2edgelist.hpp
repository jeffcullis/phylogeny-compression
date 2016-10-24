//
//  tokens2edgelist.hpp
//  
//
//  Created by Jeff Cullis on 12-11-19.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef _tokens2edgelist_hpp
#define _tokens2edgelist_hpp

#include <vector>
#include <string>
#include <list>
#include <climits>
#include <cstdlib>
#include <cassert>
#include "vertex.hpp"
#include "tokens.hpp"

class Tokens2EdgeList {
public:
	Tokens2EdgeList();
	//std::vector<size_t> * getArray(std::vector<size_t> & tokens);
    std::vector<size_t> & getEdgeList(std::vector<size_t> & tok);
  	
protected:
    std::vector<size_t> & getEdgeList ();
    
    void parseNewick(std::string & nck_str);
    
  	void initTreeVerts();
  	size_t createNewChild(size_t curr_vert);
  	void buildTree();
  	
    void initEdgeList();
    bool isOneTwo (std::vector<size_t> * list);
    void insertOnLeaf(size_t big, size_t small);
    void insertOnInterior(size_t big, size_t small);
    std::vector<size_t> * combine (std::vector<size_t> * a, std::vector<size_t> * b);
    void combineLists(size_t vert_idx);
  	void fillEdgeList(size_t curr_vert);
    void buildEdgeList();
	
    void processRootPath();
    
  	void freeLists();
    void cleanUp();
    
    void getNumTaxa();
    
    size_t numTaxa;
    std::vector<size_t> tokens;
  	std::vector<Vertex> treeVerts;
    std::list<size_t> rootPath;
  	std::vector<size_t> * edges;
};

#endif

