#include "Table.h"

void CreateStore(char *filename);

//open the file containing the database
void OpenStore(char *filename);

//get first record in the physical order
struct data *FirstRec();

//get next record in the physical order
struct data * NextRec();

//get previous record in the physical order
struct data * PriorRec();

//get Nth record in the physical order
struct data *NRec(int n);

//insert a new record
void InsertRec(char *stat);

//delete current record
void DeleteRec();

//replace the current record with the new one
void UpdateRec(char *stat);

//make sure all changes are propagated to disk and close the database
void CloseStore(char *file);

void InsertRecFromFile(char *filename);

void PrintTable();

void SearchRec(char *stat);

void DisplyCatFile(char *file);

void Commit(char *file);

void FreeSpace();

void GetPage(int x);

void ShowBuf();