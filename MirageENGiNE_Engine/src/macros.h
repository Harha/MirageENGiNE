#ifndef MACROS_H
#define MACROS_H

// std includes
#include <iostream>

// Logging
#define MLOG_DEBUG(msg_, ...)	printf("DBG: " msg_ "\n", ##__VA_ARGS__)
#define MLOG_INFO(msg_, ...)	printf("INF: " msg_ "\n", ##__VA_ARGS__)
#define MLOG_WARNING(msg_, ...)	printf("WRN: " msg_ "\n", ##__VA_ARGS__)
#define MLOG_ERROR(msg_, ...)	printf("ERR: " msg_ "\n", ##__VA_ARGS__)

// Heap object deletion
#define MDELETES(a) if( (a) != NULL ) delete (a); (a) = NULL;
#define MDELETEA(a) if ( (a) != NULL ) delete[] (a); (a) = NULL;

// OpenGL
#define BUFFER_OFFSET(i) ((void*)(i))

#endif // MACROS_H