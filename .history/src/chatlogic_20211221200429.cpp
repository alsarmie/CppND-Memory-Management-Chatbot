#include "chatlogic.h"
#include "chatbot.h"
#include "graphedge.h"
#include "graphnode.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <tuple>
#include <utility>
#include <vector>

using std::move;

/**
 * @brief Construct a new Chat Logic:: Chat Logic object
 *
 */
ChatLogic::ChatLogic()
    : _currentNode(nullptr), _chatBot(nullptr), _panelDialog(nullptr) {
  //! STUDENT CODE

  // create instance of chatbot
  //_chatBot = new ChatBot("../images/chatbot_new.png");

  // add pointer to chatlogic so that chatbot answers can be passed on to the
  // GUI
  //_chatBot->SetChatLogicHandle(this);

  //! EOF STUDENT CODE
}

/**
 * @brief Destroy the Chat Logic:: Chat Logic object
 *
 */
ChatLogic::~ChatLogic() {
  //! STUDENT CODE
  // delete chatbot instance
  //delete _chatBot;
  //_chatBot = nullptr;
  //! EOF STUDENT CODE
}

/**
 * @brief
 *
 * @tparam T
 * @param tokenID
 * @param tokens
 * @param element
 */
template <typename T>
void ChatLogic::AddAllTokensToElement(std::string tokenID, tokenlist &tokens,
                                      T &element) {
  // find all occurences for current node
  auto token = tokens.begin();
  while (true) {
    token = std::find_if(
        token, tokens.end(),
        [&tokenID](const std::pair<std::string, std::string> &pair) {
          return pair.first == tokenID;
          ;
        });
    if (token != tokens.end()) {
      element.AddToken(token->second); // add new keyword to edge
      token++;                         // increment iterator to next element
    } else {
      break; // quit infinite while-loop
    }
  }
}

void ChatLogic::LoadAnswerGraphFromFile(std::string filename) {
  // load file with answer graph elements
  std::ifstream file(filename);

  // check for file availability and process it line by line
  if (file) {
    // loop over all lines in the file
    std::string lineStr;
    while (getline(file, lineStr)) {
      // extract all tokens from current line
      tokenlist tokens;
      while (lineStr.size() > 0) {
        // extract next token
        int posTokenFront = lineStr.find("<");
        int posTokenBack = lineStr.find(">");
        if (posTokenFront < 0 || posTokenBack < 0)
          break; // quit loop if no complete token has been found
        std::string tokenStr =
            lineStr.substr(posTokenFront + 1, posTokenBack - 1);

        // extract token type and info
        int posTokenInfo = tokenStr.find(":");
        if (posTokenInfo != std::string::npos) {
          std::string tokenType = tokenStr.substr(0, posTokenInfo);
          std::string tokenInfo =
              tokenStr.substr(posTokenInfo + 1, tokenStr.size() - 1);

          // add token to vector
          tokens.push_back(std::make_pair(tokenType, tokenInfo));
        }

        // remove token from current line
        lineStr = lineStr.substr(posTokenBack + 1, lineStr.size());
      }

      // process tokens for current line
      auto type =
          std::find_if(tokens.begin(), tokens.end(),
                       [](const std::pair<std::string, std::string> &pair) {
                         return pair.first == "TYPE";
                       });
      if (type != tokens.end()) {
        // check for id
        auto idToken =
            std::find_if(tokens.begin(), tokens.end(),
                         [](const std::pair<std::string, std::string> &pair) {
                           return pair.first == "ID";
                         });
        if (idToken != tokens.end()) {
          // extract id from token
          int id = std::stoi(idToken->second);

          // node-based processing
          if (type->second == "NODE") {
            //! STUDENT CODE

            // check if node with this ID exists already
            auto newNode =
                std::find_if(_nodes.begin(), _nodes.end(),
                             [&id](unique_ptr<GraphNode> const &node) {
                               return node->GetID() == id;
                             });

            // create new element if ID does not yet exist
            if (newNode == _nodes.end()) {
              _nodes.emplace_back(make_unique<GraphNode>(id));
              newNode = _nodes.end() - 1; // get iterator to last element

              // add all answers to current node
              AddAllTokensToElement("ANSWER", tokens, **newNode);
            }

            //! EOF STUDENT CODE
          }

          // edge-based processing
          if (type->second == "EDGE") {
            //! STUDENT CODE

            // find tokens for incoming (parent) and outgoing (child) node
            auto parentToken = std::find_if(
                tokens.begin(), tokens.end(),
                [](const std::pair<std::string, std::string> &pair) {
                  return pair.first == "PARENT";
                });
            auto childToken = std::find_if(
                tokens.begin(), tokens.end(),
                [](const std::pair<std::string, std::string> &pair) {
                  return pair.first == "CHILD";
                });

            if (parentToken != tokens.end() && childToken != tokens.end()) {
              // get iterator on incoming and outgoing node via ID search
              auto parentNode = std::find_if(
                  _nodes.begin(), _nodes.end(),
                  [&parentToken](const unique_ptr<GraphNode> &node) {
                    return node->GetID() == std::stoi(parentToken->second);
                  });
              auto childNode = std::find_if(
                  _nodes.begin(), _nodes.end(),
                  [&childToken](const unique_ptr<GraphNode> &node) {
                    return node->GetID() == std::stoi(childToken->second);
                  });

              // Create new edge
              // Dereference iterator to gain access to the smart pointer.
              unique_ptr<GraphEdge> edge = make_unique<GraphEdge>(id);
              edge->SetChildNode(
                  (*childNode).get()); // uses handle, no ownership transfer.
              edge->SetParentNode(
                  (*parentNode).get()); // uses handle, no ownership transfer.
              _edges.emplace_back(edge.get());

              // find all keywords for current node
              AddAllTokensToElement("KEYWORD", tokens, *(edge.get()));

              // store reference in child node and parent node

              (*childNode)->AddEdgeToParentNode(edge.get());
              (*parentNode)->AddEdgeToChildNode(move(edge));
            }

            //! EOF STUDENT CODE
          }
        } else {
          std::cout << "Error: ID missing. Line is ignored!" << std::endl;
        }
      }
    } // eof loop over all lines in the file

    file.close();

  } // eof check for file availability
  else {
    std::cout << "File could not be opened!" << std::endl;
    return;
  }

  //! STUDENT CODE

  // identify root node
  GraphNode *rootNode = nullptr;
  for (auto &&it : _nodes) {
    // search for nodes which have no incoming edges
    if (it->GetNumberOfParents() == 0) {

      if (rootNode == nullptr) {
        rootNode = it.get(); // assign current node to root
      } else {
        std::cout << "ERROR : Multiple root nodes detected" << std::endl;
      }
    }
  }

  // add chatbot to graph root node
  ChatBot chatBot("../images/chatbot_new.png");
  chatbot.Se
  chatBot.SetRootNode(rootNode);
  rootNode->MoveChatbotHere(move(chatBot));

  //! EOF STUDENT CODE
}

void ChatLogic::SetPanelDialogHandle(ChatBotPanelDialog *panelDialog) {
  _panelDialog = panelDialog;
}

void ChatLogic::SetChatbotHandle(ChatBot *chatbot) { _chatBot = chatbot; }

void ChatLogic::SendMessageToChatbot(std::string message) {
  _chatBot->ReceiveMessageFromUser(message);
}

void ChatLogic::SendMessageToUser(std::string message) {
  _panelDialog->PrintChatbotResponse(message);
}

wxBitmap *ChatLogic::GetImageFromChatbot() {
  return _chatBot->GetImageHandle();
}