 

       
#include "unity.h"
#include <stdio.h>
#include <string.h>
#include "Parser.h"
#include "Lexer.h"
#include "funcs.h"

Parser parser;
LStack Stack;
/* for the test */

/*Parser parser;*/

void setUp(void){
	initTokenStack(&Stack);
}
void tearDown(void){
}

void test_initTokenStack(void){
	LStack s;
	initTokenStack(&s);
	TEST_ASSERT_EQUAL(s.top,s.stack);
	TEST_ASSERT_EQUAL(s.top,&s.stack[0]);
	TEST_ASSERT_NULL(s.stack[0].lexeme);
	TEST_ASSERT_NULL(s.stack[PTS_STACK_SIZE-1].lexeme);
	
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
