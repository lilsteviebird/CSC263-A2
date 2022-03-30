#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sys/timeb.h>
#include <vector>
#include <stdlib.h>
#include <xapian.h>
#include <unordered_set>
#include <unordered_map>
#include "library.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
    string data_name = argv[1];
    int line_number = atoi(argv[2]);
    int k_sets = atoi(argv[3]);
    vector <string> keywords;
    int size = sizeof(argv);

    cout << size << endl;
    for(int i = 4; i <= size;i++){

        string curr = argv[i];
        cout << curr << endl;
        keywords.push_back(curr);
            cout << "got here" <<endl;

    }
    cout << "got here" <<endl;

    cout << keywords.at(0) << endl;


    Xapian::WritableDatabase inverted_db = create_xapian_database(data_name, line_number);
    query_searcher(inverted_db, k_sets, keywords);

    cout << "\nfinished program, exiting";
    return 0;
}
