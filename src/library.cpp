#include "library.hpp"

using namespace std;

//create Xapian WritableDatabase
Xapian::WritableDatabase create_xapian_database(string datatext_name, int length){
	ifstream data_file(datatext_name);
	ifstream stop_file("stopwords.txt");

	//create stop word library
	string stop_line;
	vector <string> stop_words;
	while(getline(stop_file, stop_line)){
		stop_words.push_back(stop_line);
	}

	string line;
	int count = 0;

	Xapian:: WritableDatabase db("x_database", Xapian::DB_CREATE_OR_OPEN);
	Xapian::Document doc;
	while(getline(data_file, line)){
		if(count >= length){
			break;
		}
		//name of the document
		if(count % 2 == 0){
			// doc.clear_terms();
			// doc.clear_values();
			Xapian:: Document new_doc;
			doc = new_doc;
			// vector <string> seperated = split(line, ' ');
			doc.add_value(0, line);

			//add terms
			// int iterator = 0;
			// for (vector<string>::iterator t=seperated.begin(); t!=seperated.end(); ++t) {
			// 	string curr = *t;
			// 	if(check_stop_word(curr, stop_words) == false){
			// 		curr = remove_special_characters(curr);
			// 		if(curr.empty()){
			// 			continue;
			// 		}
			// 		doc.add_value(iterator, string(curr));
			// 		iterator++;

			// 	}
            //     // cout << curr << endl;
			// }
		}
		else{
			// vector <string> seperated = split(line, ' ');
			vector <string> seperated = line_seperator(line);
			//add words to document
			int value = 0;
			for (vector<string>::iterator t=seperated.begin(); t!=seperated.end(); ++t) {
				string curr = *t;
				if(check_stop_word(curr, stop_words) == false){
					curr = remove_special_characters(curr);
					if(curr.empty() || curr[0] == ' ' || curr.size() == 0){
						continue;
					}
					else
					{
						//doc.add_value(value, string(curr));
						doc.add_term(curr);
						value++;
					}
						
				}
                // cout << curr << endl;
			}
			db.add_document(doc);

			db.commit();

		}
		count++;
	}

	db.commit();

	// cout << count;
	data_file.close();
	stop_file.close();

	return db;
}


void query_searcher (Xapian::WritableDatabase db, int k, vector<string> keywords){

	long start = 0;
    long finish = 0;
    long time = 0;

    struct timeb timer;
    ftime(&timer);
    start = timer.time*1000 + timer.millitm;

	queue <Xapian::Query> all_queries;
	queue <string> allWords;
	// for (vector<string>::iterator t=keywords.begin(); t!=keywords.end(); ++t){
	// 	string curr = *t;
	// 	cout<< curr << endl;
	// }


	for (vector<string>::iterator t=keywords.begin(); t!=keywords.end(); ++t) {
		string curr = *t;
		vector<string> filler;
		filler.push_back(curr);
		if(curr[0] == '+'){
			Xapian::Query toAdd(
				Xapian::Query:: OP_AND,
				filler.begin(),
				filler.end()
			);
			all_queries.push(toAdd);
		}
		else{
			Xapian::Query toAdd(
				Xapian::Query:: OP_OR,
				filler.begin(),
				filler.end()
			);
			all_queries.push(toAdd);
		}
		allWords.push(curr);
	}
						cout<<"ADded the word though" <<endl;

	Xapian::Query final_query = all_queries.front();
	all_queries.pop();
	string temp_word = allWords.front();
	allWords.pop();
	while(!all_queries.empty()){
		string new_temp = allWords.front();

		if(new_temp[0] == '+'){
			final_query = Xapian::Query(
				Xapian::Query:: OP_AND,
				final_query,
				all_queries.front()
			);
		}
		else{
			final_query = Xapian::Query(
				Xapian::Query:: OP_OR,
				final_query,
				all_queries.front()
			);
		}
		all_queries.pop();
		allWords.pop();
	}

// Xapian::Query query2(
//     Xapian::Query::OP_OR,
//     keywords.begin(),
//     keywords.end()
// );
	Xapian:: Enquire enquire(db);
	 enquire.set_query(final_query);
	// enquire.set_query(query2);

	Xapian::MSet matches = enquire.get_mset(0, k); 
 
 	ftime(&timer);
    finish = timer.time*1000 + timer.millitm;
    time = finish - start;

	int asdf = k;

	cout << "where it go" << endl;
	for(Xapian::MSetIterator match = matches.begin(); match != matches.end(); match++){
		cout << "we got in here" << endl;
    	Xapian::Document doc = match.get_document();
		bool highlight = false;
		cout<< "Description Name: ";
		cout << doc.get_value(0) <<endl;
		for(Xapian::TermIterator term = doc.termlist_begin(); term != doc.termlist_end(); term++){
			string print = *term;
			bool highlight = false;
			for (vector<string>::iterator t=keywords.begin(); t!=keywords.end(); ++t){
				string curr = *t;
				highlight = false;
				if(print.compare(curr) == false){
					highlight = true;
					string concat = "===" + print + "===";
					cout << concat << endl;
				}
			}
			if(highlight == false){
				cout << print << endl;
			}
		}

		// for(Xapian::ValueIterator value = doc.values_begin(); value != doc.values_end(); value++){
		// 	string print = *value;
		// 	bool highlight = false;
		// 	for (vector<string>::iterator t=keywords.begin(); t!=keywords.end(); ++t){
		// 		string curr = *t;
		// 		highlight = false;
		// 		if(print.compare(curr) == false){
		// 			highlight = true;
		// 			string concat = "===" + print + "===";
		// 			cout << concat << endl;
		// 		}
		// 	}
		// 	if(highlight == false){
		// 		cout << print << endl;
		// 	}
		// }

		
	}	
	
	fprintf(stdout, "\nTIME: %ld milliseconds\n", time);
}


string remove_special_characters(string line){
     string temp  = "";
	//  cout << "\nLine is: ";
	//  cout << line; 
	 char legal[] = {'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G', 'h', 'H', 'i', 'I', 'j', 'J',
	 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O', 'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T', 'u', 'U', 'v',
	 'V', 'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < line.size(); ++i) {
		for(int j = 0; j < sizeof(legal)/sizeof(char); j++){
			if(line[i] == legal[j]){
				temp = temp + line[i];
				break;
			}
		}
    }
    return temp;
}

bool check_stop_word(string word_given, vector<string> stop_words){
	for (vector<string>::iterator t=stop_words.begin(); t!=stop_words.end(); ++t) {
		string curr = *t;
        if(word_given.compare(curr) == 0){
			return true;
		}
	}
	return false;
}

vector<string> line_seperator(string line){
	vector<string> return_list;
	string temp = "";
	for(std::string::size_type i = 0; i < line.size(); i++){
		if(line[i] == ' '){
			return_list.push_back(temp);
			temp = "";
		}else{
			temp = temp + line[i];
		}
	}

	return return_list;
}


//ignore custom inverted index


// InvertedIndex create_indexer(string datatext_name, int length){
// 	ifstream data_file(datatext_name);
// 	ifstream stop_file("stopwords.txt");

// 	//create stop word library
// 	string stop_line;
// 	vector <string> stop_words;
// 	while(getline(stop_file, stop_line)){
// 		stop_words.push_back(stop_line);
// 	}

// 	string line;
// 	int count = 0;
// 	InvertedIndex inverted_index;
// 	unordered_set<string> word_set;
// 	unordered_map<string, int> word_map;
// 	unordered_map<string, priority_queue <DocID, vector<DocID>, CompareP> >word_postings;

// 	while(getline(data_file, line) && count < length){
// 		DocID add_ID;
// 		//name of the document
// 		if(count % 2 == 0){
// 			add_ID.name = line;
// 		}
// 		//data of the document
// 		else{
// 			vector <string> seperated = split(line, ' ');
// 			unordered_map<string, int> line_map;
// 			vector <string> for_postings;

// 			//build freq and dictionary
// 			for (vector<string>::iterator t=seperated.begin(); t!=seperated.end(); ++t) {
// 				string curr = *t;
// 				if(check_stop_word(curr, stop_words) == false){
// 					curr = remove_special_characters(curr);
// 					word_set.insert(curr);
// 					word_map[curr]++;
// 					line_map[curr]++;
// 					for_postings.push_back(curr);
// 				}
//                 // cout << curr << endl;
// 			}
// 			//build postings list
// 			for (vector<string>::iterator t=for_postings.begin(); t!=for_postings.end(); ++t) {
// 				string curr = *t;
// 				add_ID.p = line_map[curr];

// 				if(word_postings.find(curr) == word_postings.end()){
// 					priority_queue<DocID, vector<DocID>, CompareP> new_queue;
// 					new_queue.push(add_ID);
// 				}
// 				else{
// 					//might have to use swap
// 					priority_queue<DocID, vector<DocID>, CompareP> update_queue = word_postings[curr];
// 					update_queue.push(add_ID);
// 					word_postings[curr] = update_queue;
// 				}
// 			}
// 		}
// 		count++;
// 	}
// 	inverted_index.dictionary = word_set;
// 	inverted_index.freq = word_map;
// 	inverted_index.postings = word_postings;



// 	// cout << count;
// 	data_file.close();
// 	stop_file.close();

// 	return inverted_index;
// }
