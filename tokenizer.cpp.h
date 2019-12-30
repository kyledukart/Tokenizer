template <class NumericType>
bool Tokenizer<NumericType>::getChar( char &ch ) {
  char tmp;

  // skip blanks
  while ( in.get( tmp ) && tmp == ' ' );

  // read a char
  if ( in.good( ) && tmp != '\n'&& tmp != '\0' ) {
    ch = tmp;
    return true; // if it is not a delimiter
  }
  else
    return false; // if it's a delimiter
}

template <class NumericType>
Token<NumericType> Tokenizer<NumericType>::getToken( ) {

  char ch, ch2;
  NumericType theValue;

  if ( getChar( ch ) == true ) {
    switch( ch ) {
    case '^':   prevToken = EXP;
                return EXP;
    case '/':   prevToken = DIV;
                return DIV;
    case '*':   prevToken = MULT;
                return MULT;
    case '(':   prevToken = OPAREN;
                return OPAREN;
    case ')':   prevToken = CPAREN;
                return CPAREN;
    case '+':   if (prevToken == OPAREN) {
                    prevToken = UN_PLUS;
                    return UN_PLUS;
                }
                else {
                    prevToken = PLUS;
                    return PLUS;
                }
    case '-':   if (prevToken != OPAREN) {
                    prevToken = MINUS;
                    return MINUS;
                }
                else {
                    prevToken = UN_MINUS;
                    return UN_MINUS;
                }
    case '%':   prevToken = MOD;
                return MOD;
    case '=':   getChar(ch2);
                if (ch2 == '='){
                    prevToken = EQ;
                    return EQ;
                }
                else {
                    in.putback(ch2);
                    if (prevToken == VAR_A) {
                    prevToken = ASSIGNA;
                    return ASSIGNA;
                    }
                    else if (prevToken == VAR_B) {
                    prevToken = ASSIGNB;
                    return ASSIGNB;
                    }
                    if (prevToken == VAR_C) {
                    prevToken = ASSIGNC;
                    return ASSIGNC;
                    }
                    else
                        cout << "Assignment operator must be used with a variable a, b, or c" << endl;
                }
    case '!': getChar(ch2);
              if ( ch2 == '=') {
                prevToken = NEQ;
                return NEQ;
              }
              else {
                in.putback(ch2);
                prevToken = NOT;
                return NOT;
              }
    case '&': getChar(ch2);
              if ( ch2 == '&' ) {
                prevToken = AND;
                return AND;
              }
              else {
                in.putback(ch2);
                prevToken = BITAND;
                return BITAND;
              }
    case '|': getChar(ch2);
              if ( ch2 == '|' ) {
                prevToken = OR;
                return OR;
              }
              else {
                in.putback(ch2);
                prevToken = BITOR;
                return BITOR;
              }
    case '>': getChar(ch2);
              if (ch2 == '=') {
                prevToken = GTEQ;
                return GTEQ;
              }
              else if (ch2 == '>') {
                prevToken = RSHIFT;
                return RSHIFT;
              }
              else {
                in.putback(ch2);
                prevToken = GT;
                return GT;
              }
    case '<': getChar(ch2);
              if (ch2 == '=') {
                prevToken = LTEQ;
                return LTEQ;
              }
              else if (ch2 == '<') {
                prevToken = LSHIFT;
                return LSHIFT;
              }
              else {
                in.putback(ch2);
                prevToken = LT;
                return LT;
              }
    case '~':   prevToken = BIT_COMP;
                return BIT_COMP;
    case 'a':   prevToken = VAR_A;
                return Token<NumericType>( VAR_A, 0 );
    case 'b':   prevToken = VAR_B;
                return Token<NumericType>( VAR_B, 0 );
    case 'c':   prevToken = VAR_C;
                return Token<NumericType>( VAR_C, 0 );
    default:
      in.putback( ch );
      if ( !( in >> theValue ) ) {
        cerr << "Parse error" << endl;
        return EOL;
      }
      prevToken = VALUE;
      return Token<NumericType>( VALUE, theValue );
    }
  }

  return EOL;
}
