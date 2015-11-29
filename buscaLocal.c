#include "buscaLocal.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Sequence* sequencesList;
int main(){
	sequencesList = malloc(sizeof(Sequence));
	sequencesList->next = NULL;
	sequencesList->name = "toto";
	sequencesList->value = "--234---89----45-6----";
	GapBlock* blocks = findGapBlocks(sequencesList),*temp;
	temp = blocks;
	while(temp->next != NULL){
		printf("count deb %d fin %d \n",temp->beginning, temp->end);
		temp=temp->next;
	}
	//showGapBlocks(blocks);
	//constructList();
	//improveAlignment();
	char* toto = insertGap("1234567890123456789", 3,5);
	printf("WPK %s\n", toto);
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
GapBlock* findGapBlocks(Sequence* seq){
 int i, size = strlen(seq->value);
 char* str = malloc(size);
 strcpy(str, seq->value);
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