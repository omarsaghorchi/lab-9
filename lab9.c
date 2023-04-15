#include <stdio.h>
#include <stdlib.h>


struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType *next;
};


struct HashType
{
    struct RecordType* record; 
};


int hash(int x, int tableSize)
{
  return x % tableSize;
}


int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        
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
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}


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


void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    int index = hash(record->id, tableSize); 
  

    if (hashTable[index].record == NULL)
    {
        hashTable[index].record = record; 
    }
    else
    {
        struct RecordType* current = hashTable[index].record;
        while (current->next != NULL)
        {
            current = current->next; 
        }
        current->next = record; 
    }
}


void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    for (int i = 0; i < tableSize; ++i)
    {
        printf("Index %d -> ", i);
        struct RecordType* current = hashTable[i].record;
        while (current != NULL)
        {
            printf("%d, %c, %d -> ", current->id, current->name, current->order);
            current = current->next; 
        }
        printf("NULL\n");
    }
}

int main(void)
{
    struct RecordType* pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    int hashTableSize = 10; 
    struct HashType* hashTable = (struct HashType*)calloc(hashTableSize, sizeof(struct HashType));  

    for (int i = 0; i < recordSz; ++i)
    {
        insertRecord(hashTable, &pRecords[i], hashTableSize); 
    }

    displayRecordsInHash(hashTable, hashTableSize); 


  
    free(pRecords);
    free(hashTable);

    return 0;
}

