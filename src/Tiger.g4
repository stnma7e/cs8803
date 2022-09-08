grammar Tiger;

tiger_program : PROGRAM ID LET decl_segment BEGIN funct_list END ;

decl_segment : type_decl_list var_decl_list ;

type_decl_list : type_decl type_decl_list
               | ;

var_decl_list : var_decl var_decl_list
              | ;

funct_list : funct funct_list
          | ;

type_decl : TYPE ID TASSIGN type SEMICOLON ;

type : base_type
     | ARRAY OPENBRACK INTLIT CLOSEBRACK OF base_type
     | ID ;

base_type : INT
          | FLOAT ;

var_decl : storage_class id_list COLON type optional_init SEMICOLON ;

storage_class : VAR
              | STATIC ;

id_list : ID
        | ID COMMA id_list ;

optional_init : ASSIGN const
              | ;

funct : FUNCTION ID OPENPAREN param_list CLOSEPAREN ret_type BEGIN stat_seq END ;

param_list : param param_list_tail
           | ;

param_list_tail : COMMA param param_list_tail
                | ;

ret_type : COLON type
         | ;

param : ID COLON type ;

stat_seq : stat
         | stat stat_seq ;

stat : value ASSIGN expr SEMICOLON
     | IF expr THEN stat_seq ENDIF SEMICOLON
     | IF expr THEN stat_seq ELSE stat_seq ENDIF SEMICOLON
     | WHILE expr DO stat_seq ENDDO SEMICOLON
     | FOR ID ASSIGN expr TO expr DO stat_seq ENDDO SEMICOLON
     | optprefix ID OPENPAREN expr_list CLOSEPAREN SEMICOLON
     | BREAK SEMICOLON
     | RETURN optreturn SEMICOLON
     | LET decl_segment BEGIN stat_seq END ;

optreturn : expr
          | ;
optprefix : value ASSIGN
          | ;

expr : const
     | value
     | expr binary_operator expr
     | OPENPAREN expr CLOSEPAREN ;

const : INTLIT | FLOATLIT ;

binary_operator : PLUS | MINUS
                | EQUAL | NEQUAL ;

expr_list : expr expr_list_tail
          | ;
expr_list_tail : COMMA expr expr_list_tail
               | ;

value : ID value_tail ;
value_tail : OPENBRACK value CLOSEBRACK
           | ;

PROGRAM : 'PROGRAM' ;
LET : 'LET' ;
BEGIN : 'BEGIN' ;
END : 'END' ;
TYPE : 'TYPE' ;
ARRAY : 'ARRAY' ;
OF : 'OF' ;
INT : 'INT' ;
FLOAT : 'FLOAT' ;
VAR : 'VAR' ;
STATIC : 'STATIC' ;
FUNCTION : 'FUNCTION' ;
IF : 'IF' ;
THEN : 'THEN' ;
ELSE : 'ELSE' ;
ENDIF : 'ENDIF' ;
WHILE : 'WHILE' ;
DO : 'DO' ;
ENDDO : 'ENDDO' ;
FOR : 'FOR' ;
ASSIGN : 'ASSIGN' ;
TO : 'TO' ;
BREAK : 'BREAK' ;
RETURN : 'RETURN' ;

INTLIT : [0-9]+ ;
FLOATLIT : [0-9]+'.'[0-9]* ;

TASSIGN : ':=' ;
COLON : ':' ;
SEMICOLON : ';' ;
COMMA : ',' ;
OPENPAREN : '(' ;
CLOSEPAREN : ')' ;
OPENBRACK : '[' ;
CLOSEBRACK : ']' ;

PLUS : '+' ;
MINUS : '-' ;
EQUAL : '=' ;
NEQUAL : '!=' ;
WS  :   [ \t\r\n]+ -> skip ;
