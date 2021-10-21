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

  std::string tst = "test.db";

  Database test(tst);

  if (test.getStatus()) {

    std::cout << "cannot open database\n"
              << "Reason: " << test.getFailureReason() << std::endl;
    return 1;

  } else {

    std::cout << "Success! opened " << tst << "\n";
    std::cout << "failure suggests: " << test.getFailureReason() << "\n";
  }

  std::string query = "SELECT * FROM device;";
  std::cout << "execing this query: " << query << std::endl;

  int ret = test.execQuery(query);

  std::cout << "exec returned: " << ret << "\n";

  return 0;
}
