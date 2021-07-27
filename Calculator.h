/**
 * This file defines the interfaces of a calculator and its components.
 * Author: Lucio Valentin
 * Version: 20210713
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

enum Digit{ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
enum Operation{ADDITION, SUBTRACTION, DIVISION, MULTIPLICATION, EQUAL, NONE};
enum Signal{POSITIVE, NEGATIVE};
enum Control{ON, OFF, CANCEL, RESET, MEMORY_READ_CLEAR, MEMORY_ADDITION, MEMORY_SUBTRACTION};

class Display{
  public:
    virtual void addDigit(Digit) = 0; 
    virtual void setDecimalSeparator() = 0; 
    virtual void setSignal(Signal) = 0; 
    virtual void clear() = 0; 
};

class Cpu{
  public:
    virtual void setDisplay(Display*) = 0; 
    virtual Display* getDisplay() = 0;
    
    virtual void receiveDigit(Digit) = 0; 
    virtual void receiveOperation(Operation) = 0; 
    virtual void receiveControl(Control) = 0; 
    virtual void cancel() = 0;
    virtual void reset() = 0; 
};

class Keyboard; // Early declaration, Button <-and-> Keyboard have a bidirectional association. C++ tricks.

class Button{
  public:
    virtual void setKeyboard(Keyboard*) = 0;
    virtual Keyboard* getKeyboard() = 0;
    virtual void press() = 0;
    virtual char getSymbol() = 0;
};

class DigitButton: public virtual Button{
  public:
    virtual Digit getDigit() = 0;
};

class OperationButton: public virtual Button{
  public:
    virtual Operation getOperation() = 0;
};

class ControlButton: public virtual Button{
  public:
    virtual Control getControl() = 0;
};

class Keyboard{
  public:
    virtual void setCpu(Cpu*) = 0;
    virtual Cpu* getCpu() = 0;
    virtual void addButton(Button*) = 0;
    virtual void press(Button*) = 0;
    virtual Button* findButtonBySymbol(char) = 0;
};

class Calculator{
  public:
    virtual void setKeyboard(Keyboard*) = 0;
    virtual Keyboard* getKeyboard() = 0;

    virtual void setDisplay(Display* display) = 0;
    virtual Display* getDisplay() = 0;

    virtual void setCpu(Cpu* cpu) = 0;
    virtual Cpu* getCpu() = 0;
};

#endif