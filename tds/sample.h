#pragma once

#include "tds.h"

void AM0IF (tdsAtomicModel * Model)
{
}

tdsAtomicModel * AM0ETF (tdsAtomicModel * Model, tdsTime ElapsedTime, tdsEvent ExternalEvent)
{
	return Model;
}

tdsAtomicModel * AM0ITF (tdsAtomicModel * Model)
{
	return Model;
}

tdsEvent AM0OF (tdsAtomicModel * Model)
{
	return Model;
}

tdsTime AM0TAF (tdsAtomicModel * Model)
{
	return tdsInfinite;
}

void TDSInitialize (void)
{
	TDSAtomicModels = malloc (sizeof (tdsAtomicModel));

	TDSAtomicModels -> InitializationFunction = AM0IF;
	TDSAtomicModels -> ExternalTransitionFunction = AM0ETF;
	TDSAtomicModels -> InternalTransitionFunction = AM0ITF;
	TDSAtomicModels -> OutputFunction = AM0OF;
	TDSAtomicModels -> TimeAdvanceFunction = AM0TAF;

	free (TDSAtomicModels);
	TDSAtomicModels = 0;
}