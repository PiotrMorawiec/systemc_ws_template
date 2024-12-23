
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <systemc.h>
#include "tb/tb.hpp"
#include "rtl/fir.hpp"

SC_MODULE(SYSTEM) {
  tb  * i_tb;
  fir * i_dut;

  sc_clock              w_clk;
  sc_signal<bool>       w_rst;

  sc_signal<sc_int<16>> w_inp_data;
  sc_signal<bool>       w_inp_rdy;
  sc_signal<bool>       w_inp_vld;

  sc_signal<bool>       w_out_rdy;
  sc_signal<bool>       w_out_vld;
  sc_signal<sc_int<16>> w_out_data;

  SC_CTOR(SYSTEM) : w_clk ("w_clk", 10, SC_NS) {

    i_tb = new tb("i_tb");
    i_tb->i_clk(w_clk);
    i_tb->o_rst(w_rst);

    i_tb->i_out_data(w_out_data);
    i_tb->i_out_vld(w_out_vld);
    i_tb->o_out_rdy(w_out_rdy);

    i_tb->o_inp_data(w_inp_data);
    i_tb->o_inp_vld(w_inp_vld);
    i_tb->i_inp_rdy(w_inp_rdy);

    i_dut = new fir("i_dut");
    i_dut->i_clk(w_clk);
    i_dut->i_rst(w_rst);

    i_dut->i_inp_data(w_inp_data);
    i_dut->i_inp_vld(w_inp_vld);
    i_dut->o_inp_rdy(w_inp_rdy);

    i_dut->o_out_data(w_out_data);
    i_dut->o_out_vld(w_out_vld);
    i_dut->i_out_rdy(w_out_rdy);
  }

  ~SYSTEM() {
    delete i_tb;
    delete i_dut;
  }
};

#endif
