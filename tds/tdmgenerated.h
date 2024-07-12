#pragma once

#include "tdsmodels.h"

#define TDMFunctionNameFormat

const int TDMNumberOfAtomicModels = 1;
const int TDMSizeOfStateVariableBlocks = sizeof (tdsStateVariable) * 2;

void TDMAMIF0 (tdsAtomicModel * Model)
{
	Model -> StateVariables [0] . Integer = 0;
	Model -> StateVariables [1] . Real = 10.0;
}

tdsAtomicModel * TDMAMETF0 (tdsAtomicModel * Model, tdsTime ElapsedTime, tdsEvent ExternalEvent)
{
	switch (Model -> StateVariables [0] . Integer)
	{
	}
	return Model;
}

tdsAtomicModel * TDMAMITF0 (tdsAtomicModel * Model)
{
	switch (Model -> StateVariables [0] . Integer)
	{
	}
	return Model;
}

tdsEvent TDMAMOF0 (tdsAtomicModel * Model)
{
	switch (Model -> StateVariables [0] . Integer)
	{
	}
	return Model;
}

tdsTime TDMAMTAF0 (tdsAtomicModel * Model)
{
	switch (Model -> StateVariables [0] . Integer)
	{
	}
	return tdsInfinite;
}