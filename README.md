# MIPS Assembler

In MIPS assembly, instructions are classified into three main types: R-type, I-type, and J-type. Each type has its own
specific format in terms of how the instruction is encoded in a 32-bit binary representation.

# 1. R-Type Instruction Format:
```
31     26     21    16    11     6        0
+-------+------+-----+-----+------+-------+
|opcode | rs   | rt  | rd  |shamt | funct |
+-------+------+-----+-----+------+-------+
```

# 2. I-Type Instruction Format:
```
31     26     21    16                    0
+-------+------+-----+--------------------+
|opcode | rs   | rt  |     immediate      |
+-------+------+-----+--------------------+
```
# 3. J-Type Instruction Format:
```
31     26                                 0
+-------+---------------------------------+
|opcode |        target address           |
+-------+---------------------------------+
```
