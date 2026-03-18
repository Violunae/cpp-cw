#include <iostream>
#include <string>

std::string convertCase(const std::string &s, bool upperCase) {
    std::string str = "";
    for (char c : s) {
        if (upperCase) {
            if ((c >= 97) && (c <= 122)) {
                c -= 32;
            }
        }
        else if ((c >= 65) && (c <= 90)) {
            c += 32;
        }
        str += c;
    }
    return str;
}

bool isPalindrome(const std::string &s) {
    int len = s.length();
    for (int i = 0; i <= len / 2; i++) {
        if (s[i] != s[len-i-1]) {
            return false;
        }
    }
    return true;
}

std::string rand(size_t n) {
    std::string str = "";
    while (n--) {
        str += std::rand() % 26 + 97;
    }
    return str;
}

size_t longestWordLength(const std::string &s) {
    size_t max = 0, score = 0;
    for (char c : s) {
        if (c != ' ') {
            score++;
            if (max < score) {
                max = score;
            }
        }
        else {
            score = 0;
        }
    }
    return max;
}

void rot13(std::string &s) {
    const int rot = 13;
    size_t len = s.length();
    for (int i = 0; i < len; i++) {
        unsigned char c = s[i];
        if ((c >= 97) && (c <= 122)) {
            c += rot;
            if (c > 122) c -= 26;
        }
        else if ((c >= 65) && (c <= 90)) {
            c += rot;
            if (c > 90) c -= 26;
        }
        s[i] = c;
    }
}

size_t countOccurence(const std::string &s1, const std::string &s2) {
    size_t occurences = 0;
    size_t len1 = s1.length();
    size_t len2 = s2.length();
    for (int i = 0; i < len1 - len2 + 1; i++) {
        bool found = true;
        for (int j = 0; j < len2; j++) {
            if (s1[i+j] != s2[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            occurences++;
            //i += len2 - 1;
        }
    }
    return occurences;
}

int main(int argc, char* argv[]) {
    std::cout 
    << "\"MoLoToV\" in lower case is \"" 
    << convertCase("MoLoToV", true) 
    << "\" and in upper case is \"" 
    << convertCase("MoLoToV", false) 
    << "\"\n";

    std::cout
    << "\"many angels lived on\" "
    << (isPalindrome("many angels lived on") ? "is" : "isn\'t")
    << " a palindrome, \"no devil lived on\" "
    << (isPalindrome("no devil lived on") ? "is" : "isn\'t")
    << " a palindrome\n";

    std::cout
    << "random word with 23 letters: "
    << rand(23)
    << "\n";

    std::cout
    << "longest word in this sentence has this many letters: "
    << longestWordLength("longest word in this sentence has this many letters")
    << "\n";

    std::string message = "Lorem Ipsum";
    rot13(message);
    std::cout 
    << "\"Lorem Ipsum\" encrypted is "
    << message
    << "\n";

    std::cout
    << "word \"pop\" is repeated in \"popsicle popping stop popular mop poppop\" this many times: " 
    << countOccurence("popsicle popping stop popular mop popop" , "pop")
    << "\n";

    std::cout 
    << "\n";

    return 0;
}