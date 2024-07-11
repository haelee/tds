#pragma once

#include <stdint.h>

// Data
typedef int64_t	tdsd_State;
typedef double	tdsd_Time;
typedef int64_t	tdsd_Event;
typedef int64_t tdsd_Instruction;

// Transition instructions
#define tdsi_Transition				0;
#define tdsi_TransitionIfEqualTo	1;

// Transition statements
typedef struct _tdss_Statement
{
	tdsd_Instruction Instruction;
	union
	{
		tdsd_Time	Time0;
		tdsd_Event	Event0;
	};
	union // For future use
	{
		tdsd_Time	Time1;
		tdsd_Event	Event1;
	};
}
tdss_Statement;

// Functions
typedef struct _tdsf_Transition
{
	tdsd_State	StateFrom;
	tdsd_State	StateTo;
}
tdsf_Transition;

typedef struct _tdsf_ExternalTransition
{
	tdsf_Transition	Transition;
	tdss_Statement	ElapsedTimeStatement;
	tdss_Statement	eXternalEventStatement;
}
tdsf_ExternalTransition;

typedef struct _tdsf_Output
{
	tdsd_State	State;
	tdsd_Event	OutputEvent;
}
tdsf_Output;

typedef struct _tdsf_TimeAdvance
{
	tdsd_State	State;
	tdsd_Time	Time;
}
tdsf_TimeAdvance;

// Models
typedef struct _tdsm_Atomic
{
	tdsd_State					CurrentState;

	tdsf_ExternalTransition *	ExternalTransitions;
	tdsf_Transition *			InternalTransitions;
	tdsf_Output *				Output;
	tdsf_TimeAdvance *			TimeAdvance;
}
tdsd_AtomicModel;
