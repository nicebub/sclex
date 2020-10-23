 

       
#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lexer.h"
#include "funcs.h"
/* for the test */

Lexer lexer;
LStack Stack;

void setUp(void){
	initTokenStack(&Stack);
	initLexer(&lexer);
}
void tearDown(void){
}

void test_initTokenStack(void){
	LStack s;
	initTokenStack(&s);
	TEST_ASSERT_EQUAL(s.top,s.stack);
	TEST_ASSERT_EQUAL(s.top,&s.stack[0]);
	TEST_ASSERT_NULL(s.stack[0].lexeme);
	TEST_ASSERT_NULL(s.stack[STACK_SIZE-1].lexeme);
	
}
void test_pushTokenStack(void){
	LexerToken temp;
	TEST_ASSERT_EQUAL(Stack.top,Stack.stack);
	TEST_ASSERT_EQUAL(Stack.top,&Stack.stack[0]);
	TEST_ASSERT_NULL(Stack.stack[0].lexeme);
	temp.lexeme = "string of chars";
	pushTokenStack(&Stack,temp);
	TEST_ASSERT_EQUAL(Stack.top,&Stack.stack[1]);
	TEST_ASSERT_EQUAL_STRING(Stack.stack[0].lexeme,temp.lexeme);
}
void test_peekTokenStack(void){
	LexerToken temp,temp2;
	TEST_ASSERT_EQUAL(Stack.top,Stack.stack);
	TEST_ASSERT_EQUAL(Stack.top,&Stack.stack[0]);
	TEST_ASSERT_NULL(Stack.stack[0].lexeme);
	temp.lexeme = strdup("string of chars");
	temp2.lexeme= NULL;
	pushTokenStack(&Stack,temp);
	TEST_ASSERT_EQUAL(Stack.top,&Stack.stack[1]);
	TEST_ASSERT_EQUAL_STRING(Stack.stack[0].lexeme,temp.lexeme);
	temp2 = peekTokenStack(&Stack);
	TEST_ASSERT_EQUAL(Stack.top,&Stack.stack[1]);
	TEST_ASSERT_EQUAL_STRING(Stack.stack[0].lexeme,temp2.lexeme);
	
	free(temp.lexeme);
}
void test_popTokenStack(void){
	LexerToken temp,temp2;
	TEST_ASSERT_EQUAL(Stack.top,Stack.stack);
	TEST_ASSERT_EQUAL(Stack.top,&Stack.stack[0]);
	TEST_ASSERT_NULL(Stack.stack[0].lexeme);
	temp.lexeme = strdup("string of chars");
	temp2.lexeme= NULL;
	pushTokenStack(&Stack,temp);
	TEST_ASSERT_EQUAL(Stack.top,&Stack.stack[1]);
	TEST_ASSERT_EQUAL_STRING(Stack.stack[0].lexeme,temp.lexeme);
	temp2 = popTokenStack(&Stack);
	TEST_ASSERT_EQUAL(Stack.top,Stack.stack);
	TEST_ASSERT_NULL(Stack.stack[0].lexeme);
	TEST_ASSERT_EQUAL_STRING(temp.lexeme,temp2.lexeme);	
	free(temp.lexeme);
	
}





void test_initLexer(void){
	Lexer lex;
	initLexer(&lex);
	TEST_ASSERT_EQUAL_CHAR('\0',lex.current_char);
	TEST_ASSERT_EQUAL_CHAR('\0',lex.previous_char);
	TEST_ASSERT_NULL(lex.file);
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
	lexer.inputBuffer = *buffer_from_filename("test/TestLexer.c");
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
	TEST_ASSERT_NULL(lexer.file);
	TEST_ASSERT_EQUAL(0,lexer.inputBuffer.len);
	lexer.inputBuffer = *buffer_from_filename("test/TestLexer.c");
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
	lexer.inputBuffer = *buffer_from_filename("test/TestLexer.c");
	getNextChar(&lexer);
	pass_ws(&lexer);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.current_char);
	TEST_ASSERT_EQUAL_CHAR('\n',lexer.previous_char);
	getNextChar(&lexer);
	TEST_ASSERT_EQUAL_CHAR('i',lexer.current_char);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.previous_char);
	pushBackChar(&lexer);	
	TEST_ASSERT_EQUAL_CHAR('#',lexer.previous_char);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.current_char);
}

void test_matchedNextToken(void){
	lexer.inputBuffer = *buffer_from_filename("test/TestLexer.c");
	getNextChar(&lexer);
	pass_ws(&lexer);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.current_char);

	TEST_ASSERT_NULL(matchedNextToken(&lexer,"hi").lexeme);
	TEST_ASSERT_NULL(peekTokenStack(&lexer.tokenStack).lexeme);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.current_char);
	TEST_ASSERT_EQUAL_CHAR('\n',lexer.previous_char);

	TEST_ASSERT_NULL(matchedNextToken(&lexer,"#n").lexeme);
	TEST_ASSERT_NULL(peekTokenStack(&lexer.tokenStack).lexeme);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.current_char);
	TEST_ASSERT_EQUAL_CHAR('#',lexer.previous_char);
	
	TEST_ASSERT_EQUAL_STRING("#i",matchedNextToken(&lexer,"#i").lexeme);
	TEST_ASSERT_EQUAL_STRING("#i",peekTokenStack(&lexer.tokenStack).lexeme);
	TEST_ASSERT_EQUAL_CHAR('n',lexer.current_char);
	TEST_ASSERT_EQUAL_CHAR('i',lexer.previous_char);
	
}
void test_readRawStringUntilToken(void){
	char * decs;
	decs = NULL;
	lexer.inputBuffer = *buffer_from_filename("test/TestLexer.c");
	getNextChar(&lexer);
	pass_ws(&lexer);
	while(!(matchedNextToken(&lexer,"/*").lexeme))
		getNextChar(&lexer);
	decs = readRawStringUntilToken(&lexer,"*/");
	TEST_ASSERT_EQUAL_CHAR('\n',lexer.current_char);
	TEST_ASSERT_EQUAL_STRING(" for the test ",decs);
}
