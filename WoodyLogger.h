/*
  Copyright (c) 2019 by NASa Qian <nasacj@nasacj.net>
  This file is part of the EventLogger library.

  This software is distributed under BSD 3-Clause License.
  The full license agreement can be found in the LICENSE file.

  This software is distributed without any warranty.
*/

//
// Created by nasacj on 2019-06-03.
//

#ifndef WOODYLOGGER_H
#define WOODYLOGGER_H

#include <stdint.h>
#include <iostream>

#define WOODY_LOGGER

namespace woodycxx {

enum LOGGER_LEVEL : uint32_t
{
    FAULT   = 1,
    ERROR   = 2,
    WARN    = 3,
    INFO    = 4,
    DEBUG   = 5,
    TRACE   = 6
};

class WoodyLogger {
public:
    static void Init(FILE* out_file);
    static void Init(const char* file_name, bool isEnableStdOut = true);
    static void StartLogger(int cpu = -1);
    static void StopLogger();
    static void SetLogLevel(LOGGER_LEVEL);
    static LOGGER_LEVEL GetLogLevel();
    static void WoodyLog(LOGGER_LEVEL level, const char *file, int line, const char *format, ...);

    WoodyLogger() = delete;
    WoodyLogger(WoodyLogger&) = delete;
};

#ifdef WOODY_LOGGER

#define WOODY_LOGGER_START(x) \
do \
{ \
    woodycxx::WoodyLogger::StartLogger(x); \
} \
while(0)

#define WOODY_LOGGER_INIT(x, args...) \
do \
{ \
    woodycxx::WoodyLogger::Init(x, ##args); \
} \
while(0)

#define WOODY_LOGGER_STOP() \
do \
{ \
    woodycxx::WoodyLogger::StopLogger(); \
} \
while(0)

#define WOODY_LOGGER_LEVEL(x) \
do \
{ \
    woodycxx::WoodyLogger::SetLogLevel(x); \
} \
while(0)

#define LOG_FAULT(fmt, args...) \
do \
{ \
    if (woodycxx::WoodyLogger::GetLogLevel() >= woodycxx::FAULT) \
    { \
        woodycxx::WoodyLogger::WoodyLog(woodycxx::FAULT, nullptr, -1, fmt, ##args); \
    } \
} while (0)

#define LOG_ERROR(fmt, args...) \
do \
{ \
    if (woodycxx::WoodyLogger::GetLogLevel() >= woodycxx::ERROR) \
    { \
        woodycxx::WoodyLogger::WoodyLog(woodycxx::ERROR, nullptr, -1, fmt, ##args); \
    } \
} while (0)

#define LOG_WARN(fmt, args...) \
do \
{ \
    if (woodycxx::WoodyLogger::GetLogLevel() >= woodycxx::WARN) \
    { \
        woodycxx::WoodyLogger::WoodyLog(woodycxx::WARN, nullptr, -1, fmt, ##args); \
    } \
} while (0)

#define LOG_INFO(fmt, args...) \
do \
{ \
    if (woodycxx::WoodyLogger::GetLogLevel() >= woodycxx::INFO) \
    { \
        woodycxx::WoodyLogger::WoodyLog(woodycxx::INFO, nullptr, -1, fmt, ##args); \
    } \
} while (0)

#define LOG_DEBUG(fmt, args...) \
do \
{ \
    if (woodycxx::WoodyLogger::GetLogLevel() >= woodycxx::DEBUG) \
    { \
        woodycxx::WoodyLogger::WoodyLog(woodycxx::DEBUG, __FILE__, __LINE__, fmt, ##args); \
    } \
} while (0)

#define LOG_TRACE(fmt, args...) \
do \
{ \
    if (woodycxx::WoodyLogger::GetLogLevel() >= woodycxx::TRACE) \
    { \
        woodycxx::WoodyLogger::WoodyLog(woodycxx::TRACE, __FILE__, __LINE__, fmt, ##args); \
    } \
} while (0)

#else
#define WOODY_LOGGER_START()
#define WOODY_LOGGER_INIT(x, args...)
#define WOODY_LOGGER_STOP()
#define WOODY_LOGGER_LEVEL(x)
#define LOG_FAULT(fmt, args...)
#define LOG_ERROR(fmt, args...)
#define LOG_WARN(fmt, args...)
#define LOG_INFO(fmt, args...)
#define LOG_DEBUG(fmt, args...)
#define LOG_TRACE(fmt, args...)

#endif



} // end of namespace woodycxx


#endif //EVENTLOGGER_WOODYLOGGER_H
