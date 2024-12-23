#include <iostream>
#include <sstream>
#include <systemc.h>
#include <tb.hpp>

void tb::source ()
{
  
  logger.log("INFO", "apply reset");

  // Initialize handshake
  o_inp_data.write(0);
  o_inp_vld.write(0);

  // Reset
  o_rst.write(1);
  wait();
  o_rst.write(0);

  sc_int<16> tmp;

  logger.log("INFO", "generate stimulus");


  for(int i = 0; i < 64; i++) {
    if(i > 23 && i < 29)
      tmp = 256;
    else
      tmp = 0;

    o_inp_vld.write(1);
    o_inp_data.write(tmp);

    do {
      wait();
    } while(!i_inp_rdy.read());

    start_time[i] = sc_time_stamp();
    o_inp_vld.write(0);
  }
}

void tb::sink()
{
  sc_int<16> indata;
  std::ofstream out_fid(out_fn);
  double total_cycles = 0;

  // Extract clock period
  sc_clock *clk_p = dynamic_cast<sc_clock*>(i_clk.get_interface());
  clk_period = clk_p->period();

  // Open dump file
  if(!out_fid) {
    logger.log("ERROR", "Coudln't open \"" + out_fn + "\" for writing" );
    exit(0);
  }

  // Initialize port
  o_out_rdy.write(0);

  // Read output comming from DUT
  for(int i = 0; i < 64; i++) {

    o_out_rdy.write(1);

     do {
      wait();
    } while(!i_out_vld.read());

    indata = i_out_data.read();
    o_out_rdy.write(0);
    end_time[i] = sc_time_stamp();
    total_cycles += (end_time[i] - start_time[i]) / clk_period;
    
    wait();

    out_fid << "data[" << i << "]: " << indata.to_int() << "\n";
    logger.log("INFO", "out data: " + std::to_string(indata.to_int()));
  }

  // Print latency & trhoughput
  double total_throughput = (start_time[63] - start_time[0]) / clk_period;
  cout << "Average DUT latency: " << (double) (total_cycles / 64) << " cycles" << endl;
  cout << "Average DUT throughput: " << (double) (total_throughput / 63) << " cycles per input" << endl;
  
  // Close dump file
  out_fid.close();

  sc_stop();
}
