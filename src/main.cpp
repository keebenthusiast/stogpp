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

// system includes
#include <iostream>
#include <string>

// local includes
#include "database.hpp"

// for debugging

#ifdef DEBUG
#include "log/log.h"
#endif

int main(int argc, char **argv) {

  std::cout << "Hello World!\n";

  // std::string tst = "test.dbi";
  std::string tst = "test.db";

  Database test(tst);
  Database thng(tst);

  if (test.getStatus()) {

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

  test.freeZErrMsg();

  return 0;
}
