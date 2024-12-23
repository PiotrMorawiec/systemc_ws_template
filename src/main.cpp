
#include <iostream>
#include <format>
#include <systemc>
#include "system.hpp"

SYSTEM * tb_top = NULL;

void custom_report_format(const sc_report& report, const sc_actions& actions) {

    std::cout << "[" << std::setw(10) << std::setfill(' ') <<  sc_time_stamp().to_string() << "] "
              << "[" << std::setw(10) << std::setfill(' ') << report.get_severity() << "] "
              << "[" << std::setw(10) << std::setfill(' ') << report.get_msg_type() << "] "
              << report.get_msg() << std::endl;
}

int sc_main(int argc, char* argv [])
{

  tb_top = new SYSTEM("tb_top");
  sc_trace_file* vcd_file = sc_create_vcd_trace_file("waveform");

  std::cout << "SystemC version: " << SC_VERSION << std::endl;
  // sc_report_handler::set_log_callback(custom_report_format);

  // its SC_PS by default
  // sc_set_time_resolution(1, SC_NS);

  sc_trace(vcd_file, tb_top->w_rst, "reset");
  sc_trace(vcd_file, tb_top->w_clk, "clock");
  sc_trace(vcd_file, tb_top->w_inp_data, "inp_dat");
  sc_trace(vcd_file, tb_top->w_inp_rdy, "inp_rdy");
  sc_trace(vcd_file, tb_top->w_inp_vld, "inp_vld");
  sc_trace(vcd_file, tb_top->w_out_data, "out_dat");
  sc_trace(vcd_file, tb_top->w_out_rdy, "out_rdy");
  sc_trace(vcd_file, tb_top->w_out_vld, "out_vld");

  sc_start();
  // sc_start(100, SC_NS);  // Run the simulation for 100ns

  sc_close_vcd_trace_file(vcd_file);
  return 0;
}
