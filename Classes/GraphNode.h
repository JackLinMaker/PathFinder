//
//  GraphNode.h
//  PathFinder
//
//  Created by 林光海 on 14-11-27.
//
//

#ifndef __PathFinder__GraphNode__
#define __PathFinder__GraphNode__

#include "cocos2d.h"
#include "NodeTypeEnumerations.h"
using namespace cocos2d;

class GraphNode : public Node
{
public:
    static GraphNode* create(int index);
    
    virtual bool init(int index);
    
    GraphNode();
    
    virtual ~GraphNode();
    
    int Index() const;
    
    void SetIndex(int index);
    
protected:
    int _index;
};

template <class extra_info=void*>
class NavGraphNode : public GraphNode {
public:
    static NavGraphNode* create(int index, Vec2 pos)
    {
        NavGraphNode* node = new NavGraphNode();
        if(node && node->init(index, pos)) {
            node->autorelease();
            return node;
        }
        CC_SAFE_DELETE(node);
        return NULL;
    }
    
    virtual bool init(int index, Vec2 pos)
    {
        if(GraphNode::init(index)) {
            _position = pos;
            _extraInfo = extra_info();
            return true;
        }
        
        return false;
    }
    
    NavGraphNode():_position(Vec2(0, 0)), _extraInfo(extra_info())
    {
        
    }
    
    virtual ~NavGraphNode()
    {
    
    }
    
    Vec2 Pos() const
    {
        return _position;
    }
    
    void SetPos(Vec2 pos)
    {
        _position = pos;
    }
    
    extra_info ExtraInfo() const
    {
        return _extraInfo;
    }
    
    void SetExtraInfo(extra_info info)
    {
        _extraInfo = info;
    }
    
protected:
    Vec2 _position;
    
    extra_info _extraInfo;
};

#endif /* defined(__PathFinder__GraphNode__) */
