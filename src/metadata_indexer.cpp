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

    string data_name = argv[0];
    int line_number = atoi(argv[1]);


    long start = 0;
    long finish = 0;
    long time = 0;

    struct timeb timer;
    ftime(&timer);
    start = timer.time*1000 + timer.millitm;

    //max number given can be 69184
    //InvertedIndex inverted = create_indexer("metadata.txt", 69184);
    Xapian::WritableDatabase inverted_db = create_xapian_database(data_name, line_number);
    // Xapian::WritableDatabase inverted_db = create_xapian_database("metadata.txt", 500);


    ftime(&timer);
    finish = timer.time*1000 + timer.millitm;
    time = finish - start;
    fprintf(stdout, "\nTIME: %ld milliseconds\n", time);

    cout << "\nfinished program, exiting";
    return 0;
}
