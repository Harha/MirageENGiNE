#ifndef RUNSTATE_H
#define RUNSTATE_H

namespace mirage
{

	enum EngineRunState
	{
		ERS_ERROR = -1,
		ERS_UNINTIALIZED = 0,
		ERS_INITIALIZED = 1,
		ERS_STOPPED = 2,
		ERS_RUNNING = 3
	};

}

#endif // RUNSTATE_H