 

       
#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include "Lexer.h"
#include "funcs.h"
/* for the test */

Lexer lexer;
LexerToken token;
void setUp(void){
	initLexer(&lexer);
}
void tearDown(void){
}

void test_initLexer(void){
	Lexer lex;
	initLexer(&lex);
	TEST_ASSERT_EQUAL_CHAR('\0',lex.current_char);
	TEST_ASSERT_EQUAL_CHAR('\0',lex.previous_char);
	TEST_ASSERT_NULL(lex.inputBuffer.buf);
	TEST_ASSERT_EQUAL(0,lex.inputBuffer.len);
}

void test_isWhitespace(void){
	TEST_ASSERT_EQUAL(0,is_ws('\0'));
	TEST_ASSERT_EQUAL(0,isWhitespace(&lexer));
	TEST_ASSERT_EQUAL(1,is_ws(' '));
	lexer.current_char= ' ';
	TEST_ASSERT_EQUAL(1,isWhitespace(&lexer));
}

void test_isEOF(void){
	TEST_ASSERT_EQUAL(0,isEOF(&lexer));
	lexer.current_char = EOF;
	TEST_ASSERT_EQUAL(1,isEOF(&lexer));
}
void test_isEOS(void){
	TEST_ASSERT_EQUAL(1,isEOS(&lexer));
	lexer.current_char = EOF;
	TEST_ASSERT_EQUAL(0,isEOS(&lexer));	
}
void test_isNewline(void){
	TEST_ASSERT_EQUAL(0,isNewline(&lexer));
	lexer.current_char = '\n';
	TEST_ASSERT_EQUAL(1,isNewline(&lexer));
}
void test_pass_ws(void){
	lexer.inputBuffer = *buffer_from_filename("/Users/scotty/Programming/sclex/test/TestLexer.c");
	getNextChar(&lexer);
	TEST_ASSERT_EQUAL_CHAR(' ', lexer.current_char);
	TEST_ASSERT_EQUAL(isWhitespace(&lexer),is_ws(' '));
	pass_ws(&lexer);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.current_char);
	TEST_ASSERT_EQUAL(0,isWhitespace(&lexer));
	
}

void test_getNextChar(void){
	TEST_ASSERT_EQUAL_CHAR('\0',lexer.current_char);
	TEST_ASSERT_EQUAL_CHAR('\0',lexer.previous_char);
	TEST_ASSERT_EQUAL(0,lexer.inputBuffer.len);
	lexer.inputBuffer = *buffer_from_filename("/Users/scotty/Programming/sclex/test/TestLexer.c");
	getNextChar(&lexer);
	pass_ws(&lexer);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.current_char);
	TEST_ASSERT_EQUAL_CHAR('\n',lexer.previous_char);
	getNextChar(&lexer);
	TEST_ASSERT_EQUAL_CHAR('i',lexer.current_char);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.previous_char);
	
/*	TEST_ASSERT_EQUAL_CHAR('\0',lexer.current_char);*/
}

void test_pushBackChar(void){
	lexer.inputBuffer = *buffer_from_filename("/Users/scotty/Programming/sclex/test/TestLexer.c");
	getNextChar(&lexer);
	pass_ws(&lexer);
	TEST_ASSERT_EQUAL_CHAR('\n',lexer.previous_char);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.current_char);
	getNextChar(&lexer);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.previous_char);
	TEST_ASSERT_EQUAL_CHAR('i',lexer.current_char);
	pushBackChar(&lexer);	
	TEST_ASSERT_EQUAL_CHAR('#',lexer.previous_char);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.current_char);
}

void test_matchedNextToken(void){
	lexer.inputBuffer = *buffer_from_filename("/Users/scotty/Programming/sclex/test/TestLexer.c");
	getNextChar(&lexer);
	pass_ws(&lexer);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.current_char);
	token.lexeme = "hi";
	token.id = 3;
	token.type = 3;
	TEST_ASSERT_NULL(matchedNextToken(&lexer,token).lexeme);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.current_char);
	TEST_ASSERT_EQUAL_CHAR('\n',lexer.previous_char);
	token.lexeme = "#n";
	token.id = 4;

	TEST_ASSERT_NULL(matchedNextToken(&lexer,token).lexeme);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.current_char);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.previous_char);
	token.lexeme = "#i";
	token.id = 5;
	
	TEST_ASSERT_EQUAL_STRING("#i",matchedNextToken(&lexer,token).lexeme);
	TEST_ASSERT_EQUAL_CHAR('n',lexer.current_char);
	TEST_ASSERT_EQUAL_CHAR('i',lexer.previous_char);
	
}
void test_readRawStringUntilToken(void){
	char * decs;
	decs = NULL;
	lexer.inputBuffer = *buffer_from_filename("/Users/scotty/Programming/sclex/test/TestLexer.c");
	getNextChar(&lexer);
	pass_ws(&lexer);
	token.lexeme = "/*";
	token.id = 3;
	token.type = 3;
	while(!(matchedNextToken(&lexer,token).lexeme))
		getNextChar(&lexer);
	token.lexeme = "*/";
	token.id = 3;
	token.type = 3;
	decs = readRawStringUntilToken(&lexer,token);
	TEST_ASSERT_EQUAL_CHAR('\n',lexer.current_char);
	TEST_ASSERT_EQUAL_STRING(" for the test ",decs);
}


void test_getNextToken(void){
	LexerToken tempToken;
	lexer.inputBuffer = *buffer_from_filename("/Users/scotty/Programming/sclex/example/lex.l");
	getNextChar(&lexer);
	while(!isEOF(&lexer)){
		tempToken = getNextToken(&lexer);
		if(tempToken.lexeme){
			printf("token found: %s\n",tempToken.lexeme);
		}
		getNextChar(&lexer);
	}
}
