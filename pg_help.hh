#ifndef PG_HELP_HH
#define PG_HELP_HH

#include <libpq-fe.h>

namespace pghelp {

class uncopyable_s {
protected:
  uncopyable_s() {}
  ~uncopyable_s() {}

private:
  uncopyable_s(const uncopyable_s &);
  uncopyable_s &operator=(const uncopyable_s &);
};

class pg_conn_s : private uncopyable_s {
public:
  explicit pg_conn_s(const char *conn_str) { c_ = PQconnectdb(conn_str); }

  pg_conn_s(PGconn *conn) { c_ = conn; }

  ~pg_conn_s() { PQfinish(c_); }

  bool is_ok() const noexcept { return PQstatus(c_) == CONNECTION_OK; }

  const char *error_message() const noexcept { return PQerrorMessage(c_); }

  PGconn *get() const noexcept { return c_; }

private:
  PGconn *c_;
};

class pg_result_s : private uncopyable_s {
public:
  pg_result_s(pg_conn_s &connection, const char *query) {
    r_ = PQexec(connection.get(), query);
  }

  explicit pg_result_s(PGresult *res) { r_ = res; }

  ~pg_result_s() { PQclear(r_); }

  const char *get_value(int tup_num, int field_num) const noexcept {
    return PQgetvalue(r_, tup_num, field_num);
  }

  bool is_null(int tup_num, int field_num) const noexcept {
    return PQgetisnull(r_, tup_num, field_num);
  }

  PGresult *get() const noexcept { return r_; }

  bool is_command_ok() const noexcept {
    return PQresultStatus(r_) == PGRES_COMMAND_OK;
  }

  bool is_tuples_ok() const noexcept {
    return (PQresultStatus(r_) == PGRES_TUPLES_OK);
  }

  int count() const noexcept { return PQntuples(r_); }

  const char *error_message() const noexcept {
    return PQresultErrorMessage(r_);
  }

private:
  PGresult *r_;
};
}

#endif // PG_HELP_HH
