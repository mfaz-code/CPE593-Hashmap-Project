#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    // Assuming dictionary is an unordered_map<string, vector<string>>
    std::unordered_map<std::string, std::vector<std::string>> dictionary;
    // Initialize dictionary...


    

    std::unordered_map<int, char> letter_to_num;
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

        std::vector<std::string> keys;
        for (auto const& pair : dictionary) {
            keys.push_back(pair.first);
        }

        for (int i = 0; i < keys.size(); ++i) {
            std::string prefix = keys[i];
            std::vector<std::string> words_list = dictionary[prefix];
            if (words_list.size() > 64) {
                int len_prefix = prefix.length();
                for (int j = 0; j < 26; ++j) {
                    std::string new_key = prefix + letter_to_num[j];
                    dictionary[new_key] = {};
                    keys.push_back(new_key);
                }
                for (auto const& word : words_list) {
                    dictionary[word.substr(0, len_prefix+1)].push_back(word);
                }
                dictionary.erase(prefix);
            }
        }
    }

    return 0;
}
