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

    keywords.push_back("+Datasets");
    keywords.push_back("+accuracy");
    keywords.push_back("+data");
    keywords.push_back("+total");
    keywords.push_back("+updated");

    keywords.push_back("+why");
    keywords.push_back("+fire");
    keywords.push_back("+cannot");
    keywords.push_back("+armament");
    keywords.push_back("+whatever");

    keywords.push_back("+assess");
    keywords.push_back("+situation");
    keywords.push_back("+dangerous");
    keywords.push_back("+safe");
    keywords.push_back("+tag");

     keywords.push_back("+strange");
    keywords.push_back("+Julio");
    keywords.push_back("+said");
    keywords.push_back("+hello");
    keywords.push_back("+book");

    // for(int i = 4; i <= size;i++){

    //     string curr = argv[i];
    //     if(curr.compare("")){
    //         break;
    //     }
    //     cout << curr << endl;
    //     keywords.push_back(curr);
    //         cout << "got here" <<endl;

    // }
    // cout << "got here" <<endl;

    // cout << keywords.at(0) << endl;


    Xapian::WritableDatabase inverted_db = create_xapian_database(data_name, line_number);
    query_searcher(inverted_db, k_sets, keywords);

    cout << "\nfinished program, exiting";
    return 0;
}
