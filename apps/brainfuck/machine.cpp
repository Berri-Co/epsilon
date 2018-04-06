#include "machine.h"

namespace Brainfuck {

Machine::Machine(bool interruptOnOutput) :
  m_interruptOnOutput(interruptOnOutput)
{
  resetVm();
}

Machine::Error Machine::run(const char * program) {
  m_pc = program;
  m_mptr = m_memory;
  m_stackp = 0;

  return resume();
}

Machine::Error Machine::resume() {
  while (*m_pc != 0) {
    switch (*m_pc) {
      case '>':
        m_mptr++;
        if (m_mptr - m_memory >= BRAINFUCK_MEMORY) {
          m_mptr = m_memory;
        }
        break;
      case '<':
        m_mptr--;
        if (m_mptr < m_memory) {
          m_mptr = m_memory + BRAINFUCK_MEMORY - 1;
        }
        break;
      case '+':
        (*m_mptr)++;
        break;
      case '-':
        (*m_mptr)--;
        break;
      case '.':
        if (m_obufp + 1 >= BRAINFUCK_OUTBUFFER) {
          // Silently discard - Output buffer full
          break;
        }
        m_outbuffer[m_obufp] = *m_mptr;
        m_outbuffer[++m_obufp] = 0;
        if (m_interruptOnOutput) {
          return Error::Output;
        }
        break;
      case ',':
        if (m_ibufp == 0) {
          return Error::Input;
        }

        *m_mptr = m_inbuffer[0];
        memmove(m_inbuffer, m_inbuffer + 1, m_ibufp - 1);
        m_ibufp--;
        break;
      case '[':
        if (*m_mptr == 0) {
          // Skip loop
          int inner = 0;
          const char * i = m_pc + 1;
          for (; *i != 0; ++i) {
            if (*i == '[') {
              inner++;
            } else if (*i == ']') {
              if (!inner) break;
              else inner--;
            }
          }
          if (*i == 0) {
            return Error::MissingRBracket;
          }
          m_pc = i + 1;
          continue;
        } else {
          // Enter loop
          if (m_stackp >= BRAINFUCK_STACK) {
            return Error::StackOverflow;
          }
          m_stack[m_stackp++] = m_pc;
          m_loopCounter[m_stackp] = 0;
        }
        break;
      case ']':
        if (m_stackp == 0) {
          return Error::MissingLBracket;
        }

        if (*m_mptr != 0) {
          // Jump back into loop
          if (m_loopCounter[m_stackp - 1]++ > BRAINFUCK_LOOPLIMIT) {
            return Error::LoopLimit;
          }
          m_pc = m_stack[m_stackp - 1] + 1;
          continue;
        } else {
          // Exit loop
          m_stackp--;
        }
        break;
    }

    m_pc++;
  }

  return Error::Success;
}

void Machine::input(value_t value) {
  if (m_ibufp >= BRAINFUCK_INBUFFER) {
    // Silently discard - Input buffer overflow
    return;
  }
  m_inbuffer[m_ibufp++] = value;
}

size_t Machine::getOutput(char * buffer, size_t len) {
  size_t n = strlcpy(buffer, (const char *)m_outbuffer, len);
  m_obufp = 0;
  *m_outbuffer = 0;
  return n;
}

void Machine::setInterruptOnOutput(bool interruptOnOutput) {
  m_interruptOnOutput = interruptOnOutput;
}

void Machine::resetVm() {
  for (int i = 0; i < BRAINFUCK_MEMORY; ++i) {
    m_memory[i] = 0;
  }
  m_ibufp = 0;
  m_obufp = 0;
  *m_outbuffer = 0;
}

}
