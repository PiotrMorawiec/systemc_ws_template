
#include <iostream>
#include <systemc.h>
#include "fir.hpp"

void fir::fir_main(void) {
  sc_int<16> taps[5];

  // Reset
  for(int i = 0; i < 5; i++)
    taps[i] = 0;
  
  // Initialize handshake
  o_out_data.write(0);
  o_inp_rdy.write(0);
  o_out_vld.write(0);

  wait();

  // FIR filter
  while(true) {

    sc_int<16> in_val;
    sc_int<16> out_val;

    o_inp_rdy.write(1);

    do {
      wait();
    } while(!i_inp_vld.read());

    in_val = i_inp_data.read();
    o_inp_rdy.write(0);

    // Read input into shifr register
    for(int i = 4; i > 0; i--)
      taps[i] = taps[i-1];

    taps[0] = in_val;

    // perform multiply and accumulate
    for(int i = 0; i < 5; i++)
      out_val += coef[i] * taps[i];

    o_out_vld.write(1);
    o_out_data.write(out_val);

    do {
      wait();
    } while(!i_out_rdy.read());

    o_out_vld.write(0);

    wait();
  }
}
