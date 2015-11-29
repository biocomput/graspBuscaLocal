#ifndef _BUSCA_
#define _BUSCA_

typedef struct sequence {
  char *name;
  char *value;
  struct sequence* next;
} Sequence;

typedef struct gapBlock {
  int beginning;
  int end;
  struct gapBlock* next;
} GapBlock;
void constructList();
void improveAlignment();
GapBlock *findGapBlocks(char* seq);
void showGapBlocks(GapBlock* gapArray);
void printGapBlock(GapBlock* toShow);
char* removePart(char* sentence, int beginning, int end);
char* insertGap(char* sentence,int position, int n);

void computeSequence(Sequence* seq);
void moveBlock(Sequence* seq, GapBlock* block);
int isInBlock(GapBlock* block, int i);
#endif