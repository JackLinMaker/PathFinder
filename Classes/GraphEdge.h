//
//  GraphEdge.h
//  PathFinder
//
//  Created by 林光海 on 14-11-27.
//
//

#ifndef __PathFinder__GraphEdge__
#define __PathFinder__GraphEdge__

#include "cocos2d.h"
#include "NodeTypeEnumerations.h"
using namespace cocos2d;

class GraphEdge : public Node
{
public:
    static GraphEdge* create(int from, int to, double cost);
    
    GraphEdge();
    
    virtual bool init(int from, int to, double cost);
    
    virtual ~GraphEdge();
    
    int From() const;
    
    void SetFrom(int from);
    
    int To() const;
    
    void SetTo(int to);
    
    double Cost() const;
    
    void SetCost(double cost);
    
    bool operator==(const GraphEdge& rhs)
    {
        return rhs._from == this->_from &&
               rhs._to == this->_to     &&
               rhs._cost == this->_cost;
    }
    
    bool operator!=(const GraphEdge& rhs)
    {
        return !(*this == rhs);
    }
    
protected:
    int _from;
    int _to;
    double _cost;
    
};

/*
 NavGraphEdge
 */

class NavGraphEdge : public GraphEdge
{
public:
    enum
    {
        normal              = 0,
        swim                = 1 << 0,
        crawl               = 1 << 1,
        creep               = 1 << 3,
        jump                = 1 << 3,
        fly                 = 1 << 4,
        grapple             = 1 << 5,
        goes_through_door   = 1 << 6,
    };
public:
    static NavGraphEdge* create(int from, int to, double cost, int flags, int idOfIntersectingEntity);
    
    NavGraphEdge();
    
    virtual bool init(int from, int to, double cost, int flags, int idOfIntersecting);
    
    virtual ~NavGraphEdge();
    
    int Flags() const;
    
    void SetFlags(int flags);
    
    int IDOfIntersecting() const;
    
    void SetIdOfIntersecting(int id);
protected:
    int _flags;
    
    int _idOfIntersecting;
};


#endif /* defined(__PathFinder__GraphEdge__) */
