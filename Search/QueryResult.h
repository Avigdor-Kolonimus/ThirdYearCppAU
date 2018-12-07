// This file contains code from "C++ Primer, Fifth Edition", 
// by Stanley B.Lippman, Josee Lajoie, and Barbara E. Moo

#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <string>
#include <vector>
#include <set>
#include <iostream>

class QueryResult {
	friend std::ostream& print(std::ostream&, const QueryResult&);
	friend std::ostream& print(std::ostream&, const QueryResult&, size_t, size_t);
	friend class NQuery;
	public:
		typedef std::vector<std::string>::size_type line_no;
		typedef std::set<line_no>::const_iterator line_it;
		QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, 
	            std::shared_ptr<std::vector<std::string>> f):
				sought(s), lines(p), file(f) { }
		
		std::set<line_no>::iterator begin() {return lines->begin();}
		std::set<line_no>::iterator end() {return lines->end();}
		std::set<line_no>::const_iterator cbegin() const {return lines->cbegin();}
		std::set<line_no>::const_iterator cend() const {return lines->cend();}
		std::shared_ptr<std::vector<std::string>> get_file() { return file; }		
	private:
		std::string sought;  // word this query represents
		std::shared_ptr<std::set<line_no>> lines; // lines it's on
		std::shared_ptr<std::vector<std::string>> file;  //input file
};
#endif
