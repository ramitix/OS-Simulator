//Ramy Atalla
#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <list>
#include <string>
#include <queue>
#include <algorithm>
#include "PCB.h"
#include "IODEVICES.h"
#include "CPU.h"

using namespace std;

class PCB;
class CPU;


class Memory {

        public:
            Memory( long int memorySize);

            long int GetFreeMemory() const;
            long int GetUsedMemory() const;
            long int GetTotalMemory() const;

            void SetFreeMemory( long int memoryFree);
            void SetUsedMemory( long int memoryUsed);
            void SetTotalMemory( long int memoryTotal);

            void MemoryFragmentationUpdate();
            void MemorySorting();
            void InsertToMemory(PCB* pcb, CPU & cpu);
            void DeleteAndMergeMemory(int terminatedProcessId);

            vector<PCB*> GetMemory()const;
            friend ostream& operator << (ostream& out, Memory& memory);


        private:
            long int freeMemory;
            long int usedMemory;
            long int totalMemory;
            vector<PCB*> memorySpace;


};

#endif // MEMORY_H
