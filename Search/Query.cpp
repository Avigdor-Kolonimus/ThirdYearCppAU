/**
*Cpp file of class Query
*Author Alexey Titov
*Version 1.0
*Date 12.2018
**/
//libraries
#include "Query.h"
#include "TextQuery.h"
#include <memory>
#include <set>
#include <regex>
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <iterator>
using namespace std;
/**************************************MY CODE***********************************************/
//the functon returns s1
const string AndQuery::getS1()const{
    return this->s1;
}
//the function returns s2
const string AndQuery::getS2()const{
    return this->s2;
}
//the function splits a string into an array of words
vector<string> NQuery::resplit(const string & s)const {
    string rgx_str = "[|:,. ]";
    vector<string> elems;
    regex rgx (rgx_str);
    sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    sregex_token_iterator end;
    while (iter != end){
        string str=*iter;
        if (str.compare(""))
            elems.push_back(*iter);
        ++iter;
    }
    return elems;
  }
//the function returns result of query "word1 {n} word2"
QueryResult NQuery::eval(const TextQuery& text) const{
    auto qr_AND = andquery.eval(text);          //result of query from AndQuery class
    const string s1 = andquery.getS1();         //first word
    const string s2 = andquery.getS2();         //second word
    vector<int> vnum{};                         //array of lines that answer the query
    for (auto num : *qr_AND.lines){          // for every element in the set 
        string tmp = *(qr_AND.file->begin() + num);     //string from file
        vector<string> v = resplit(tmp);                //array of words from string
        int pos1=-1, pos2=-1,index=0;                   
        int flag = 0;
        for (const auto & e: v) {
            if (s1.compare(e)==0)       //found the first word
                pos1=index;
            if (s2.compare(e)==0)       //found the second word
                pos2=index;
            index++;
            //check the distance between words
            if (pos1!=-1 && pos2!=-1 && (abs(pos1-pos2)-1)<=this->num)
                flag=1;
        }
        if (flag)
            vnum.push_back(num);
    }
    auto ret_lines = make_shared<set<line_no>>(vnum.begin(), vnum.end()); 
    return QueryResult(s1 + " {"+ to_string(this->num) +"} " + s2, ret_lines, qr_AND.get_file());
}
//the function print a line between line m and line n in which the word/words appeared
ostream &print(ostream &os, const QueryResult &qr, size_t m, size_t n){
    int counter_lines=0;
    // print line between m and n in which the word appeared
	for (auto num : *qr.lines){                      // for every element in the set 
        if ((num+1)>=m && n>=(num+1)){
            os << "(line " << num + 1 << ") "<< *(qr.file->begin() + num) << endl;
            counter_lines++;
        }
    }
	// print the count and all occurrences
    os << "\"" << qr.sought << "\" occurs " << counter_lines << " times" << endl;
	return os;
}
/*********************************************************************************************/
//The code received with the task
QueryResult AndQuery::eval(const TextQuery& text) const{
    auto left = left_query.eval(text), right = right_query.eval(text);
	// set to hold the intersection of left and right
    auto ret_lines = make_shared<set<line_no>>();  
    // writes the intersection of two ranges to a destination iterator
    set_intersection(left.begin(), left.end(), 
                   right.begin(), right.end(),
                   inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(s1 + " {AND} " + s2, ret_lines, left.get_file());
}
//The code received with the task
QueryResult OrQuery::eval(const TextQuery& text) const{
    auto left = left_query.eval(text), right = right_query.eval(text); 
	// copy the line numbers from the left-hand operand into the result set
	auto ret_lines = 
	     make_shared<set<line_no>>(left.begin(), left.end());
	// insert lines from the right-hand operand
	ret_lines->insert(right.begin(), right.end());
	// return the new QueryResult representing the union of lhs and rhs
    return QueryResult(s1 + " {OR} " + s2, ret_lines, left.get_file());
}
//The code received with the task
ostream &print(ostream &os, const QueryResult &qr){
    // print each line in which the word appeared
	for (auto num : *qr.lines) // for every element in the set 
        os << "(line " << num + 1 << ") " 
		   << *(qr.file->begin() + num) << endl;
	// print the count and all occurrences
    os << "\"" << qr.sought << "\" occurs " << qr.lines->size() << " times" << endl;
	return os;
}