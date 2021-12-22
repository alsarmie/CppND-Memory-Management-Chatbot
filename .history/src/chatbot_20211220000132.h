#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <string>
#include <wx/bitmap.h>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot {
private:
  // data handles (owned)
  wxBitmap *_image = NULL; // avatar image

  // data handles (not owned)
  GraphNode *_currentNode = nullptr;
  GraphNode *_rootNode = nullptr;
  ChatLogic *_chatLogic = nullptr;

  // proprietary functions
  int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
  // constructors / destructors
  ChatBot();                     // constructor WITHOUT memory allocation
  ChatBot(std::string filename); // constructor WITH memory allocation
  ~ChatBot();                    //Destructor
  Chat

  /// STUDENT CODE
  ////

  ////
  /// EOF STUDENT CODE

  // getters / setters
  void SetCurrentNode(GraphNode *node);
  void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
  void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
  ChatLogic *GetChatLogicHandle() const { return _chatLogic; }
  wxBitmap *GetImageHandle() const { return _image; }

  // communication
  void ReceiveMessageFromUser(std::string &message);
};

#endif /* CHATBOT_H_ */
