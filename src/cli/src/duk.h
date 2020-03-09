#ifndef MAIN_H
#define MAIN_h
#include "duktape.h"
extern int _main(int argc, char *argv[]);
class Duk{
	public:
		Duk(int argc,char** argv);
		~Duk();
		void usage();
		void cleanup();
		void repl();
		void reg();
	private:
		duk_context *ctx;
		int retval;
		int have_files;
		int have_eval;
		int interactive;
		int memlimit_high;
		int alloc_provider;
		int lowmem_log;
		int debugger;
		int recreate_heap;
		int no_heap_destroy;
		int verbose;
		int run_stdin;
		const char *compile_filename=NULL;
		int i;
};
#endif


