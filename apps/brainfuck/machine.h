#ifndef APPS_BRAINFUCK_MACHINE_H
#define APPS_BRAINFUCK_MACHINE_H

extern "C" {
#include <stdio.h>
#include <string.h>
}

#define BRAINFUCK_MEMORY 30000
#define BRAINFUCK_INBUFFER 30
#define BRAINFUCK_OUTBUFFER 30
#define BRAINFUCK_STACK 30
#define BRAINFUCK_LOOPLIMIT 30000

namespace Brainfuck {

typedef signed char value_t;
typedef void (*print_func_t)(value_t);

class Machine {
public:
  enum Error {
    Success,
    Output,
    Input, 
    MissingLBracket,
    MissingRBracket,
    StackOverflow,
    LoopLimit
  };

  Machine(bool interruptOnOutput = false);
  Error run(const char * program);
  Error resume();
  void input(value_t value);
  size_t getOutput(char * buffer, size_t len);
  void setInterruptOnOutput(bool interruptOnOutput);
  void resetVm();

private:
  // Configurations
  bool m_interruptOnOutput;

  // Current VM
  value_t m_memory[BRAINFUCK_MEMORY];
  value_t m_inbuffer[BRAINFUCK_INBUFFER];
  int m_ibufp;
  value_t m_outbuffer[BRAINFUCK_OUTBUFFER];
  int m_obufp;

  // Current program
  const char * m_pc;
  value_t * m_mptr;
  const char * m_stack[BRAINFUCK_STACK];
  int m_loopCounter[BRAINFUCK_STACK];
  int m_stackp;
};

}

#endif
