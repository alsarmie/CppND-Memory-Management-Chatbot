#include "graphnode.h"
#include "graphedge.h"

/**
 * @brief Construct a new Graph Node:: Graph Node object
 *
 * @param id int
 */
GraphNode::GraphNode(int id) : _id(id) {}

/**
 * @brief Destroy the Graph Node:: Graph Node object
 *
 */
GraphNode::~GraphNode() {}

/**
 * @brief Adds a token into _answers vector.
 *
 * @param token std::string
 */
void GraphNode::AddToken(std::string token) { _answers.emplace_back(token); }

/**
 * @brief Adds edge to _parentEdges vector.
 *
 * @param edge GraphEdge *
 */
void GraphNode::AddEdgeToParentNode(GraphEdge *edge) {
  _parentEdges.emplace_back(edge);
}

/**
 * @brief Populates _childEdges vector with GraphEdge unique pointers. Move
 * semantics enabled. R.32: Take a unique_ptr<widget> parameter to express that
 * a function assumes ownership of a widget
 *
 * @param edge unique_ptr<GraphEdge>
 */
void GraphNode::AddEdgeToChildNode(unique_ptr<GraphEdge> edge) {
  _childEdges.emplace_back(move(edge));
}
//! STUDENT CODE

/**
 * @brief Method to move chatbot resource to caller's node. Move semantics
 * enabled.
 *
 * @param chatbot ChatBot
 */

void GraphNode::MoveChatbotHere(ChatBot chatbot) {
  _chatBot = move(chatbot);
  _chatBot.SetCurrentNode(this);
}
//!Alternative with smart pointer. Works, but move assignment operator is never called.
// void GraphNode::MoveChatbotHere(ChatBot chatbot) {
//   _chatBot = make_unique<ChatBot>(move(chatbot));
//   (*_chatBot).SetCurrentNode(this);
// }

/**
 * @brief Method to move chatbot resource to a new node. Calls MoveChatbotHere.
 * Move semantics enabled.
 *
 * @param newNode GraphNode *
 */
void GraphNode::MoveChatbotToNewNode(GraphNode *newNode) {
  newNode->MoveChatbotHere(move(*_chatBot));
}
//! EOF STUDENT CODE

/**
 * @brief Getter method to retrieve an specific Child edge.
 *
 * @param index int
 * @return GraphEdge*
 */
GraphEdge *GraphNode::GetChildEdgeAtIndex(int index) {
  //! STUDENT CODE
  return (_childEdges[index]).get();
  //! EOF STUDENT CODE
}