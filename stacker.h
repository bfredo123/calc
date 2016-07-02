class Stack {
public:
  double* items;
  int pointer;
  Stack ();
  ~Stack ();
  void reset () { pointer = 0; }
  void push (double x) { items[pointer++] = x; }
  double pop (void) { return items[--pointer]; }
};

extern Stack stack;

template<typename T>
class Symbols {
  char** names;
  T* values;
  int count;
public:
  Symbols ();
  int lookup(const char* name);
  int add (const char* name);
  int add (const char* name, T val);
  T get (int index);
  void set (int index, T val);
};

extern Symbols<double> variables;

typedef double (*pfunc) (double);

extern Symbols<pfunc> functions;

class Instruction {
 public:
  virtual void execute () = 0;
};


class Push: public Instruction {
  double val;
 public:
  Push (double x) { val = x; }
  void execute () { stack.push(val); }
};

class PushVariable: public Instruction {
  int var;
 public:
  PushVariable (int varIndex) { var = varIndex; }
  void execute () { 
    double val = variables.get(var);
    stack.push(val); 
  }
};

class Add: public Instruction {
 public:
  void execute () { 
    double a = stack.pop(); 
    double b = stack.pop ();
    stack.push(a+b);
  }
};

class Sub: public Instruction {
 public:
  void execute () { 
    double b = stack.pop(); 
    double a = stack.pop ();
    stack.push(a-b);
  }
};

class Mul: public Instruction {
 public:
  void execute () { 
    double a = stack.pop(); 
    double b = stack.pop ();
    stack.push(a*b);
  }
};

class Div: public Instruction {
 public:
  void execute () { 
    double b = stack.pop(); 
    double a = stack.pop ();
    stack.push(a/b);
  }
};

class FunctionCall: public Instruction {
  pfunc fn;
 public:
  FunctionCall (pfunc f) { fn = f; }
  void execute () {
    double x = stack.pop ();
    x = (*fn)(x);
    stack.push (x);
  }
};

class Program {
  Instruction** instructions;
  int pc;
 public:
  Program ();
  void add(Instruction*);
  void execute ();
};
