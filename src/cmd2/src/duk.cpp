#include"dukcli.h"
#include"duk.h"
#include"srv.h"
#include"mongoose-cpp/Server.h"
#include"mongoose-cpp/WebController.h"
Duk::Duk(int argc, char *argv[]) {
	ctx = NULL;
	retval = 0;
	have_files = 0;
	have_eval = 0;
	interactive = 0;
	memlimit_high = 1;
	alloc_provider = ALLOC_DEFAULT;
	lowmem_log = 0;
	debugger = 0;
	recreate_heap = 0;
	no_heap_destroy = 0;
	verbose = 0;
	run_stdin = 0;
	//main_argc = argc;
	//main_argv = (char **) argv;
#if defined(EMSCRIPTEN)
	EM_ASM(
		try {
			FS.mkdir("/working");
			FS.mount(NODEFS, { root: "." }, "/working");
		} catch (e) {
			console.log("Failed to mount NODEFS /working: " + e);
		}
		try {
			FS.mount(NODEFS, { root: "/tmp" }, "/tmp");
		} catch (e) {
			console.log("Failed to mount NODEFS /tmp: " + e);
		}
	);
#endif
#if defined(DUK_CMDLINE_LOWMEM)
	alloc_provider = ALLOC_LOWMEM;
#endif
	(void) lowmem_log;
#if defined(DUK_CMDLINE_SIGNAL)
	set_sigint_handler();
#endif
	for (i = 1; i < argc; i++) {
		char *arg = argv[i];
		if (!arg) {
			this->usage();
			break;
		}
		if (strcmp(arg, "--restrict-memory") == 0) {
			memlimit_high = 0;
		} else if (strcmp(arg, "-i") == 0) {
			interactive = 1;
		} else if (strcmp(arg, "-b") == 0) {
			allow_bytecode = 1;
		} else if (strcmp(arg, "-c") == 0) {
			if (i == argc - 1) {
				this->usage();
				break;
			}
			i++;
			compile_filename = argv[i];
		} else if (strcmp(arg, "-e") == 0) {
			have_eval = 1;
			if (i == argc - 1) {
				this->usage();
				break;
			}
			i++;
		} else if (strcmp(arg, "--alloc-default") == 0) {
			alloc_provider = ALLOC_DEFAULT;
		} else if (strcmp(arg, "--alloc-logging") == 0) {
			alloc_provider = ALLOC_LOGGING;
		} else if (strcmp(arg, "--alloc-torture") == 0) {
			alloc_provider = ALLOC_TORTURE;
		} else if (strcmp(arg, "--alloc-hybrid") == 0) {
			alloc_provider = ALLOC_HYBRID;
		} else if (strcmp(arg, "--alloc-lowmem") == 0) {
			alloc_provider = ALLOC_LOWMEM;
		} else if (strcmp(arg, "--lowmem-log") == 0) {
			lowmem_log = 1;
		} else if (strcmp(arg, "--debugger") == 0) {
			debugger = 1;
#if defined(DUK_CMDLINE_DEBUGGER_SUPPORT)
		} else if (strcmp(arg, "--reattach") == 0) {
			debugger_reattach = 1;
#endif
		} else if (strcmp(arg, "--recreate-heap") == 0) {
			recreate_heap = 1;
		} else if (strcmp(arg, "--no-heap-destroy") == 0) {
			no_heap_destroy = 1;
		} else if (strcmp(arg, "--no-auto-complete") == 0) {
#if defined(DUK_CMDLINE_LINENOISE_COMPLETION)
			no_auto_complete = 1;
#endif
		} else if (strcmp(arg, "--verbose") == 0) {
			verbose = 1;
		} else if (strcmp(arg, "--run-stdin") == 0) {
			run_stdin = 1;
		} else if (strlen(arg) >= 1 && arg[0] == '-') {
			this->usage();
			break;
		} else {
			have_files = 1;
		}
	}
	if (!have_files && !have_eval && !run_stdin) {
		interactive = 1;
	}
#if defined(DUK_CMDLINE_RLIMIT)
	set_resource_limits(memlimit_high ? MEM_LIMIT_HIGH : MEM_LIMIT_NORMAL);
#else
	if (memlimit_high == 0) {
		fprintf(stderr, "Warning: option --restrict-memory ignored, no rlimit support\n");
		fflush(stderr);
	}
#endif
	ctx = create_duktape_heap(alloc_provider, debugger, lowmem_log);
	this->reg();
	for (i = 1; i < argc; i++) {
		char *arg = argv[i];
		if (!arg) {
			continue;
		} else if (strlen(arg) == 2 && strcmp(arg, "-e") == 0) {
			if (i == argc - 1) {
				retval = 1;
				this->cleanup();
			}
			if (handle_eval(ctx, argv[i + 1]) != 0) {
				retval = 1;
				this->cleanup();
			}
			i++;
			continue;
		} else if (strlen(arg) == 2 && strcmp(arg, "-c") == 0) {
			i++;
			continue;
		} else if (strlen(arg) >= 1 && arg[0] == '-') {
			continue;
		}

		if (verbose) {
			fprintf(stderr, "*** Executing file: %s\n", arg);
			fflush(stderr);
		}

		if (handle_file(ctx, arg, compile_filename) != 0) {
			retval = 1;
			this->cleanup();
		}

		if (recreate_heap) {
			if (verbose) {
				fprintf(stderr, "*** Recreating heap...\n");
				fflush(stderr);
			}

			destroy_duktape_heap(ctx, alloc_provider);
			ctx = create_duktape_heap(alloc_provider, debugger, lowmem_log);
		}
	}
	/*
	if (run_stdin) {
		if (handle_fh(ctx, stdin, "stdin", compile_filename) != 0) {
			retval = 1;
			this->cleanup();
		}
		if (recreate_heap) {
			if (verbose) {
				fprintf(stderr, "*** Recreating heap...\n");
				fflush(stderr);
			}

			destroy_duktape_heap(ctx, alloc_provider);
			ctx = create_duktape_heap(alloc_provider, debugger, lowmem_log);
		}
	}
	if(interactive){
		this->repl();
	}
	*/
}
Duk::~Duk(){
	std::cout<<"~Duk()"<<std::endl;
};
void Duk::usage(){
	std::cerr<<R"(
Usage: duk [options] [<filenames>]

   -i                 enter interactive mode after executing argument file(s) / eval code
   -e CODE            evaluate code
   -c FILE            compile into bytecode and write to FILE (use with only one file argument)
   -b                 allow bytecode input files (memory unsafe for invalid bytecode)
   --run-stdin        treat stdin like a file, i.e. compile full input (not line by line)
   --verbose          verbose messages to stderr
   --restrict-memory  use lower memory limit (used by test runner)
   --alloc-default    use Duktape default allocator)";
#if defined(DUK_CMDLINE_ALLOC_LOGGING)
	std::cerr<<R"(
   --alloc-logging    use logging allocator, write alloc log to /tmp/duk-alloc-log.txt
)";
#endif
#if defined(DUK_CMDLINE_ALLOC_TORTURE)
	std::cerr<<R"(
   --alloc-torture    use torture allocator
)";
#endif
#if defined(DUK_CMDLINE_ALLOC_HYBRID)
	std::cerr<<R"(
   --alloc-hybrid     use hybrid allocator
)";
#endif
#if defined(DUK_CMDLINE_LOWMEM)
	std::cerr<<R"(
   --alloc-lowmem     use pooled allocator (enabled by default for duk-low)
   --lowmem-log       write alloc log to /tmp/lowmem-alloc-log.txt
)";
#endif
#if defined(DUK_CMDLINE_DEBUGGER_SUPPORT)
	std::cerr<<R"(
   --debugger         start example debugger
   --reattach         automatically reattach debugger on detach
)";
#endif
	std::cerr<<R"(
   --recreate-heap    recreate heap after every file
   --no-heap-destroy  force GC, but don't destroy heap at end (leak testing)
)";
#if defined(DUK_CMDLINE_LINENOISE_COMPLETION)
	std::cerr<<R"(
   --no-auto-complete disable linenoise auto completion
)";
#else
	std::cerr<<R"(
   --no-auto-complete disable linenoise auto completion [ignored, not supported]
)";
#endif
	std::cerr<<R"(

If <filename> is omitted, interactive mode is started automatically.

Input files can be either ECMAScript source files or bytecode files
(if -b is given).  Bytecode files are not validated prior to loading,
so that incompatible or crafted files can cause memory unsafe behavior.
See discussion in
https://github.com/svaarala/duktape/blob/master/doc/bytecode.rst#memory-safety-and-bytecode-validation.
	)";
	fflush(stderr);
	std::cout<<"asdf"<<std::endl;
}
void Duk::cleanup(){
	/*
	if (interactive) {
		fprintf(stderr, "Cleaning up...\n");
		fflush(stderr);
	}

	if (ctx && no_heap_destroy) {
		duk_gc(ctx, 0);
	}
	if (ctx && !no_heap_destroy) {
		destroy_duktape_heap(ctx, alloc_provider);
	}
	ctx = NULL;
	*/
}
void Duk::repl(){
	/*
	if(handle_interactive(ctx) != 0) {
		retval = 1;
		this->cleanup();//goto cleanup;
	}
	*/
}
void Duk::reg(){
	/*
	dukglue_register_function(ctx,&test,"test");
	dukglue_register_function(ctx,&srvstart,"srvstart");
	dukglue_register_function(ctx,&srvstop,"srvstop");
	dukglue_register_constructor<Server>(ctx,"Server");
	dukglue_register_method(
		ctx,
		&Server::start,
		"start"
	);
	dukglue_register_method(
		ctx,
		&Server::stop,
		"stop"
	);
	dukglue_register_method(
		ctx,
		&Server::setOption,
		"setOption"
	);
	dukglue_register_method(
		ctx,
		&Server::printStats,
		"printStats"
	);
	dukglue_register_method(
		ctx,
		&Server::poll,
		"poll"
	);
	*/
}
