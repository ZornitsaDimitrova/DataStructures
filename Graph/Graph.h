#pragma once
#include <cassert>
#include <unordered_map>
#include <map>
#include <iostream>

template <class VertexType, class CostType>
class Graph
{
public:
	//begin
	void addVertex(const VertexType&);
	bool hasVertex(const VertexType&) const;
	//end
	void addEdge(const VertexType&, const VertexType&, const CostType&);
	bool hasEdge(const VertexType&, const VertexType&) const;
	CostType getCost(const VertexType&, const VertexType&) const;

	// the columns are map, because the rows are relatively small, but the maps are many
	// & - stops the copying
	// the first const - prohibits the reference from being changed 
	const std::map<VertexType, CostType>& neighbors(const VertexType&) const;

private:
	//the rows are unordered map
	//so as not to write the whole thing always
	using MainIterator = typename std::unordered_map<VertexType, std::map<VertexType, CostType>>::const_iterator;

public:
	class VertexIterator
	{
	public:

		VertexIterator(const MainIterator&);

		VertexIterator& operator++();
		VertexType operator*();
		bool operator != (const VertexIterator&) const;
	private:
		MainIterator main_it;
	};


	VertexIterator begin() const;
	VertexIterator end() const;

private:

	std::unordered_map<VertexType, std::map<VertexType, CostType>> graph;

};
//the first map gives the second one which is giving the price according to the second city
template <class VertexType, class CostType>
void Graph<VertexType, CostType>::addVertex(const VertexType &v)
{
	graph[v];//=....; // adding a vertex without neighbours
}
template <class VertexType, class CostType>
bool Graph<VertexType, CostType>::hasVertex(const VertexType &v) const
{
	return graph.count(v) > 0;
}
template <class VertexType, class CostType>
void Graph<VertexType, CostType>::addEdge(const VertexType &v1, const VertexType &v2, const CostType &c)
{
	assert(hasVertex(v1));
	assert(hasVertex(v2));

	graph[v1][v2] = c;
}
template <class VertexType, class CostType>
bool Graph<VertexType, CostType>::hasEdge(const VertexType &v1, const VertexType &v2) const
{

	//has vertex checks in the main map, count in the internal(embedded) map
	return hasVertex(v1) && hasVertex(v2) && graph.at(v1).count(v2) > 0;
}
template <class VertexType, class CostType>
CostType Graph<VertexType, CostType>::getCost(const VertexType &v1, const VertexType &v2) const
{
	//hasedge- there is an edge, the price
	assert(hasEdge(v1, v2));
	return graph.at(v1).at(v2);
}
// wherever it is constant we call at

template <class VertexType, class CostType>
const std::map<VertexType, CostType>& Graph<VertexType, CostType>::neighbors(const VertexType &v) const
{
	assert(hasVertex(v));
	return graph.at(v);
}

template <class VertexType, class CostType>
Graph<VertexType, CostType>::VertexIterator::VertexIterator(const typename Graph<VertexType, CostType>::MainIterator &_it) :main_it(_it)
{}

template <class VertexType, class CostType>
typename Graph<VertexType, CostType>::VertexIterator& Graph<VertexType, CostType>::VertexIterator::operator++()
{
	++main_it;
	return *this;
}

template <class VertexType, class CostType>
VertexType Graph<VertexType, CostType>::VertexIterator::operator*()
{
	// iterate the firsts of the map
	return main_it->first;
}

template <class VertexType, class CostType>
bool Graph<VertexType, CostType>::VertexIterator::operator != (const typename Graph<VertexType, CostType>::VertexIterator &other) const
{
	return main_it != other.main_it;
}

template <class VertexType, class CostType>
typename Graph<VertexType, CostType>::VertexIterator Graph<VertexType, CostType>::begin() const
{
	return typename Graph<VertexType, CostType>::VertexIterator(graph.begin());
}

template <class VertexType, class CostType>
typename Graph<VertexType, CostType>::VertexIterator Graph<VertexType, CostType>::end() const
{
	return typename Graph<VertexType, CostType>::VertexIterator(graph.end());
}
