/*
 *  main.cpp
 *  
 *
 *  Created by Jeff Cullis on 12-11-09.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include "tokens2edgelist.hpp"
#include "edgelist2tokens.hpp"
#include "tokens.hpp"
#include "edgelist.hpp"

using namespace std;

const size_t numTaxa = 50;
const size_t numIter = 1000;
Tokens2EdgeList t2e;
EdgeList2Tokens e2t;
vector<size_t> edges(numTaxa-3);


void init_edges(vector<size_t> & edges) {
    size_t i;
    size_t numEdges;
    for (i=0; i<numTaxa-3; ++i) {
        numEdges = 2*i+3;
        edges[i] = rand() % numEdges;
    }
}

void init_edges_fixed(vector<size_t> & edges) {
    edges[0] = 0;
    edges[1] = 0;
    edges[2] = 6;
    edges[3] = 1;
    edges[4] = 8;
}

bool edges_cmp(vector<size_t> & edges1, vector<size_t> & edges2) {
    size_t i;
    if (edges1.size() == edges2.size()) {
        for (i=0; i<edges1.size(); ++i) {
            if (edges1[i] != edges2[i]) {
                return (0);
            }
        }
    } else {
        return (0);
    }
    return (1);
}

void print_edges (vector<size_t> & a) {
    for (size_t i=0; i<a.size(); ++i) {
        cout << a[i] << "\t";
    }
    cout << endl;
}

bool run_test() {
    bool result = 0;
    init_edges(edges);
    vector<size_t> & toks = e2t.getTokens(edges);
    string & nwk = Tokens::tokens2newick(toks);
	vector<size_t> & edges_new = t2e.getEdgeList(toks);
    result = edges_cmp(edges, edges_new);  
    if (!result) {
        cout << "Error - the input edges" << endl;
        print_edges(edges);
        cout << "With Newick string" << endl;
        cout << nwk << endl;
        cout << "Yielded the following non-equivalent output edgesay" << endl;
        print_edges(edges_new);
    }
    delete &nwk;
    delete &edges_new;  
    return (result);
}

bool run_all(size_t numIter) {
    size_t i;
    bool result = 1;
    for (i=0; result != 0 and i < numIter; ++i) {
        result = run_test();
    }
    return result;
}

int main() {
    srand(time(NULL));
    if (run_all(numIter)) {
        cout << "All " << numIter << " randomised tests have passed." << endl;
    } else {
        cout << "Error found during randomised test." << endl;
    }
	return 0;
}
