#pragma once

#include "tdm.h"

typedef struct _tdsDEVSSimulator
{
	tdmDEVSModel *	DEVSModel;
	tdmTime			LastEventTime;
	tdmTime			NextEventTime;
}
tdsDEVSSimulator;
