//
//  GraphNode.cpp
//  PathFinder
//
//  Created by 林光海 on 14-11-27.
//
//

#include "GraphNode.h"

GraphNode* GraphNode::create(int index)
{
    GraphNode* node = new GraphNode();
    if(node && node->init(index)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return NULL;
}

bool GraphNode::init(int index)
{
    if(Node::init()) {
        _index = index;
        return true;
    }
    
    return false;
}

GraphNode::GraphNode():_index(invalid_node_index)
{

}

GraphNode::~GraphNode()
{

}

int GraphNode::Index() const
{
    return _index;
}

void GraphNode::SetIndex(int index)
{
    _index = index;
}

