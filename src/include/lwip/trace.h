/**
 * @file
 * Trace infrastructure
 */

#ifndef LWIP_HDR_TRACE_H
#define LWIP_HDR_TRACE_H

#if defined(LWIP_TRACE)

#include "trcRecorder.h"

extern TraceStringHandle_t g_lwip_ch;
extern TraceStringHandle_t g_lwip_err_ch;

void lwip_trace_init(void);
TraceEntryHandle_t lwip_trace_netconn_type_string(u32_t typ);
TraceStringHandle_t lwip_trace_string_alloc(const char *s);
void lwip_trace_string_free(TraceStringHandle_t handle);

#define trace_string_t TraceStringHandle_t

#define TRACE_NETCONN_TYPE_STRING(t) lwip_trace_netconn_type_string(t)

#define TRACE_STRING_ALLOC(s) lwip_trace_string_alloc(s)
#define TRACE_STRING_FREE(s) lwip_trace_string_free(s)

#define LWIP_TRACEF(fmt, ...) xTracePrintF(g_lwip_ch, fmt, __VA_ARGS__)
#define LWIP_TRACEL(msg) xTracePrint(g_lwip_ch, msg)

#define LWIP_ERR_TRACEF(fmt, ...) xTracePrintF(g_lwip_err_ch, fmt, __VA_ARGS__)
#define LWIP_ERR_TRACEL(msg) xTracePrint(g_lwip_err_ch, msg)

#else /* no-op verions of the macros */

#define trace_string_t int

#define TRACE_NETCONN_TYPE_STRING(t) 0

#define TRACE_STRING_ALLOC(s) 0
#define TRACE_STRING_FREE(s)

#define LWIP_TRACEF(fmt, ...) (void) fmt
#define LWIP_TRACEL(msg) (void) msg

#define LWIP_ERR_TRACEF(fmt, ...) (void) fmt
#define LWIP_ERR_TRACEL(msg) (void) msg

#endif /* defined(LWIP_TRACE) */

#endif /* LWIP_HDR_TRACE_H */
