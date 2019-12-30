// Public routine that performs the evaluation. Examines the postfix machine
// to see if a single result is left and if so, return it; otherwise prints
// error.
template<class NumericType>
NumericType Evaluator<NumericType>::getValue( ) {

  Tokenizer<NumericType> tok( str );
  Token<NumericType> lastToken;

  do {
    lastToken = tok.getToken( );
    processToken( lastToken );
  } while ( lastToken.getType( ) != EOL );

  if ( postFixStack.empty( ) ) {
    cerr << "Missing operand!" << endl;
    return 0;
  }

  NumericType theResult = postFixStack.back( );
  postFixStack.pop_back( );
//  postFixVarStack.pop_back();
  if ( !postFixStack.empty( ) )
    cerr << "Warning: missing operators!" << endl;

  return theResult;
}

// After token is read, use operator precedence parsing algorithm to process
// it; missing opening parentheses are detected here.
template<class NumericType>
void Evaluator<NumericType>::
processToken( const Token<NumericType> &lastToken ) {
  TokenType topOp;
  TokenType lastType = lastToken.getType( );

  switch( lastType ) {
  case VALUE:
    postFixStack.push_back( lastToken.getValue( ) );
    postFixVarStack.push_back( ' ' );
    return;

  case VAR_A:
    postFixStack.push_back( var_a );
    postFixVarStack.push_back( 'a' );
    return;

  case VAR_B:
    postFixStack.push_back( var_b );
    postFixVarStack.push_back( 'b' );
    return;

  case VAR_C:
    postFixStack.push_back( var_c );
    postFixVarStack.push_back( 'c' );
    return;

  case CPAREN:
    while( ( topOp = opStack.back( ) ) != OPAREN &&
	   topOp != EOL )
      binaryOp( topOp );
    if ( topOp == OPAREN )
      opStack.pop_back( ); // get rid of opening parentheses
    else
      cerr << "Missing open parenthesis" << endl;
    break;

  default: // general operator case
    while ( PREC_TABLE[ lastType ].inputSymbol <=
	    PREC_TABLE[ topOp = opStack.back( ) ].topOfStack )
      binaryOp( topOp );

    if ( lastToken.getType( ) != EOL ) {
      opStack.push_back( lastType );
    }
    break;
  }
}

// Process an operator by taking two items off the postfix stack, applying
// the operator, and pushing the result.
// Print error if missing closing parenthesis or division by 0.
template<class NumericType>
void Evaluator<NumericType>::binaryOp( TokenType topOp ) {
  if ( topOp == OPAREN ) {
    cerr << "Unbalanced parentheses" << endl;
    opStack.pop_back( );
    return;
  }
  NumericType rhs = getTop( );
  NumericType lhs;
  if (topOp != UN_PLUS && topOp != UN_MINUS && topOp != NOT && topOp != BIT_COMP) {
    lhs = getTop( );
  }

  if ( topOp == EXP ) {
    postFixStack.push_back( NumericType( pow( lhs, rhs ) ) );
    postFixVarStack.push_back(' ');
  }
  else if ( topOp == PLUS ) {
    postFixStack.push_back( lhs + rhs );
    postFixVarStack.push_back(' ');
  }
  else if ( topOp == MINUS ) {
    postFixStack.push_back( lhs - rhs );
    postFixVarStack.push_back(' ');
  }
  else if ( topOp == MULT ) {
    postFixStack.push_back( lhs * rhs );
    postFixVarStack.push_back(' ');
  }
  else if ( topOp == DIV )
    if ( rhs != 0 ) {
      postFixStack.push_back( lhs / rhs );
      postFixVarStack.push_back(' ');
    }
    else {
      cerr << "Division by zero" << endl;
      postFixStack.push_back( lhs );
      postFixVarStack.push_back(' ');
    }
  else if (topOp == UN_PLUS) {
    postFixStack.push_back(rhs);
    postFixVarStack.push_back(' ');
  }
  else if (topOp == UN_MINUS) {
    postFixStack.push_back(rhs * -1);
    postFixVarStack.push_back(' ');
  }
  else if (topOp == NOT) {
    if (rhs == 0) {
      postFixStack.push_back(1);
      postFixVarStack.push_back(' ');
    }
    else {
      postFixStack.push_back(0);
      postFixVarStack.push_back(' ');
    }
  }
  else if (topOp == BIT_COMP) {
    postFixStack.push_back(~rhs);
    postFixVarStack.push_back(' ');
  }
  else if (topOp == ASSIGNA) {
        var_a = rhs;
        postFixStack.push_back(var_a);
        postFixVarStack.push_back(var_a);
    }
  else if (topOp == ASSIGNB) {
        var_b = rhs;
        postFixStack.push_back(var_b);
        postFixVarStack.push_back(var_b);
    }
  else if (topOp == ASSIGNC) {
        var_c = rhs;
        postFixStack.push_back(var_c);
        postFixVarStack.push_back(var_c);
    }
    else if ( topOp == MOD ) {
    postFixStack.push_back( lhs % rhs );
    postFixVarStack.push_back(' ');
    }
    else if ( topOp == BITAND ) {
    postFixStack.push_back( lhs & rhs );
    postFixVarStack.push_back(' ');
    }
    else if ( topOp == BITOR ) {
    postFixStack.push_back( lhs | rhs );
    postFixVarStack.push_back(' ');
    }
    else if ( topOp == GT ){
        if (lhs > rhs) {
            postFixStack.push_back( 1 );
            postFixVarStack.push_back(' ');
        }
        else {
            postFixStack.push_back( 0 );
            postFixVarStack.push_back(' ');
        }
    }
    else if ( topOp == LT ) {
        if (lhs < rhs) {
            postFixStack.push_back( 1 );
            postFixVarStack.push_back(' ');
        }
        else {
            postFixStack.push_back( 0 );
            postFixVarStack.push_back(' ');
        }
    }
    else if ( topOp == LSHIFT ) {
    postFixStack.push_back( lhs << rhs );
    postFixVarStack.push_back(' ');
    }
    else if ( topOp == RSHIFT ) {
    postFixStack.push_back( lhs >> rhs );
    postFixVarStack.push_back(' ');
    }
    else if ( topOp == LTEQ ){
        if (lhs <= rhs) {
            postFixStack.push_back( 1 );
            postFixVarStack.push_back(' ');
        }
        else {
            postFixStack.push_back( 0 );
            postFixVarStack.push_back(' ');
        }
    }
    else if ( topOp == GTEQ){
        if (lhs >= rhs) {
            postFixStack.push_back( 1 );
            postFixVarStack.push_back(' ');
        }
        else {
            postFixStack.push_back( 0 );
            postFixVarStack.push_back(' ');
        }
    }
    else if ( topOp == EQ ){
        if (lhs == rhs) {
            postFixStack.push_back( 1 );
            postFixVarStack.push_back(' ');
        }
        else {
            postFixStack.push_back( 0 );
            postFixVarStack.push_back(' ');
        }
    }
    else if ( topOp == NEQ ){
        if (lhs != rhs) {
            postFixStack.push_back( 1 );
            postFixVarStack.push_back(' ');
        }
        else {
            postFixStack.push_back( 0 );
            postFixVarStack.push_back(' ');
        }
    }
    else if ( topOp == AND ) {
    postFixStack.push_back( lhs && rhs );
    postFixVarStack.push_back(' ');
    }
    else if ( topOp == OR ) {
    postFixStack.push_back( lhs || rhs );
    postFixVarStack.push_back(' ');
    }

  opStack.pop_back( );
}

// top and pop the postfix machine stack; return the result.
// If the stack is empty, print an error message.
template<class NumericType>
NumericType Evaluator<NumericType>::getTop( ) {
  if ( postFixStack.empty( ) ) {
    cerr << "Missing operand" << endl;
    return 0;
  }

  NumericType tmp = postFixStack.back( );
  postFixStack.pop_back( );
  return tmp;
}
