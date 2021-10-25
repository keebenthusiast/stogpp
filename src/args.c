/*
 * Where command line arguments are processed.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * stogpp is released under the GPL 3.0 or later license (see LICENSE).
 * Go to the project repo here:
 * https://gitlab.com/keebenthusiast/stogpp
 *
 * Written by: Christian Kissinger,
 */

#include "args.h"

/**
 * @brief initialize struct value defaults
 *
 * @param cfg the config struct
 *
 * @note this function serves as a fallback should the ini file
 * be completely useless or even gone for whatever reason.
 */
static void initialize_config_struct(config *cfg) {
  cfg->port = 5033;
  cfg->buffer_size = 8192;
  cfg->keep_alive = 400;
  cfg->client_count = 16;
  cfg->cert_loc = strndup(DEF_CERT_LOC, strlen(DEF_CERT_LOC));
  cfg->db_loc = strndup(DEF_DB_LOC, strlen(DEF_DB_LOC));
}

int process_args(int argc, char **argv, config *cfg) {
  int rv = 0;
  int daemon_start = 0;

  /* start by initializing the config struct */
  initialize_config_struct(cfg);
  parse_configuration(cfg, CONF_LOCATION);

  if (argc >= 2) {
    /* a quick little shortcut that utilizes strncmp */
#define CMP(argi, arg, argl, args, argsl)                                      \
  strncasecmp(argv[argi], arg, argl) == 0 ||                                   \
      strncasecmp(argv[argi], args, argsl) == 0

    for (int i = 1; i < argc; i++) {
      if (CMP(i, DAEMON_ARG, DAEMON_ARG_LEN, "-d", 3)) {
        daemon_start = 1;
      } else if (CMP(i, CONFIG_ARG, CONFIG_ARG_LEN, "-c", 3)) {
        i++;
        parse_configuration(cfg, argv[i]);
      } else if (CMP(i, PORT_ARG, PORT_ARG_LEN, "-p", 3)) {
        i++;
        cfg->port = atoi(argv[i]);
      } else if (CMP(i, SERVER_BUF_ARG, SERVER_BUF_ARG_LEN, "-b", 3)) {
        i++;
        cfg->buffer_size = atoi(argv[i]);
      } else if (CMP(i, KEEP_ALIVE_ARG, KEEP_ALIVE_ARG_LEN, "-k", 3)) {
        i++;
        cfg->keep_alive = atoi(argv[i]);
      } else if (CMP(i, CLIENT_COUNT_ARG, CLIENT_COUNT_ARG_LEN, "-i", 3)) {
        i++;
        cfg->client_count = atoi(argv[i]);
      } else if (CMP(i, CERT_LOC_ARG, CERT_LOC_ARG_LEN, "-e", 3)) {
        i++;
        if (cfg->cert_loc != NULL) {
          free((char *)cfg->cert_loc);
          cfg->cert_loc = NULL;
        }

        cfg->cert_loc = strndup(argv[i], strlen(argv[i]));
      } else if (CMP(i, DB_LOC_ARG, DB_LOC_ARG_LEN, "-f", 3)) {
        i++;
        if (cfg->db_loc != NULL) {
          free((char *)cfg->db_loc);
          cfg->db_loc = NULL;
        }

        cfg->db_loc = strndup(argv[i], strlen(argv[i]));
      } else if (CMP(i, HELP_ARG, HELP_ARG_LEN, "-h", 3)) {
        // PRINT USAGE HERE!
        rv = 1;
        break;
      } else {
        fprintf(stdout, "unknown arg: %s\n", argv[i]);
        rv = 1;
        break;
      }
    }
  }

  if (daemon_start && !rv) {
#ifdef DEBUG
    log_trace("WILL RUN AS A DAEMON!");
#endif
    fprintf(stdout, "server daemonizing\n");
    // rv = run_as_daemon();
    if (rv) {
      rv = -1;
    }
  }

  return rv;
}

void usage(char *program_name) {
  fprintf(stdout, "Usage: %s [args]...\n", program_name);
  fprintf(stdout, "run stog server\n\n");
  fprintf(stdout, "When no args are passed in, the server will "
                  "start without daemonizing.\n\n");
  fprintf(stdout, "args: (order does not matter)\n");
  fprintf(stdout, "-d, --daemon                "
                  "Have server execute as a daemon\n");
  fprintf(stdout, "-c, --config                "
                  "specify ini configuration file\n");
  fprintf(stdout, "-p, --port                  "
                  "specify port for server to listen on\n");
  fprintf(stdout, "-b, --server-buffer         "
                  "specify server buffer length in bytes\n");
  fprintf(stdout, "-k, --keep-alive            "
                  "specify keep alive time in seconds\n");
  fprintf(stdout, "-i, --client-count          "
                  "specify number of clients allowed to connect "
                  "at once\n");
  fprintf(stdout, "-e, --certificate-location  "
                  "specify location of certificate pem file\n");
  fprintf(stdout, "-f, --database-file         "
                  "specify database file to use\n");
  fprintf(stdout, "-h, --help                  "
                  "shows usage\n\n");
  fprintf(stdout, "Examples:\n");
  fprintf(stdout,
          "%s \n"
          "Execute server with defaults.\n\n",
          program_name);
  fprintf(stdout,
          "%s -d \n"
          "Execute server with defaults but as a daemon.\n\n",
          program_name);
  fprintf(stdout,
          "%s --port 2425 -d -k 600 \n"
          "Execute server as a daemon with most defaults, but\n"
          "listen on port 2425 and set keep_alive to 600 seconds\n\n",
          program_name);
}
