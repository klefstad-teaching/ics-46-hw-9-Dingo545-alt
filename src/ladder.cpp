#include "ladder.h"
#include <cctype>
#include <cstddef>

void error(string word1, string word2, string msg){
    cerr << "Error with words [" << word1 << "] and [" << word2 << "]: " << msg << endl;
}

// --------------------------------------------------------------------------
// Check if edit distance between two strings is within d. True if it is, False if it isnt.
// Chek if the two words are "neighbors" (edit distance 1)
// supports replacing one letter, inserting one letter, or deleating one letter
// --------------------------------------------------------------------------
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if (d != 1) return false; // assume that d is 1
    if (str1 == str2) return false; // same words are not adjacent

    int len1 = str1.size(), len2 = str2.size();

    if (abs(len1 - len2) > 1) return false;

    // if lengths are equal than substitution
    if (len1 == len2){
        int diffCount = 0;
        for (int i = 0; i < len1; i++){
            if(str1[i] != str2[i]) diffCount++;
            if (diffCount > 1) return false;
        }
        return diffCount == 1;
    } else{
        // if lengths differ by one, check for insert or delete
        const string &shorter = (len1 < len2) ? str1 : str2; // Identify shorter and longer strings
        const string &longer = (len1 < len2) ? str2 : str1;

        int i = 0, j = 0, diffCount = 0;

        while (i < shorter.size() && j < longer.size()) {
            if (shorter[i] == longer[j]){
                i++;
                j++;
            } else{
                diffCount++;
                j++; // skip on character in the longer string
                if (diffCount > 1) return false;
            }
        }
        // accoun for extra letter at the end, if any
        if (j < longer.size()) diffCount++;
        return diffCount == 1;    
    }
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    
}

void load_words(set<string> & word_list, const string& file_name){}

void print_word_ladder(const vector<string>& ladder){}

void verify_word_ladder(){}
