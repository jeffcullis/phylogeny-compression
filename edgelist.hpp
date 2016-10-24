#include <boost/dynamic_bitset.hpp>

class EdgeList
{
    public:
        boost::dynamic_bitset<> & packEdgeList(std::vector<std::size_t> & edges);
        std::vector<std::size_t> & unpackEdgeList(boost::dynamic_bitset<> & packedEdgeList);
    
    private:
        void append_bits (boost::dynamic_bitset<> & packedEdges, const boost::dynamic_bitset<> & b);
};

