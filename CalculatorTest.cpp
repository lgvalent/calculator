/**
 * This file defines test routines for calculator and its components.
 * Author: Lucio Valentin
 * Version: 20210316
 */
#include <iostream>

#include "Calculator.h"

class MockupDisplay: public Display{
  public:
    void addDigit(Digit){   } 
    void setDecimalSeparator(){   } 
    void setSignal(Signal){   }; 
    void clear(){   } 
};

class MockupCpu: public Cpu{
    Digit reg1[8], reg2[8];
    Operation op = NONE;
  public:
    MockupCpu(Display*){   }
    void setDisplay(Display*){   }
    Display* getDisplay(){ return new MockupDisplay();  }
    
    void receiveDigit(Digit){   } 
    void receiveOperation(Operation){   } 
    void receiveControl(Control){   } 
    void cancel(){   } 
    void reset(){   } 
};

class MockupButtonNull: public virtual Button{
  public:
    void setKeyboard(Keyboard*){   }
    Keyboard* getKeyboard(){ return nullptr; }
    void press(){    }
    char getSymbol(){  return 0;  }
};

class MockupKeyboard: public Keyboard{
    Button* mockupButtons[1];
  public:
    MockupKeyboard(Cpu*){   }
    void setCpu(Cpu*){    }
    Cpu* getCpu(){ return new MockupCpu(new MockupDisplay()); }
    void press(Button*){    }
    void addButton(Button* button){  button->setKeyboard(this); this->mockupButtons[0] = button; }
    Button* findButtonBySymbol(char){ return new MockupButtonNull(); }
};

class MockupButton: public virtual Button{
  public:
    void setKeyboard(Keyboard*){   }
    Keyboard* getKeyboard(){ return new MockupKeyboard(new MockupCpu(new MockupDisplay())); }
    void press(){    }
    char getSymbol(){  return 0;  }
};

class MockupDigitButton: public MockupButton, public DigitButton{
  public:
    Digit getDigit(){ return ZERO;  }
};

class MockupOperationButton: public MockupButton, public OperationButton{
  public:
    Operation getOperation(){ return NONE; }
};

class MockupControlButton: public MockupButton, public ControlButton{
  public:
    Control getControl(){ return OFF; }
};

class MockupCalculator: public Calculator{
  public:
    MockupCalculator(Display*, Cpu*, Keyboard*){  }

    void setKeyboard(Keyboard*){   }
    Keyboard* getKeyboard(){ return new MockupKeyboard(new MockupCpu(new MockupDisplay())); }

    void setDisplay(Display* display){   }
    Display* getDisplay(){ return new MockupDisplay(); }

    void setCpu(Cpu* cpu){   }
    Cpu* getCpu(){ return new MockupCpu(new MockupDisplay()); }
};

class DisplayTest{
  public:
    static void run(Display* display){
        display->clear();
        display->addDigit(ZERO);
        display->addDigit(ONE);
        display->addDigit(TWO);
        display->addDigit(THREE);
        display->addDigit(FOUR);
        display->setDecimalSeparator();
        display->addDigit(FIVE);
        display->addDigit(SIX);
        display->addDigit(SEVEN);
        display->addDigit(EIGHT);
        display->addDigit(NINE);
    }
};

class CpuTest{
  public:
    static void run(Cpu* cpu, Display* display){
          cpu->setDisplay(display);
          
          cpu->receiveDigit(ONE);
          cpu->receiveDigit(TWO);
          cpu->receiveDigit(THREE);
          
          cpu->cancel();
          
          cpu->receiveDigit(ONE);
          cpu->receiveDigit(TWO);
          cpu->receiveDigit(THREE);
          
          cpu->receiveOperation(ADDITION);

          cpu->receiveDigit(FOUR);
          cpu->receiveDigit(FIVE);
          cpu->receiveDigit(SIX);
          
          cpu->receiveOperation(EQUAL);
          
          cpu->receiveOperation(SUBTRACTION);
 
          cpu->receiveDigit(ONE);
          cpu->receiveDigit(ONE);
          cpu->receiveDigit(ONE);
 
          cpu->receiveOperation(ADDITION);

          cpu->receiveDigit(ONE);

          cpu->receiveOperation(ADDITION);

          cpu->receiveDigit(ONE);

          cpu->receiveOperation(EQUAL);

          cpu->reset();
    }
};

class ButtonTest{
    public:
      static void run(Button* button){
        button->press();
      }
};

class KeyboardTest{
  public:
    static void run(Keyboard* keyboard){
      char symbols[] = {'0', '1', '2', '+',  '3', '=', 'C'};
      for(const char &symbol: symbols){
        Button* button = keyboard->findButtonBySymbol(symbol);
        if(button)
          ButtonTest::run(button);
        else
          std::cerr << "No button found for symbol '" << symbol << "'.\n";
      }  
    }
};

class CalculatorTest{
    public:
      static void run(Calculator* calculator){
          DisplayTest::run(calculator->getDisplay());
          CpuTest::run(calculator->getCpu(), calculator->getDisplay());
          KeyboardTest::run(calculator->getKeyboard());
          
          calculator->getKeyboard()->findButtonBySymbol('C')->press();

          calculator->getKeyboard()->findButtonBySymbol('1')->press();
          calculator->getKeyboard()->findButtonBySymbol('2')->press();
          calculator->getKeyboard()->findButtonBySymbol('3')->press();
          calculator->getKeyboard()->findButtonBySymbol('+')->press();
          calculator->getKeyboard()->findButtonBySymbol('4')->press();
          calculator->getKeyboard()->findButtonBySymbol('5')->press();
          calculator->getKeyboard()->findButtonBySymbol('6')->press();
          calculator->getKeyboard()->findButtonBySymbol('=')->press();

          calculator->getKeyboard()->findButtonBySymbol('-')->press();
          calculator->getKeyboard()->findButtonBySymbol('7')->press();
          calculator->getKeyboard()->findButtonBySymbol('8')->press();

          calculator->getKeyboard()->findButtonBySymbol('-')->press();
          calculator->getKeyboard()->findButtonBySymbol('9')->press();
          calculator->getKeyboard()->findButtonBySymbol('=')->press();

      }
};
