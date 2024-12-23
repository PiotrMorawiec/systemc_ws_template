
#ifndef _FIR_H_
#define _FIR_H_

SC_MODULE(fir)  {
  sc_in <bool>        i_clk;
  sc_in <bool>        i_rst;
  sc_in <sc_int<16>>  i_inp_data;
  sc_in<bool>         i_inp_vld;
  sc_out<bool>        o_inp_rdy;
  sc_out <sc_int<16>> o_out_data;
  sc_out<bool>        o_out_vld;
  sc_in<bool>         i_out_rdy;

  void fir_main();

  SC_CTOR (fir) {
    SC_CTHREAD(fir_main, i_clk.pos());
    reset_signal_is(i_rst, true);
  }
};

const sc_uint <8> coef[5] = {18, 77, 107, 20, 34};

#include "fir.tpp"

#endif
