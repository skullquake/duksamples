#ifndef APP_DUK_EXTRAS_SOLOAD_DUK_SOLOAD_H
#define APP_DUK_EXTRAS_SOLOAD_DUK_SOLOAD_H
#include "duktape.h"
#if defined(__cplusplus)
extern "C" {
#endif
extern void duk_soload(duk_context *ctx, duk_uint_t flags);
#if defined(__cplusplus)
}
#endif
#endif
