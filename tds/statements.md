## Transition Instructions
```c
#define tdsi_Transition				0;
#define tdsi_TransitionIfEqualTo	1;
```

## Transition Statement
```c
typedef struct _tdss_Statement
{
	tdsd_Instruction Instruction;
	union
	{
		tdsd_Time	Time0;
		tdsd_Event	Event0;
	};
	union // For future use
	{
		tdsd_Time	Time1;
		tdsd_Event	Event1;
	};
}
tdss_Statement;
```
