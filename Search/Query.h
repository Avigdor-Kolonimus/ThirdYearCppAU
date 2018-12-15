/**
*Header file of class Query
*Author Alexey Titov
*Version 1.0
*Date 12.2018
**/
#ifndef QUERY_H
#define QUERY_H
//libraries
#include "TextQuery.h"
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
using namespace std;
// abstract class 
class Query_base {
    public:
        using line_no = TextQuery::line_no;
        Query_base() = default;
	    virtual ~Query_base() = default;
        virtual QueryResult eval(const TextQuery&) const = 0; 
    //private:
};
//The code received with the task
class WordQuery: public Query_base {
    public:
        WordQuery(const std::string &s): query_word(s) { }
        WordQuery() { }
        QueryResult eval(const TextQuery &t) const{ 
            return t.query(query_word); 
        }
	    std::string rep() const { 
            return query_word; 
        }
    private:
        std::string query_word;
};
//The code received with the task
class AndQuery: public Query_base {
    public:
        AndQuery(const std::string &left_string, const std::string &right_string): 
                left_query(WordQuery(left_string)), right_query(WordQuery(right_string)),
			    s1(left_string), s2(right_string){ }
        AndQuery(){ }
        QueryResult eval(const TextQuery&) const;
        const string getS1()const;
        const string getS2()const;
    private:
        WordQuery left_query, right_query;
	    const std::string s1, s2;
};
//The code received with the task
class OrQuery: public Query_base {
    public:
        OrQuery(const std::string &left_string, const std::string &right_string): 
                left_query(WordQuery(left_string)), right_query(WordQuery(right_string)),
			    s1(left_string), s2(right_string){ }
        QueryResult eval(const TextQuery&) const;
    private:
        WordQuery left_query, right_query;
	    const std::string s1, s2;
};
//My class NotQuery, word1 number word2
class NQuery:public AndQuery {
    public:
        NQuery(const std::string &left_string, const std::string &right_string, int _num):
        andquery(left_string,right_string), num(_num) { }
        QueryResult eval(const TextQuery&) const;
        vector<string> resplit(const string& )const;
    private:
        AndQuery andquery;
        int num;
};
#endif
