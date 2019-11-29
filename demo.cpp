/*
  Copyright (c) 2014-2019 by NASa Qian <nasacj@nasacj.net>
  This file is part of the EventLogger library.

  This software is distributed under BSD 3-Clause License.
  The full license agreement can be found in the LICENSE file.

  This software is distributed without any warranty.
*/

//
// Created by nasacj on 2019-06-03.
//

#include "WoodyLogger.h"
#include <thread>
#include <unistd.h>

void PrintLogThread() {
    LOG_ERROR("PrintLogThread Join -->");
    LOG_ERROR("PrintLogThread END <---");
    usleep(1000);
}

int main() {
    WOODY_LOGGER_START();

    /*
     * WOODY_LOGGER_INIT marco is used to configure
     * the log output, it has 2 parameters:
     *  ("file_path_name", is_enalbe_output_to_stdout)
     *
     *  e.g.
     *  WOODY_LOGGER_INIT("./log.txt");
     *
     *  Will configure the log output into "./log.txt"
     *  file and also the stdout. If user want to turn-off
     *  the stdout:
     *
     *  WOODY_LOGGER_INIT("./log.txt", false); //disable stdout
     *
     *  User can also configure the FILE handler
     *  (e.g. stdout, stderr):
     *
     *  WOODY_LOGGER_INIT(stderr);
     *
     *  User can direct the file name to "/dev/null" and
     *  disable the stdout, then the log will NOT output any:
     *
     *  WOODY_LOGGER_INIT("/dev/null", false);
     *
     *  This is used in benchmark test.
     *
     *  If WOODY_LOGGER_INIT is not configured, it will output
     *  to stdout in default. As the demo shows bellow.
     */
    //WOODY_LOGGER_INIT("/dev/null", false);

    /*
     * There are 6 log levels as Strong to Week order:
     * FAULT, ERROR, WARN, INFO, DEBUG, TRACE
     *
     * Logger will only output the level which is stronger
     * than the current configured level.
     * e.g.
     *
     * If the level is setup to INFO, then DEBUG and TRACE
     * will not be output.
     *
     * WOODY_LOGGER_LEVEL() can be called in a thread which
     * means the log level can be controlled dynamically.
     * User can write a thread listen to a port as a Server.
     * The client process can connect to the server and
     * configure the level dynamically.
     */
    WOODY_LOGGER_LEVEL(woodycxx::DEBUG);

    /*
     * The output format
     *
     * DEBUG, TRACE Level:
     * [YYYY-MM-DD HH:mm:ss.nanoseconds] [LEVEL] [thread_id] [__FILE__: __LINE__] message
     *
     * FAULT, ERROR, WARN, INFO Level:
     * [YYYY-MM-DD HH:mm:ss.nanoseconds] [LEVEL] [thread_id] message
     *
     */
    LOG_TRACE("Test LOG_TRACE: %d", 12345);  // TRACE will output on DEBUG level
    LOG_DEBUG("Test LOG_DEBUG: %d", 23456);
    LOG_ERROR("Test LOG_ERROR: %d", 6543210);
    LOG_WARN ("Test LOG_WARN : %07d", 123);
    LOG_INFO ("Test LOG_INFO : %.5f", 1.0/3.0);
    LOG_FAULT("Test LOG_FAULT: %p", &PrintLogThread);

    std::thread print_thread1 = std::thread(PrintLogThread);
    print_thread1.join();

    usleep(10000);
    WOODY_LOGGER_STOP();
    return 0;
}

