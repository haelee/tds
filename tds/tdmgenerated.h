#pragma once

// This code will be automatically generated by TDM.

#include "tds.h"

#define TDMFunctionNameFormat

const int TDMNumberOfAtomicModels = 2;
const int TDMSizeOfStateVariableBlock = sizeof (tdsCommon) * 2;

///////////////////////////////////////////////////////////////////////////////
// Atomic Model 0
// 0: SEND
// 1: WAUT
// 2: IDLE

void TDMAMIF0 (tdsAtomicModel * Model)
{
	Model -> StateVariables = TDSStateVariableBlock;
	Model -> StateVariables [0] . Integer = 0;
}

tdsAtomicModel * TDMAMETF0 (tdsAtomicModel * Model, tdsTime ElapsedTime, tdsEvent ExternalEvent)
{
	switch (Model -> StateVariables [0] . Integer)
	{
		default:
			Model -> StateVariables [0] . Integer = 2;
	}
	return Model;
}

tdsAtomicModel * TDMAMITF0 (tdsAtomicModel * Model)
{
	switch (Model -> StateVariables [0] . Integer)
	{
		case 0:
			Model -> StateVariables [0] . Integer = 1;
			break;

		default:
			Model -> StateVariables [0] . Integer = 2;
			break;
	}
	return Model;
}

tdsEvent TDMAMOF0 (tdsAtomicModel * Model)
{
	return (tdsEvent) {. Integer = 0};
}

tdsTime TDMAMTAF0 (tdsAtomicModel * Model)
{
	switch (Model -> StateVariables [0] . Integer)
	{
		case 0:
			return 0.0;
		case 1:
			return 60.0;
	}

	return tdsTimeInfinite;
}

///////////////////////////////////////////////////////////////////////////////
// Atomic Model 1
// 0: REPLY
// 1: IDLE

void TDMAMIF1 (tdsAtomicModel * Model)
{
	Model -> StateVariables = TDSStateVariableBlock + 1;
	Model -> StateVariables [0] . Integer = 1;
}

tdsAtomicModel * TDMAMETF1 (tdsAtomicModel * Model, tdsTime ElapsedTime, tdsEvent ExternalEvent)
{
	switch (Model -> StateVariables [0] . Integer)
	{
		default:
			Model -> StateVariables [0] . Integer = 0;
	}
	return Model;
}

tdsAtomicModel * TDMAMITF1 (tdsAtomicModel * Model)
{
	switch (Model -> StateVariables [0] . Integer)
	{
		default:
			Model -> StateVariables [0] . Integer = 1;
			break;
	}
	return Model;
}

tdsEvent TDMAMOF1 (tdsAtomicModel * Model)
{
	return (tdsEvent) {. Integer = 0};
}

tdsTime TDMAMTAF1 (tdsAtomicModel * Model)
{
	switch (Model -> StateVariables [0] . Integer)
	{
		case 0:
			return rand () % 100;
	}

	return tdsTimeInfinite;
}