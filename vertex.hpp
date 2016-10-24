#ifndef _vertex_hpp
#define _vertex_hpp

#include <vector>
#include <iostream>

#define VERT_NULL 1000000

class Vertex {
  public:
    size_t parent;
    size_t child[2];
    size_t idx;
    size_t val;
    std::vector<size_t> * list[2];
    Vertex();
    void setParent (size_t p);
    size_t getParent ();
    void setChild (size_t c);
    void swapChild (size_t orig_child, size_t new_child);
    void setValue (size_t v);
    size_t getValue ();
    void setIndex (size_t i);
    size_t getIndex ();
    void setList (std::vector<size_t> * l);
    void clearLists ();
};

#endif
