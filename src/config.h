/*
 * Configuration related header.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * stogpp is released under the GPL 3.0 or later license (see LICENSE).
 * Go to the project repo here:
 * https://gitlab.com/keebenthusiast/stogpp
 *
 * Written by: Christian Kissinger
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "inih/ini.h"

/* Useful Constants */
#define CONF_LOCATION ((const char *)"/etc/stog/config.ini")

#ifdef DEBUG
#include "log/log.h"
#define CONF_LOCATION ((const char *)"resources/stog.ini")
#define DEF_CERT_LOC ((const char *)"resources/test.pem")
#define DEF_DB_LOC ((const char *)"resources/test.db")
#else
#define CONF_LOCATION ((const char *)"/etc/stog/config.ini")
#define DEF_CERT_LOC ((const char *)"/etc/stog/stogcert.pem")
#define DEF_DB_LOC ((const char *)"/var/lib/stog/stog.db")
#endif

// sections
#define NETWORK ((const char *)"network")
#define DATABASE ((const char *)"database")

// names
#define PORT ((const char *)"port")
#define BUF_SIZE ((const char *)"buffer_size")
#define KEEP_ALIVE ((const char *)"keep_alive")
#define CLIENT_COUNT ((const char *)"client_count")
#define CERTIFICATE ((const char *)"certificate_location")
#define DB_LOC ((const char *)"db_location")

enum {

  // section lens
  NETWORK_LEN = 8,
  DATABASE_LEN = 9,

  // name lens
  PORT_LEN = 5,
  BUF_SIZE_LEN = 12,
  KEEP_ALIVE_LEN = 11,
  CLIENT_COUNT_LEN = 13,
  CERTIFICATE_LEN = 21,
  DB_LOC_LEN = 12,

};

/**
 * @typedef config
 * @brief configuration parser struct
 */
typedef struct {
  uint16_t port;
  uint32_t buffer_size;
  uint32_t keep_alive;
  uint32_t client_count;
  const char *cert_loc;
  const char *db_loc;
} config;

/* prototypes */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize configuration variable, to ini file.
 *
 * @param cfg the config struct where configuration will be stored.
 * @param loc the config file location.
 *
 * @note check the return value and handle accordingly.
 *
 * returns 1 for any error that may occur,
 * returns 0 otherwise.
 */
int parse_configuration(config *cfg, const char *loc);

#ifdef __cplusplus
}
#endif

#endif
