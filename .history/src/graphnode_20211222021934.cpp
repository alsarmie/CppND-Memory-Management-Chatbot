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
GraphNode::~GraphNode() {
}


void GraphNode::AddToken(std::string token) { _answers.emplace_back(token); }


void GraphNode::AddEdgeToParentNode(GraphEdge *edge) {
  _parentEdges.emplace_back(edge);
}

// R.32: Take a unique_ptr<widget> parameter to express that a function assumes
// ownership of a widget
void GraphNode::AddEdgeToChildNode(unique_ptr<GraphEdge> edge) {
  _childEdges.emplace_back(move(edge));
}

//! STUDENT CODE

void GraphNode::MoveChatbotHere(ChatBot chatbot) {
  _chatBot = move(chatbot);
  _chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode) {
  newNode->MoveChatbotHere(move(_chatBot));
  //_chatBot = nullptr; // invalidate pointer at source
}

//! EOF STUDENT CODE

/**
 * @brief Getter method ti
 * 
 * @param index int
 * @return GraphEdge* 
 */
GraphEdge *GraphNode::GetChildEdgeAtIndex(int index) {
  //! STUDENT CODE
  return (_childEdges[index]).get();
  //! EOF STUDENT CODE
}