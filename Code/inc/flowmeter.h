#include "stdint.h"

typedef struct FlowMeter{
	uint32_t _coint;
	float coff;
}FlowMeter;

uint32_t callback_flowmeter(FlowMeter *flow);
