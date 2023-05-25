#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

void breaker (const vector<string>& intake, unordered_map<string, vector<string>>& dictionary ){ //function that performs everything in main
  //unordered_map<string, vector<string>> dictionary;
  unordered_map<int, char> letter_to_num;

  dictionary[""] = intake;

  while (true) {
      bool all_less_than_64 = true;
      for (auto const& pair : dictionary) {
          if (pair.second.size() > 64) {
              all_less_than_64 = false;
              break;
          }
      }
      if (all_less_than_64) {
          break;
      }

      vector<std::string> keys_to_delete;
      vector<std::string> keys_to_add_back;
      unordered_map<string, vector<string>> new_entries;

      vector<string> keys;
      for (auto const& pair : dictionary) {
          keys.push_back(pair.first);
      }

      for (const auto &prefix : keys) {
          vector<string> words_list = dictionary[prefix];
          if (words_list.size() > 64) {
              int len_prefix = prefix.length();
              for (int i = 0; i < 26; ++i) {
                  string new_key = prefix + letter_to_num[i];
                  new_entries[new_key] = {};
              }
              for (const auto &word : words_list) {
                  if (word.length() == len_prefix) {
                      keys_to_add_back.push_back(prefix);
                      continue;
                  }
                  new_entries[word.substr(0, len_prefix+1)].push_back(word);
              }
              for (int i = 0; i < 26; ++i) {
                  string key_to_check = prefix + letter_to_num[i];
                  if (new_entries[key_to_check].empty()) {
                      new_entries.erase(key_to_check);
                  }
              }
              keys_to_delete.push_back(prefix);
          }
      }

      // Delete old keys and merge new entries into dictionary
      for (const auto &key : keys_to_delete) {
          dictionary.erase(key);
      }

      for (const auto &key : keys_to_add_back) {
          dictionary[key] = {key};
      }

      // Merge new_entries into dictionary
      for (const auto &pair : new_entries) {
          dictionary[pair.first] = pair.second;
      }
  }

  //return dictionary;
}


int main() {
    // Assuming dictionary is an unordered_map<string, vector<string>>
    unordered_map<string, vector<string>> dictionary;
    vector<string> intake;
   // unordered_map<int, char> letter_to_num;
    string word;
    fstream f("dict.txt");

    while (f){
      getline(f, word);
      intake.push_back(word);
    }

    
    breaker(intake, dictionary); // breaker will break down the intake into giant hash table with prefixes as keys and suffix list as values.

    /*
    dictionary[""] = intake;

    for(int i = 0; i < 26; ++i) {
        letter_to_num[i] = 'a' + i;
    }

    while (true) {
        bool all_less_than_64 = true;
        for (auto const& pair : dictionary) {
            if (pair.second.size() > 64) {
                all_less_than_64 = false;
                break;
            }
        }
        if (all_less_than_64) {
            break;
        }

        vector<std::string> keys_to_delete;
        vector<std::string> keys_to_add_back;
        unordered_map<string, vector<string>> new_entries;

        vector<string> keys;
        for (auto const& pair : dictionary) {
            keys.push_back(pair.first);
        }

        for (const auto &prefix : keys) {
            vector<string> words_list = dictionary[prefix];
            if (words_list.size() > 64) {
                int len_prefix = prefix.length();
                for (int i = 0; i < 26; ++i) {
                    string new_key = prefix + letter_to_num[i];
                    new_entries[new_key] = {};
                }
                for (const auto &word : words_list) {
                    if (word.length() == len_prefix) {
                        keys_to_add_back.push_back(prefix);
                        continue;
                    }
                    new_entries[word.substr(0, len_prefix+1)].push_back(word);
                }
                for (int i = 0; i < 26; ++i) {
                    string key_to_check = prefix + letter_to_num[i];
                    if (new_entries[key_to_check].empty()) {
                        new_entries.erase(key_to_check);
                    }
                }
                keys_to_delete.push_back(prefix);
            }
        }

        // Delete old keys and merge new entries into dictionary
        for (const auto &key : keys_to_delete) {
            dictionary.erase(key);
        }

        for (const auto &key : keys_to_add_back) {
            dictionary[key] = {key};
        }

        // Merge new_entries into dictionary
        for (const auto &pair : new_entries) {
            dictionary[pair.first] = pair.second;
        }
    }
*/

    uint64_t cntr = 0;
    for(const auto &pair : dictionary){
      //cout << pair.first << endl;
      if(pair.first == ""){
        cout << "blank string exists!" << endl;
        dictionary.erase("");
        cout << "blank string erased" << endl;
      }
      //cout << pair.first;
      ++cntr;
    }
    //cout << endl;
    cout << "size of keys " << cntr << endl;

    vector<string> testCase = dictionary[""];
    //cout << "empty key val is " << testCase << endl;

    uint64_t cntr2 = 0;
    for(const auto &pair : dictionary){
      ++cntr2;
    }
    
    cout << "counter after delete of blank string " << cntr2 << endl;

    cout << dictionary.size() << endl;
    cout << "clearing dictionary" << endl;
    dictionary.clear();

    cout << dictionary.size();

    return 0;
}
