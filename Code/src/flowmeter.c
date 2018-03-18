#include "flowmeter.h"

uint32_t callback_flowmeter(FlowMeter *flow){
	(*flow)._coint++;
	return (uint32_t)((*flow)._coint * (*flow).coff);
}
