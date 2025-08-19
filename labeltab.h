#ifndef LABELTAB_H
#define LABELTAB_H

#include "config.h"

typedef struct {
    char name[MAX_LABEL_LEN];
    int address;  // address in memory
} Label;

typedef struct {
    Label labels[MAX_LABELS];
    int count;
} LabelTab;

// Initialize label table
void initLabelTab(LabelTab *tab);

// Add a label with address
int addLabel(LabelTab *tab, const char *name, int address);

// Lookup address by label, returns -1 if not found
int lookupLabel(const LabelTab *tab, const char *name);

// Dump label table for debugging
void dumpLabelTable(const LabelTab *tab);

#endif // LABELTAB_H
