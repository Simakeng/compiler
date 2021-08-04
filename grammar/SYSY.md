CompUnit -> Decl CompUnit
CompUnit -> '$'
Decl -> ConstDecl
Decl -> VarOrFuncDecl
ConstDecl -> 'const' Type Ident VarDeclbody
VarOrFuncDecl -> Type Ident VarOrFuncDeclBody

Type -> 'int'
Type -> 'void'

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

Stmt -> Decl
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




Exp -> AddExp AssignExpBody
ConstExp -> AddExp

AssignExpBody -> '=' AddExp
AssignExpBody -> ε

Cond -> LOrExp

ArrayAcces -> '[' Exp ']' ArrayAcces
ArrayAcces -> ε

PrimaryExp -> '(' Exp ')' 
PrimaryExp -> Number

LvalAux -> ArrayAcces
FuncCall -> '(' FuncRParams FuncRParamsNext ')' 

LvalAuxOrFuncCall -> LvalAux
LvalAuxOrFuncCall -> FuncCall

UnaryExp -> PrimaryExp 
UnaryExp -> Ident LvalAuxOrFuncCall
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

