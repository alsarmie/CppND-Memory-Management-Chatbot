#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include "chatbot.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>
using std::make_unique;
using std::move;
using std::unique_ptr;
// forward declarations
class GraphEdge;

class GraphNode {
private:
  //! STUDENT CODE

  // data handles (owned)
  std::vector<unique_ptr<GraphEdge>> _childEdges; // edges to subsequent nodes

  // data handles (not owned)
  std::vector<GraphEdge *> _parentEdges; // edges to preceding nodes
  ChatBot _chatBot;
  //!Alternative
  // Change from ChatBot _chatBot as it makes a ChatBot constructor call
  // for each node created. .
  //unique_ptr<ChatBot> _chatBot;

  //! EOF STUDENT CODE

  // proprietary members
  int _id;
  std::vector<std::string> _answers;

public:
  // constructor / destructor
  GraphNode(int id);
  ~GraphNode();

  // getter / setter
  int GetID() { return _id; }
  int GetNumberOfChildEdges() { return _childEdges.size(); }
  GraphEdge *GetChildEdgeAtIndex(int index);
  std::vector<std::string> GetAnswers() { return _answers; }
  int GetNumberOfParents() { return _parentEdges.size(); }

  // proprietary functions
  void AddToken(std::string token); // add answers to list
  void AddEdgeToParentNode(GraphEdge *edge);
  void AddEdgeToChildNode(
      unique_ptr<GraphEdge> edge); // Take ownership of GraphEdge object

  //! STUDENT CODE

  void MoveChatbotHere(ChatBot chatbot);

  //! EOF STUDENT CODE

  void MoveChatbotToNewNode(GraphNode *newNode);
};

#endif /* GRAPHNODE_H_ */