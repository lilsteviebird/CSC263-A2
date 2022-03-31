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
#include <fstream>
#include <sstream>




int main(int argc, const char * argv[]) {
    string data_name = argv[1];
        
    std::string line;
    
    int time = 0;

    ifstream data_file(data_name);

    
    Xapian::WritableDatabase inverted_db = create_xapian_database(data_name, 40000);

    while (std::getline(data_file, line)) {
        std::stringstream   linestream(line);
        std::string         value;
        vector <string> keywords;

    while(getline(linestream,value,','))
    {
        //std::cout << "Value(" << value << ")\n";
        keywords.push_back(value);
        
    }
    time += query_searcher1(inverted_db, 10, keywords);
    std::cout << "Line Finished" << std::endl;

    }

    time = time/30;

    std::cout << time << std::endl;

}