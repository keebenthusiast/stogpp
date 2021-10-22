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

// local includes
#include "database.hpp"

static int callback(void *param, int argc, char **argv, char **azColName) {

  Database *obj = reinterpret_cast<Database *>(param);

  for (int i = 0; i < argc; i++) {

#ifdef DEBUG
#endif

    obj->appendOutputStr((argv[i]) ? argv[i] : "NULL");

    if (i < (argc - 1)) {

      obj->appendOutputStr("|");
    } else {

      obj->appendOutputStr("\n");
    }
  }

  return 0;
}

Database::Database(std::string location) {

  this->output.clear();
  this->rc = sqlite3_open(location.c_str(), &this->db);
}

Database::~Database() {

  this->freeZErrMsg();
  this->output.clear();
  sqlite3_close(this->db);
}

int Database::execQuery(const std::string query) {

  this->output.clear();

  this->rc =
      sqlite3_exec(this->db, query.c_str(), callback, this, &this->zErrMsg);

  return this->rc;
}

std::string Database::getOutputStr() { return this->output; }

void Database::appendOutputStr(std::string str) {
  this->output = this->output.append(str);
}

int Database::getStatus() const { return this->rc; }

std::string Database::getFailureReason() const {
  return sqlite3_errmsg(this->db);
}

std::string Database::getZErrMsg() const { return this->zErrMsg; }

void Database::freeZErrMsg() {

  if (this->zErrMsg != NULL) {
    sqlite3_free(this->zErrMsg);
    this->zErrMsg = 0;
  }
}
