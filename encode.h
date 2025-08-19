#ifndef ENCODE_H
#define ENCODE_H

#include <stdint.h>
#include "parser.h"
#include "labeltab.h"

// Encode a parsed instruction into 32-bit machine code
uint32_t encodeInstruction(const ParsedInstruction *pi, const LabelTab *labels);

#endif // ENCODE_H
