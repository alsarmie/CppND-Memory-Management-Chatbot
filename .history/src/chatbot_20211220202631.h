#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <string>
#include <wx/bitmap.h>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot {
private:
  // data handles (owned)
  wxBitmap *_image ; // avatar image

  // data handles (not owned)
  GraphNode *_currentNode ;
  GraphNode *_rootNode ;
  ChatLogic *_chatLogic ;

  // proprietary functions
  int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
  // constructors / destructors
  ChatBot();                     // constructor WITHOUT memory allocation
  ChatBot(std::string filename); // constructor WITH memory allocation
  //Rule of Five
  ~ChatBot();                    // Destructor

  /// STUDENT CODE
  ////

  ChatBot(const ChatBot &chatbot);  // Copy Constructor
  ChatBot &operator=( const ChatBot &chatbot); // Copy assignment operator

  ChatBot(ChatBot &&chatbot);                 // Move Constructor
  ChatBot &operator=(ChatBot &&chatbot) noexcept;      // Move assignment Operator
  friend void swap(ChatBot &A,ChatBot &B);
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
