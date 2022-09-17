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

stat : value ASSIGN expr SEMICOLON                              # ValueAssign
     | IF expr THEN stat_seq ENDIF SEMICOLON                    # IfThen
     | IF expr THEN stat_seq ELSE stat_seq ENDIF SEMICOLON      # IfThenElse
     | WHILE expr DO stat_seq ENDDO SEMICOLON                   # While
     | FOR ID ASSIGN expr TO expr DO stat_seq ENDDO SEMICOLON   # For
     | optprefix ID OPENPAREN expr_list CLOSEPAREN SEMICOLON    # OptAssign
     | BREAK SEMICOLON                                          # Break
     | RETURN optreturn SEMICOLON                               # Return
     | LET decl_segment BEGIN stat_seq END                      # Let
     ;

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

PROGRAM : 'program' ;
LET : 'let' ;
BEGIN : 'begin' ;
END : 'end' ;
TYPE : 'type' ;
ARRAY : 'array' ;
OF : 'of' ;
INT : 'int' ;
FLOAT : 'float' ;
VAR : 'var' ;
STATIC : 'static' ;
FUNCTION : 'function' ;
IF : 'if' ;
THEN : 'then' ;
ELSE : 'else' ;
ENDIF : 'endif' ;
WHILE : 'while' ;
DO : 'do' ;
ENDDO : 'enddo' ;
FOR : 'for' ;
ASSIGN : ':=' ;
TO : 'to' ;
BREAK : 'break' ;
RETURN : 'return' ;

INTLIT : [0-9]+ ;
FLOATLIT : [0-9]+'.'[0-9]* ;

TASSIGN : '=' ;
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

ID : [_a-zA-Z]+[_0-9a-zA-Z]* ;
