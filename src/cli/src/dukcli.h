#ifndef DUK_CMDLINE_H_INCLUDED
#define DUK_CMDLINE_H_INCLUDED
#include"duktape.h"
#include"linenoise.h"
extern int main_argc;
extern char **main_argv;
extern int interactive_mode;
extern int allow_bytecode;
#if defined(DUK_CMDLINE_DEBUGGER_SUPPORT)
extern int debugger_reattach;
#endif
#if defined(DUK_CMDLINE_LINENOISE_COMPLETION)
extern int no_auto_complete;
#endif
extern void *lowmem_pool_ptr;
void lowmem_init(void);
void lowmem_free(void);
void lowmem_dump(void);
void lowmem_register(duk_context *ctx);
void lowmem_start_exec_timeout(void);
void lowmem_clear_exec_timeout(void);
void *lowmem_alloc_wrapped(void *udata, duk_size_t size);
void *lowmem_realloc_wrapped(void *udata, void *ptr, duk_size_t size);
void lowmem_free_wrapped(void *udata, void *ptr);
#define MEM_LIMIT_NORMAL (128*1024*1024)
#define MEM_LIMIT_HIGH (2047*1024*1024)
#define LINEBUF_SIZE 65536
int duk_cmdline_stack_check(void);
static void print_greet_line(void);
#if defined(DUK_CMDLINE_RLIMIT)
static void set_resource_limits(rlim_t mem_limit_value);
#endif 
#if defined(DUK_CMDLINE_SIGNAL)
static void my_sighandler(int x);
static void set_sigint_handler(void);
#endif 
static void cmdline_fatal_handler(void *udata, const char *msg);
static void print_pop_error(duk_context *ctx, FILE *f);
static duk_ret_t wrapped_compile_execute(duk_context *ctx, void *udata);
#if defined(DUK_CMDLINE_LINENOISE_COMPLETION)
static duk_ret_t linenoise_add_completion(duk_context *ctx);
static char *linenoise_hints(const char *buf, int *color, int *bold);
static void linenoise_freehints(void *ptr);
static void linenoise_completion(const char *buf, linenoiseCompletions *lc);
#endif
static int handle_fh(duk_context *ctx, FILE *f, const char *filename, const char *bytecode_filename);
int handle_file(duk_context *ctx, const char *filename, const char *bytecode_filename);
int handle_eval(duk_context *ctx, char *code);
#if defined(DUK_CMDLINE_LINENOISE)
static int handle_interactive(duk_context *ctx);
#else 
static int handle_interactive(duk_context *ctx);
#endif
#if defined(DUK_CMDLINE_FILEIO)
static duk_ret_t fileio_read_file(duk_context *ctx);
static duk_ret_t fileio_write_file(duk_context *ctx);
#endif 
static duk_ret_t string_frombufferraw(duk_context *ctx);
#if defined(DUK_CMDLINE_DEBUGGER_SUPPORT)
static duk_idx_t debugger_request(duk_context *ctx, void *udata, duk_idx_t nvalues)
static void debugger_detached(duk_context *ctx, void *udata);
#endif
#define  ALLOC_DEFAULT  0
#define  ALLOC_LOGGING  1
#define  ALLOC_TORTURE  2
#define  ALLOC_HYBRID   3
#define  ALLOC_LOWMEM   4
extern duk_context *create_duktape_heap(int alloc_provider, int debugger, int lowmem_log);
extern void destroy_duktape_heap(duk_context *ctx, int alloc_provider);
int duk_cmdline_stack_check(void);
#endif
