#ifndef CONFIG_H
#define CONFIG_H

#include<string>
#include<vector>
#include<exception>
#include<locale>
#include<codecvt>
#include<map>
#include<filesystem>
#include<fstream>

using std::string;
using std::wstring;
using std::basic_string;
using std::vector;
using std::runtime_error;
using std::stoi;
using std::stod;
using std::codecvt_utf8;
using std::wstring_convert;
using std::to_string;
using std::map;
using std::make_pair;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::stringstream;
using namespace std::filesystem;

typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long llong;
typedef unsigned long long ullong;
typedef unsigned char byte;

#ifndef interface
#define interface struct
#endif

#ifndef einterface
#define einterface struct __declspec(dllexport)
#define eclass class __declspec(dllexport)
#endif

#ifndef package
#define package struct __declspec(dllexport)
#endif

#endif