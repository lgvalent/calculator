#include "Calculator.h"
#include "CalculatorTest.cpp"
/* Here include your .h files */

int main()
{
    /* Replace all Mockups classes with yours own */
    Display* display = new MockupDisplay();

    Cpu* cpu = new MockupCpu(display);

    Keyboard* keyboard = new MockupKeyboard(cpu);

    Calculator* calculator = new MockupCalculator(display, cpu, keyboard);

    /* This section is common to all codes */
    DisplayTest::run(display);
    CpuTest::run(cpu, display);
    KeyboardTest::run(keyboard);
    CalculatorTest::run(calculator);

    /* If you prefer, implement your own tests here */


    return 0;
}
