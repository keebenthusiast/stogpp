/*
 * Database class template here.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * stogpp is released under the GPL 3.0 or later license (see LICENSE).
 * Go to the project repo here:
 * https://gitlab.com/keebenthusiast/stogpp
 *
 * Written by: Christian Kissinger
 */

#ifndef DATABASE_H_
#define DATABASE_H_

// system includes
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>

// local includes
#include "sqlite3/sqlite3.h"

/**
 * @brief database class for usage.
 */

class Database {

public:
  Database(std::string location);

  virtual ~Database();

  int execQuery(const std::string query);

  /* regarding status's */
  int getStatus() const;

  std::string getFailureReason() const;

  std::string getZErrMsg() const;

private:
  sqlite3 *db;
  int rc;
  char *zErrMsg = 0;
};

#endif
