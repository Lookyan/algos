#ifndef LOGGER
#define LOGGER
#include <iostream>
#include <fstream>
using namespace std;
const char* fileLog = "log.txt";

class Logger
{
public:
    Logger(const char* time,const char* fileName, const char* funcName, int line, const char* args);
    Logger(const char* time,const char* fileName, const char* funcName, int line, const int* int_arg);
    Logger(const char* time,const char* fileName, const char* funcName, int line, int args);
    ~Logger();
private:
    const char* _time;
    const char* _fileName;
    const char* _funcName;
    const char* _args;
    const int* _int_arg;
    int int_args;
};

Logger::Logger(const char* time,const char* fileName,
               const char* funcName, int line, const char* args)
{
    ofstream file(fileLog, ios::app);
    _time = time;
    _fileName = fileName;
    _funcName = funcName;
    _args = args;
    file << _time<< " Entering " << _funcName << "() - ("<< _fileName << ":" << line << ")" << endl;
    file <<"Arguments are "<< _args <<endl;
}

Logger::Logger(const char* time,const char* fileName,
               const char* funcName, int line, const int* int_arg)
{
    ofstream file(fileLog, ios::app);
    _time = time;
    _fileName = fileName;
    _funcName = funcName;
    _int_arg = int_arg;
    file << _time<< " Entering " << _funcName << "() - ("<< _fileName << ":" << line << ")" << endl;
    file <<"Arguments are "<< _int_arg  <<endl;
}

Logger::Logger(const char* time, const char* fileName,
               const char* funcName, int line, int args)
{
    ofstream file(fileLog, ios::app);
    _time = time;
    _fileName = fileName;
    _funcName = funcName;
    int_args = args;
    file << _time<< " Entering " << _funcName << "() - ("<< _fileName << ":" << line << ")" << endl;
    file <<"Arguments are "<< int_args <<endl;
}

Logger::~Logger()
{
    ofstream file(fileLog, ios::app);
    file << _time <<  " Leaving  " << _funcName <<"() - (" << _fileName << ")" << endl << endl <<endl;
}

#ifdef DEBUG
#define LOG_TRACE(argument) Logger logger(__TIME__,__FILE__,__FUNCTION__, __LINE__,argument);
#else
#define LOG_TRACE
#endif

#endif // LOGGER
