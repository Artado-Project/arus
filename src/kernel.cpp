#include <terminal.hpp>
#include <dt.hpp>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <timer.hpp>
#include <keyboard.hpp>
#include <serial.hpp>

extern "C" void kernel_main(void)
{
  serial::init();
  serial::write_str_serial("[knl] Initializing\n");
  serial::write_str_serial("[dts] Initializing\n");
  init_descriptor_tables();
  asm volatile ("sti");
  serial::write_str_serial("[tty] Initializing\n");
  terminal::initialize();

  // Ember logo
  terminal::setcolor(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK);
  terminal::print("   __ _ _ __ _   _ ___ \n"
                  "  / _` | '__| | | / __|\n"
                  " | (_| | |  | |_| \\__ \\ \n"
                  "  \\__,_|_|   \\__,_|___/ \n");

  terminal::setcolor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
  terminal::print("Welcome to Arus!\n");
  terminal::print("Version 1, Build 0.0.1\n");
  serial::write_str_serial("[pit] Initializing\n");
  timer::init(100);
  serial::write_str_serial("[kbd] Initializing\n");
  keyboard::init();
  serial::write_str_serial("[knl] Initialized\n");
  for (;;){
    asm volatile("hlt");
  }
}