//
//  SparseGraph.h
//  PathFinder
//
//  Created by 林光海 on 14-11-27.
//
//

#ifndef PathFinder_SparseGraph_h
#define PathFinder_SparseGraph_h

#include "cocos2d.h"
#include <string>
#include <iostream>
#include "NodeTypeEnumerations.h"
using namespace cocos2d;

template <class node_type, class edge_type>
class SparseGraph : public Node
{
public:
	typedef edge_type EdgeType;
	typedef node_type NodeType;
	typedef Vector<node_type> NodeVector;
	typedef Vector<edge_type> EdgeList;
	typedef Vector<EdgeList> EdgeListVector;
private:
	// the nodes that comprise this graph
	NodeVector _nodes;
	// a vector of adjacency edge lists.
	EdgeListVector _edges;
	// is this a directed graph
	bool _digraph;
	// the index of the next node to be added
	int _nextNodeIndex;
	// returns true if an edge is not already present in the graph
	// Used when adding edges to make sure no duplicates are created
	bool UniqueEdge(int from, int to) const;
	// iterates through all the edges in the graph and removes any
	// that point to an invalidated node
	void CullInvalidEdges();
public:
	static SparseGraph* create(bool digraph);

	virtual bool init(bool digraph);

	SparseGraph();

	virtual ~SparseGraph();

	const NodeType& GetNode(int index) const;

	NodeType& GetNode(int index);

	const EdgeType& GetEdge(int from, int to) const;

	EdgeTyp& GetEdge(int from, int to);

	// retrieves the next free node index
	int GetNextFreeNodeIndex() const
	{
		return _nextNodeIndex;
	}

	// adds a node to the graph and returns its index
	int AddNode(node_type node);

	// removes a node by setting its index to invalid_node_index
	void RemoveNode(int node);

	void AddEdge(EdgeType edge);

	void RemoveEdge(int from, int to);

	void SetEdgeCost(int from, int to, double cost);

	int NumNodes() const
	{
		return _nodes.size();
	}

	int NumActiveNodes() const
	{
		int count = 0;
		for(unsigned int n = 0; n < _nodes.size(); ++n) {
			if(_nodes[n].Index() != invalid_node_index) {
				++count;
			}
		}
		return count;
	}

	int NumEdges() const
	{
		int tot = 0;

		for(EdgeListVector::const_iterator curEdge = _edges.begin(); curEdge != _edges.end(); ++curEdge) {
			tot += curEdge->size();
		}

		return tot;
	}

	bool isDigraph() const
	{
		return _digraph;
	}

	bool isEmpty() const
	{
		return _nodes.empty();
	}

	// returns true if a node with the given index is present in the graph
	bool isNodePresent(int nd) const;

	// returns true if an edge connecting the nodes to and from
	// is present in the graph
	bool isEdgePresent(int from, int to) const;

	bool Load(const char* FileName);

	// clears the graph ready for a new node insertions
	void Clear() { _nextNodeIndex = 0; _nodes.clear(); _edges.clear(); }

	void RemoveEdges()
	{
		for(EdgeListVector::iterator it = _edges.begin(); it != _edges.end(); ++it) {
			it->clear();
		}
	}

	// non const class used to iterate through all the edges
	// connected to a specific node
	class EdgeIterator
	{
	public:
		EdgeIterator(SparseGraph<node_type, edge_type>& graph, int node):G(graph), NodeIndex(node)
		{
			curEdge = G._edges[NodeIndex].begin();
		}

		EdgeType* begin()
		{
			curEdge = G._edges[NodeIndex].begin();
			return &(*curEdge);
		}

		EdgeType* next()
		{
			++curEdge;
			if(end())
				return NULL;
			return &(*curEdge);
		}

		bool end()
		{
			return (curEdge == G._edges[NodeIndex].end());
		}

	private:
		typename EdgeList::iterator curEdge;

		SparseGraph<node_type, edge_type>& G;

		const int NodeIndex;
	};

	friend class EdgeIterator;

	class ConstEdgeIterator
	{
	public:
		ConstEdgeIterator(const SparseGraph<node_type, edge_type>& graph, int node):G(graph), NodeIndex(node)
		{
			curEdge = G._edges[NodeIndex].begin();
		}

		const EdgeType* begin()
		{
			curEdge = G._edges[NodeIndex].begin;

			if(end())
				return 0;
			return &(*curEdge);
		}

		const EdgeType* next()
		{
			++curEdge;
			if(end())
			{
				return NULL;
			}else {
				return &(*curEdge);
			}
		}

		bool end()
		{
			return (curEdge == G._edges[NodeIndex].end());
		}
	private:
		typename EdgeList::const_iterator curEdge;

		const SparseGraph<node_type, edge_type>& G;

		const int NodeIndex;
	};

	friend class ConstEdgeIterator;

	class NodeIterator
	{
	private:
		typename NodeVector::iterator curNode;
		
		SparseGraph<node_type, edge_type>& G;

		void GetNextValidNode(typename NodeVector::iterator& it)
		{
			if(curNode == G._nodes.end() || it->Index() != invalid_node_index)
				return;

			while((it->Index() == invalid_node_index)) {
				++it;
				if(curNode == G._nodes.end())
					break;
			}
		}
	public:
		NodeIterator(SparseGraph<node_type, edge_type>& graph):G(graph)
		{
			curNode = G._nodes.begin();
		}

		node_type* begin()
		{
			curNode = G._nodes.begin();
			GetNextValidNode(curNode);
			return &(*curNode);
		}

		node_type* next()
		{
			++curNode;
			if(end())
				return NULL;
			GetNextValidNode(curNode);
			return &(*curNode);
		}

		bool end()
		{
			return (curNode == G._nodes.end());
		}
	};

	friend class NodeIterator;

	class ConstNodeIterator
	{
	private:
		typename NodeVector::const_iterator curNode;

		const SparseGraph<node_type, edge_type>& G;

			void GetNextValidNode(typename NodeVector::iterator& it)
		{
			if(curNode == G._nodes.end() || it->Index() != invalid_node_index)
				return;

			while((it->Index() == invalid_node_index)) {
				++it;
				if(curNode == G._nodes.end())
					break;
			}
		}

	public:
		node_type* begin()
		{
			curNode = G._nodes.begin();
			GetNextValidNode(curNode);
			return &(*curNode);
		}

		node_type* next()
		{
			++curNode;
			if(end())
				return NULL;
			GetNextValidNode(curNode);
			return &(*curNode);
		}

		bool end()
		{
			return (curNode == G._nodes.end());
		}
	};

	friend class ConstNodeIterator;
};

//--------------------------- isNodePresent --------------------------------
//
//  returns true if a node with the given index is present in the graph
//--------------------------------------------------------------------------
template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::isNodePresent(int index) const
{
	if((index >= (int)_nodes.size() || (_nodes[index].Index() == invalid_node_index))) {
		return false;
	}else {
		return true;
	}
}

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::isEdgePresent(int from, int to) const
{
	if(isNodePresent(from) && isNodePresent(to)) {
		for(EdgeList::const_iterator curEdge = _edges[from].begin(); curEdge != _edges[from].end(); ++curEdge) {
			if(curEdge->To() == to)
				return true;
		}

		return false;
	}else {
		return false;
	}
}

//------------------------------ GetNode -------------------------------------
//
//  const and non const methods for obtaining a reference to a specific node
//----------------------------------------------------------------------------
template <class node_type, class edge_type>
const node_type& SparseGraph<node_type, edge_type>::GetNode(int index) const
{
	CC_ASSERT((index < (int)_nodes.size()) && (index >= 0) && "<SparseGraph::GetNode>:invalid index");
	return _nodes[index];
}

 //non const version
template <class node_type, class edge_type>
node_type& SparseGraph<node_type, edge_type>::GetNode(int index)
{
	CC_ASSERT((index < (int)_nodes.size()) && (index >= 0) && "<SparseGraph::GetNode>:invalid index");
	return _nodes[index];
}

//------------------------------ GetEdge -------------------------------------
//
//  const and non const methods for obtaining a reference to a specific edge
//----------------------------------------------------------------------------
template <class node_type, class edge_type>
const edge_type& SparseGraph<node_type, edge_type>::GetEdge(int from, int to) const
{
	CC_ASSERT( (from < _nodes.size()) && (from >= 0) && _nodes[from].Index() != invalid_node_index && "<SparseGraph::GetEdge>:invalid from index" );
	CC_ASSERT( (to < _nodes.size()) && (to >= 0) && _nodes[to].Index() != invalid_node_index && "<SparseGraph::GetEdge>:invalid to index" );
	for(EdgeList::const_iterator curEdge = _edges[from].begin(); curEdge != _edges[from].end(); ++curEdge) {
		if(curEdge->To() == to)
			return *curEdge;
	}

	CC_ASSERT(0 && "<SparseGraph::GetEdge>: edge does not exist");
}

//non const version
template <class node_type, class edge_type>
edge_type& SparseGraph<node_type, edge_type>::GetEdge(int from, int to)
{
	CC_ASSERT( (from < _nodes.size()) && (from >= 0) && _nodes[from].Index() != invalid_node_index && "<SparseGraph::GetEdge>: invalid 'from' index" );
	CC_ASSERT( (to < _nodes.size()) &&
          (to >=0)              &&
          _nodes[to].Index() != invalid_node_index &&
          "<SparseGraph::GetEdge>: invalid 'to' index");
	for(EdgeList::const_iterator curEdge = _edges[from].begin(); curEdge != _edges[from].end(); ++curEdge) {
		if(curEdge->To() == to)
			return *curEdge;
	}

	CC_ASSERT(0 && "<SparseGraph::GetEdge>: edge does not exist");
}

template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::AddEdge(EdgeType edge)
{
	CC_ASSERT( (edge.From() < _nextNodeIndex) && (edge.To() < _nextNodeIndex) && "<SparseGraph::AddEdge>: invalid node index");
	if( (_nodes[edge.To()].Index() != invalid_node_index) && (_nodes[edge.From().Index() != invalid_node_index]) ) {
		// add the edge, first making sure it is unique
		if(UniqueEdge(edge.From(), edge.To())) {
			_edges[edge.From()].push_back(edge);
		}
		
		//if the graph is undirected we must add another connection in the opposite
		//direction
		if(!_digraph) {
			if(UniqueEdge(edge.To(), edge.From())) {
				EdgeType NewEdge = edge;
				NewEdge.SetTo(edge.From());
				NewEdge.SetFrom(edge.To());

				_edges[edge.To()].push_back(NewEdge);
			}
		}

	}

}

//----------------------------- RemoveEdge ---------------------------------
template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::RemoveEdge(int from, int to)
{
	
}


#endif
