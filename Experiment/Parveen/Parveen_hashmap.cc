#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

// The djb2 hash function
unsigned long hash_string(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

// Convert a string to a base 28 number using arithmetic encoding
unsigned long encode_string(std::string str) {
    unsigned long result = 0;

    for (char c : str) {
        if (c >= 'a' && c <= 'z') { // encode letter
            result = result * 28 + (c - 'a');
        } else if (c == ' ') { // skip spaces
            continue;
        } else if (c == '_') { // encode END1
            result = result * 28 + 26;
        } else if (c == '-') { // encode END2
            result = result * 28 + 27;
        } else {
            std::cerr << "Invalid character: " << c << std::endl;
            exit(1);
        }
    }

    return result;
}

int main() {

    const int k = 64;
    const std::string filename = "dictionary.txt";
    const std::string bigger_filename = "dictionary_bigger.txt";
    const std::vector<std::string> prefixes = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    
    std::ifstream input_file(filename);
    std::ifstream bigger_input_file(bigger_filename);

    std::unordered_map<unsigned long, std::string> hashmap;

    // Read dictionary file and build hashmap
    if (input_file.is_open()) {
        std::string line;
        while (std::getline(input_file, line)) {
            if (line.empty() || line[0] != 'a') { // skip words that don't start with 'a'
                continue;
            }
            unsigned long key = encode_string(line);
            hashmap[key] = line;
        }
        input_file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(1);
    }

    // Count number of elements starting with 'a'
    int count_a = 0;
    for (const auto& pair : hashmap) {
        if (pair.second[0] == 'a') {
            count_a++;
        }
    }
    std::cout << "Number of elements starting with 'a': " << count_a << std::endl;

    // Break down by prefix and build separate hashmaps
    for (std::string prefix : prefixes) {
        std::unordered_map<unsigned long, std::string> sub_hashmap;
        for (const auto& pair : hashmap) {
            if (pair.second.substr(0, 2) == prefix && sub_hashmap.size() < k) {
                sub_hashmap[pair.first] = pair.second;
            }
        }
        std::cout << "Prefix " << prefix << ": " << sub_hashmap.size() << " words" << std::endl;
    }

    // Break down into words starting with aa, ab, ac, etc.
    int k = 64;
    int num_words = 0;
    char prefix[3] = "aa";
    while (num_words >= k) {
        // Create a new hashmap for the current prefix
        unordered_map<unsigned long, int> hashmap;
        // Add words to the hashmap
        for (auto& p : word_count) {
            if (p.first.substr(0, 2) == prefix) {
                string encoded_string = encode_string(p.first);
                unsigned long hash_value = hash_string((unsigned char *)encoded_string.c_str());
                hashmap[hash_value] = p.second;
            }
        }
        // Count the number of words in the hashmap
        num_words = hashmap.size();
        // Move on to the next prefix
        prefix[1]++;
        if (prefix[1] > 'z') {
            prefix[0]++;
            prefix[1] = 'a';
        }
        if (prefix[0] > 'z') {
            break;
        }
    }

    // Print the number of elements starting with 'a'
    cout << "Number of elements starting with 'a': " << num_starting_with_a << endl;

    return 0;
}
  
