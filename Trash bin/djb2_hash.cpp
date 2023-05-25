#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

// The djb2 hash function
unsigned long hash_string(unsigned char *str) {
    unsigned long hash = 5381;
    int c; // when assgin char to int, it convert by UTF-8

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // equivalent to hash = hash * 33 + c
    }

    return hash;
}




int main() {// test
    const char *input_string = "paranormal";
    const char *prefix = "para";
    const char *suffix = "normal";
    //int prefixSize = strlen(prefix);
    //int suffixSize = strlen(suffix);
    const int fullSize =  strlen(prefix) + strlen(suffix);
    char full[fullSize]; //IGNORE THIS ERROR WILL COMPILE
    strcat(full, prefix);
    strcat(full, suffix);
    unsigned long hash_value, hash_value_full;
    
    
    hash_value = hash_string((unsigned char *)input_string);

    std::cout << "Hash value for \"" << input_string << "\" is: " << hash_value << std::endl;

    hash_value_full = hash_string((unsigned char *)full);

    std::cout << "Hash value for \"" << full << "\" is: " << hash_value_full << std::endl;

    return 0;
}


