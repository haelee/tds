#include "tds.h"
#include "tdmgenerated.h"

void TDSInitializeModels (void)
{
	TDSAtomicModels = malloc (sizeof (tdsAtomicModel) * TDMNumberOfAtomicModels);
	
	TDSAtomicModels -> InitializationFunction = TDMAMIF0;
	TDSAtomicModels -> ExternalTransitionFunction = TDMAMETF0;
	TDSAtomicModels -> InternalTransitionFunction = TDMAMITF0;
	TDSAtomicModels -> OutputFunction = TDMAMOF0;
	TDSAtomicModels -> TimeAdvanceFunction = TDMAMTAF0;

	free (TDSAtomicModels);
	TDSAtomicModels = 0;
}

int main (void)
{
	return 0;
}