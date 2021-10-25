/*
 * Strictly for configuration related information.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * stogpp is released under the GPL 3.0 or later license (see LICENSE).
 * Go to the project repo here:
 * https://gitlab.com/keebenthusiast/stogpp
 *
 * Written by: Christian Kissinger
 */

#include "config.h"

/*******************************************************************************
 * Everything related to configuration will reside here.
 ******************************************************************************/

/**
 * @note refer to the inih/ini.c and inih/ini.h for more information
 * and implementation on how it works.
 */
static int ini_callback_handler(void *user, const char *section,
                                const char *name, const char *value) {
  config *pconfig = (config *)user;

  /* a quick little shortcut that utilizes strncmp */
#define MATCH(s, sl, n, nl)                                                    \
  strncasecmp(section, s, sl) == 0 && strncasecmp(name, n, nl) == 0

  // Network
  if (MATCH(NETWORK, NETWORK_LEN, PORT, PORT_LEN)) {
    pconfig->port = atoi(value);
  } else if (MATCH(NETWORK, NETWORK_LEN, BUF_SIZE, BUF_SIZE_LEN)) {
    pconfig->buffer_size = atoi(value);
  } else if (MATCH(NETWORK, NETWORK_LEN, KEEP_ALIVE, KEEP_ALIVE_LEN)) {
    pconfig->keep_alive = atoi(value);
  } else if (MATCH(NETWORK, NETWORK_LEN, CLIENT_COUNT, CLIENT_COUNT_LEN)) {
    pconfig->client_count = atoi(value);
  } else if (MATCH(NETWORK, NETWORK_LEN, CERTIFICATE, CERTIFICATE_LEN)) {
    /* ensure string is empty */
    if (pconfig->cert_loc != NULL) {
      free((char *)pconfig->cert_loc);
      pconfig->cert_loc = NULL;
    }

    pconfig->cert_loc = strndup(value, strlen(value));
  }
  // Database
  else if (MATCH(DATABASE, DATABASE_LEN, DB_LOC, DB_LOC_LEN)) {
    if (pconfig->db_loc != NULL) {
      free((char *)pconfig->db_loc);
      pconfig->db_loc = NULL;
    }

    pconfig->db_loc = strndup(value, strlen(value));
  }
  // Default case
  else {
    return 0; /* unknown section/name, error */
  }
  return 1;
}

int parse_configuration(config *cfg, const char *loc) {
  int rv = 0;
  if (ini_parse(loc, ini_callback_handler, cfg) < 0) {

#ifdef DEBUG
    log_warn("Cannot load config file '%s'", loc);
#endif

    rv = 1;
  }

  return rv;
}
