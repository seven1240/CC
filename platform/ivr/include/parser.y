%token_type { double }

%left  PLUS MINUS.
%left  DIVIDE TIMES MOD.
%right POW NOT.

%include {
#include <assert.h>
#include <string.h>
#include <math.h>

#include "parser.h"

struct result_t {
  enum error_t {
    NOT_ACCEPTED,
    SYNTAX_ERROR,
    DIVIDE_BY_ZERO,
    STACK_OVERFLOW,
    RESULT_OVERFLOW,
    PARSE_ERROR,
    UNKNOWN_ERROR,
    ACCEPTED
  };

  double value;
  error_t error_type;

  result_t() : value(0), error_type(NOT_ACCEPTED) {}
  ~result_t() {}

  void check_val(double val) {
    if (!isfinite(val)) {
      error_type = RESULT_OVERFLOW;
    }
  }
};

}

%extra_argument { result_t *result }

%parse_failure {
  result->error_type = result_t::PARSE_ERROR;
}

%stack_overflow {
  result->error_type = result_t::STACK_OVERFLOW;
}

%syntax_error {
  result->error_type = result_t::SYNTAX_ERROR;
}

%parse_accept {
  if (result->error_type == result_t::NOT_ACCEPTED) {
    result->error_type = result_t::ACCEPTED;
  }
}

program ::= expr(A). {
  if (result->error_type == result_t::NOT_ACCEPTED &&
      isfinite(A)){
    result->value = A;
  } else {
    result->error_type = result_t::RESULT_OVERFLOW;
  }
}

expr(A) ::= expr(B) MINUS  expr(C). {
  A = B - C;
  result->check_val(A);
}
expr(A) ::= expr(B) PLUS   expr(C). {
  A = B + C;
  result->check_val(A);
}
expr(A) ::= expr(B) TIMES  expr(C). {
  A = B * C;
  result->check_val(A);
}
expr(A) ::= MINUS  expr(B). [NOT] { A = - B; }
expr(A) ::= PLUS   expr(B). [NOT] { A = B; }
expr(A) ::= expr(B) POW expr(C). {
  A = pow(B, C);
  result->check_val(A);
}
expr(A) ::= LP expr(B) RP. { A = B; }
expr(A) ::= expr(B) DIVIDE expr(C). {
  if (C != 0.0) {
    A = B / C;
    result->check_val(A);
  } else {
    result->error_type = result_t::DIVIDE_BY_ZERO;
  }
}
expr(A) ::= expr(B) MOD expr(C). {
  if (C != 0.0) {
    A = fmod(B, C);
    result->check_val(A);
  } else {
    result->error_type = result_t::DIVIDE_BY_ZERO;
  }
}

expr(A) ::= INTEGER(B). { A = B; }
