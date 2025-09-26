/*
 [The "BSD licence"] Copyright (c) 2013 Sam Harwell All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted
 provided that the following conditions are met: 1. Redistributions of source code must retain the
 above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in
 binary form must reproduce the above copyright notice, this list of conditions and the following
 disclaimer in the documentation and/or other materials provided with the distribution. 3. The name
 of the author may not be used to endorse or promote products derived from this software without
 specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */

/** C 2011 grammar built from the C11 Spec */

// $antlr-format alignTrailingComments true, columnLimit 150, minEmptyLines 1, maxEmptyLinesToKeep 1, reflowComments false, useTab false
// $antlr-format allowShortRulesOnASingleLine false, allowShortBlocksOnASingleLine true, alignSemicolons hanging, alignColons hanging

grammar Orc;

@header {
    #include "OrcParserBase.h"
}

options {
    superClass = OrcParserBase;
    contextSuperClass = OrcRuleContext;
}

program
    : rootDeclaration*
    ;

rootDeclaration
    // | classDefinition
    // | functionDefinition
    : packageStatement
    | includeStatement
    | importStatement
    | structDefinition
    | enumDefinition
    | classDefinition
    | extensionDefinition
    | globalVarDeclaration
    | globalFunctionDefinition
    | emptyStatement
    ;

arguments
    : '(' (singleExpression (',' singleExpression)* ','?)? ')'
    ;

expressionSequence
    : singleExpression (',' singleExpression)*
    ;

closureExpression
    : '^' type Id? argumentsDeclaration block
    ;

singleExpression
    // Split to try `new Date()` first, then `new Date`.
    : singleExpression arguments                                  # CallExpression
    | singleExpression '++'                                       # PostIncrementExpression
    | singleExpression '--'                                       # PostDecreaseExpression
    | closureExpression                                           # labelClosureExpression
    | singleExpression '[' singleExpression ']'                   # MemberIndexExpression
    | singleExpression ('.' | '->') '#'? Id                       # MemberDotExpression
    | New Id arguments                                            # NewExpression
    | '&' singleExpression                                        # GetAddressExpression
    | '*' singleExpression                                        # DerefExpression
    | '++' singleExpression                                       # PreIncrementExpression
    | '--' singleExpression                                       # PreDecreaseExpression
    | '+' singleExpression                                        # UnaryPlusExpression
    | '-' singleExpression                                        # UnaryMinusExpression
    | '~' singleExpression                                        # BitNotExpression
    | '!' singleExpression                                        # NotExpression
    | singleExpression ('*' | '/' | '%') singleExpression         # MultiplicativeExpression
    | singleExpression ('+' | '-') singleExpression               # AdditiveExpression
    | singleExpression '??' singleExpression                      # CoalesceExpression
    | singleExpression ('<<' | '>>' | '>>>') singleExpression     # BitShiftExpression
    | singleExpression ('<' | '>' | '<=' | '>=') singleExpression # RelationalExpression
    | singleExpression Instanceof singleExpression                # InstanceofExpression
    // | singleExpression In singleExpression                                 # InExpression
    | singleExpression ('==' | '!=' | '===' | '!==') singleExpression      # EqualityExpression
    | singleExpression '&' singleExpression                                # BitAndExpression
    | singleExpression '^' singleExpression                                # BitXOrExpression
    | singleExpression '|' singleExpression                                # BitOrExpression
    | singleExpression '&&' singleExpression                               # LogicalAndExpression
    | singleExpression '||' singleExpression                               # LogicalOrExpression
    | singleExpression '?' singleExpression ':' singleExpression           # TernaryExpression
    | '(' type ')' singleExpression                                        # CastExpression
    | <assoc = right> singleExpression '=' singleExpression                # AssignmentExpression
    | <assoc = right> singleExpression assignmentOperator singleExpression # AssignmentOperatorExpression
    // | Import '(' singleExpression ')'                                      # ImportExpression
    // | singleExpression templateStringLiteral                               # TemplateStringExpression // ECMAScript 6
    // | yieldStatement                                                       # YieldExpression          // ECMAScript 6
    | This    # ThisExpression
    | Id      # IdentifierExpression
    | Super   # SuperExpression
    | literal # LiteralExpression
    // | arrayLiteral                                                         # ArrayLiteralExpression
    // | objectLiteral                                                        # ObjectLiteralExpression
    | '(' expressionSequence ')' # ParenthesizedExpression
    ;

assignmentOperator
    : '*='
    | '/='
    | '%='
    | '+='
    | '-='
    | '<<='
    | '>>='
    | '>>>='
    | '&='
    | '^='
    | '|='
    | '**='
    | '??='
    ;

emptyStatement
    : ';'
    ;

structDefinition
    : 'struct' Id '{' structMember* '}'
    ;

structMember
    : type Id arraySizeDeclaration? eos
    | functionPointerVarDeclaration eos
    ;

//变量声明,只支持单个变量
arraySizeDeclaration
    : '[' DecimalLiteral ']'
    ;

varDeclaration
    : Static? type Id arraySizeDeclaration? ('=' singleExpression)?
    | Static? functionPointerVarDeclaration
    ;

statement
    : closureExpression eos
    | varDeclaration eos
    | scopeStatement
    | block
    | continueStatement
    | breakStatement
    | selectionStatement
    | returnStatement
    | iterationStatement
    | singleExpression eos
    | emptyStatement
    ;

continueStatement
    : Continue eos
    ;

breakStatement
    : Break eos
    ;

returnStatement
    : Return singleExpression? eos
    ;

scopeStatement
    : singleExpression ('~' | '.') block
    ;

iterationStatement
    : While singleExpression block
    // | Do statement While '(' singleExpression ')' ';'
    | For '(' forCondition ')' block
    | For forCondition block
    ;

forCondition
    : (varDeclaration | singleExpression?) ';' singleExpression? ';' singleExpression?
    ;

selectionStatement
    : 'if' singleExpression block ('else if' singleExpression block)* ('else' block)?
    ;

block
    : '{' statement* '}'
    ;

type
    : typeQualifier? primitiveType arraySizeDeclaration?
    // | type '(' '*'+ ')' '(' argumentsDeclaration ')'
    // | functionType
    | closureType
    | pointer
    | ref
    | typeQualifier? Struct? Id
    ;

closureType
    : '^' type argumentsDeclaration //这是闭包
    ;

//用于解析clang 生成的函数类型
// char *(char*, int)
functionTypeArg
    : type Id?
    ;

attribute
    : '__attribute__' '(' '(' Id ')' ')'
    ;

functionType
    : type argumentsDeclaration attribute*
    ;

typeQualifier
    : Const
    | 'restrict'
    | 'volatile'
    | '_Atomic'
    ;

pointer
    : typeQualifier? (primitiveType | (Struct? Id)) (typeQualifier* '*' typeQualifier*)+
    ;

ref
    : Struct? Id '@'
    ;

primitiveType
    : 'int'
    | 'short'
    | 'float'
    | 'double'
    | 'char'
    | 'bool'
    | 'void'
    | 'long'
    | 'long' 'long'
    | 'long' 'double'
    | 'unsigned' 'char'
    | 'unsigned' 'int'
    | 'unsigned' 'short'
    | 'unsigned' 'long'
    | 'unsigned' 'long' 'long'
    ;

enumDefinition
    : Enum Id '{' enumItem (',' enumItem)* ','? '}' eos
    ;

enumItem
    : Id ('=' DecimalLiteral)?
    ;

extensionDefinition
    : Extension Id extensionBlock
    ;

extensionBlock
    : '{' (methodDeclaration)* '}'
    ;

classDefinition
    : Class Refc? Id (Extends Id)? classDefinitionBlock eos
    ;

classDefinitionBlock
    : '{' (classFieldDeclaration | methodDeclaration)* '}'
    ;

classFieldDeclaration
    : type Id arraySizeDeclaration? assignRightPart? eos
    | functionPointerVarDeclaration assignRightPart? eos
    ;

methodDeclaration
    : functionDefinition
    | externFunctionDeclaration
    ;

//赋值右边
assignRightPart
    : '=' singleExpression
    ;

argumentDeclaration
    : type Id?
    | functionPointerVarDeclaration
    ;

argumentsDeclaration
    : '(' (argumentDeclaration (',' argumentDeclaration)*)? ','? ')'
    |
    ;

functionPointerVarDeclaration
    : type '(' '*'+ Id? ')' argumentsDeclaration attribute*
    ;

functionDefinition
    : type Id argumentsDeclaration block
    ;

globalFunctionDefinition
    : Static? functionDefinition
    | Static? externFunctionDeclaration
    ;

globalVarDeclaration
    : varDeclaration eos
    ;

//外部函数声明
externFunctionDeclaration
    : Extern type Id argumentsDeclaration eos
    ;

importStatement
    // : 'import' StringLiteral eos
    : 'import' '*' 'from' StringLiteral eos
    | 'import type' '*' 'from' StringLiteral eos
    ;

includeStatement
    : '#include' includePathCharacters eos
    ;

includePathCharacters
    : '<' (~'>')* '>'
    | StringLiteral
    ;

packageStatement
    : 'package' Id eos
    ;

literal
    : NullLiteral
    | BooleanLiteral
    | DecimalLiteral
    | HexIntegerLiteral
    | OctalIntegerLiteral
    | BinaryIntegerLiteral
    | StringLiteral
    | CharLiteral
    ;

//---------------lexer----------------
/// Keywords

Break
    : 'break'
    ;

Do
    : 'do'
    ;

Instanceof
    : 'instanceof'
    ;

// Typeof     : 'typeof';
Case
    : 'case'
    ;

Else
    : 'else'
    ;

New
    : 'new'
    ;

// Var        : 'var';
// Catch      : 'catch';
// Finally    : 'finally';
Return
    : 'return'
    ;

Void
    : 'void'
    ;

Continue
    : 'continue'
    ;

For
    : 'for'
    ;

// Switch     : 'switch';
While
    : 'while'
    ;

// Debugger   : 'debugger';
// Function_  : 'function';
This
    : 'self'
    ;

// With       : 'with';
// Default    : 'default';
If
    : 'if'
    ;

// Throw      : 'throw';
// Delete     : 'delete';
// In         : 'in';
// Try        : 'try';
// As         : 'as';
From
    : 'from'
    ;

// Of         : 'of';
// Yield      : 'yield';
// YieldStar  : 'yield*';

/// Future Reserved Words

Struct
    : 'struct'
    ;

Class
    : 'class'
    ;

Enum
    : 'enum'
    ;

Extends
    : 'extends'
    ;

Extern
    : 'extern'
    ;

Super
    : 'super'
    ;

Extension
    : 'extension'
    ;

Const
    : 'const'
    ;

Export
    : 'export'
    ;

Import
    : 'import'
    ;

Static
    : 'static'
    ;

// Type : 'type';

Async
    : 'async'
    ;

Await
    : 'await'
    ;

Refc
    : 'refc'
    ;

NullLiteral
    : 'null'
    | 'NULL'
    ;

BooleanLiteral
    : 'true'
    | 'false'
    ;

DecimalLiteral
    : DecimalIntegerLiteral '.' [0-9] [0-9_]* 'f'?
    | '.' [0-9] [0-9_]* 'f'?
    | DecimalIntegerLiteral 'L'?
    | 'nan'
    | 'infinity'
    ;

HexIntegerLiteral
    : '0' [xX] [0-9a-fA-F] HexDigit*
    ;

OctalIntegerLiteral
    : '0' [oO] [0-7] [_0-7]*
    ;

BinaryIntegerLiteral
    : '0' [bB] [01] [_01]*
    ;

fragment DecimalIntegerLiteral
    : '0'
    | [1-9] [0-9_]*
    ;

StringLiteral
    : (
        '"' DoubleStringCharacter* '"'
        // | '\'' SingleStringCharacter* '\''
    )
    ;

CharLiteral
    : '\'' SingleStringCharacter '\''
    ;

Id
    : [a-zA-Z_] [a-zA-Z_0-9]*
    ;

fragment DoubleStringCharacter
    : ~["\\\r\n]
    | '\\' EscapeSequence
    ;

fragment SingleStringCharacter
    : ~['\\\r\n]
    | '\\' EscapeSequence
    ;

fragment EscapeSequence
    : CharacterEscapeSequence
    | '0' // no digit ahead! TODO
    | HexEscapeSequence
    | UnicodeEscapeSequence
    | ExtendedUnicodeEscapeSequence
    ;

fragment CharacterEscapeSequence
    : SingleEscapeCharacter
    | NonEscapeCharacter
    ;

fragment HexEscapeSequence
    : 'x' HexDigit HexDigit
    ;

fragment UnicodeEscapeSequence
    : 'u' HexDigit HexDigit HexDigit HexDigit
    | 'u' '{' HexDigit HexDigit+ '}'
    ;

fragment ExtendedUnicodeEscapeSequence
    : 'u' '{' HexDigit+ '}'
    ;

fragment SingleEscapeCharacter
    : ['"\\bfnrtv]
    ;

fragment NonEscapeCharacter
    : ~['"\\bfnrtv0-9xu\r\n]
    ;

fragment HexDigit
    : [_0-9a-fA-F]
    ;

// anyLineTerminator: LineTerminator*;
// LineTerminator: [\r\n];
CloseBrace
    : '}'
    ;

LineTerminator
    : [\r\n\u2028\u2029] -> channel(HIDDEN)
    ;

Whitespace
    : [ \t]+ -> channel(HIDDEN)
    ;

BlockComment
    : '/*' .*? '*/' -> channel(HIDDEN)
    ;

LineComment
    : '//' ~[\r\n]* [\r\n]+ -> channel(HIDDEN)
    ;

eos
    : ';'
    | EOF
    | {this->lineTerminatorAhead()}?
    | {this->closeBrace()}?
    ;