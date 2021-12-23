#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <string>
#include <wx/bitmap.h>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot {
private:
  // data handles (owned)
  wxBitmap *_image; // avatar image

  // data handles (not owned)
  GraphNode *_currentNode;
  GraphNode *_rootNode;
  ChatLogic *_chatLogic;

  int _minKeywordSize{0};
  // proprietary functions
  int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
  // constructors / destructors
  ChatBot();                     // constructor WITHOUT memory allocation
  ChatBot(std::string filename); // constructor WITH memory allocation
  // Rule of Five
  ~ChatBot(); // Destructor
  //! STUDENT CODE
  ChatBot(const ChatBot &chatbot); // Copy Constructor
  // ChatBot &operator=(ChatBot chatbot); // Copy assignment operator
  ChatBot(ChatBot &&chatbot) noexcept;            // Move Constructor
  ChatBot &operator=(ChatBot &&chatbot) noexcept; // Move assignment Operator

  /**
   * @brief Swap function that makes an unqualified swap with std::swap
   * associated.
   *
   * @param A type ChatBot
   * @param B type ChatBot
   */
  friend void swap(ChatBot &A, ChatBot &B) {
    using std::swap; // To enable ADL
    // Swap object's members
    swap(A._chatLogic, B._chatLogic);
    swap(A._rootNode, B._rootNode);
    swap(A._image, B._image);
    swap(A._currentNode, B._currentNode);
  }

  //! EOF STUDENT CODE
  // getters / setters
  void SetCurrentNode(GraphNode *node);
  void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
  void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
  ChatLogic *GetChatLogicHandle() const { return _chatLogic; }
  wxBitmap *GetImageHandle() const { return _image; }

  void SetMinKeywordSize(int minKeywordSize) { _minKeywordSize = minKeywordSize; }
  // communication
  void ReceiveMessageFromUser(std::string &message);
};

#endif /* CHATBOT_H_ */
