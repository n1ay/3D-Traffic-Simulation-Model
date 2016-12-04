/*
 * Test.cpp
 *
 *  Created on: 03.12.2016
 *      Author: kamil
 */

#include "Test.hpp"

int Test::counter = 1;

Test::Test() {

}

Test::~Test() {

}

template <typename T> void Test::test(T test, T result, std::string name) {
	int number = Test::counter++;
	if(!(test == result)) {
		std::cerr<<"Test "<<number<<" ("<<name<<") failed."<<std::endl;
		std::cerr<<"Test object was: "<<test<<std::endl;
		std::cerr<<"But expected result was: "<<result<<std::endl;
	} else {
		std::cout<<"Test "<<number<<" ("<<name<<") passed."<<std::endl;
	}
}

template <typename T> void Test::test(T test, T result) {
	test(test, result, "");
}
