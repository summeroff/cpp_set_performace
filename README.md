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
Main function calls one of this functions `testByTimings();`	or `testForVSProfiler();`.

First just run tests calls and check cpu ticks. 

Second can be used to run with MS Visual Studio profiler. 

## Results 
```
ticks in test1_setStrByValue         = 909
ticks in test2_setStrByValueWithMove = 607
ticks in test3_setStrByReference     = 141
ticks in test4_setStrByRValue        = 952
ticks in test5_setStrByRValueWithMove= 563
```
It looks like that a pass by reference is a fastest way. 

This numbers cannot be used to determine how fast but only to compare which way is relatively faster.
