CompUnit -> Decl CompUnit
CompUnit -> '$'
Decl -> ConstDecl
Decl -> VarOrFuncDecl
ConstDecl -> 'const' Type Ident VarDeclbody VarDeclNext
VarOrFuncDecl -> Type Ident VarOrFuncDeclBody VarDeclNext

VarDeclNext -> ',' Ident VarDeclbody VarDeclNext
VarDeclNext -> ';'
VarDeclNext -> ε

Type -> 'int'
Type -> 'void'

VarOrFuncDeclBody -> VarDeclbody
VarOrFuncDeclBody -> FuncDeclBody

VarDeclbody -> ArraySizeDecl VarInit

ArraySizeDecl -> '[' ArraySizeNum ']' ArraySizeDecl
ArraySizeDecl -> ε

ArraySizeNum -> ConstExp
ArraySizeNum -> ArrayPtrEmpty
ArrayPtrEmpty -> ε

VarInit -> ε
VarInit -> '=' VarInitValue 

VarInitValue -> ConstExp
VarInitValue -> '{' VarInitValue VarInitValueNext '}'

VarInitValueNext -> ',' VarInitValue VarInitValueNext
VarInitValueNext -> ε

FuncDeclBody -> '(' FuncParamDecl FuncParamDeclNext ')' CodeBlock

FuncParamDecl -> ε
FuncParamDecl -> 'int' Ident ArraySizeDecl
FuncParamDecl -> Ident ArraySizeDecl

FuncParamDeclNext -> ε
FuncParamDeclNext -> ',' FuncParamDecl FuncParamDeclNext

CodeBlock -> '{' Stmts '}'

Stmts -> Stmt Stmts
Stmts -> ε

Stmt -> Decl
Stmt -> Exp ';'
Stmt -> CodeBlock 
Stmt -> 'while' '(' Cond ')' Stmt
Stmt -> 'break' ';'
Stmt -> 'continue' ';'
Stmt -> 'return' ReturnVal ';'

Stmt -> 'if' '(' Cond ')' Stmt ElseStmt 

ReturnVal -> ε
ReturnVal -> Exp

ElseStmt -> 'else' Stmt
ElseStmt -> ε




Exp -> AssignExp
AssignExp -> AddExp AssignExpNext
ConstExp -> AddExp

AssignExpNext -> '=' AddExp
AssignExpNext -> ε

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
FuncRParamsNext -> ',' FuncRParams FuncRParamsNext


UnaryOp -> '+'
UnaryOp -> '-'
UnaryOp -> '!'
MulExp -> UnaryExp MulExpNext
MulExpNext -> ε
MulExpNext -> '*' UnaryExp MulExpNext
MulExpNext -> '/' UnaryExp MulExpNext
MulExpNext -> '%' UnaryExp MulExpNext

AddExp -> MulExp AddExpNext
AddExpNext -> ε
AddExpNext -> '+' MulExp AddExpNext
AddExpNext -> '-' MulExp AddExpNext

RelExp -> AddExp RelExpNext
RelExpNext -> ε
RelExpNext -> '<' AddExp RelExpNext
RelExpNext -> '>' AddExp RelExpNext
RelExpNext -> '<=' AddExp RelExpNext
RelExpNext -> '>=' AddExp RelExpNext

EqExp -> RelExp EqExpNext
EqExpNext -> ε
EqExpNext -> '==' RelExp EqExpNext
EqExpNext -> '!=' RelExp EqExpNext

LAndExp -> EqExp LAndExpNext
LAndExpNext -> ε
LAndExpNext -> '&&' EqExp LAndExpNext

LOrExp -> LAndExp LOrExpNext
LOrExpNext -> '||' LAndExp LOrExpNext
LOrExpNext -> ε

