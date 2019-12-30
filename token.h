#ifndef TOKEN_H
#define TOKEN_H

using namespace std;

enum TokenType {
  EOL,         // end of line                   the same as the original
  VALUE,       // constant                      the same as the original
  OPAREN,      // (                             the same as the original
  CPAREN,      // )                             the same as the original

  NOT,         // !                             logical negation
  BIT_COMP,    // ~                             bit comp

  UN_MINUS,    // -                             unary negation
  UN_PLUS,     // +                             unary positive

  MULT,        // *                             the same as the original
  DIV,         // /                             the same as the original
  MOD,     // %

  PLUS,        // -                             the same as the original
  MINUS,       // +                             the same as the original

  LSHIFT,     // <<
  RSHIFT,     // >>
  LT,          // <
  LTEQ,          // <=
  GT,          // >
  GTEQ,          // >=

  EQ,       // ==
  NEQ,    // !=

  BITAND,     // &
  EXP,     // ^
  BITOR,     // |

  AND,     // &&
  OR,      // ||
  VAR_A,       // variable a
  VAR_B,       // variable b
  VAR_C,       // variable c
  ASSIGNA,    // =
  ASSIGNB,
  ASSIGNC
};

// the class definition is the same as the original
template <class NumericType>
class Token {
 public:
  Token( TokenType tt = EOL, const NumericType & nt = 0 )
    : theType( tt ), theValue( nt ) {
  }

  TokenType getType( ) const {
    return theType;
  }
  const NumericType &getValue( ) const {
    return theValue;
  }

 private:
  TokenType   theType;
  NumericType theValue;
};

#endif
