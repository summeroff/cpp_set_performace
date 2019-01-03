# cpp_set_performace
Check how fast different types of passing values to a set function

Five different ways to pass value to a set function. Which use combination of `(std::string _str)`, `(const std::string& _str)`, `std::move(_str)` and  `(const std::string&& _str)`.

## Build 
```
mkdir build 
cd build 
cmake -G "Visual Studio 15 2017 Win64"  ../   
cmake --build . --target ALL_BUILD --config Release -- /p:CharacterSet=Unicode
```

## Running 
Main function calls one of this functions `testByTimings();` or `testForVSProfiler();`.

First function just run tests calls and check cpu ticks. 

Second function can be used to run with MS Visual Studio profiler. 

## Results 
```
tests_repeats=5, set_repeats=10000000
ticks in              test1_setStrByValue =  4062, zeroes =   0 , max   828
ticks in      test2_setStrByValueWithMove =  3408, zeroes =   0 , max   688
ticks in          test3_setStrByReference =   578, zeroes =   0 , max   125
ticks in             test4_setStrByRValue =  4078, zeroes =   0 , max   828
ticks in     test5_setStrByRValueWithMove =  3484, zeroes =   0 , max   703
ticks in  test6_setStrByReferenceWithMove =   593, zeroes =   0 , max   125
ticks in         test7_setStrByPointerPtr =   578, zeroes =   0 , max   125
ticks in          test8_setStrBySharedPtr =  1094, zeroes =   0 , max   250
```
It looks like that `pass by reference` and `by pointer` is a fastest way. 

Also using `std::move(_str)` can make pass by value a bit faster but nowhere as fast as pass by reference. 

This numbers cannot be used to determine how fast but only to compare which way is relatively faster. 

Also this is synthetic and no way to say what amount of speedup can real code get. 
