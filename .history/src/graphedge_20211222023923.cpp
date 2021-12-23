#include "graphedge.h"
#include "graphnode.h"

/**
 * @brief Construct a new Graph Edge:: Graph Edge object
 * 
 * @param id int
 */
GraphEdge::GraphEdge(int id) : _id(id) {}


/**
 * @brief 
 * 
 * @param childNode 
 */
void GraphEdge::SetChildNode(GraphNode *childNode) { _childNode = childNode; }

void GraphEdge::SetParentNode(GraphNode *parentNode) {
  _parentNode = parentNode;
}

void GraphEdge::AddToken(std::string token) { _keywords.push_back(token); }