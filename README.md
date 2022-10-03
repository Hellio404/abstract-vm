# abstract-vm
The purpose of this project is to create a simple virtual machine that can interpret programs written in a basic assembly language.

### grammer of the assembly language
```
S := INSTR [SEP INSTR]* #

INSTR :=
    push VALUE
    | pop
    | dump
    | assert VALUE
    | add
    | sub
    | mul
    | div
    | mod
    | print
    | exit

VALUE :=
    int8(N)
    | int16(N)
    | int32(N)
    | float(Z)
    | double(Z)

N := [-]?[0..9]+

Z := [-]?[0..9]+.[0..9]+

SEP := '\n'+
```
### Example of the assembly language supported
```pl
; -------------
; sample.avm -
; -------------

push int32(42)
push int32(33)
add
push float(44.55)
mul
push double(42.42)
push int32(42)
dump
pop
assert double(42.42)
exit

```


## Description of the instructions supported:

**Comments:** Comments start with a ’;’ and finish with a newline. A comment can
be either at the start of a line, or after an instruction.

**push *v*:** Pushes the value *v* at the top of the stack. The value *v* must have one of
the following form:
- **int8(n) :** Creates an 8-bit integer with value n.
- **int16(n) :** Creates a 16-bit integer with value n.
- **int32(n) :** Creates a 32-bit integer with value n.
- **float(z) :** Creates a float with value z.
- **double(z) :** Creates a double with value z.

**pop:** Unstacks the value from the top of the stack. If the stack is empty, the
program execution must stop with an error.

**dump:** Displays each value of the stack, from the most recent one to the oldest
one WITHOUT CHANGING the stack. Each value is separated from the next one
by a newline.

**assert **v: Asserts that the value at the top of the stack is equal to the one passed
as parameter for this instruction. If it is not the case, the program execution must
stop with an error. The value v has the same form that those passed as parameters
to the instruction push.

**add:** Unstacks the first two values on the stack, adds them together and stacks the
result. If the number of values on the stack is strictly inferior to 2, the program
execution must stop with an error.

**sub:** Unstacks the first two values on the stack, subtracts them, then stacks the
result. If the number of values on the stack is strictly inferior to 2, the program
execution must stop with an error.

**mul:** Unstacks the first two values on the stack, multiplies them, then stacks the
result. If the number of values on the stack is strictly inferior to 2, the program
execution must stop with an error.