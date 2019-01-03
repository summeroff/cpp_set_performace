// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <list>

#ifdef DEBUG
const int set_repeats = 10000;
const int tests_repeats = 10;
#else
const int set_repeats = 10000000;
const int tests_repeats = 5;
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
	void setStrByReferenceWithMove(const std::string& _str)
	{
		stra = std::move(_str);
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
	void setStrByPointer(const std::string* _str_ptr)
	{
		stra = *_str_ptr;
		counter++;
	}
	void setStrBySharedPtr(const std::shared_ptr<std::string> _str_ptr)
	{
		stra = *_str_ptr;
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

inline void test6_setStrByReferenceWithMove(myClass & myObj)
{
	for (int i = 0; i < set_repeats; i++)
	{
		myObj.beforeSet();
		myObj.setStrByReferenceWithMove(test_str);
		myObj.afterSet();
	}
}

inline void test7_setStrByPointerPtr(myClass & myObj)
{
	for (int i = 0; i < set_repeats; i++)
	{
		myObj.beforeSet();
		myObj.setStrByPointer(&test_str);
		myObj.afterSet();
	}
}

inline void test8_setStrBySharedPtr(myClass & myObj)
{
	auto ptr = std::make_shared<std::string>(test_str);
	for (int i = 0; i < set_repeats; i++)
	{
		myObj.beforeSet();
		myObj.setStrBySharedPtr(ptr);
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
		test6_setStrByReferenceWithMove(myObj);
		test7_setStrByPointerPtr(myObj);
		test8_setStrBySharedPtr(myObj);
	}

	std::cout << "final counter = " << myObj.getCounter() << std::endl;
}

void print_ticks(const std::string & name, const std::list<int> &ticks)
{
	int ticks_sum = 0;
	int ticks_zeroes = 0;
	int ticks_max = 0;
	for (int tick : ticks)
	{
		ticks_sum += tick;
		if (tick == 0)
		{
			ticks_zeroes++;
		}
		if (ticks_max == 0 || ticks_max < tick)
		{
			ticks_max = tick;
		}
	}
	std::cout << "ticks in " << std::setw(32) << name << " = " << std::setw(5) << ticks_sum << ", zeroes = " << std::setw(3) << ticks_zeroes << " , max " << std::setw(5) << ticks_max << std::endl;
}

void testByTimings()
{
	myClass myObj;

	DWORD ticksend;
	DWORD ticksstart;
	std::list< int> test1_ticks;
	std::list< int> test2_ticks;
	std::list< int> test3_ticks;
	std::list< int> test4_ticks;
	std::list< int> test5_ticks;
	std::list< int> test6_ticks;
	std::list< int> test7_ticks;
	std::list< int> test8_ticks;

	for (int i = 0; i < tests_repeats; i++)
	{
		ticksstart = GetTickCount();
		test1_setStrByValue(myObj);
		ticksend = GetTickCount();
		test1_ticks.push_back(ticksend - ticksstart);

		ticksstart = GetTickCount();
		test2_setStrByValueWithMove(myObj);
		ticksend = GetTickCount();
		test2_ticks.push_back(ticksend - ticksstart);

		ticksstart = GetTickCount();
		test3_setStrByReference(myObj);
		ticksend = GetTickCount();
		test3_ticks.push_back(ticksend - ticksstart);

		ticksstart = GetTickCount();
		test4_setStrByRValue(myObj);
		ticksend = GetTickCount();
		test4_ticks.push_back(ticksend - ticksstart);

		ticksstart = GetTickCount();
		test5_setStrByRValueWithMove(myObj);
		ticksend = GetTickCount();
		test5_ticks.push_back(ticksend - ticksstart);

		ticksstart = GetTickCount();
		test6_setStrByReferenceWithMove(myObj);
		ticksend = GetTickCount();
		test6_ticks.push_back(ticksend - ticksstart);

		ticksstart = GetTickCount();
		test7_setStrByPointerPtr(myObj);
		ticksend = GetTickCount();
		test7_ticks.push_back(ticksend - ticksstart);

		ticksstart = GetTickCount();
		test8_setStrBySharedPtr(myObj);
		ticksend = GetTickCount();
		test8_ticks.push_back(ticksend - ticksstart);
	}


	print_ticks("test1_setStrByValue", test1_ticks);
	print_ticks("test2_setStrByValueWithMove", test2_ticks);
	print_ticks("test3_setStrByReference", test3_ticks);
	print_ticks("test4_setStrByRValue", test4_ticks);
	print_ticks("test5_setStrByRValueWithMove", test5_ticks);
	print_ticks("test6_setStrByReferenceWithMove", test6_ticks);
	print_ticks("test7_setStrByPointerPtr", test7_ticks);
	print_ticks("test8_setStrBySharedPtr", test8_ticks);

	std::cout << "final counter = " << myObj.getCounter() << std::endl;
}

int main()
{
	std::cout << "tests_repeats=" << tests_repeats << ", set_repeats=" << set_repeats << std::endl;

	//testForVSProfiler();
	testByTimings();
}
