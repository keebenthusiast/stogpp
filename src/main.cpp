/*
 * Main function here.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * stogpp is released under the GPL 3.0 or later license (see LICENSE).
 * Go to the project repo here:
 * https://gitlab.com/keebenthusiast/stogpp
 *
 * Written by: Christian Kissinger
 */

#include "main.hpp"

int main(int argc, char **argv) {

#ifdef DEBUG
  FILE *lg = fopen(LOGLOCATION, "w");

  if (lg == NULL) {
    fprintf(stderr, "Failed to open log file %s\n", LOGLOCATION);

    fclose(lg);

    return 1;
  }

  log_add_fp(lg, DEBUG_LEVEL);
  log_trace("Stog Logger initialized");
#endif

  /*
   * Process args
   */
  config *cfg = (config *)malloc(sizeof(config));

  int arg_result = process_args(argc, argv, cfg);

  if (arg_result != 0) {
#ifdef DEBUG
    log_debug("Failed to process arg, exiting...");
#endif
    if (arg_result) {
      usage(argv[0]);
    } else if (arg_result < 0) {
      fprintf(stdout, "Failed to execute as daemon, exiting...\n");
    }

    /* Clean up as this is a big deal. */
    if (cfg->db_loc != NULL) {
      free((void *)cfg->db_loc);
      cfg->db_loc = NULL;
    }

    if (cfg->cert_loc != NULL) {
      free((void *)cfg->cert_loc);
      cfg->cert_loc = NULL;
    }

    free(cfg);

#ifdef DEBUG
    fclose(lg);
#endif

    return 1;
  }

#ifdef DEBUG
  log_trace("args processed");
#endif

  /*
  std::cout << "Hello World!\n";

  // std::string tst = "test.dbi";
  std::string tst = "test.db";

  Database test(tst);
  Database thng(tst);

  if (test.getStatusCode() != SQLITE_OK) {

    std::cout << "cannot open database\n"
              << "Reason: " << test.getFailureReason() << std::endl;
    return 1;

  } else {

    std::cout << "Success! opened " << tst << "\n";
    std::cout << "failure suggests: " << test.getFailureReason() << "\n";
  }

  std::string query = "SELECT * FROM device;";
  std::string queryThng = "SELECT dev_name,dev_type FROM device;";
  std::cout << "execing this query: " << query << std::endl;

  int ret = test.execQuery(query);
  int ret2 = thng.execQuery(queryThng);

  std::cout << "test: \n" << test.getOutputStr();
  std::cout << "thing: \n" << thng.getOutputStr();

  std::cout << "exec returned: " << ret << "\n";
  if (ret != SQLITE_OK) {

    std::cout << "reason: " << test.getZErrMsg() << std::endl;
    test.freeZErrMsg();
  }

  test.freeZErrMsg();*/

  /* upon exit, clean up */
  if (cfg->db_loc != NULL) {
    free((void *)cfg->db_loc);
    cfg->db_loc = NULL;
  }

  if (cfg->cert_loc != NULL) {
    free((void *)cfg->cert_loc);
    cfg->cert_loc = NULL;
  }

  free(cfg);

#ifdef DEBUG
  fclose(lg);
#endif

  return 0;
}
