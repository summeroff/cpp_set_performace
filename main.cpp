// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <windows.h>

#ifdef DEBUG
const int set_repeats = 10000;
const int tests_repeats = 10;
#else
const int set_repeats = 100000;
const int tests_repeats = 100;
#endif // DEBUG

const std::string test_str14 = "testtext1234__";
const std::string test_str140 = "testtext1234__testtext1234__testtext1234__testtext1234__testtext1234__testtext1234__testtext1234__testtext1234__testtext1234__testtext1234__";
const std::string test_str7 = "tstx13_";

const std::string & test_str = test_str140;
const int test_str_size = test_str.size();

class myClass
{
	std::string stra;

	long long counter;  //use counter to not let compiler optimize repeated calls 

public:
	void setStrByValue(std::string _str)
	{
		stra = _str;
		counter++;
	}
	void setStrByValueWithMove(std::string _str)
	{
		stra = std::move(_str);
		counter++;
	}
	void setStrByReference(const std::string& _str)
	{
		stra = _str;
		counter++;
	}
	void setStrByRValue(std::string&& _str)
	{
		stra = _str;
		counter++;
	}
	void setStrByRValueWithMove(std::string&& _str)
	{
		stra = std::move(_str);
		counter++;
	}

	myClass()
	{
		counter = 0;
	}

	inline void beforeSet()
	{
		resetStr();
		if (test_str.size() != test_str_size && stra.size() == 0)
		{
			std::cout << "failed set size check test_str = " << test_str.size() << std::endl;
			exit(0);
		}
	}

	inline void afterSet()
	{
		if (stra.size() != test_str_size)
		{
			std::cout << "failed set size check stra = " << stra.size() << std::endl;
			exit(0);
		}
	}

	inline void resetStr()
	{
		stra.clear();
	}

	long long getCounter() { return counter; };
};


inline void test1_setStrByValue(myClass & myObj)
{
	for (int i = 0; i < set_repeats; i++)
	{
		myObj.beforeSet();
		myObj.setStrByValue(test_str);
		myObj.afterSet();
	}
}

inline void test2_setStrByValueWithMove(myClass & myObj)
{
	for (int i = 0; i < set_repeats; i++)
	{
		myObj.beforeSet();
		myObj.setStrByValueWithMove(test_str);
		myObj.afterSet();
	}
}

inline void test3_setStrByReference(myClass & myObj)
{
	for (int i = 0; i < set_repeats; i++)
	{
		myObj.beforeSet();
		myObj.setStrByReference(test_str);
		myObj.afterSet();
	}
}

inline void test4_setStrByRValue(myClass & myObj)
{
	for (int i = 0; i < set_repeats; i++)
	{
		myObj.beforeSet();
		myObj.setStrByRValue(std::string(test_str));
		myObj.afterSet();
	}
}

inline void test5_setStrByRValueWithMove(myClass & myObj)
{
	for (int i = 0; i < set_repeats; i++)
	{
		myObj.beforeSet();
		myObj.setStrByRValueWithMove(std::string(test_str));
		myObj.afterSet();
	}
}

void testForVSProfiler()
{
	myClass myObj;
	for (int i = 0; i < tests_repeats; i++)
	{
		test3_setStrByReference(myObj);
		test1_setStrByValue(myObj);
		test2_setStrByValueWithMove(myObj);
		test4_setStrByRValue(myObj);
		test5_setStrByRValueWithMove(myObj);
	}
	
	std::cout << "final counter = " << myObj.getCounter() << std::endl;
}

void testByTimings()
{
	myClass myObj;

	DWORD ticksend;
	DWORD ticksstart;
	int test1_ticks = 0;
	int test2_ticks = 0;
	int test3_ticks = 0;
	int test4_ticks = 0;
	int test5_ticks = 0;

	for (int i = 0; i < tests_repeats; i++)
	{
		ticksstart = GetTickCount();
		test1_setStrByValue(myObj);
		ticksend = GetTickCount();
		test1_ticks += ticksend - ticksstart;

		ticksstart = GetTickCount();
		test2_setStrByValueWithMove(myObj);
		ticksend = GetTickCount();
		test2_ticks += ticksend - ticksstart;

		ticksstart = GetTickCount();
		test3_setStrByReference(myObj);
		ticksend = GetTickCount();
		test3_ticks += ticksend - ticksstart;

		ticksstart = GetTickCount();
		test4_setStrByRValue(myObj);
		ticksend = GetTickCount();
		test4_ticks += ticksend - ticksstart;

		ticksstart = GetTickCount();
		test5_setStrByRValueWithMove(myObj);
		ticksend = GetTickCount();
		test5_ticks += ticksend - ticksstart;
	}

	std::cout << "ticks in test1_setStrByValue         = " << test1_ticks << std::endl;
	std::cout << "ticks in test2_setStrByValueWithMove = " << test2_ticks << std::endl;
	std::cout << "ticks in test3_setStrByReference     = " << test3_ticks << std::endl;
	std::cout << "ticks in test4_setStrByRValue        = " << test4_ticks << std::endl;
	std::cout << "ticks in test5_setStrByRValueWithMove= " << test5_ticks << std::endl;
	
	std::cout << "final counter = " << myObj.getCounter() << std::endl;
}

int main()
{
	//testForVSProfiler();
	testByTimings();
}
