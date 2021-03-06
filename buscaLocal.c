#include "buscaLocal.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Sequence* sequencesList;
int main(){
	sequencesList = malloc(sizeof(Sequence));
	sequencesList->next = NULL;
	sequencesList->name = "toto";
	sequencesList->value = "--2348945-6----";
	// char* tmp = removePart(sequencesList->value,0,2);
	// printf("%s\n", tmp);
	computeSequence(sequencesList);
}

void showGapBlocks(GapBlock* gapArray){
	GapBlock* current;
	current = gapArray;
	do{
		printGapBlock(current);
		current = current->next;
	}while(current->next);
}
void printGapBlock(GapBlock* toShow){
	printf("Block début : %d fin : %d\n",toShow->beginning, toShow->end);
}
void computeSequence(Sequence* seq){
	GapBlock* blocks = findGapBlocks(seq->value),*temp;
	temp = blocks;
	while(temp->next != NULL){
		moveBlock(seq,temp);
		temp = temp->next;
	}
}
void moveBlock(Sequence* seq, GapBlock* block){
	int i;
	char* shortStr = removePart(seq->value,block->beginning, block->end+1), *tempStr ;
	GapBlock* blockShort = findGapBlocks(shortStr);
	for(i=0;i<=strlen(shortStr);i++){
		if(isInBlock(blockShort,i) == 0){
			tempStr = insertGap(shortStr,i,block->end-block->beginning+1);
			printf("etape %d : %s\n",i,tempStr);
		}
	}
}
int isInBlock(GapBlock* block, int i){
	GapBlock* temp = block;
	int ret = 0;
	do{
		if(i>temp->beginning && i<= temp->end){
			//printf("I : %d, beg %d end %d\n",i,temp->beginning,temp->end);
			ret = 1;
			break;
		}
		temp = temp->next;
	}while(temp->next != NULL);
	return ret;
}
GapBlock* findGapBlocks(char* seq){
 int i, size = strlen(seq);
 char* str = malloc(size);
 strcpy(str, seq);
 GapBlock *current, *gapArray, *before;
 gapArray = malloc(sizeof(GapBlock));
  gapArray->next = NULL;
  current = gapArray;
 for(i = 0;i<size;i++){
 	if(str[i]=='-'){
 		current->beginning = i;
 		do{
 			i++;
 		}while(str[i] =='-');
 		
 		current->end = i-1;
 		current->next = malloc(sizeof(GapBlock));
 		before = current;
 		current = current->next;
 		current->next = NULL;
 	}
 }
 return gapArray;
}
char* removePart(char* sentence, int beginning, int end){
	int strSize = strlen(sentence);
	if(beginning<=end && strSize>=end){
		int size = end-beginning;
		char *newStr = malloc(strlen(sentence)-size+1);
		strncpy(newStr,sentence,beginning);
		strncpy(newStr+beginning, sentence+end,strlen(sentence)-end+1);
		return newStr;
	}
	return ;
	
}
char* insertGap(char* sentence,int position, int n){
	char* newStr = malloc(strlen(sentence)+n),*gapString = malloc(n), *gap = "-";
	int count = 0;
	while(count<n){
		count++;
		strcat(gapString,gap);
	}
	strncpy(newStr,sentence,position);
	strcat(newStr,gapString);
	strncpy(newStr+position+n, sentence+position,strlen(sentence)-position+1);
	return newStr;
}