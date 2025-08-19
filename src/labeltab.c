#include <stdio.h>
#include <string.h>
#include "labeltab.h"

void initLabelTab(LabelTab *tab) {
    tab->count = 0;
}

int addLabel(LabelTab *tab, const char *name, int address) {
    if (tab->count >= MAX_LABELS) return 0; // table full

    // Avoid duplicates
    for (int i = 0; i < tab->count; i++) {
        if (strcmp(tab->labels[i].name, name) == 0) return 0;
    }

    strncpy(tab->labels[tab->count].name, name, MAX_LABEL_LEN-1);
    tab->labels[tab->count].name[MAX_LABEL_LEN-1] = '\0';
    tab->labels[tab->count].address = address;
    tab->count++;
    return 1;
}

int lookupLabel(const LabelTab *tab, const char *name) {
    for (int i = 0; i < tab->count; i++) {
        if (strcmp(tab->labels[i].name, name) == 0) {
            return tab->labels[i].address;
        }
    }
    return -1; // not found
}

void dumpLabelTable(const LabelTab *tab) {
    if (!tab) {
        printf("Label table is NULL\n");
        return;
    }

    if (tab->count == 0) {
        printf("Label table is empty.\n");
        return;
    }

    printf("\n--- Label Table ---\n");
    for (int i = 0; i < tab->count; i++) {
        printf("%d: %-10s -> %d\n", i, tab->labels[i].name, tab->labels[i].address);
    }
    printf("-------------------\n\n");
}
