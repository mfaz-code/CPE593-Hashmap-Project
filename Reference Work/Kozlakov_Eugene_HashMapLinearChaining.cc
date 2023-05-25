/*
author: Eugene Kozlakov, 3/4/2023 - 3/5/2023
resources/references:
  -Dr. Kruger's Lecture 05 Hashing slides.
  -Video: "Hash Table and Hash Functions": https://www.youtube.com/watch?v=KyUTuwz_b7Q
  -Stack overflow heap/stack array assignment: https://stackoverflow.com/questions/675817/how-do-i-create-an-array-in-c-which-is-on-the-heap-instead-of-the-stack
  -Switch statement refpage: https://en.cppreference.com/w/cpp/language/switch
  -Stackoverflow: "How big should my hashmap be?" : https://stackoverflow.com/questions/12348741/how-big-should-my-hashmap-be

Note(s):
  -Be advised that this hash table is not accounted to be dynamic. Since we were given a dictionary of a known size, I built my table and hash function surrounding that fact.
    -In my defense, I inquired about it in the CPE593 chat and no one answered.
  -Theoretically you can initialize this hashmap with a file containing any list of words up to size 2^18 items.
    -Possibly even more, if you don't mind instances of chaining.
  -This is one of the bulkier programs I wrote with a lot in it. My documentation may be sketchy -- so if you have any questions, don't hesitate to reach out to me on discord.


*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

class HashMapLinearChain{
  private:
    struct Node{
      bool occupied;
      string value; //the word we would be looking for.
      Node* next;
      uint32_t collisionCount;
    };

    uint32_t histogram[10]={0}; //histogram table -- will tally number of collision instances. i.e., histogram[0] = 10 means there are 10 bins that experienced 0 collisions.
    uint32_t capacity; //capacity. currently fixed, does not account for dynamic growth.
    uint32_t size; //size tracker
    Node *table; //making table on heap, to avoid blowing up stack

    uint32_t hash(string word){ //create a hash function based on product of ASCII code of char and position in word.
      uint32_t wordSum = 0; //creating running sum

      for (uint32_t i = 0; i<word.length(); i++){ //for loop to cycle through word
        wordSum += word[i] * pow(26,i); // running sum is ASCII value of letter in position i, multiplied by i+1 to avoid making first char zero. would this make a major difference? not sure.
        //added multiplier to do base 26 hashing for each word. not sure if this was a good idea...
      }
      
      return wordSum&(capacity-1); // return x mod 2^k; from slide 9 of Lecture 5; ensuring index is one that fits into table;
    }

    void delChain(Node* chainHead){ //deletes a chain sticking out of a particular index in table

      if(chainHead->next != nullptr){
        delChain(chainHead->next);
      }
      delete chainHead;
    }

  public:
    HashMapLinearChain() : capacity(pow(2,18)), size(0), table(new Node[capacity]), histogram(){ //pow(2,18) is = 262,144
      for (uint32_t i = 0; i< capacity; i++){
        table[i].next = nullptr; //assigning the next value for each node in table to be null
        table[i].occupied = false;
        table[i].value = "[empty]"; //this will serve as a default value for unfilled spots in the indices of the table
        table[i].collisionCount = 0; //will keep track of number of collisions per index.
      }
    }
    ~HashMapLinearChain() { //i'm not sure if this destructor actually deletes EVERYTHING-- im hoping it does.
      //create method of destroying chains first, THEN table.
      for (uint32_t i = 0; i<capacity; i++){
        if(table[i].next != nullptr){
          delChain(table[i].next);
        }
      }

      delete table;
    }

    void addWord(string word){
      uint32_t index = hash(word);

      //cout << word << " index is " << index << endl; //for debugging, disregard

      //if element is occupied in table, then chain a node to the element in array table[];
      if(table[index].occupied == true){
        table[index].collisionCount++; //increase collision count by one.
        Node* nextChain = new Node;
        nextChain->value = word;
        nextChain->next = table[index].next;
        table[index].next = nextChain;
        size++;
        return;
      }
      //otherwise, just fill out the element in the array.
      table[index].value = word;
      table[index].occupied = true;
      size ++;
      
    }

    bool find (string word){
      //cout << "looking for: " << word << endl;
      uint32_t index = hash(word);
      //cout << "hash of " << word << " is " << index << endl;
      //cout << "table output table[" << index <<"].value = " << table[index].value << endl;
      Node* p = table[index].next;
      int i = 1; //this counter is used to find the particular link a word is at in a chain

      if(table[index].value == word){
        //cout << word << " has been found at index " << index << endl;
        return true;
      } 

      if(table[index].value == "[empty]") {//check if index is loaded with default value. If it is, it cant be in a chain or anywhere else.
        return false;
      } else { //walking down the chain from an index
        while(p != nullptr){
          if (p->value == word){
            return true;
          }
          if (p->next == nullptr){ 
            return false;
            //function then breaks on its own anyway.
          }
            p = p->next;
            i++;
        }
        
      }
    }
    

    uint32_t getSize(){
      return size;
    }
    
    void printHistogram(){
      cout << "printing histogram stats" << endl;
      cout << "======================" << endl;
      for (int i = 0; i <10; i++){
        switch(i){
          case 9:
            cout << i << "+ Collisions, " << histogram[i] <<" Instances" <<  endl;
            break;
          default:
             cout << i << "  Collisions, " << histogram[i] <<" Instances" <<  endl;
        }     
      }
    }

     //generate a histogram
    void generateHistogram(){
      cout << "starting histogram stats" << endl;
      uint32_t delta;
      for(uint32_t i = 0; i<capacity; i++){ //checking every single bin
        delta = 9 - table[i].collisionCount;
        switch(delta){        
          case 1: // 8 collisions
            histogram[8]++;
            break;
          case 2: //7 collisions
            histogram[7]++;
            break;
          case 3:
            histogram[6]++;
            break;
          case 4:
            histogram[5]++;
            break;
          case 5:
            histogram[4]++;
            break;
          case 6:
            histogram[3]++;
            break;
          case 7:
            histogram[2]++;
            break;
          case 8:
            histogram[1]++;
            break;
          case 9:
            histogram[0]++;
            break; 
          default: //anything else is clearly 9 collisions or greater. this would be case 0
            histogram[9]++;
            break;
        }
        
      }
    }

    void printSpecificTableValue(uint32_t index){
      cout << "Value at table index " << index << ": " << table[index].value << endl;
    }

    
  };




int main(){
  HashMapLinearChain dict;
  string word, initFile, checkFile;
  bool found;

  cout << "Please input file name (with filetype ending) to initialize the the Hashmap" << endl;
  cin >> initFile;

  fstream f(initFile);

  //reading in file, adding to dictionary
  while(f){
    getline(f, word);
    dict.addWord(word);
  }
  f.close();
  cout << "dictionary input completed. dictionary file closed." << endl;

  cout << "# of table entries: " << dict.getSize() << endl;

  cout << "====="<< endl;
  dict.generateHistogram();
  dict.printHistogram();
  
  cout << "Please input file name (with .txt ending) to check against dictionary." << endl;
  cin >> checkFile;
  fstream g(checkFile);

  while(g){
    getline(g, word);
    found = dict.find(word);
    if(found){
      cout << "true: " << word << " was found in " << initFile << endl;
    }
    if(!found){
      cout << "false: " << word << " was not found in " << initFile << endl;
    }
  }

  g.close();


}