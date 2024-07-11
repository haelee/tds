## Atomic Model
```c
typedef struct _tdsm_Atomic
{
	tdsd_State					CurrentState;

	tdsf_ExternalTransition *	ExternalTransitions;
	tdsf_Transition *			InternalTransitions;
	tdsf_Output *				Output;
	tdsf_TimeAdvance *			TimeAdvance;
}
tdsd_AtomicModel;
```