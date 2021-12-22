#include "graphedge.h"
#include "graphnode.h"

/**
 * @brief Construct a new Graph Edge:: Graph Edge object
 * 
 * @param id int
 */
GraphEdge::GraphEdge(int id) : _id(id) {}

/**
 * @brief Setter method for _childNode.
 * 
 * @param childNode GraphNode *
 */
void GraphEdge::SetChildNode(GraphNode *childNode) { _childNode = childNode; }

/**
 * @brief Setter method for _parentNode
 * 
 * @param parentNode GraphNode *
 */
void GraphEdge::SetParentNode(GraphNode *parentNode) {
  _parentNode = parentNode;
}

/**
 * @brief Add token to _keywords vector.
 * 
 * @param token std::string
 */
void GraphEdge::AddToken(std::string token) { _keywords.push_back(token); }