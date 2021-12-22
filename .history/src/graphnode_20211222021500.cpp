#include "graphnode.h"
#include "graphedge.h"
/***/
GraphNode::GraphNode(int id) : _id(id) {}

GraphNode::~GraphNode() {
  //! STUDENT CODE

  //! EOF STUDENT CODE
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

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index) {
  //! STUDENT CODE

  return (_childEdges[index]).get();

  //! EOF STUDENT CODE
}