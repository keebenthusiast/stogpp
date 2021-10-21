/*
 * Database class implementation here.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * stogpp is released under the GPL 3.0 or later license (see LICENSE).
 * Go to the project repo here:
 * https://gitlab.com/keebenthusiast/stogpp
 *
 * Written by: Christian Kissinger
 */

#include "database.hpp"

static int callback(void *param, int argc, char **argv, char **azColName) {

  for (int i = 0; i < argc; i++) {
    if (i < (argc - 1)) {
      printf("%s|", argv[i] ? argv[i] : "NULL");
    } else {
      printf("%s\n", argv[i] ? argv[i] : "NULL");
    }
  }

  return 0;
}

Database::Database(std::string location) {

  this->rc = sqlite3_open(location.c_str(), &this->db);
}

Database::~Database() { sqlite3_close(this->db); }

int Database::execQuery(const std::string query) {

  std::cout << "Before exec statement\n";
  this->rc = sqlite3_exec(this->db, query.c_str(), callback, 0, &this->zErrMsg);
  std::cout << "After exec statement\n";

  return this->rc;
}

int Database::getStatus() const { return this->rc; }

std::string Database::getFailureReason() const {
  return sqlite3_errmsg(this->db);
}

std::string Database::getZErrMsg() const { return this->zErrMsg; }
