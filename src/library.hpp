#ifndef library_hpp
#define library_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <list>
#include <xapian.h>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>   
#include <sys/timeb.h>


using namespace std;

typedef struct {
    string name;
    //prioirty
    int p = 0;
} DocID;

typedef struct {
    bool operator()(DocID const& p1, DocID const& p2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return p1.p > p2.p;
    }
} CompareP;

typedef struct {
    unordered_set<string> dictionary;
    unordered_map<string, int> freq;
    unordered_map<string, priority_queue <DocID, vector<DocID>, CompareP> >postings;
} InvertedIndex ;

InvertedIndex create_indexer(string datatext_name, int length);
Xapian::WritableDatabase create_xapian_database(string datatext_name, int length);
string remove_special_characters(string line);
bool check_stop_word(string word_given, vector<string> stop_words);
void query_searcher (Xapian::WritableDatabase db, int k, vector<string> keywords);
vector<string> line_seperator(string line);
#endif /* library_hpp */