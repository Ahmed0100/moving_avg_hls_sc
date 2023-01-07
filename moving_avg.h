#ifndef MOVING_AVG_H
#define MOVING_AVG_H
#include "define.h"

SC_MODULE(moving_avg)
{
public:
	sc_in<bool> clk;
	sc_in<bool> reset_n;
	sc_in<sc_uint<8> > data_in;

	sc_out<sc_uint<8> > data_out;

	void moving_avg_main(void);

	SC_CTOR(moving_avg)
	{
		SC_CTHREAD(moving_avg_main, clk.pos());
		reset_signal_is(reset_n,false);
	}
};
#endif
