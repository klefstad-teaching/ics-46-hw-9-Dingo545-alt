#include "ladder.h"
#include <algorithm> 

int main(){
    string start_word, end_word;
    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;

    // Convert both words to lower-case.
    transform(start_word.begin(), start_word.end(), start_word.begin(), ::tolower);
    transform(end_word.begin(), end_word.end(), end_word.begin(), ::tolower);

    // Check that the start and end words are different.
    if (start_word == end_word)
        error(start_word, end_word, "Start and end words must be different.");
    
    set<string> dictionary;
    load_words(dictionary, "../src/words.txt");

    if (dictionary.find(end_word) == dictionary.end()) 
        error(start_word, end_word, "End word must be in the dictionary.");
    
    vector<string> ladder = generate_word_ladder(start_word, end_word, dictionary);
    print_word_ladder(ladder);

    return 0;
    

    //verify_word_ladder();
}