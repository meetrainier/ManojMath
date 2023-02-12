#pragma once
//#include <concepts>//(C++20)//Fundamental library concepts
#include <coroutine>////(C++20)

//Coroutine support library
//Utilities library
//Coroutines library
#include <any>

//(C++17)

//std::any class

#include <bitset>

//std::bitset class template

#include <chrono>



//C++ time utilites
//#include <compare>

////(C++20)

//Three - way comparison operator support
#include <csetjmp>

//Macro(and function) that saves(and jumps) to an execution context
#include <csignal>

//Functions and macro constants for signal management
//context
#include <cstdarg>

//Handling of variable length argument lists

#include <cstddef>

//Standard macrosand typedefs
#include <cstdlib>

//General purpose utilities : program control, dynamic memory allocation, random numbers, sortand search
#include <ctime>

//C - style time / date utilites
//#include <expected>//(C++23)

//std::expected class template
#include <functional>

//Function objects, Function invocations, Bind operationsand Reference wrappers
#include <initializer_list>


//std::initializer_list class template
//#include <optional>//(C++17)

//std::optional class template

//#include <source_location>//(C++20)

//Supplies means to obtain source code location
//context
#include <tuple>

//

//std::tuple class template
//context
#include <type_traits>

//

//Compile - time type information
#include <typeindex>

//

//std::type_index

#include <typeinfo>

//Runtime type information utilities
#include <utility>

//Various utility components
#include <variant>

//(C++17)

//std::variant class template
//#include <version> ////(C++20)//Supplies implementation - dependent library information
#include <memory>

//High - level memory management utilities
#include <memory_resource>

//(C++17)

//Polymorphic allocators and memory resources

#include <new>

//Low - level memory management utilities

#include <scoped_allocator>

//

//Nested allocator class
//Numeric limits

#include <cfloat>
#include <cinttypes>
#include <climits>
#include <cstdint>
#include <limits>
//#include <stdfloat>
#include <cassert>
#include <cerrno>
#include <exception>


//#include <stacktrace>
#include <stdexcept>
#include <system_error>
#include <cctype>
#include <charconv>
#include <cstring>
#include <cuchar>
#include <cwchar>
#include <cwctype>
//#include <format>////(C++20)
#include <string>
#include <string_view>//(C++17)
#include <array>
#include <deque>
//#include <flat_map>//(C++23)
//std::flat_map and std::flat_multimap container adaptors
//#include <flat_set>//(C++23)

//std::flat_set and std::flat_multiset container adaptors

#include <forward_list>

//std::forward_list container

#include <list>

//std::list container

#include <map>

//std::map and std::multimap associative containers

//#include <mdspan>//(C++23)
#include<queue>
//std::queue and std::priority_queue container adaptors
#include <set>

//std::set and std::multiset associative containers

//#include <span>//(C++20)

//std::span view

#include <stack>

//std::stack container adaptor

#include <unordered_map>



//std::unordered_map and std::unordered_multimap unordered associative containers

#include <unordered_set>



//std::unordered_set and std::unordered_multiset unordered associative containers

#include <vector>

//std::vector container
//Iterators library

#include <iterator>

//Range iterators
//Ranges library

//#include <generator>//(C++23)

//std::generator class template

//#include <ranges>//(C++20)

//Range access, primitives, requirements, utilitiesand adaptors
//Algorithms library

#include <algorithm>

#include <execution>//(C++17)

//Predefined execution policies for parallel versions of the algorithms
//Numerics library

//#include <bit>//(C++20)

//Bit manipulation functions

#include <cfenv>
//Floating - point environment access functions

#include <cmath>
//Common mathematics functions

#include <complex>
//Complex number type
//#include <numbers>//(C++20)

//Math constants

#include <numeric>

//Numeric operations on values in ranges

#include <random>

////Random number generators and distributions

#include <ratio>

//Compile - time rational arithmetic

#include <valarray>

//Class for representingand manipulating arrays of values
//Localization library

#include <clocale>

//C localization utilities

//#include <codecvt>//(deprecated in C++17)
//Unicode conversion facilities

#include <locale>

//Localization utilities
//Input / output library

#include <cstdio>

//C - style input - output functions
#include <fstream>

//std::basic_fstream, std::basic_ifstream, std::basic_ofstream class templatesand several typedefs
#include <iomanip>

//Helper functions to control the format of inputand output
#include <ios>

//std::ios_base class, std::basic_ios class templateand several typedefs
#include <iosfwd>

//Forward declarations of all classes in the input / output library
#include <iostream>//Several standard stream objects
#include <istream>//std::basic_istream class template and several typedefs
#include <ostream>

//std::basic_ostream, std::basic_iostream class templatesand several typedefs
//#include <print> //(C++23)//Formatted output library including std::print
//#include <spanstream>//(C++23) //std::basic_spanstream, std::basic_ispanstream, std::basic_ospanstream class templatesand typedefs
#include  <sstream>
//std::basic_stringstream, std::basic_istringstream, std::basic_ostringstream class templatesand several typedefs
#include <streambuf>

//std::basic_streambuf class template
#include <strstream>
//(deprecated in C++98)//std::strstream, std::istrstream, std::ostrstream

//#include <syncstream> ////(C++20)//std::basic_osyncstream, std::basic_syncbuf, and typedefs
//Filesystem library
#include <filesystem>//(C++17)

//std::path classand supporting functions
//Regular Expressions library
#include  <regex>

//

//Classes, algorithmsand iterators to support regular expression processing
//Atomic Operations library
#include <atomic>

//

//Atomic operations library
//Thread support library
#include <barrier>

////(C++20)

//Barriers
#include <condition_variable>
//
//Thread waiting conditions
#include <future>//Primitives for asynchronous computations
#include <latch> ////(C++20)

#include <mutex>//
//Mutual exclusion primitives

#include <semaphore>////(C++20)

//Semaphores
//<shared_mutex>(C++14)//Shared mutual exclusion primitives
#include <stop_token> ////(C++20)

//Stop tokens for std::jthread
#include <thread> //std::thread classand supporting functions