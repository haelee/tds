#include "tds.h"
#include "tdmgenerated.h"

// Need to consider the use of .so file for loading models

bool TDSInitializeModels (void)
{
	int ModelIndex = TDMNumberOfAtomicModels;
	void * MainHandle;
	void * Function;
	char FunctionName [256];

	if (! TDMNumberOfAtomicModels)
	{
		fprintf (stderr, "ERROR: The number of atomic models is not given.\n");
		return false;
	}

 	MainHandle = dlopen (NULL, RTLD_LAZY);
	if (! MainHandle)
	{
		fprintf (stderr, "ERROR: Failed to dlopen the main process.\n");
		return false;
	}

	TDSAtomicModels = malloc (sizeof (tdsAtomicModel) * TDMNumberOfAtomicModels);
	if (! TDSAtomicModels)
	{
		fprintf (stderr, "ERROR: Failed to allocate a memoryblock for atomic models.\n");
		return false;
	}

	TDSStateVariableBlock = malloc (sizeof (TDSAtomicModels) * TDMSizeOfStateVariableBlock);
	if (! TDSStateVariableBlock)
	{
		fprintf (stderr, "ERROR: Failed to allocate a memory block for state variables.\n");
		return false;
	}

	do
	{
		snprintf (FunctionName, sizeof (FunctionName), "TDMAMIF%d", ModelIndex);
		TDSAtomicModels [ModelIndex] . InitializationFunction = dlsym (MainHandle, FunctionName);
		if (! TDSAtomicModels [ModelIndex] . InitializationFunction)
		{
			fprintf (stderr, "ERROR: Failed to find function \'%s\' in the main process.\n", FunctionName);
			return false;
		}
		TDSAtomicModels [ModelIndex] . ExternalTransitionFunction = TDMAMETF0;
		TDSAtomicModels [ModelIndex] . InternalTransitionFunction = TDMAMITF0;
		TDSAtomicModels [ModelIndex] . OutputFunction = TDMAMOF0;
		TDSAtomicModels [ModelIndex] . TimeAdvanceFunction = TDMAMTAF0;
	} while (-- ModelIndex);

	dlclose (MainHandle);

	free (TDSStateVariableBlock);
	TDSStateVariableBlock = 0;

	free (TDSAtomicModels);
	TDSAtomicModels = 0;

	return true;
}

int main (void)
{
	return 0;
}