//Ramy Atalla
#ifndef CPU_h
#define CPU_h
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <algorithm>
#include "PCB.h"
#include "IODEVICES.h"
#include "Memory.h"


using namespace std;

class PCB;
class Printer;
class Disk;
class Memory;


bool SortingPriority(PCB* a,PCB* b);

class CPU{

   public:

        list <PCB*> GetReadyQueue()const;

        void AddToReadyQueue(PCB* process);
        void TerminateProcess(Memory& memory);
        void AddProcessToPrinter(int number, string name , int size, vector<Printer>& printers);
        void AddProcessToDisk(int number, string name ,int size, vector<Disk>& disks);
//        bool SortingPriority(PCB* a,PCB* b);

        friend ostream& operator << (ostream& out, CPU& cpu);


    private:
        list <PCB*> readyQueue;

};
#endif //CPU_h
