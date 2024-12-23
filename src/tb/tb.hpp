
#ifndef _TB_H_
#define _TB_H_

#include <systemc.h>
#include "tb.hpp"
#include "../lib/logger.hpp"

SC_MODULE(tb)
{
  Logger logger;

  sc_in<bool>        i_clk;
  sc_out<bool>       o_rst;
  
  sc_out<sc_int<16>> o_inp_data;
  sc_out<bool>       o_inp_vld;
  sc_in<bool>        i_inp_rdy;
  
  sc_in<sc_int<16>>  i_out_data;
  sc_in<bool>        i_out_vld;
  sc_out<bool>       o_out_rdy;

  std::string        out_fn = "output.txt";
  sc_time            start_time[64], end_time[64], clk_period;

  void source();
  void sink();

  SC_CTOR(tb) : logger("simulation.log")  {
    SC_CTHREAD(source, i_clk.pos());
    SC_CTHREAD(sink,   i_clk.pos());
  }
};

#endif
