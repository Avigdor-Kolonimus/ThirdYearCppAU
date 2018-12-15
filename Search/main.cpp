/**
*Main file
*This file contains code from "C++ Primer", 
*by Stanley B.Lippman, Jose Lajoie, and Barbara E. Moo
*Author Alexey Titov
*Version 1.0
*Date 12.2018
**/
//libraries
#include "Query.h"
#include "TextQuery.h"
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
using namespace std;
//macro definition 
//regex of word1
#define REGULAR1 "([\\w]+)"
//regex of word1 [m,n]
#define REGULAR2 "([\\w]+)(\\s)(\\[)([\\d]+)(,)([\\d]+)(\\])"
//regex of word1 {AND/OR} word2
#define REGULAR3 "([\\w]+)(\\s)(\\{)([A-Z]{2,3})(\\})(\\s)([\\w]+)"
//regex of word1 {AND/OR} word2 [m,n]
#define REGULAR4 "([\\w]+)(\\s)(\\{)([A-Z]{2,3})(\\})(\\s)([\\w]+)(\\s)(\\[)([\\d]+)(,)([\\d]+)(\\])"
//regex of word1 {n} word2
#define REGULAR5 "([\\w]+)(\\s)(\\{)([\\d]+)(\\})(\\s)([\\w]+)"
//regex of word1 {n} word2 [m,n]
#define REGULAR6 "([\\w]+)(\\s)(\\{)([\\d]+)(\\})(\\s)([\\w]+)(\\s)(\\[)([\\d]+)(,)([\\d]+)(\\])"

int main(int argc, char **argv){
    if (argc != 2){
		cerr << "No input file" << endl; 
		return EXIT_FAILURE;
	}
    ifstream infile(argv[1]);
    if (!infile){
		cerr << "No input file!" << endl; 
		return EXIT_FAILURE;
	}
	TextQuery tq(infile); // store the file in a vector and build the query map
//	tq.display_map();     // debugging aid
	
	while (true) {
		int m, n, num;
		cout << "Enter one or two words to look for, or q to quit:\n";
		string line, str, str_m, str_n, str_num;
		getline(cin, line);
		if (line.empty() || line == "q")
			break;
		std::regex regular(REGULAR1);
		std::cmatch result;
		//word1
		if (std::regex_match(line.c_str(),result,regular)){
			WordQuery query(line);
			auto qResult = query.eval(tq);
			print(cout, qResult) << endl;
			continue;
		}
		//word1 [m,n]
		regular=REGULAR2;
		if (std::regex_match(line.c_str(),result,regular)){
			str=result[1]; str_m=result[4]; str_n=result[6];
			m=atoi(str_m.c_str());
			n=atoi(str_n.c_str());
			if (!(m>n || m<1 || n<1)){
				WordQuery query(str);
				auto qResult = query.eval(tq);
				print(cout, qResult, m ,n) << endl;
				continue;
			}
		}
		//word1 {AND/OR} word2
		regular=REGULAR3;
		if (std::regex_match(line.c_str(),result,regular)){
			str = result[4];
			if (str.compare("AND")==0){
				AndQuery aquery(result[1], result[7]);  
				auto qResult = aquery.eval(tq);
				print(cout, qResult) << endl;
				continue;
			}
			if (str.compare("OR")==0){
				OrQuery oquery(result[1], result[7]);   
				auto qResult = oquery.eval(tq);
				print(cout, qResult) << endl;
				continue;
			}
		}
		//word1 {AND/OR} word2 [m,n]
		regular=REGULAR4;
		if (std::regex_match(line.c_str(),result,regular)){
			str = result[4];
			str_m=result[10]; str_n=result[12];
			m=atoi(str_m.c_str());
			n=atoi(str_n.c_str());
			if (!(m>n || m<1 || n<1)){
				if (str.compare("AND")==0){
					AndQuery aquery(result[1], result[7]);  
					auto qResult = aquery.eval(tq);
					print(cout, qResult, m, n) << endl;
					continue;
				}
				if (str.compare("OR")==0){
					OrQuery oquery(result[1], result[7]);   
					auto qResult = oquery.eval(tq);
					print(cout, qResult, m, n) << endl;
					continue;
				}
			}
		}
		//word1 {n} word2
		regular=REGULAR5;
		if (std::regex_match(line.c_str(),result,regular)){
			str_n=result[4];
			num=atoi(str_n.c_str());
			if (num>0){
				NQuery nquery(result[1], result[7], num);
				auto qResult = nquery.eval(tq);
				print(cout, qResult) << endl;
				continue;
			}
		}
		// word1 {n} word2 [m,n]
		regular=REGULAR6;
		if (std::regex_match(line.c_str(),result,regular)){
			str_m=result[10]; str_n=result[12]; str_num=result[4];
			num=atoi(str_num.c_str());
			m=atoi(str_m.c_str());
			n=atoi(str_n.c_str());
			if (num>0 && m<n && m>0 && n>0){
				NQuery nquery(result[1], result[7], num);
				auto qResult = nquery.eval(tq);
				print(cout, qResult, m, n) << endl;
				continue;
			}
		}
		cout << "Unrecognized search" <<"\n"<<endl;
	}
	return 0;
}
