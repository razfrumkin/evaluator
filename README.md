# evaluator

An evaluator that can work with integer and boolean expressions as well as bitwise operations.

## Features
- Power operator (`^`)
- Arithmetic operators (`+`, `-`, `*`, `/`, `%`)
- Bitwise operators
  - Bitwise negation (`~`)
  - Bitwise left (`<<`)
  - Bitwise right (`>>`)
  - Bitwise and (`band`)
  - Bitwise or (`bor`)
  - Bitwise xor (`xor`)
- Boolean operators
  - And (`and`)
  - Or (`or`)
  - Not (`not`)
  - Equals (`==`)
  - Doesn't equal (`!=`)
  - Less than (`<`)
  - Greater than (`>`)
  - Less than or equal (`<=`)
  - Greater than or equal (`>=`)

## Notes
- Dividing between two integers will always result in an integer.
- Integers are not divisible by zero.
- Boolean expression are represented in 1 and 0 for true and false respectively.
- Errors are partially handled so the evaluator would output `NaN` for syntax errors.
