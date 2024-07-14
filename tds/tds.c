// Simulation engine
#include "tds.h"
#include "tdm.h"

static int TDSNumberOfAtomicModels = 0;
static tdmAtomicModel * TDSAtomicModels = 0;
static tdmTime * TDSNextEventTime = 0;

bool TDSInitializeSimulation (void)
{
	int ModelIndex = TDSNumberOfAtomicModels;
	tdmAtomicModel * AtomicModel = TDSAtomicModels;

	do
	{
		(* AtomicModel -> InitializationFunction) (AtomicModel);
		AtomicModel ++;
	}
	while (-- ModelIndex);

	return true;
}

int main (void)
{
	TDMInitializeModels ();

	TDSAtomicModels = TDMGetAtomicModels ();
	TDSNextEventTime = TDMGetNextEventTimeBlock ();
	TDSNumberOfAtomicModels = TDMGetNumberOfAtomicModels ();

	TDSInitializeSimulation ();

	TDMFinalizeModels ();
	return 0;
}