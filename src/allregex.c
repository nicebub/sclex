#include "Parser.h"
#include "lex_error.h"
#include "retodfa.h"
RegularExpressionTreeArray* parseRegularExpressionSet(Parser* parser)
{
   RegularExpressionTreeArray* ret = NULL;
   struct _node*      concatParent = NULL;
   struct _node*         hashChild = NULL;
   struct _node*             regex = NULL;
   int                     counter = 0;
   int                    firstrun = 0;

   if(NULL != parser)
   {
      /* create the initial parse tree structure */
      parser->parseTree = create_ta(512);
      if(NULL != parser->parseTree)
      {
      	/* Start parsing the input stream , if we have found
      	end of file,its coming next, or we found a '%' symbolizing
   	   the end of the definition section, then don't start further
      	parsing for regular expressions. Otherwise DO.
      	*/
   	   firstrun = 1;
      	do{
      		concatParent = create_node((char)CONCAT);
   	   	if(NULL == concatParent)
            {
   			   lex_error(9);
      		}
            else
            {
               hashChild = create_node('#');
   		      if(NULL != hashChild)
               {
                  regex = parseRegularExpression(parser);
      		      if(NULL == regex)
                  {
       		   	   switch(firstrun)
                     {
      				      case 1:
      					      lex_error(7);
   	   				      break;
           		   		default:
   		    	   	     getNextChar(&parser->lexer);
    			  	   	     continue;
      			      }
      		      }

   	   	      concatParent->left = regex;
           		   concatParent->right = hashChild;
      	       	firstpos(&concatParent);
      		      lastpos(&concatParent);
                  parser->parseTree->t[counter] = concatParent;
                  parser->parseTree->used++;
                  parser->parseTree->finalpos[parser->parseTree->num_re] =hashChild->uniq;
      	         parser->parseTree->num_re++;
   	            counter++;
   		         switch(firstrun)
                  {
      			      case 1:
      	   	         parser->parseTree->atop = concatParent;
   		   		      firstrun = 0;
         			   	break;
            			case 0:
      		      	default:
   	   			      hashChild = create_node((char)OR);
   		            	if(NULL == hashChild)
                        {
   				         	lex_error(10);
                           break;
      				      }
         	   			hashChild->left = parser->parseTree->atop;
   	       	   		hashChild->right = concatParent;
   			         	firstpos(&hashChild);
   		   	         lastpos(&hashChild);
            		   	parser->parseTree->atop = hashChild;
      		      		break;
         	   	}
                  /*	   pass_ws(&parser->lexer);*/
               	/*  if(parser->lexer.current_char == '%' || parser->lexer.current_char == EOF) return parser->parseTree;*/
   	            setIndividualTokens(&parser->lexer,0);
               }
               else
               {
      			   lex_error(8);
      		   }
            }
   	   }while(NULL == matchToken(&parser->lexer,tokenForType(SECTION_STARTER)).lexeme);

         pushBackLastToken(&parser->lexer,tokenForType(SECTION_STARTER));
   	   ret = parser->parseTree;
      }
      else
      {
   	   lex_error(6);
      }
   }
   else
   {
      LOG_0("NULL arguments given");
   }

   return ret;
}
