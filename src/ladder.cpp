#include "ladder.h"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm> 

void error(string word1, string word2, string msg){
    cerr << "Error with words [" << word1 << "] and [" << word2 << "]: " << msg << endl;
}

// --------------------------------------------------------------------------
// Check if edit distance between two strings is within d. True if it is, False if it isnt.
// Chek if the two words are "neighbors" (edit distance 1)
// supports replacing one letter, inserting one letter, or deleating one letter
// --------------------------------------------------------------------------
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if (str1 == str2) return true; // same words are not adjacent

    int len1 = str1.size(), len2 = str2.size();

    if (abs(len1 - len2) > d) return false;

    // if lengths are equal than substitution
    if (len1 == len2){
        int diffCount = 0;
        for (int i = 0; i < len1; i++){
            if(str1[i] != str2[i]) diffCount++;
            if (diffCount > d) return false;
        }
        return diffCount <= d;
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
        // account for extra letter at the end, if any
        diffCount += (longer.size() - j);
        return diffCount <= d;    
    }
}


bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

// --------------------------------------------------------------------------
// Uses bfs to generate a minimun-length word ladder
// --------------------------------------------------------------------------
vector<string> get_neighbors(const string& word, const set<string>& word_list) {
    vector<string> neighbors;

    // Substitution of one letter
    for (int i = 0; i < (int)word.size(); i++) {
        char original = word[i];
        for (char c = 'a'; c <= 'z'; c++) {
            if (c == original) continue;
            string new_word = word;
            new_word[i] = c;
            if (word_list.count(new_word)) 
                neighbors.push_back(new_word);
        }
    }

    // Insertion of one letter
    for (int i = 0; i <= (int)word.size(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            string new_word = word.substr(0, i) + c + word.substr(i);
            if (word_list.count(new_word)) 
                neighbors.push_back(new_word);
        }
    }

    // Deletion of one letter
    if (!word.empty()) {
        for (int i = 0; i < (int)word.size(); i++) {
            string new_word = word.substr(0, i) + word.substr(i + 1);
            if (word_list.count(new_word)) 
                neighbors.push_back(new_word);
        }
    }
    
    std::sort(neighbors.begin(), neighbors.end());
    return neighbors;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (!word_list.count(end_word)) return{};
    
    queue<vector<string>> ladder_queue;
    set<string> visited;

    ladder_queue.push({ begin_word });
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> path = ladder_queue.front();
        ladder_queue.pop();
        
        // last word in the current path
        const string& last_word = path.back();

        // generate all valid neighbors (words that differ by 1 edit)
        vector<string> neighbors = get_neighbors(last_word, word_list);
        for (auto& nbr : neighbors) {
            if (!visited.count(nbr)) {
                visited.insert(nbr);

                // build the new path
                vector<string> new_path = path;
                new_path.push_back(nbr);

                // reached the end word, return immediately (shortest path).
                if (nbr == end_word) {
                    return new_path;
                }
                // enqueue and continue
                ladder_queue.push(new_path);
            }
        }
    }

    // exhaust BFS without finding end_word, then no ladder exists
    
    return {};
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream infile(file_name.c_str());
    if (!infile){
        cerr << "Could not open dictionary file: " << file_name << endl;
        return;
    }

    string word;
    while (infile >> word){
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
    infile.close();
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()){
        cout << "No word ladder found." << endl;
    } else{
        cout << "Word ladder found: ";
        for (size_t i = 0; i < ladder.size(); i++){
            cout << ladder[i];
            if (i < ladder.size() - 1)
                cout << " ";
        }
        cout << " " <<endl;
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "../src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}