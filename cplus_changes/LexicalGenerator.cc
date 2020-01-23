#include <cstdio>
#include <cerrno>
#include <string>
struct LexicalGenerator {
	virtual ~LexicalGenerator() = default;
	virtual void parseSpecFile() =0;
	virtual void generateLexer() = 0;
	virtual void outputCode() = 0;
	virtual void takeInput(const char* filename) = 0;
	virtual void openFile() = 0;
private:
	FILE * openfile;
	FILE * outputFile;
	char * filename;
	char * outputname;
};

struct CLanguageGenerator : LexicalGenerator {
	CLanguageGenerator() : filename{}, openfile{}, outputfile{} {
		outputname = "sclex.yy.c";
		
	}
	void outputCode() override {
		try{
		outputfile = std::fopen(outputname,"w");
		if(!outputfile) throw std::runtime_error(strerror(errno));
		}
		catch(std::runtime_error &e){
			printf("%s\n",e.what());
		}
	}
	void generateLexer() override {
		
	}
	~CLanguageGenerator(){
		if(filename)
			delete[] filename;
		if(openfile)
			std::fclose(openfile);
		if(outputfile)
			std::fclose(outputfile);	
	}
	void parseSpecFile() override {
		
	}
	
	void openFile() override{
		try {
			openfile = std::fopen(this->filename, "r");
			if (!openfile) throw std::runtime_error(strerror(errno));
		}
		catch(std::runtime_error &e) {
			printf("%s\n",e.what());
			exit(EXIT_FAILURE);
		}		
	}
	void takeInput(const char* filename) override {
		this->filename = new char[sizeof(filename)];
		std::strcpy(this->filename,filename);
	}
private:
	FILE * openfile;
	FILE * outputfile;
	char * filename;
	const char* outputname;
};

