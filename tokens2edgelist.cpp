#include "tokens2edgelist.hpp"

using namespace std;

Tokens2EdgeList::Tokens2EdgeList() : treeVerts(), rootPath(), tokens() {
    numTaxa = 0;
}

void Tokens2EdgeList::initTreeVerts() {
	treeVerts.push_back(Vertex());
    treeVerts.push_back(Vertex());
    treeVerts.push_back(Vertex());
	treeVerts[0].setParent(1);
	treeVerts[1].setParent(0);
    treeVerts[1].setValue(0);
    treeVerts[2].setParent(0);
    treeVerts[0].setChild(2);
}

size_t Tokens2EdgeList::createNewChild(size_t curr_vert) {
	treeVerts.push_back(Vertex());
	size_t new_vert = treeVerts.size() - 1;
	treeVerts[curr_vert].setChild(new_vert);
	treeVerts[new_vert].setParent(curr_vert);
	return (new_vert);
}

void Tokens2EdgeList::buildTree() {
	size_t i, tok;
    size_t curr_vert = 2;
	initTreeVerts();
    
    numTaxa = 1;
    for (i=3; i<tokens.size(); ++i) {
        tok = tokens[i];
        switch (tok) {
            case LB :
                curr_vert = createNewChild(curr_vert);
                break;
            case RB :
                curr_vert = treeVerts[curr_vert].getParent();
                break;
            case COMMA :
				curr_vert = treeVerts[curr_vert].getParent();
				curr_vert = createNewChild(curr_vert);
                break;
            default :
                treeVerts[curr_vert].setValue(tok);
                numTaxa++;
        }
    }
}

void Tokens2EdgeList::initEdgeList() {
    std::vector<size_t>::iterator it;
    edges = new std::vector<size_t>(numTaxa-3);
    for (it = edges->begin(); it < edges->end(); ++it) {
        *it = 0;
    }
}

// test whether a = (1,2,...) terminal branch.	
bool Tokens2EdgeList::isOneTwo (std::vector<size_t> * list) {
	if (list->size() > 1 and list->at(0) == 1 and list->at(1) == 2) {
        return 1;
    }
    return 0;
}	

void Tokens2EdgeList::insertOnLeaf(size_t big, size_t small) {
    assert(big > small);
    
    if (!(small == 1 and big == 2)) {
        if (small > 2) {
            edges->at(big-3) = 2 * small - 3;
        } else {
            edges->at(big-3) = small;
        }
    }
}

void Tokens2EdgeList::insertOnInterior(size_t big, size_t small) {
    assert(big > small);
    edges->at(big-3) = (small * 2 - 2);
}

std::vector<size_t> * Tokens2EdgeList::combine (std::vector<size_t> * a, std::vector<size_t> * b) 
{
	std::vector<size_t> * lpar = new std::vector<size_t>;
    std::vector<size_t>::iterator it;
    
    for (it = a->begin(); it != a->end(); ++it) {
    	if (*it < b->at(0)) {
    		lpar->push_back(*it);
    	}
    }
	if (lpar->size() == 1) {
        insertOnLeaf(b->at(0), a->at(0));
	} else {
		insertOnInterior(b->at(0), lpar->back());
	}
	lpar->push_back(b->at(0));
	return (lpar);
}

// Given two edgesays a[0] < b[0], remove all in a > b[0], return a U b.
void Tokens2EdgeList::combineLists(size_t vert_idx)
{
	std::vector<size_t> * a;
	std::vector<size_t> * b;
    size_t par_idx = treeVerts[vert_idx].getParent();
	
	if (treeVerts[vert_idx].list[0][0] < treeVerts[vert_idx].list[1][0]) {
        a = treeVerts[vert_idx].list[0];
		b = treeVerts[vert_idx].list[1];
	} else {
		a = treeVerts[vert_idx].list[1];
		b = treeVerts[vert_idx].list[0];
	}
    
	if (isOneTwo(a)) {
        rootPath.push_front(b->at(0));
        delete b;
		treeVerts[par_idx].setList(a);
        treeVerts[vert_idx].list[0] = NULL;
        treeVerts[vert_idx].list[1] = NULL;
	} else {
		treeVerts[par_idx].setList(combine(a, b));
        treeVerts[vert_idx].clearLists();
	}
}

void Tokens2EdgeList::fillEdgeList(size_t curr_vert) {
	size_t c0, c1;
	c0 = treeVerts[curr_vert].child[0];
	c1 = treeVerts[curr_vert].child[1];
    size_t par_idx = treeVerts[curr_vert].getParent();;
	
	if ( c0 == VERT_NULL and c1 == VERT_NULL ) {
		std::vector<size_t> * list = new std::vector<size_t>;
		list->push_back( treeVerts[curr_vert].getValue() );
        treeVerts[par_idx].setList(list);
	} else if ( c0 != VERT_NULL and c1 != VERT_NULL and c0 != c1 ) {
        fillEdgeList(c0);
		fillEdgeList(c1);
		combineLists(curr_vert);
	} else {
		cerr << "Error - index " << curr_vert << " has invalid child indices " 
				<< c0 << " and " << c1 << endl;
	}
}

void Tokens2EdgeList::processRootPath() {
    std::list<size_t>::iterator it;
    std::list<size_t> temp;
    size_t t_idx = 0;
    for (it = rootPath.begin(); it != rootPath.end(); ++it) {
        if (temp.size() == 0) {
            insertOnLeaf(*it, 0);
        } else if (*it < temp.front()) {
            insertOnLeaf(*it, 0);
            while (temp.size() > 1) {
                insertOnInterior(temp.back(), temp.front());
                temp.pop_back();
            }
            temp.pop_back();
        } else if (*it < temp.back()) {
            while (*it < temp.back()) {
                insertOnInterior(temp.back(), *it);
                temp.pop_back();
            }
        }
        temp.push_back(*it);
    }
    while (temp.size() > 1) {
        insertOnInterior(temp.back(), temp.front());
        temp.pop_back();
    }
}

void Tokens2EdgeList::buildEdgeList() {
    initEdgeList();
    fillEdgeList(0);
    processRootPath();
}

void Tokens2EdgeList::freeLists() {
    size_t i;
    for (i=0; i<treeVerts.size(); ++i) {
        if (treeVerts[i].list[0]) {
            cerr << "List 0 found at location " << i << endl;
        }
        if (treeVerts[i].list[1]) {
            cerr << "List 1 found at location " << i << endl;
        }

    }
}

void Tokens2EdgeList::cleanUp () {
    delete treeVerts[1].list[0];
    treeVerts[1].list[0] = NULL;
    //freeLists();
    edges = NULL;
    treeVerts.clear();
    rootPath.clear();
    tokens.clear();
}

void Tokens2EdgeList::getNumTaxa() {
    size_t i;
    numTaxa=0;
    for (i=0; i<tokens.size(); ++i) {
        if (tokens[i] < COMMA) {
            numTaxa++;
        }
    }
}

std::vector<size_t> & Tokens2EdgeList::getEdgeList () {
    std::vector<size_t> * temp;
    buildTree();
    buildEdgeList();
    temp = edges;
    cleanUp();
    return (*temp);
}

std::vector<size_t> & Tokens2EdgeList::getEdgeList(std::vector<size_t> & nv) {
    tokens = nv;
    getNumTaxa();
    return (getEdgeList());
}

