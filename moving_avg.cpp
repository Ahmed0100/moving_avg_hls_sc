#include "moving_avg.h"

void moving_avg::moving_avg_main(void)
{
	sc_uint<11> sum=0;
	sc_uint<8> buffer[SIZE];

	//reset state
	wait();
	//main thread
	while(1)
	{
		for(int i=SIZE-1;i>0;i--)
		{
			buffer[i]=buffer[i-1];
		}
		buffer[0] = data_in.read();
		sum = buffer[0];
		for(int i=1;i<SIZE;i++)
		{
			sum += buffer[i];
		}
		data_out.write(sum/SIZE);
		wait();
	}
}
