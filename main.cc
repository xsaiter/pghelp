// test

#include <iostream>
#include <string>
#include <string.h>
#include "pg_help.hh"

using namespace pghelp;

int main(int argc, char *argv[]) {
  pg_conn_s conn("host=127.0.0.1 port=5432 dbname=venus user=isa "
                 "password=1q2w3e connect_timeout=2");
  if (!conn.is_ok()) {
    std::cerr << "failed to open a connection to the database - "
              << conn.error_message() << std::endl;
    return 1;
  }

  pg_result_s r(conn, "select generate_series(10,20) as x;");
  if (!r.is_tuples_ok()) {
    std::cerr << "failed to execute sql query - " << r.error_message()
              << std::endl;
    return 1;
  }

  auto n = r.count();
  if (n == 11) {
    std::cout << "count - OK" << std::endl;
  } else {
    std::cout << "count - FAIL" << std::endl;
  }

  auto val = r.get_value(0, 0);
  if (strcmp(val, "10") == 0) {
    std::cout << "value - OK" << std::endl;
  } else {
    std::cout << "value - FAIL" << std::endl;
  }

  return 0;
}
