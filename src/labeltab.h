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

// function prototypes
void initLabelTab(LabelTab *tab);
int addLabel(LabelTab *tab, const char *name, int address);
int lookupLabel(const LabelTab *tab, const char *name);
void dumpLabelTable(const LabelTab *tab);

#endif // LABELTAB_H
