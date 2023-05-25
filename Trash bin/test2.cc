#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

int main() {
    // Create an unordered_map
    std::unordered_map<std::string, std::vector<std::string>> my_dict;

    for(char ch = 'a'; ch <= 'z'; ++ch) {
        std::string key = std::string(1, ch);
        std::string str1 = key + "a";
        std::string str2 = key + "b";
        std::string str3 = key + "c";
        my_dict[key] = {str1, str2, str3};
    }

    // Later if you want to add more keys:
    //my_dict["aa"] = {"aaa", "aab", "aac"};
    //my_dict["cd"] = {"cda", "cdb", "cdc"};

    // Print the unordered_map
    for(const auto &item : my_dict) {
        std::cout << "Key: " << item.first << ", Values: ";
        for(const auto &value : item.second) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
