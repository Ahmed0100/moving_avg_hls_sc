#include "define.h"
#ifndef TB_MOVING_AVG_H
#define TB_MOVING_AVG_H
SC_MODULE(tb_moving_avg)
{
	sc_in<bool> clk;
	sc_in<bool> reset_n;
	sc_in<sc_uint<8> > data_out;
	sc_out<sc_uint<8> > data_in;

	//file pointers
	FILE* data_in_file, *data_out_golden_file, *data_out_file;
	FILE* data_out_read_file, *diff_file;
	//functions
	void compare_results();
	void recv();
	void send();
	SC_CTOR(tb_moving_avg)
	{
		SC_CTHREAD(send,clk.pos());
		reset_signal_is(reset_n,false);
		SC_CTHREAD(recv,clk.pos());
		reset_signal_is(reset_n,false);
	}
};
#endif
