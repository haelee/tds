## (Internal) Transition Function
```c
typedef struct _tdsf_Transition
{
	tdsd_State	StateFrom;
	tdsd_State	StateTo;
}
tdsf_Transition;
```

## External Transition Function
```c
typedef struct _tdsf_ExternalTransition
{
	tdsf_Transition	Transition;
	tdss_Statement	ElapsedTimeStatement;
	tdss_Statement	eXternalEventStatement;
}
tdsf_ExternalTransition;
```

## Output Function
```c
typedef struct _tdsf_Output
{
	tdsd_State	State;
	tdsd_Event	OutputEvent;
}
tdsf_Output;
```

## Time Advance Function
```c
typedef struct _tdsf_TimeAdvance
{
	tdsd_State	State;
	tdsd_Time	Time;
}
tdsf_TimeAdvance;
```
