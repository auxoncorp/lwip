/**
 * @file
 * Trace module
 *
 */
#include "lwip/opt.h"

#if LWIP_TRACE /* don't build if not configured for use in lwipopts.h */

#include "lwip/def.h"
#include "lwip/api.h"
#include "lwip/debug.h"
#include "lwip/trace.h"

#include <string.h>

static TraceStringHandle_t g_netcon_types[11] = {NULL};

TraceStringHandle_t g_lwip_ch = NULL;
TraceStringHandle_t g_lwip_err_ch = NULL;

static int netconn_type_to_str_index(u32_t typ)
{
    int index = 0; // INVALID

    if(typ == NETCONN_TCP)
    {
        index = 1;
    }
#if LWIP_IPV6
    else if(typ == NETCONN_TCP_IPV6)
    {
        index = 2;
    }
#endif /* LWIP_IPV6 */
    else if(typ == NETCONN_UDP)
    {
        index = 3;
    }
    else if(typ == NETCONN_UDPLITE)
    {
        index = 4;
    }
    else if(typ == NETCONN_UDPNOCHKSUM)
    {
        index = 5;
    }
#if LWIP_IPV6
    else if(typ == NETCONN_UDP_IPV6)
    {
        index = 6;
    }
    else if(typ == NETCONN_UDPLITE_IPV6)
    {
        index = 7;
    }
    else if(typ == NETCONN_UDPNOCHKSUM_IPV6)
    {
        index = 8;
    }
#endif /* LWIP_IPV6 */
    else if(typ == NETCONN_RAW)
    {
        index = 9;
    }
#if LWIP_IPV6
    else if(typ == NETCONN_RAW_IPV6)
    {
        index = 10;
    }
#endif /* LWIP_IPV6 */

    return index;
}

void lwip_trace_init(void)
{
    traceResult tr;

    tr = xTraceStringRegister("lwip", &g_lwip_ch);
    LWIP_ASSERT("", (tr == TRC_SUCCESS));

    tr = xTraceStringRegister("lwip_error", &g_lwip_err_ch);
    LWIP_ASSERT("", (tr == TRC_SUCCESS));

    tr = xTraceStringRegister("INVALID", &g_netcon_types[0]);
    LWIP_ASSERT("", (tr == TRC_SUCCESS));
    tr = xTraceStringRegister("TCP", &g_netcon_types[1]);
    LWIP_ASSERT("", (tr == TRC_SUCCESS));
    tr = xTraceStringRegister("TCP_IPV6", &g_netcon_types[2]);
    LWIP_ASSERT("", (tr == TRC_SUCCESS));
    tr = xTraceStringRegister("UDP", &g_netcon_types[3]);
    LWIP_ASSERT("", (tr == TRC_SUCCESS));
    tr = xTraceStringRegister("UDPLITE", &g_netcon_types[4]);
    LWIP_ASSERT("", (tr == TRC_SUCCESS));
    tr = xTraceStringRegister("UDPNOCHKSUM", &g_netcon_types[5]);
    LWIP_ASSERT("", (tr == TRC_SUCCESS));
    tr = xTraceStringRegister("UDP_IPV6", &g_netcon_types[6]);
    LWIP_ASSERT("", (tr == TRC_SUCCESS));
    tr = xTraceStringRegister("UDPLITE_IPV6", &g_netcon_types[7]);
    LWIP_ASSERT("", (tr == TRC_SUCCESS));
    tr = xTraceStringRegister("UDPNOCHKSUM_IPV6", &g_netcon_types[8]);
    LWIP_ASSERT("", (tr == TRC_SUCCESS));
    tr = xTraceStringRegister("RAW", &g_netcon_types[9]);
    LWIP_ASSERT("", (tr == TRC_SUCCESS));
    tr = xTraceStringRegister("RAW_IPV6", &g_netcon_types[10]);
    LWIP_ASSERT("", (tr == TRC_SUCCESS));
}

TraceEntryHandle_t lwip_trace_netconn_type_string(u32_t typ)
{
    return g_netcon_types[netconn_type_to_str_index(typ)];
}

TraceStringHandle_t lwip_trace_string_alloc(const char *s)
{
    traceResult tr;
    TraceStringHandle_t handle = NULL;

    tr = xTraceStringRegister(s, &handle);
    if(tr == TRC_SUCCESS)
    {
        return handle;
    }
    else
    {
        return NULL;
    }
}

void lwip_trace_string_free(TraceStringHandle_t handle)
{
    if(handle != NULL)
    {
        xTraceEntryDelete((TraceEntryHandle_t) handle);
    }
}

#endif /* LWIP_TRACE */
