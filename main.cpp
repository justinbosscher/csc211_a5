#include "bst.h"
#include "dna.h"
#include <iostream>
#include <string>


// COMPARATOR FUNCTIONS
// integer less-than
bool intLT(int &x, int &y){
	return x < y;
} // end intLT bool

// double less-than
bool doubleLT(double &x, double &y){
	return x < y;
} // end doubleLT bool

// string lexicographically less-than
bool stringLT(std::string &x, std::string &y){
	return x < y;
} // end stringLT bool

// DNA sequence less-than
bool dnaSeqLT(DNA &x, DNA &y){
	return x.getSequence().length() < y.getSequence().length();
} // end dnaLT

// DNA header lexicographically less-than
bool dnaHdrLT(DNA &x, DNA &y){
	return x.getHeader() < y.getHeader();
} // end dnaHdrLT


// MAIN
int main() {

	// tests integers
	std::vector<int> intV = {1, 5, 9, 2, 17, 392, 27, 346};
	BST<int> b(intV, &intLT);

	try{
		int z = b.find(392, &intLT);
		std::cout << z << std::endl;
	}catch(std::runtime_error){
		std::cout << "Integer test failed." << std::endl;
	} // end catch


	// test for integer that is not present
	try{
		int qq = b.find(7, &intLT);
		if (qq != 7){
		std::cout << "Non-existent Integer Test Failed." << std::endl;
		} // end if
	}catch(std::runtime_error){
		std::cout << "Non-existent Integer Test is a Success." << std::endl;
	} // end non-existent integer try/catch


	// test doubles
	std::vector<double> dubV = {0.00, 1.11, 2.22, 3.33, 0.44, 100.00, 5.55, 6.66};
	BST<double> d(dubV, &doubleLT);

	try{
		double y = d.find(6.66, &doubleLT);
		std::cout << y << std:: endl;
	}catch(std::runtime_error){
		std::cout << "Double test failed." << std::endl;
	} // end catch


	// test for double that is not present
	try{
		double pi = d.find(3.14, &doubleLT);
		if (pi != 3.14){
		std::cout << "Non-existent Double Test Failed." << std::endl;
		} // end if
	}catch(std::runtime_error){
		std::cout << "Non-existent Double Test is a Success." << std::endl;
	} // end non-existent integer try/catch


	// test strings
	std::vector<std::string> strV = {"zero", "one", "three", "five", "sixteen", "eighteen"};
	BST<std::string> s(strV, &stringLT);

	try{
		std::string x = s.find("sixteen", &stringLT);
		std::cout << x << std::endl;
	}catch(std::runtime_error){
		std::cout << "String test failed." << std::endl;
	} // end catch


	// test for string that is not present
	try{
	 	std::string str = s.find("test", &stringLT);
		if (str != "test"){
		std::cout << "Non-existent String Test Failed." << std::endl;
		} // end if
	}catch(std::runtime_error){
		std::cout << "Non-existent String Test is a Success." << std::endl;
	} // end non-existent integer try/catch


	// create test DNA objects, place them in vector, and test
	DNA test1 = DNA(">a", "GAT");
	DNA test2 = DNA(">f", "TACC");
	DNA test3 = DNA(">c", "AC");
	DNA test4 = DNA(">r", "CAGGAT");
	DNA testA = DNA(">test", "GATTACA");
	std::vector<DNA> dnaV = {test1, test2, test3, test4};


	// test sequence length
	BST<DNA> g(dnaV, &dnaSeqLT);
	try{
		DNA w = g.find(test3, &dnaSeqLT);
		std::cout << w.getSequence() << std::endl;
	}catch(std::runtime_error){
		std::cout << "Sequence test failed." << std::endl;
	} // end catch


	// test for sequence that is not present
	try{
		DNA ss = g.find(testA, &dnaSeqLT);
		if (ss.getSequence() != testA.getSequence()){
		std::cout << "Non-existent Sequence Test Failed." << std::endl;
		} // end if
	}catch(std::runtime_error){
		std::cout << "Non-existent Sequence Test is a Success." << std::endl;
	} // end non-existent sequence try/catch


	// test header lexicographically
	BST<DNA> h(dnaV, &dnaHdrLT);
	try{
		DNA v = h.find(test2, &dnaHdrLT);
		std::cout << v.getHeader() << std::endl;
	}catch(std::runtime_error){
		std::cout << "Header test failed." << std::endl;
	} // end catch


	// test for header that is not present
	try{
	 	DNA hh = h.find(testA, &dnaHdrLT);
		if (hh.getHeader() != testA.getHeader()){
		std::cout << "Non-existent Header Test Failed." << std::endl;
		} // end if
	}catch(std::runtime_error){
		std::cout << "Non-existent Header Test is a Success." << std::endl;
	} // end non-existent integer try/catch


	return 0;
} // end main
