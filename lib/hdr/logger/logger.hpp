#ifndef _YJ_LOG_H_
#define _YJ_LOG_H_

#include <ctime>
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdarg>
#include <iomanip>
#include <unistd.h>



#define LOG_LEVEL_OFF       0
#define LOG_LEVEL_FATAL     10
#define LOG_LEVEL_ERROR     20
#define LOG_LEVEL_WARN      30
#define LOG_LEVEL_INFO      40
#define LOG_LEVEL_DEBUG     50
#define LOG_LEVEL_TRACE     60
#define LOG_LEVEL_ALL       100

#define fatal(str, ...) writeLog(__FUNCTION__, __LINE__, LOG_LEVEL_FATAL, str, __VA_ARGS__)
#define error(str, ...) writeLog(__FUNCTION__, __LINE__, LOG_LEVEL_ERROR, str, __VA_ARGS__)
#define warn(str, ...) writeLog(__FUNCTION__, __LINE__, LOG_LEVEL_WARN, str, __VA_ARGS__)
#define info(str, ...) writeLog(__FUNCTION__, __LINE__, LOG_LEVEL_INFO, str, __VA_ARGS__)
#define debug(str, ...) writeLog(__FUNCTION__, __LINE__, LOG_LEVEL_DEBUG, str, __VA_ARGS__)
#define trace(str, ...) writeLog(__FUNCTION__, __LINE__, LOG_LEVEL_TRACE, str, __VA_ARGS__)

using namespace std; 

class Log {
private:
    FILE *fp; 
    int logLevel; 
    char* LOG_PATH;
    string getTimestamp();
    int OpenLogFile();
    void setLogLevelFromEnv();

public:
    Log(const char* LOG_NAME);
    Log(int level, const char* LOG_NAME);
    ~Log();
    void writeLog(const char *funcName, int line, int lv, const char *str, ...);
    void setLogLevel(int level);
    int getLogLevel();
};

extern Log *mlog;
static char LOG_FILE[100];
#endif /* _YJ_LOG_H_*/
