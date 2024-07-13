#include "tds.h"
#include "tdmgenerated.h"

bool TDSInitializeModels (void)
{
	TDSAtomicModels = malloc (sizeof (tdsAtomicModel) * TDMNumberOfAtomicModels);
	if (! TDSAtomicModels)
	{
		return false;
	}
	TDSStateVariableBlock = malloc (sizeof (TDSAtomicModels) * TDMSizeOfStateVariableBlock);
	if (! TDSStateVariableBlock)
	{
		return false;
	}

	TDSAtomicModels -> InitializationFunction = TDMAMIF0;
	TDSAtomicModels -> ExternalTransitionFunction = TDMAMETF0;
	TDSAtomicModels -> InternalTransitionFunction = TDMAMITF0;
	TDSAtomicModels -> OutputFunction = TDMAMOF0;
	TDSAtomicModels -> TimeAdvanceFunction = TDMAMTAF0;

	free (TDSStateVariableBlock);
	TDSStateVariableBlock = 0;

	free (TDSAtomicModels);
	TDSAtomicModels = 0;
}

int main (void)
{
	return 0;
}