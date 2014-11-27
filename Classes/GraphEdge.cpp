//
//  GraphEdge.cpp
//  PathFinder
//
//  Created by 林光海 on 14-11-27.
//
//

#include "GraphEdge.h"

GraphEdge* GraphEdge::create(int from, int to, double cost)
{
    GraphEdge* edge = new GraphEdge();
    if(edge && edge->init(from, to, cost)) {
        edge->autorelease();
        return edge;
    }
    CC_SAFE_DELETE(edge);
    return NULL;
}

GraphEdge::GraphEdge()
:_cost(1.0f)
,_from(invalid_node_index)
,_to(invalid_node_index)
{

}

bool GraphEdge::init(int from, int to, double cost)
{
    if(Node::init()) {
        _from = from;
        _to = to;
        _cost = cost;
        return true;
    }
    
    return false;
}

GraphEdge::~GraphEdge()
{

}

int GraphEdge::From() const
{
    return _from;
}

void GraphEdge::SetFrom(int from)
{
    _from = from;
}

int GraphEdge::To() const
{
    return _to;
}

void GraphEdge::SetTo(int to)
{
    _to = to;
}

double GraphEdge::Cost() const
{
    return _cost;
}

void GraphEdge::SetCost(double cost)
{
    _cost = cost;
}

/*
 NavGraphEdge
 */
NavGraphEdge* NavGraphEdge::create(int from, int to, double cost, int flags, int idOfIntersectingEntity)
{
    NavGraphEdge* edge = new NavGraphEdge();
    if(edge && edge->init(from, to, cost, flags, idOfIntersectingEntity)) {
        edge->autorelease();
        return edge;
    }
    
    CC_SAFE_DELETE(edge);
    return NULL;
}

NavGraphEdge::NavGraphEdge():_flags(0), _idOfIntersecting(-1)
{

}

bool NavGraphEdge::init(int from, int to, double cost, int flags, int idOfIntersecting)
{
    if(GraphEdge::init(from, to, cost)) {
        _flags = flags;
        _idOfIntersecting = idOfIntersecting;
        return true;
    }
    
    return false;
}

NavGraphEdge::~NavGraphEdge()
{

}

int NavGraphEdge::Flags() const
{
    return _flags;
}

void NavGraphEdge::SetFlags(int flags)
{
    _flags = flags;
}

int NavGraphEdge::IDOfIntersecting() const
{
    return _idOfIntersecting;
}

void NavGraphEdge::SetIdOfIntersecting(int id)
{
    _idOfIntersecting = id;
}












