//#include <string>
//#include <cstdio>
#include "LexicalGenerator.cc"
int main(const int argc, const char** argv){
	CLanguageGenerator cLexGenerator{};
	if(argc == 2){
		cLexGenerator.takeInput(argv[1]);
		cLexGenerator.openFile();
		cLexGenerator.outputCode();
	}
}