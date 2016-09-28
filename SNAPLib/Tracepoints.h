#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER snap

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./Tracepoints.h"

#if !defined(_SNAP_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _SNAP_TP_H

#include <lttng/tracepoint.h>

#endif

#include <lttng/tracepoint-event.h>
