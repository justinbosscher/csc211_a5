/*
Implementation for the DNA class
*/

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "dna.h"


bool validseq(std::string seq) {
	for (int i=0; i < (int)seq.length(); i++) {
		switch (seq[i]) {
			case 'A' : break;
			case 'C' : break;
			case 'T' : break;
			case 'G' : break;
			case 'N' : break;
			default : return false;
		}
	}
	return true;
}

bool validhdr(std::string hdr) {
	if (hdr.length() > 0 && hdr[0] == '>')
		return true;
	else return false;
}

DNA::DNA() {
	seq = "";
	hdr = ">";
}

DNA::DNA(std::string header, std::string sequence) {
	seq = sequence;
	hdr = header;
	if (! validseq(seq)) throw std::runtime_error("Invalid sequence");
	if (! validhdr(hdr)) throw std::runtime_error("Invalid header, must start with '>'");
}

DNA::DNA(std::ifstream &infile) {
	bool header_found = false;
	for (std::string line; std::getline(infile, line); ) {
		if (! header_found && line[0] == '>') {
			header_found = true;
			hdr = line;
		} else {
			seq += line;
		}
	}
	if (! validseq(seq)) throw std::runtime_error("Invalid sequence");
	if (! validhdr(hdr)) throw std::runtime_error("Invalid header, must start with '>'");
}



std::string DNA::getSequence() {
	return seq;
}

std::string DNA::getHeader() {
	return hdr;
}



std::string DNA::toFasta(int columns) {
	std::string result = hdr + "\n";
	int i = 0;
	while (i < (int)seq.length()) {
		if (i + columns < (int)seq.length()) {
			result += seq.substr(i, columns) + "\n";
			i += columns;
		} else {
			result += seq.substr(i) + "\n";
			break;
		}

	}

	return result;
}

DNA DNA::revcomp() {
	std::string result = "";
	/*
	iterate backwards through the string
	so the result is in the proper order
	*/
	for (int i=seq.length()-1; i >= 0; i--) {
		switch (seq[i]) {
			case 'A': result += 'T'; break;
			case 'T': result += 'A'; break;
			case 'C': result += 'G'; break;
			case 'G': result += 'C'; break;
			case 'N': result += 'N'; break;
		}
	}
	return DNA(hdr, result);
}

size_t DNA::find(std::string query, size_t start) {
	std::string rq = DNA::DNA(">", query).revcomp().getSequence();
	size_t fwd = seq.find(query, start);
	size_t bck = seq.find(rq, start);
	if (fwd != std::string::npos && bck == std::string::npos) return fwd;
	if (bck != std::string::npos && fwd == std::string::npos) return bck;
	return (fwd < bck) ? fwd : bck;

}

bool operator==(DNA d1, DNA d2) {
	return d1.seq == d2.seq;
}

std::ostream &operator<<(std::ostream & os, DNA d) {
	return os << d.toFasta();
}