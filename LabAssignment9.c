#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
  int		id;
  char	name;
  int		order; 
};

// Fill out this structure
struct HashType
{
  int	key;
  struct RecordType	data;
  struct HashType *next;
};

// Compute the hash function
int hash(int x)
{
  return x % 23;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
  FILE* inFile = fopen(inputFileName, "r");
  int dataSz = 0;
  int i, n;
  char c;
  struct RecordType *pRecord;
  *ppData = NULL;

  if (inFile)
  {
    fscanf(inFile, "%d\n", &dataSz);
    *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
    // Implement parse data block
    
    if (*ppData == NULL)
    {
      printf("Cannot allocate memory\n");
      exit(-1);
    }
    for (i = 0; i < dataSz; ++i)
    {
      pRecord = *ppData + i;
      fscanf(inFile, "%d ", &n);
      pRecord->id = n;
      fscanf(inFile, "%c ", &c);
      pRecord->name = c;
      fscanf(inFile, "%d ", &n);
      pRecord->order = n;
    }

    fclose(inFile);
  }

  return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
  int i;
  printf("\nRecords:\n");
  for (i = 0; i < dataSz; ++i)
  {
    printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
  }
  printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
  int i;

  for (i=0;i<hashSz;++i)
  {
    // if index is occupied with any records, print all
    if(pHashArray!=NULL){
      printf("index %d -> %d, %c, %d\n", i, pHashArray->data.id,pHashArray->data.name, pHashArray->data.order);
    }
  }
}

int main(void)
{
  struct RecordType *pRecords;
  int recordSz = 0;

  recordSz = parseData("input.txt", &pRecords);
  printRecords(pRecords, recordSz);
  // Your hash implementation
  struct HashType hashTable[23]={0};
  int i;
  for(i=0;i<recordSz;++i){
    struct RecordType *pRecord=&pRecords[i];
    int index=hash(pRecord->id);
    if(hashTable[index].data.id==0){
      hashTable[index].data=*pRecord;
    }else{
      struct HashType *pNext=&hashTable[index];
      while(pNext->next!=NULL){
        pNext=pNext->next;
      }
    }
          
    
    }
  
  displayRecordsInHash(hashTable, 23);
  for(i=0;i<23;++i){
    struct HashType *pNext=&hashTable[i];
    while(pNext!=NULL){
      free(pNext);
      pNext=pNext->next;
    }
  }
  free(pRecords);
  return 0;
}
  
