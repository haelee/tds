///////////////////////////////////////////////////////////////////////////////
// tds.s
// Model-independent
///////////////////////////////////////////////////////////////////////////////

#include "tdm.h"

// Pointer to the model array
static tdmDEVSModel * TDSDEVSModels = 0;

void TDSInitializeSimulation (tdmTime InitialTime)
{
	tdmDEVSModel * DEVSModel = 0;

	TDSDEVSModels		= TDMGetDEVSModels ();
	DEVSModel			= TDSDEVSModels;

	// For each of the atomic models:
	do
	{
		// Call the initialization function of the model.
		(* DEVSModel -> InitializationFunction) (DEVSModel);

		// Set the time of the last event to the initial time.
		DEVSModel -> LastEventTime = InitialTime;

		// Call the time advance function (ta) of the model.
		// Update the time of the next event using the return value of the function.
		DEVSModel -> NextEventTime = InitialTime + (* DEVSModel -> TimeAdvanceFunction) (DEVSModel);
	}
	while (++ DEVSModel -> StateVariables);
}

void TDSFinalizeSimulation (void)
{
}

tdmDEVSModel * TDSGetImminentModel (void)
{
	tdmDEVSModel *	DEVSModel		= TDSDEVSModels;
	tdmDEVSModel *	ImminentModel	= DEVSModel;

	while (++ DEVSModel -> StateVariables)
	{
		if (DEVSModel -> NextEventTime < ImminentModel -> NextEventTime)
		{
			ImminentModel = DEVSModel;
		}
	}

	return ImminentModel -> NextEventTime < tdmTimeInfinite ? ImminentModel : 0;
}

void TDSRun (tdmTime SimulationTime)
{
	tdmDEVSModel *	ImminentModel	= 0;
	tdmDEVSModel **	Couplings		= 0;
	tdmCommon		Event;

	TDSInitializeSimulation (SimulationTime);

	// If there exists an imminent model,
	while ((ImminentModel = TDSGetImminentModel ()))
	{
		// Call the output function (lambda) of the imminet model.
		Event = (* ImminentModel -> OutputFunction) (ImminentModel);

		// Call the internal transition function (delta_int) of the model.
		(* ImminentModel -> InternalTransitionFunction) (ImminentModel);

		// Set the time of the last event to the current simulation time.
		ImminentModel -> LastEventTime = SimulationTime;

		// Call the time advance function (ta) of the model.
		// Update the time of the next event using the return value of the function.
		ImminentModel -> NextEventTime = SimulationTime + (* ImminentModel -> TimeAdvanceFunction) (ImminentModel);

		Couplings = ImminentModel -> OutputCouplings;

		// For each of the connecting model,
		while (* Couplings)
		{
			// Call the external transition function (delta_ext) of the model.
			(* (* Couplings) -> ExternalTransitionFunction) (* Couplings, SimulationTime - (* Couplings) -> LastEventTime, Event);

			// Set the time of the last event to the current simulation time.
			(* Couplings) -> LastEventTime = SimulationTime;

			// Call the time advance function (ta) of the model.
			// Update the time of the next event using the return value of the function.
			(* Couplings) -> NextEventTime = SimulationTime + (* (* Couplings) -> TimeAdvanceFunction) (* Couplings);
		}
	}

	TDSFinalizeSimulation ();
}

int main (void)
{
	TDMInitializeModels ();

	TDSRun (0.0);

	TDMFinalizeModels ();
	return 0;
}