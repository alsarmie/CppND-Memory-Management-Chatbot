#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

#include "chatbot.h"
#include "chatlogic.h"
#include "graphedge.h"
#include "graphnode.h"
#include <utility>
/**
 * @brief Construct a new Chat Bot:: Chat Bot object  WITHOUT memory allocation
 * (default)
 *
 */
ChatBot::ChatBot()
    : _image(nullptr), _chatLogic(nullptr), _rootNode(nullptr),
      _currentNode(nullptr) {
  // invalidate data handles
  std::cout << "ChatBot Constructor (No Memory allocation)" << std::endl;
}

/**
 * @brief Construct a new Chat Bot:: Chat Bot object WITH memory allocation
 * (_image member)
 *
 * @param filename Used by wxBitmap, avatar image location path.
 */
ChatBot::ChatBot(std::string filename)
    : _chatLogic(nullptr), _rootNode(nullptr), _currentNode(nullptr) {
  std::cout << "ChatBot Constructor (With Memory allocation)" << std::endl;

  // load avatar image into heap memory
  _image = new wxBitmap(filename, wxBITMAP_TYPE_PNG);
}
/**
 * @brief Destroy the Chat Bot:: Chat Bot object
 *
 */
ChatBot::~ChatBot() {
  std::cout << "ChatBot Destructor" << std::endl;
  // deallocate heap memory
  if (_image != NULL) // Attention: wxWidgets used NULL and not nullptr
  {
    delete _image;
    _image = NULL;
  }
  // TODO: Check if there is a possibility to use the non-owned handles.
  // If Chatbot destructor gets called, it is still possible to call
  // GetChatLogicHandle/GetImageHandle afterwards (unless the chatbot pointer is
  // set to nullptr right afterwards.). Hence, setting the non-owned data
  // handles to nullptr.
  _currentNode = nullptr;
  _rootNode = nullptr;
  _chatLogic = nullptr;
}

/// STUDENT CODE
////

/**
 * @brief Copy Construct a new Chat Bot:: Chat Bot object (deep copy)
 *
 * @param chatbot
 */
ChatBot::ChatBot(const ChatBot &chatbot)
    : _currentNode(chatbot._currentNode), _rootNode(chatbot._rootNode),
      _chatLogic(chatbot._chatLogic) {
  std::cout << "ChatBot Copy C~tor" _image =
      new wxBitmap("../images/chatbot_new.png", wxBITMAP_TYPE_PNG);
  *_image = *chatbot._image;
}

/**
 * @brief Copy Assignment operator overload Chat Bot:: Chat Bot object
 *
 * @param chatbot
 * @return ChatBot&
 */
ChatBot &ChatBot::operator=(const ChatBot &chatbot) {
  std::cout << "ChatBot Copy Assignment Operator" << std::endl;
  //! C.62: Make copy assignment safe for self-assignment ():
  //! Enforcement (Simple) Assignment operators should not contain the pattern
  //! if (this == &a) return *this;
  //! Copy-and-swap idiom is used here

  // if (this == &chatbot)
  //   return *this;
  delete _image;
  _image = new wxBitmap("../images/chatbot_new.png", wxBITMAP_TYPE_PNG);
  *_image = *chatbot._image;
  _currentNode = chatbot._currentNode;
  _rootNode = chatbot._currentNode;
  _chatLogic = chatbot._chatLogic;
  return *this;
}

friend void swap(ChatBot &A, ChatBot &B) { 
  using std::swap;//To enable ADL
//Swap object's members
  swap(A._image,B._image);
  swap(A._currentNode,B.currentNode);
  swap(A._rootNode,B._rootNode);
  swap(A._chatLogic,B._chatLogic);
}
////
/// EOF STUDENT CODE

void ChatBot::ReceiveMessageFromUser(std::string &message) {
  // loop over all edges and keywords and compute Levenshtein distance to query
  typedef std::pair<GraphEdge *, int> EdgeDist;
  std::vector<EdgeDist> levDists; // format is <ptr,levDist>

  for (size_t i = 0; i < _currentNode->GetNumberOfChildEdges(); ++i) {
    GraphEdge *edge = _currentNode->GetChildEdgeAtIndex(i);
    for (auto keyword : edge->GetKeywords()) {
      EdgeDist ed{edge, ComputeLevenshteinDistance(keyword, message)};
      levDists.push_back(ed);
    }
  }

  // select best fitting edge to proceed along
  GraphNode *newNode;
  if (levDists.size() > 0) {
    // sort in ascending order of Levenshtein distance (best fit is at the top)
    std::sort(levDists.begin(), levDists.end(),
              [](const EdgeDist &a, const EdgeDist &b) {
                return a.second < b.second;
              });
    newNode = levDists.at(0).first->GetChildNode(); // after sorting the best
                                                    // edge is at first position
  } else {
    // go back to root node
    newNode = _rootNode;
  }

  // tell current node to move chatbot to new node
  _currentNode->MoveChatbotToNewNode(newNode);
}

void ChatBot::SetCurrentNode(GraphNode *node) {
  // update pointer to current node
  _currentNode = node;

  // select a random node answer (if several answers should exist)
  std::vector<std::string> answers = _currentNode->GetAnswers();
  std::mt19937 generator(int(std::time(0)));
  std::uniform_int_distribution<int> dis(0, answers.size() - 1);
  std::string answer = answers.at(dis(generator));

  // send selected node answer to user
  _chatLogic->SendMessageToUser(answer);
}

int ChatBot::ComputeLevenshteinDistance(std::string s1, std::string s2) {
  // convert both strings to upper-case before comparing
  std::transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
  std::transform(s2.begin(), s2.end(), s2.begin(), ::toupper);

  // compute Levenshtein distance measure between both strings
  const size_t m(s1.size());
  const size_t n(s2.size());

  if (m == 0)
    return n;
  if (n == 0)
    return m;

  size_t *costs = new size_t[n + 1];

  for (size_t k = 0; k <= n; k++)
    costs[k] = k;

  size_t i = 0;
  for (std::string::const_iterator it1 = s1.begin(); it1 != s1.end();
       ++it1, ++i) {
    costs[0] = i + 1;
    size_t corner = i;

    size_t j = 0;
    for (std::string::const_iterator it2 = s2.begin(); it2 != s2.end();
         ++it2, ++j) {
      size_t upper = costs[j + 1];
      if (*it1 == *it2) {
        costs[j + 1] = corner;
      } else {
        size_t t(upper < corner ? upper : corner);
        costs[j + 1] = (costs[j] < t ? costs[j] : t) + 1;
      }

      corner = upper;
    }
  }

  int result = costs[n];
  delete[] costs;

  return result;
}