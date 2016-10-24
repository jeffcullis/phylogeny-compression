#include "vertex.hpp"

Vertex::Vertex () {
	parent = idx = val = child[0] = child[1] = VERT_NULL;
	list[0] = list[1] = NULL;
}

void Vertex::setParent (size_t p) {
	parent = p;
}

size_t Vertex::getParent () {
	return parent;
}

void Vertex::setChild (size_t c) {
	if (child[0] == VERT_NULL) {
		child[0] = c;
	} else if (child[1] == VERT_NULL) {
		child[1] = c;
	} else {
		std::cerr << "Can't set child - both children already set." << std::endl;
	}
}

void Vertex::swapChild (size_t orig_child, size_t new_child) {
	if (child[0] == orig_child) {
		child[0] = new_child;
	} else if (child[1] == orig_child) {
		child[1] = new_child;
	} else {
		std::cerr << "Vert " << idx << " points to a non-root vert that doesn't point back." << std::endl;
	}
}

void Vertex::setValue (size_t v) {
	val = v;
}

size_t Vertex::getValue () {
	return val;
}

void Vertex::setIndex (size_t i) {
	idx = i;
}

size_t Vertex::getIndex () {
	return idx;
}

void Vertex::setList (std::vector<size_t> * l) {
	if (list[0] == NULL) {
		list[0] = l;
	} else if (list[1] == NULL) {
		list[1] = l;
	} else {
		std::cerr << "Error: both lists already set." << std::endl;
	}
}

void Vertex::clearLists () {
    if (list[0]) { 
        delete list[0];
        list[0] = NULL;
    }
    if (list[1]) {
        delete list[1];
        list[1] = NULL;
    }
}
