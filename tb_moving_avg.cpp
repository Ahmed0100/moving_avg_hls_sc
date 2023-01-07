#include "tb_moving_avg.h"
void tb_moving_avg::send()
{
	int i=0;
	unsigned int data_in_read;
	data_in_file = fopen(INFILENAME,"rt");
	if(!data_in_file)
	{
		cout<<"Could not open file "<<INFILENAME<<endl;
		sc_stop();
		exit(-1);
	}
	wait();
	i=0;
	while(true)
	{
		while(fscanf(data_in_file,"%u",&data_in_read) !=
				EOF)
		{
			data_in.write(data_in_read);
			wait();
		}
		fclose(data_in_file);
		cout<<endl<<"starting comparing results"<<endl;
		compare_results();
		sc_stop();
		wait();
	}
}

void tb_moving_avg::recv()
{
	unsigned int data_out_write=0;
	data_out_file = fopen(OUTFILENAME,"wt");
	if(!data_out_file)
	{
		cout<<"could not open "<<OUTFILENAME<<endl;
		sc_stop();
		exit(-1);
	}
	wait();
	while(true)
	{
		data_out_write = data_out.read();
		fprintf(data_out_file, "%d\n", data_out_write);
		wait();
	}
}

void tb_moving_avg::compare_results()
{
	int data_out_val, data_out_golden_val, line=1, errors=0;
	fclose(data_out_file);
	data_out_file= fopen(OUTFILENAME,"rt");
	if(!data_out_file)
	{
		cout<<"could not open file"<<OUTFILENAME<<endl;
		sc_stop();
		exit(-1);
	}
	data_out_golden_file = fopen(OUTFILENAME_GOLDEN,"rt");
	if(!data_out_golden_file)
	{
		cout<<"could not open file"<<OUTFILENAME_GOLDEN<<endl;
		sc_stop();
		exit(-1);
	}
	diff_file = fopen(DIFFFILENAME,"w");
	if(!diff_file)
	{
		cout<<"could not open file"<<DIFFFILENAME<<endl;
		sc_stop();
		exit(-1);
	}
	while(fscanf(data_out_golden_file, "%d",&data_out_golden_val) != EOF)
	{
		fscanf(data_out_file,"%d",&data_out_val);
		cout<<endl<<"cycle["<<line<<"]: "<<
				data_out_golden_val<<"-- "<<data_out_val;

		if(data_out_val != data_out_golden_val)
		{
			cout<<"\n output mismatch [line:" <<line<<
					"] golden:"<<data_out_golden_val<<
					"-- output: "<<data_out_val<<endl;
			errors++;
		}
		line++;
	}
	if(errors == 0)
		cout<<"SIMULATION FINISHED SUCCESSFULLY"<<endl;
	else
		cout<<"SIMULATION FAILED"<<endl;
	fclose(data_out_file);
	fclose(data_out_golden_file);
	fclose(data_out_file);
}
