#ifndef MACROS_H
#define MACROS_H

// std includes
#include <iostream>

// Logging
#define MLOG(msg) std::cout << "LOG: " << msg << std::endl;
#define MWRN(msg) std::cout << "WRN: " << msg << std::endl;
#define MERR(msg) std::cerr << "ERR: " << msg << std::endl;

// Delete
#define MDELETES(a) if( (a) != NULL ) delete (a); (a) = NULL;
#define MDELETEA(a) if ( (a) != NULL ) delete[] (a); (a) = NULL;

// opengl
#define BUFFER_OFFSET(i) ((void*)(i))

#endif // MACROS_H