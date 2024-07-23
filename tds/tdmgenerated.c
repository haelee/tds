///////////////////////////////////////////////////////////////////////////////
// tdmgenerated.c
// Model-dependent
///////////////////////////////////////////////////////////////////////////////

#include "tdm.h"

#include <stdio.h>
#include <stdlib.h>

#define TDM_NUMBER_OF_ATOMIC_MODELS		2
#define TDM_NUMBER_OF_STATE_VARIABLES	2

// Model array
static tdmDEVSModel TDMDEVSModels	[TDM_NUMBER_OF_ATOMIC_MODELS + 1]	= {0};

// State variable array
static tdmCommon TDMStateVariables	[TDM_NUMBER_OF_STATE_VARIABLES]		= {0};

///////////////////////////////////////////////////////////////////////////////
// Atomic Model B
// 0: SEND / 1: WAIT / 2: IDLE
///////////////////////////////////////////////////////////////////////////////

static tdmDEVSModel * TDM_A_Couplings [2] = {0};

void TDM_A_Initialization (tdmDEVSModel * Model)
{
	Model -> StateVariables [0] . Integer = 0; // Model A's initial state is SEND.
}

void TDM_A_ExternalTransition (tdmDEVSModel * Model, tdmTime ElapsedTime, tdmEvent ExternalEvent)
{
	printf ("Recvd\n");

	if (2 == Model -> StateVariables [0] . Integer)
	{
		printf ("Late reply\n");
	}
	else
	{
		printf ("Reply ont ime\n");
	}

	// Model A transitions to IDLE.
	Model -> StateVariables [0] . Integer = 2;
}

void TDM_A_InternalTransition (tdmDEVSModel * Model)
{
	switch (Model -> StateVariables [0] . Integer)
	{
		case 0:
			// Model A transitions to WAIT.
			Model -> StateVariables [0] . Integer = 1;
			break;

		default:
			printf ("No reply\n");
			// Model A transitions to IDLE.			
			Model -> StateVariables [0] . Integer = 2;
			break;
	}
}

tdmEvent TDM_A_Output (tdmDEVSModel * Model)
{
	return (tdmEvent) {. Integer = 0};
}

tdmTime TDM_A_TimeAdvance (tdmDEVSModel * Model)
{
	switch (Model -> StateVariables [0] . Integer)
	{
		case 0:
			return 0.0;

		case 1:
			return 60.0;
	}
	return tdmTimeInfinite;
}

///////////////////////////////////////////////////////////////////////////////
// Atomic Model B
// 0: REPLY / 1: IDLE
///////////////////////////////////////////////////////////////////////////////

static tdmDEVSModel * TDM_B_Couplings [2] = {0};

void TDM_B_Initialization (tdmDEVSModel * Model)
{
	Model -> StateVariables [0] . Integer = 1;
}

void TDM_B_ExternalTransition (tdmDEVSModel * Model, tdmTime ElapsedTime, tdmEvent ExternalEvent)
{
	switch (Model -> StateVariables [0] . Integer)
	{
		default:
			Model -> StateVariables [0] . Integer = 0;
	}
}

void TDM_B_InternalTransition (tdmDEVSModel * Model)
{
	switch (Model -> StateVariables [0] . Integer)
	{
		default:
			Model -> StateVariables [0] . Integer = 1;
			break;
	}
}

tdmEvent TDM_B_Output (tdmDEVSModel * Model)
{
	return (tdmEvent) {. Integer = 0};
}

tdmTime TDM_B_TimeAdvance (tdmDEVSModel * Model)
{
	switch (Model -> StateVariables [0] . Integer)
	{
		case 0:
			return rand () % 100;
	}

	return tdmTimeInfinite;
}

///////////////////////////////////////////////////////////////////////////////
// Model-dependent functions
///////////////////////////////////////////////////////////////////////////////

void TDMInitializeModels (void)
{
	TDMDEVSModels [0] . StateVariables				= TDMStateVariables;
	TDMDEVSModels [0] . InitializationFunction		= TDM_A_Initialization;
	TDMDEVSModels [0] . ExternalTransitionFunction	= TDM_A_ExternalTransition;
	TDMDEVSModels [0] . InternalTransitionFunction	= TDM_A_InternalTransition;
	TDMDEVSModels [0] . OutputFunction				= TDM_A_Output;
	TDMDEVSModels [0] . TimeAdvanceFunction			= TDM_A_TimeAdvance;

	TDMDEVSModels [0] . OutputCouplings				= TDM_A_Couplings;
	TDMDEVSModels [0] . OutputCouplings [0]			= TDMDEVSModels + 1;
	TDMDEVSModels [0] . OutputCouplings [1]			= 0;

	TDMDEVSModels [1] . StateVariables				= TDMStateVariables + 1;
	TDMDEVSModels [1] . InitializationFunction		= TDM_B_Initialization;
	TDMDEVSModels [1] . ExternalTransitionFunction	= TDM_B_ExternalTransition;
	TDMDEVSModels [1] . InternalTransitionFunction	= TDM_B_InternalTransition;
	TDMDEVSModels [1] . OutputFunction				= TDM_B_Output;
	TDMDEVSModels [1] . TimeAdvanceFunction			= TDM_B_TimeAdvance;

	TDMDEVSModels [1] . OutputCouplings				= TDM_B_Couplings;
	TDMDEVSModels [1] . OutputCouplings [0]			= TDMDEVSModels;
	TDMDEVSModels [1] . OutputCouplings [1]			= 0;

    TDMDEVSModels [2] . StateVariables				= 0;
}

///////////////////////////////////////////////////////////////////////////////
// Model-independent functions
///////////////////////////////////////////////////////////////////////////////

void TDMFinalizeModels (void)
{
}

tdmDEVSModel * TDMGetDEVSModels (void)
{
	return TDMDEVSModels;
}
