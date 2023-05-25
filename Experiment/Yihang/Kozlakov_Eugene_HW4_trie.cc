/*
Author: Eugene Kozlakov
Sources and References:
  -Advice from Prof. Dov Kruger.
  -My "Double Linked List" code. It should be called "Kozlakov_Eugene_DoubleLinkedList.cc" in a previous submission.
  -Quiz 4. There was some sample code that laid out how to add words to a trie. I reverse engineered it to get a better idea of how it works.
  If any concerns, please contact me.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class trie {

  private:
    class Node {
      public:
        bool isWord;
        hashtable --> nullptr
        Node* next[26];
        Node() : isWord(false) { // constructor
          //write loops
          for(int i=0; i<26; i++){ //ensuring first 26 elements in root are null
            next[i] = nullptr;
          }
        }

    };
    
  public:
    Node root; //start of trie //how to initialize...?

  public:
    trie() : root(){}
    ~trie(){
      delAll(&root); // destructor will just call existing function.
    }

    void addWord(string word){
      char c2;
      //cout << "adding new word" << endl;
      Node* p = &root; // starting from the root.
      for (int i = 0; i<word.length(); i++){ // iterating through every letter, from zero to length of word.
        int c = word[i] - 'a';  //setting char so that the 'c' variable gets assigned a value anywhere from 0-25: the 26 letters of the alphabet.
        if(p->next[c] == nullptr){
          //cout << "adding new node" << endl;
          p->next[c] = new Node(); // if the character in the next trie is null, set it to the following letter. //why error?
        }
        p = p->next[c];
      }
      p->isWord = true;
    }

    void delAll (Node* p){ //delete entire library when program closes.
      for(int i=0; i<26; i++){
        if(p->next[i] != nullptr){
          delAll(p->next[i]);
        }
      }
      delete p;
    }

    void checkWord(string word){
      Node* p = &root;
      for(int i = 0; i < word.length(); i++){
        char c = word[i] - 'a';
        if(p->next[c] != nullptr){
            p = p->next[c];
        } else {
          cout << "[" << word << "] has *NOT* been found in the dictionary." << endl;
          return;
        }
      }
      if (p->isWord == true){
        cout << "[" << word << "] has been found in the dictionary."<< endl;
      } else {
        cout << "[" << word << "] has *NOT* been found in the dictionary.2"<< endl;
      }

      return;
    }


};

int main(){
  // trie dict;
  // fstream f("dict.txt");
  // string word;
  // string s;

  // everything below is just me testing. will be removed.
 // while (f){ // while fstream 'f' is good and readable; // use this loop as the one that intakes and maps words to trie.
  
  //}
  // while(f){
  //   getline(f, word);
  //   dict.addWord(word);
  // }
  // f.close();
  // cout << "dictionary file 'dict.txt' has been mapped." << endl;

  // cout << "please insert the file name (with .txt ending) which you want to check in the dictionary." << endl;
  // cin >> s;
  // fstream g(s);

  // while (g){
  //   getline(g, word);
  //   dict.checkWord(word);    
  // }

  // g.close();


  trie dict;
  std::fstream f("dict.txt");
  std::string word;
  std::string s;

  while (std::getline(f, word)) {
      cout << word << endl;
      dict.addWord(word);
      break;
  }
  f.close();
  std::cout << "dictionary file 'dict.txt' has been mapped." << std::endl;

  dict.addWord("abcd");

  std::cout << "Please enter a word to check in the dictionary: " << std::endl;
  std::cin >> word;
  dict.checkWord(word);
  

  // cout << "Please enter a word to check in the dictionary: " << endl;
  // cin >> word;
  // dict.checkWord(word);    



  /*
  char c = word[4];
  int d = word[4] - 'a';
  cout << "word: " << word << endl;
  cout << "char: "<< c << endl;
  cout << "word length: " << word.length() << endl;
  cout << "integer format: " <<  d << endl;
  f.close();
  */
  return 0;
}