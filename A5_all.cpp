//-----------------------------------------------
/**
*	This file contains all the functionalities
mentioned in assignment 5

*
* @author  Mehakpreet Singh
* @version 1.0
* @since   2018-08-12
*/
//-----------------------------------------------

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <map>
#include <set>
#include <iterator>

using namespace std;

//function declaration
//Problem 1
bool is_palindrome(const std::string&);
int main();
void test_is_palindrome();
//Problem 2
template <class Iterator>
pair<Iterator, bool> second_max(Iterator, Iterator);
void test_second_max(vector<int>);
//Problem 3
int countStringLambda(vector<string>&, int);
int countStringFreeFun(vector<string>&, int);
bool isLessThan(const string&, int);
int countStringFunctor(vector<string>&, int);
//Problem 4
void charFrequency();
class ShorterLengthThan
{
private:
	int num;
public:
	ShorterLengthThan(int n) : num(n) {  }

	int operator () (const string& str) const {
		return static_cast<int>(str.length()) < num;
	}
};
//Problem 5
void multisetUsingDefinedComparator();
struct CustomCompare
{
	bool operator()(const string& lhs, const string& rhs)
	{
		bool flag = false;
		if (lhs.length() < rhs.length())
			flag = true;
		else if (lhs.length() == rhs.length()) {
			flag = (lhs < rhs);
		}
		return flag;
	}
};

//-----------------------------------------------
/*
This is the driver main funtion to test all the 
funtionalities
*/
//-----------------------------------------------
int main()
{
	// problem 1:
	test_is_palindrome();
	cout << "\n";

	// problem 2:
	std::vector<int> v1{1}; // one element
	test_second_max(v1);

	std::vector<int> v2{ 1, 1 }; // all elements equal
	test_second_max(v2);

	std::vector<int> v3{ 1, 1, 3, 3, 7, 7 }; // at least with two distict elements
	test_second_max(v3);
	cout << "\n";

	// problem 3:
	std::vector<std::string> vecstr
	{ "count_if", "Returns", "the", "number", "of", "elements", "in", "the",
		"range", "[first", "last)", "for", "which", "pred", "is", "true."
	};
	cout << countStringLambda(vecstr, 5) << endl;
	cout << countStringFreeFun(vecstr, 5) << endl;
	cout << countStringFunctor(vecstr, 5) << endl;
	cout << "\n";

	// problem 4:
	charFrequency();
	cout << "\n";

	// problem 5:
	multisetUsingDefinedComparator();
	cout << "\n";
	system("pause");
	return 0;
}

//Problem 1

//test
//-----------------------------------------------
/*
This function tests the isPalindrome() funtion
*/
//-----------------------------------------------
void test_is_palindrome()
{
	std::string str_i = std::string("was it a car or a cat i saw?");
	std::string str_u = std::string("was it a car or a cat u saw?");
	
	cout << "the phrase \"" + str_i + "\" is " + (is_palindrome(str_i) ? "" : "not") + " a palindrome" << endl;
	cout << "the phrase \"" + str_u + "\" is " + (is_palindrome(str_u) ? "" : "not") + " a palindrome" << endl;
}


//working
//-----------------------------------------------
/*
This function checks whether the given string is
palindrome or not.
@param str_i, string to be tested
*/
//-----------------------------------------------
bool is_palindrome(const std::string & str_i)
{
	string temp;
	remove_copy_if(str_i.begin(), str_i.end(), back_inserter(temp), [](char c) {return !isalpha(c); });
	transform(temp.begin(), temp.end(), temp.begin(), toupper);
	return equal(temp.begin(), temp.end()-((temp.length()+1)/2), temp.rbegin());
}

//Problem 2

//Working
//-----------------------------------------------
/*
This function returns the value of the second maximum
element in a given container.
@param start, iterator to the beginning of the container
@param finish, iterator to the end of the container
*/
//-----------------------------------------------
template<class Iterator>
pair<Iterator, bool> second_max(Iterator start, Iterator finish)
{
	pair<Iterator, bool> retval;
	bool flag = true;
	//if container is empty
	if (start == finish) {
		//return make_pair<finish, false>;
		retval.first = finish;
		retval.second = false;
	}
	else {
		auto largest = start;
		auto second_largest = start;
		auto ptr = start;
		while (ptr != finish) {
			if (*ptr > *largest) {
				second_largest = largest;
				largest = ptr;
			}
			else if (*ptr > *second_largest) {
				second_largest = ptr;
				flag = false;
			}
			++ptr;
		}
		if (*largest == *second_largest && flag) {
			//return make_pair<start, false>;
			retval.first = start;
			retval.second = false;
		}
		else {
			//return make_pair<second_largest, true>;
			retval.first = second_largest;
			retval.second = true;
		}
	}
	return retval;
}

//test
//-----------------------------------------------
/*
This function tests the second_max() funtion
*/
//-----------------------------------------------
void test_second_max(vector<int> vec) {
	//return type from auto below: pair<vector<int>::iterator, bool>
	auto retval = second_max(vec.begin(), vec.end());
	if (retval.second) {
		cout << "The second largest element in vec is " << *retval.first << endl;
	}
	else {
		if (retval.first == vec.end())
			cout << "List empty, no elements\n";
		else
			cout << "Container's elements are all equal to " << *retval.first << endl;
	}
}

//Problem 3

//using lambda
//-----------------------------------------------
/*
This function returns the count of the number of
elements in a vector<string> with length less than
the provided integer value.
@param vecstr, string to be tested
@param n,		length against which to be tested
*/
//-----------------------------------------------
int countStringLambda(vector<string>& vecstr, int n) {
	return count_if(vecstr.begin(), vecstr.end(), [n](const string& str) {return static_cast<int>(str.length())<n; });
}
//using a free function
//-----------------------------------------------
/*
This function returns the count of the number of
elements in a vector<string> with length less than
the provided integer value.
@param vecstr, string to be tested
@param n,		length against which to be tested
*/
//-----------------------------------------------
int countStringFreeFun(vector<string>& vecstr, int n)
{
	using namespace std::placeholders;
	//auto fn = bind(isLessThan, _1, n);
	return count_if(vecstr.begin(), vecstr.end(), bind(isLessThan, _1, n));
}
bool isLessThan(const string & str, int n)
{
	return static_cast<int>(str.length()) < n;
}
//using function object
//-----------------------------------------------
/*
This function returns the count of the number of
elements in a vector<string> with length less than
the provided integer value.
@param vecstr, string to be tested
@param n,		length against which to be tested
*/
//-----------------------------------------------
int countStringFunctor(vector<string>& vecstr, int n)
{
	return count_if(vecstr.begin(), vecstr.end(), ShorterLengthThan(n));
}


//Problem 4
//-----------------------------------------------
/*
This function returns the freq of each character
in the user-input.
*/
//-----------------------------------------------
void charFrequency() {
	cout << "Enter one or more lines of text.\n";
	cout << "To end input press Ctrl-Z in Windows and Ctrl-D in Linux\n";
	string line;
	map<char, int> charFreq;
	
	while (getline(cin, line)) {
		//remove white spaces
		line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
		//transform to lowercase
		transform(line.begin(), line.end(), line.begin(), tolower);
		//filling the map as the input is being entered by the user
		for_each(line.begin(), line.end(),
			[&charFreq](char c)
		{map<char, int>::iterator it = charFreq.begin();
		it = charFreq.find(c);
		if (it == charFreq.end())
			charFreq[c] = 1;
		else
			it->second++;
		});
	}
	cin.clear();

	//printing the map on the console
	for_each(charFreq.begin(), charFreq.end(),
		[](pair<char, int> it)
	{	
		cout << it.first << " " << it.second << endl;
	});
}

//Problem 5
//-----------------------------------------------
/*
This function implements custom comparator for
inserting elements in hashmap
*/
//-----------------------------------------------
void multisetUsingDefinedComparator() {
	multiset<string, CustomCompare> gibberish;
	vector<string> vec =
	{"C", "BB", "A", "CC",  "A",  "B",  "BB",  "A",  "D",  "CC",  "DDD", "AAA"};
	copy(vec.begin(), vec.end(), std::inserter(gibberish, gibberish.begin()));
	ostream_iterator<string> out(cout, " ");
	copy(gibberish.begin(), gibberish.end(), out);
}