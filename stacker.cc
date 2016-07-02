#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include "stacker.h"
#include "proggen.h"

/*
class StackItem {
  enum { Number, Operator, Variable } type;
  union {
    double number;
    char operator;
    char* variable;
  } value;
};
*/

Stack stack;


template<typename T>
Symbols<T>::Symbols () {
  count = 0;
  names = new char* [50];
  values = new T [50];
}

template<typename T>
int Symbols<T>::lookup (const char* name) {
  for (int i = 0; i < count; i++) {
    if (!strcmp (name, names[i])) {
      return i;
    }
  }
  return -1;
}

template<typename T>
int Symbols<T>::add (const char* name) {
  int ret = lookup(name);
  if (ret == -1) {
    names[count] = strdup (name);
    values[count] = (T)0;
    ret = count++;
  }
  return ret;
}

template<typename T>
int Symbols<T>::add (const char* name, T val) {
  int i = add(name);
  set(i, val);
}

template<typename T>
T Symbols<T>::get (int index) {
  return values[index];
}

template<typename T>
void Symbols<T>::set (int index, T val) {
  values[index] = val;
}

Symbols<double> variables;
Symbols<pfunc> functions;

Program::Program () {
  instructions = new Instruction* [50];
  pc = 0;
}

void Program::add(Instruction* i) {
  instructions[pc++] = i;
}

void Program::execute () {
  for(int i = 0; i < pc; i++) {
    instructions[i]->execute ();
  }
}

Stack::Stack () : pointer(0) {
  items = new double [50];
}

Stack::~Stack () {
  delete [] items;
}


Program program;

extern "C" double initProg () {
  variables.add("x");
  functions.add("sin", sin);
  functions.add("cos", cos);
  functions.add("tan", tan);
  functions.add("exp", exp);
  functions.add("log", log);
  //  functions.add("ln", ln);
}

extern "C" double genEval (double val) {
  double ret;
  int ix = variables.lookup("x");
  variables.set (ix, val);

  stack.reset ();
  program.execute();
  ret = stack.items[0];
  printf("ret=%f\n", ret);
  return ret;
}

extern "C" void push(double value) {
  program.add (new Push(value));
}
extern "C" void pushVariable (char* name) {
  int varIndex = variables.lookup (name);
  program.add (new PushVariable(varIndex));
}

extern "C" void functionCall (char* name) {
  //  printf("functionCall name='%s'\n", name);
  int i = functions.lookup (name);
  pfunc f = functions.get(i);
  program.add (new FunctionCall(f));
}

extern "C" void add () {
  program.add(new Add());
}

extern "C" void sub () {
  program.add(new Sub());
}

extern "C" void mul () {
  program.add(new Mul());
}

extern "C" void gendiv () {
  program.add(new Div());
}
extern "C" void genpow () {}
extern "C" void neg () {}

