CompUnit -> Decl CompUnit
CompUnit -> ε
Decl -> ConstDecl
Decl -> VarOrFuncDecl
ConstDecl -> 'const' Type ConstDeclBody
VarOrFuncDecl -> Type Ident VarOrFuncDeclBody

Type -> 'int'
Type -> 'void'
ConstDeclBody -> Ident VarDeclbody

VarOrFuncDeclBody -> VarDeclbody 
VarOrFuncDeclBody -> FuncDeclBody

VarDeclbody -> ArraySizeDecl VarDecl

ArraySizeDecl -> '[' ArraySizeNum ']' ArraySizeDecl
ArraySizeDecl -> ε

ArraySizeNum -> ε
ArraySizeNum -> ConstExp

VarDecl -> ';'
VarDecl -> '=' VarInitValue ';'

VarInitValue -> ConstInitVal
VarInitValue -> '{' VarInitValue VarInitValueNext '}'

VarInitValueNext -> ',' VarInitValueNext
VarInitValueNext -> VarInitValue
VarInitValueNext -> ε

ConstInitVal -> ConstExp

ConstExp -> Exp

FuncDeclBody -> '(' FuncParamDecl FuncParamDeclNext ')' CodeBlock

FuncParamDecl -> ε
FuncParamDecl -> 'int' ArraySizeDecl Ident

FuncParamDeclNext -> ε
FuncParamDeclNext -> ',' FuncParamDeclNext
FuncParamDeclNext -> FuncParamDecl

CodeBlock -> '{' Stmts '}'

Stmts -> Stmt Stmts
Stmts -> ε

Stmt -> ε
Stmt -> Decl ';'
Stmt -> LVal '=' Exp ';'
Stmt -> Exp ';'
Stmt -> CodeBlock 
Stmt -> 'if' '(' Cond ')' Stmt ElseStmt 
Stmt -> 'while' '(' Cond ')' Stmt
Stmt -> 'break' ';'
Stmt -> 'continue' ';'
Stmt -> 'return' ReturnVal ';'

ReturnVal -> ε
ReturnVal -> Exp

ElseStmt -> 'else' Stmt
ElseStmt -> ε


Exp -> AddExp
ConstExp -> AddExp

Cond -> LOrExp
LVal -> Ident ArrayAcces

ArrayAcces -> '[' Exp ']' ArrayAcces
ArrayAcces -> ε

PrimaryExp -> '(' Exp ')' 
PrimaryExp -> LVal
PrimaryExp -> Number
UnaryExp -> PrimaryExp 
UnaryExp -> Ident '(' FuncRParams FuncRParamsNext ')' 
UnaryExp -> UnaryOp UnaryExp

FuncRParams -> ε
FuncRParams -> Exp
FuncRParamsNext -> ε
FuncRParamsNext -> ',' FuncRParamsNext
FuncRParamsNext -> Exp

UnaryOp -> '+'
UnaryOp -> '-'
UnaryOp -> '!'
MulExp -> UnaryExp MulExpNext
MulExpNext -> ε
MulExpNext -> '*' MulExp MulExpNext
MulExpNext -> '/' MulExp MulExpNext
MulExpNext -> '%' MulExp MulExpNext

AddExp -> MulExp AddExpNext
AddExpNext -> ε
AddExpNext -> '+' AddExp AddExpNext
AddExpNext -> '-' AddExp AddExpNext

RelExp -> AddExp RelExpNext
RelExpNext -> ε
RelExpNext -> '<' RelExp RelExpNext
RelExpNext -> '>' RelExp RelExpNext
RelExpNext -> '<=' RelExp RelExpNext
RelExpNext -> '>=' RelExp RelExpNext

EqExp -> RelExp EqExpNext
EqExpNext -> ε
EqExpNext -> '==' EqExp EqExpNext
EqExpNext -> '!=' EqExp EqExpNext

LAndExp -> EqExp LAndExpNext
LAndExpNext -> ε
LAndExpNext -> '&&' EqExp LAndExpNext

LOrExp -> EqExp LOrExpNext
LOrExpNext -> '||' EqExp LOrExpNext
LOrExpNext -> ε

