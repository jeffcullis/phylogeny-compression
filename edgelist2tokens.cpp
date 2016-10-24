#include "edgelist2tokens.hpp"

EdgeList2Tokens::EdgeList2Tokens() : treeVerts(), edgeRep(), tokens()
{
}

void EdgeList2Tokens::push_new_vertex() {
	treeVerts.push_back(Vertex());
    treeVerts.back().setIndex(treeVerts.size()-1);
}

// Create default 4-vert 3-leaf tree with leaves 0,1,2.
void EdgeList2Tokens::initVerts () {
    size_t i;
	for (i=0; i<4; ++i) { 
		push_new_vertex();
	}
	for (i=1; i<4; ++i) {
		treeVerts[i].setParent(0);
        treeVerts[i].setValue(i-1);
	}
	// Setup trifurcation point's neighbours
	treeVerts[0].setParent(1);
    treeVerts[0].setChild(2);
    treeVerts[0].setChild(3);
}	

// splice a new taxon onto a given edge.
// using convention that edges are referenced by the
// root edge of their corresponding (non-root) vertex.
void EdgeList2Tokens::addTaxon(size_t edgeNo, size_t value)
{
	assert(edgeNo < treeVerts.size() and edgeNo > 0);
    size_t src = edgeNo;
    size_t src_parent = treeVerts[src].getParent();
	push_new_vertex();
	push_new_vertex();
   	size_t n = treeVerts.size();
    size_t new_leaf = n - 2;
    size_t new_internal = n - 1;
    
    treeVerts[new_leaf].setValue(value);
    
	if(edgeNo != 1)
	{	
        treeVerts[new_leaf].setParent(new_internal);
		treeVerts[new_internal].setChild(new_leaf);
		treeVerts[new_internal].setChild(src);
		treeVerts[new_internal].setParent(src_parent);
		treeVerts[src].setParent(new_internal);
        treeVerts[src_parent].swapChild(src, new_internal);
	} else {
        size_t v0ch0 = treeVerts[0].child[0];
        size_t v0ch1 = treeVerts[0].child[1];
        treeVerts[new_internal].setChild(v0ch0);
        treeVerts[v0ch0].setParent(new_internal);
        treeVerts[new_internal].setChild(v0ch1);
        treeVerts[v0ch1].setParent(new_internal);
        treeVerts[0].child[0] = new_leaf;
        treeVerts[0].child[1] = new_internal;
        treeVerts[new_leaf].setParent(0);
        treeVerts[new_internal].setParent(0);
	}
}

void EdgeList2Tokens::buildTree() {
	size_t i;
    initVerts();
	for(i=0; i<edgeRep.size(); ++i) {
		addTaxon(edgeRep[i]+1, i+3);
	}
}

void EdgeList2Tokens::buildTokens(size_t currVert, bool notFirst) {
	if (treeVerts[currVert].child[0] != VERT_NULL) {
        if (notFirst) { tokens.push_back(LB); }
		buildTokens(treeVerts[currVert].child[0], 1);
	}
	if (treeVerts[currVert].child[1] != VERT_NULL) {
		tokens.push_back(COMMA);
		buildTokens(treeVerts[currVert].child[1], 1);
        if (notFirst) { tokens.push_back(RB); }
	}
	if (treeVerts[currVert].child[0] == VERT_NULL and treeVerts[currVert].child[1] == VERT_NULL) {
		tokens.push_back (treeVerts[currVert].getValue());
	}
}

// recalculate the newick tokens based on the linked tree state.
std::vector<size_t> & EdgeList2Tokens::createTokens() {
	tokens.push_back(LB);
	tokens.push_back(0);
	tokens.push_back(COMMA);
	buildTokens(treeVerts[1].getParent(), 0);
	tokens.push_back(RB);
	std::vector<size_t> & res = *(new std::vector<size_t>(tokens));
    return(res);
}

void EdgeList2Tokens::cleanUp() {
    treeVerts.clear();
    edgeRep.clear();
    tokens.clear();
}

std::vector<size_t> & EdgeList2Tokens::getTokens (std::vector<size_t> & edges) {
    edgeRep = edges;
    buildTree();
    std::vector<size_t> & res = createTokens();
    cleanUp();
	return(res);
}


