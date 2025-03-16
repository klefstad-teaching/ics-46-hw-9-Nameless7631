#include "ladder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <queue>

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}



void error(string word1, string word2, string msg){
    std::cerr << "ERROR: " << word1 << "and" << word2 << "caused" << msg << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int word1_len = str1.length();
    int word2_len = str2.length();
    if ((word1_len - word2_len) > d || (word2_len - word1_len) > d) return false;
    int word1_idx = 0, word2_idx = 0, count = 0;
    while (word1_idx < word1_len && word2_idx < word2_len){
        if (str1[word1_idx] != str2[word2_idx]){
            if (++count > d) return false;
            if (word1_len > word2_len) ++word1_idx;
            else if (word2_len > word1_len) ++word2_idx;
            else{
                ++word1_idx;
                ++word2_idx;
            }
        }
        else{
            ++word1_idx;
            ++word2_idx;
        }
    }
    count += (word1_len - word1_idx) + (word2_len - word2_idx);
    return count <= d;
}

bool is_adjacent(const string& word1, const string& word2){
    int word1_len = word1.length();
    int word2_len = word2.length();
    if ((word1_len - word2_len) > 1 || (word2_len - word1_len) > 1) return false;
    int word1_idx = 0, word2_idx = 0, count = 0;
    while (word1_idx < word1_len && word2_idx < word2_len){
        if (word1[word1_idx] != word2[word2_idx]){
            if (++count > 1) return false;
            if (word1_len > word2_len) ++word1_idx;
            else if (word2_len > word1_len) ++word2_idx;
            else{
                ++word1_idx;
                ++word2_idx;
            }
        }
        else{
            ++word1_idx;
            ++word2_idx;
        }
    }
    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    std::queue<std::vector<std::string>> ladder_queue;
    ladder_queue.push({begin_word});

    std::set<std::string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()){
        std::vector<std::string> ladder = ladder_queue.front();
        ladder_queue.pop();
        std::string last_word = ladder.back();
        for (const std::string word : word_list){
            if (visited.find(word) == visited.end() && is_adjacent(last_word, word)){
                visited.insert(word);
                std::vector<std::string> copy = ladder;
                copy.push_back(word);
                if (word == end_word) return copy;
                ladder_queue.push(copy);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name){
    std::ifstream inputFile;
    std::string line;

    inputFile.open(file_name);

    if (inputFile.is_open()){
        while (getline(inputFile, line)){
            word_list.insert(line);
        }
        inputFile.close();
    }
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.size() == 0){
        std::cout << "No word ladder found." << std::endl;
        return;
    }

    std::cout << "Word ladder found: ";
    for (const std::string s : ladder){
        std::cout << s << " ";
    }
    std::cout << std::endl;
}

void verify_word_ladder(){
    set<string> word_list;

    load_words(word_list, "./src/words.txt");

    // std::vector result = generate_word_ladder("cat", "dog", word_list);
    // print_word_ladder(result);
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    // result = generate_word_ladder("marty", "curls", word_list);
    // print_word_ladder(result);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    // result = generate_word_ladder("code", "data", word_list);
    // print_word_ladder(result);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    // result = generate_word_ladder("work", "play", word_list);
    // print_word_ladder(result);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    // result = generate_word_ladder("sleep", "awake", word_list);
    // print_word_ladder(result);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    // result = generate_word_ladder("car", "cheat", word_list);
    // print_word_ladder(result);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}