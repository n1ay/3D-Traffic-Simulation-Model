/*
 * Test.hpp
 *
 *  Created on: 03.12.2016
 *      Author: kamil
 */

#ifndef TEST_HPP_
#define TEST_HPP_

#include <iostream>

class Test {
	Test();
	~Test();
public:
	static int counter;
	template <typename T> void test(T test, T result, std::string name);
	template <typename T> void test(T test, T result);
};

#endif /* TEST_HPP_ */
