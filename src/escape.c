/**
 This files has code for the parser to recognize and deal with escape
	character sequences by constructing nodes of a parse tree and 
	returning them as a representation for the input.
Examples of escqpe character sequences:
	\t
	\n
	\r
	\0

*/
#include "Parser.h"
#include "baseset.h"
#include "chrset.h"
#include "log.h"

/**

	struct _node* escape_char(struct _cset **ta,buffer* parser->lexer.inputBuffer,char* c)

Functionality: This runs the part of the parser that recognizes escape
	character sequences and constructs nodes for the parse tree to reprsent
	this. This representation is then returned, or an error happens and NULL
	is returned.

Parameters: a memory location of a pointer to a character set _cset **ta
			an already existing and initialized buffer pointer buffer* parser->lexer.inputBuffer
			a character pointer char* c that is points to the current input
			character

Returns: returns a tree structure to be added to the parse tree that represents
	the esapce character sequence, or NULL if an error is detected.

Results: a node is created to represent the escape character and it is
	returned

*/
RegularExpressionTreeNode* parseEscapeChars(Parser* parser)
{
   /* char_set** */
   /* temporary node help create new nodes and add them to a tree */
   RegularExpressionTreeNode* ret = NULL;

   if(NULL != parser)
   {
      getNextChar(&parser->lexer);

      /* create the node and return it,
         switch statement for later use
      */
      switch(parser->lexer.current_char)
      {
         case 'n':
            ret = create_node('\n');
            break;
	      case 't':
      		ret = create_node('\t');
            break;
      	case '\\':
      	case '\'':
	      case '"':
      	case '%':
      	case '*':
	      case '+':
      	case '?':
	      case '{':
      	case '}':
	      case '[':
         case ']':
	      case '(':
         case ')':
	      case '/':
         case '.':
	      case ':':
         case '|':
		      ret = create_node(parser->lexer.current_char);
            break;
		      /* If all else fails, then report an error and return NULL */
	      default:
		      LOG_ERROR("doesn't support that kind of escape character <%c>",parser->lexer.current_char);
            break;
      }
   }
   else
   {
      LOG_ERROR("NULL arguments given");
   }
   LOG_0("escaped this character, or tried <%c>", parser->lexer.current_char);
   return ret;
}
