/*
 * SPDX-License-Identifier: BSD-3-Clause
 * Copyright (C) 2019-2021, Christian Kissinger
 * kiss-light Hub is released under the New BSD license (see LICENSE).
 * Go to the project repo here:
 * https://gitlab.com/kiss-light-project/Kiss-Light_Hub
 *
 * Written by: Christian Kissinger
 */

#ifndef ARGS_H_
#define ARGS_H_

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "config.h"
//#include "daemon.h"
#include "inih/ini.h"

#ifdef DEBUG
#include "log/log.h"
#endif

/* constants */
#define DAEMON_ARG ((const char *)"--daemon")                 // or -d
#define CONFIG_ARG ((const char *)"--config")                 // or -c
#define PORT_ARG ((const char *)"--port")                     // or -p
#define SERVER_BUF_ARG ((const char *)"--server-buffer")      // or -b
#define KEEP_ALIVE_ARG ((const char *)"--keep-alive")         // or -k
#define CLIENT_COUNT_ARG ((const char *)"--client-count")     // or -i
#define CERT_LOC_ARG ((const char *)"--certificate-location") // or -e
#define DB_LOC_ARG ((const char *)"--database-file")          // or -f
#define HELP_ARG ((const char *)"--help")                     // or -h

enum {

  DAEMON_ARG_LEN = 9,
  CONFIG_ARG_LEN = 9,
  PORT_ARG_LEN = 7,
  SERVER_BUF_ARG_LEN = 16,
  KEEP_ALIVE_ARG_LEN = 13,
  CLIENT_COUNT_ARG_LEN = 15,
  CERT_LOC_ARG_LEN = 23,
  DB_LOC_ARG_LEN = 16,
  HELP_ARG_LEN = 7,
};

/* prototypes */
#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @brief Process arguments passed in (from main).
 *
 * @param argc passing in argc from main would be easiest.
 * @param argv passing in argv from main would be easiest.
 * @param cfg passing in configuration struct
 *
 * @note Returns 0 for success, nonzero for error. returns -1
 * if running as a daemon failed
 */
int process_args(int argc, char **argv, config *cfg);

/**
 * @brief Displays the usage when -h or --help is specified.
 *
 * @param program_name just pass in argv[0] here.
 */
void usage(char *program_name);

#ifdef __cplusplus
}
#endif

#endif
