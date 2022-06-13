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
  serial::log("knl", "Initializing");
  serial::log("dts", "Initializing");
  init_descriptor_tables();
  asm volatile ("sti");
  serial::log("tty", "Initializing");
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
  serial::log("pit", "Initializing");
  timer::init(100);
  serial::log("kbd", "Initializing");
  keyboard::init();
  serial::log("knl", "Initialized");
  for (;;){
    asm volatile("hlt");
  }
}