#include <iostream>
#include <vector>
#include "edgelist.hpp"

void EdgeList::append_bits (boost::dynamic_bitset<> & packedEdges, const boost::dynamic_bitset<> & b)
{
    for (size_t i=0; i<b.size(); i++) {
        packedEdges.push_back(b[i]);
    }
}

boost::dynamic_bitset<> & EdgeList::packEdgeList(std::vector<std::size_t> & edges)
{
    boost::dynamic_bitset<> & packedEdges = *(new boost::dynamic_bitset<>);
    // First three taxa 0, 1, 2 and edges 0,1,2, are preset.
    std::size_t bit_width = 2; // Only need to specify values to a max of 2 - 2 bits required.
    std::size_t bit_repeat = 1;
    std::size_t rep_idx = 0;
    for (std::size_t i = 0; i < edges.size(); i++) {
        const boost::dynamic_bitset<> b(bit_width, edges[i]);
        append_bits(packedEdges, b);
        rep_idx++;
        if (rep_idx >= bit_repeat) {
            bit_width++;
            bit_repeat = 2*bit_repeat;
            rep_idx = 0;
        }
    }
    return packedEdges;
}

std::vector<std::size_t> & EdgeList::unpackEdgeList(boost::dynamic_bitset<> & packedEdges)
{
    std::size_t bit_width = 2;
    std::size_t bit_repeat = 1;
    std::size_t rep_idx = 0;
    std::size_t num_bits = packedEdges.size();
    std::vector<std::size_t> & unpackedEdges = *(new std::vector<std::size_t>);
    for (std::size_t bit_idx=0; bit_idx < num_bits; ) {
        boost::dynamic_bitset<> b(bit_width, 0ul);
        for (std::size_t i=0; i<bit_width; i++) {
            b[i] = packedEdges[bit_idx];
            bit_idx++;
        }
        std::size_t val = b.to_ulong();  // BUG: NEED TO CATCH POSSIBLE ULONG OVERFLOW ERROR HERE - see boost docs.

        /*
        From: http://www.boost.org/doc/libs/1_56_0/libs/dynamic_bitset/example/example3.cpp
        bool fits_in_ulong = true;
        unsigned long ul = 0;
        try {
            ul = x.to_ulong();
        } catch(std::overflow_error &) {
        */


        std::cout << "Got value " << val << std::endl;
        unpackedEdges.push_back(val);
        
        rep_idx++;
        if (rep_idx >= bit_repeat) {
            bit_width++;
            bit_repeat = 2*bit_repeat;
            rep_idx = 0;
        }
    }
    return unpackedEdges;
}

/*
SizeTVal::SizeTVal(std::vector<size_t> vecVal) : TVal(vecVal)
{
  numTrees = dblFact(n);
  size_t blocksize = numTrees;
  value = 0;
  for(size_t i=3, j=0; i<=2*n-5; i = i+2, ++j)
  {
    blocksize = blocksize/i;
    value = (*vecValue)[j] * blocksize;
  }
}

SizeTVal::SizeTVal(size_t val, size_t numTaxa) : TVal(numTaxa)
{
  numTrees = dblFact(n);
  size_t blocksize = numTrees;
  size_t currVal = val;
  for(size_t i=3, j=0; i<=2*n-5; i = i+2, ++j)
  {
    blocksize = blocksize/i;
    (*vecValue)[j] = currVal/blocksize;
    currVal = currVal%blocksize;
  }
}
*/

/*
SizeTVal::SizeTVal(size_t numTaxa) : TVal(numTaxa)
{
  // value = SizeTVal::getNull();
  // originalValue = SizeTVal::getNull();
  value = originalValue = 0;
  for( size_t i=0; i<numTaxa-3; ++i )
    (*vecValue)[i] = 0;
  numTrees = dblFact(n);
}

SizeTVal::SizeTVal(std::vector<size_t> vecVal) : TVal(vecVal)
{
  buildVal();
  originalValue = value;
  numTrees = dblFact(n);
}

SizeTVal::SizeTVal(size_t val, size_t numTaxa) : TVal(numTaxa)
{
  numTrees = dblFact(n);
  setValue(val);
}

SizeTVal::~SizeTVal()
{
}

void SizeTVal::buildVal()
{
  numTrees = dblFact(n);
  size_t blocksize = numTrees;
  value = 0;
  for(size_t i=3, j=0; i<=2*n-5; i = i+2, ++j)
  {
    blocksize = blocksize/i;
    value = value + getPos(j+3) * blocksize; // or: value = value + (*vecValue)[j] * blocksize;
  }
}

size_t SizeTVal::getNull()
{
  return INT_MAX;
}

size_t SizeTVal::getValue()
{
  return value;
}

void SizeTVal::setValue(size_t val)
{
  assert( val < numTrees );
  value = val;
  originalValue = val;
  
  // numTrees = dblFact(n);
  size_t blocksize = numTrees;
  size_t currVal = val;
  for(size_t i=3, j=0; i<=2*n-5; i = i+2, ++j)
  {
    blocksize = blocksize/i;
    (*vecValue)[j] = currVal/blocksize;
    currVal = currVal%blocksize;
  }
}
  

void SizeTVal::setPos(size_t taxIndex, size_t edgeNo)
{
  assert(taxIndex < n);
  size_t denom = dblFact(taxIndex+1);
  value += (numTrees/denom)*(edgeNo - getPos(taxIndex));
  (*vecValue)[taxIndex-3] = edgeNo; // or could call TVal::setPos(taxIndex, edgeNo);
}

size_t SizeTVal::dblFact(size_t numTaxa)
{
  size_t res;
  res = 1;
  size_t i;
  for(i = 2*numTaxa - 5; i > 1; i = i-2)
  {
    res = res * i;
  }
  return res;
}
*/



/*
int main() {

    std::cout << "Hello World!\n" << std::endl;
    std::vector<std::size_t> arr {1,2,3,4,5};
    boost::dynamic_bitset<> & packarray = array2packarray(arr);
    std::cout << "Got bitset " << packarray << std::endl;
    std::vector<std::size_t> & arr2 = packarray2array(packarray);
    return 0;
}

*/
