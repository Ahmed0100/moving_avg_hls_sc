#include "moving_avg.h"
#include "tb_moving_avg.h"
int sc_main(int argc, char** argv)
{
	sc_clock clk("clk",25,SC_NS,0.5,12.5,SC_NS,true);
	sc_signal<bool> reset_n;
	sc_signal<sc_uint<8> > data_in;
	sc_signal<sc_uint<8> > data_out;

	int x;
	char name[10];
	//instantiations
	moving_avg moving_avg_inst("moving_avg_inst");
	tb_moving_avg tb_moving_avg_inst("tb_moving_avg_inst");

	//connections
	moving_avg_inst.clk(clk);
	moving_avg_inst.reset_n(reset_n);
	moving_avg_inst.data_in(data_in);
	moving_avg_inst.data_out(data_out);

	tb_moving_avg_inst.clk(clk);
	tb_moving_avg_inst.reset_n(reset_n);
	tb_moving_avg_inst.data_in(data_in);
	tb_moving_avg_inst.data_out(data_out);

#ifdef WAVE_DUMP
	sc_trace_file* trace_file = sc_create_vcd_trace_file("trace_file");
	sc_trace(trace_file,clk,"clk");
	sc_trace(trace_file,reset_n,"reset_n");
	sc_trace(trace_file,data_in,"data_in");
	sc_trace(trace_file,data_out,"data_out");
#endif
	sc_start(25,SC_NS);
	reset_n.write(0);
	sc_start(25,SC_NS);
	reset_n.write(1);
	sc_start();
#ifdef WAVE_DUMP
	sc_close_vcd_trace_file(trace_file);
#endif
	return 0;
}
