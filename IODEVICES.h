//Ramy Atalla
#ifndef IODEVICES_H
#define IODEVICES_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <algorithm>
#include "PCB.h"
#include "Memory.h"
#include "CPU.h"

using namespace std;
class PCB;
class CPU;

class Printer
{
     public:
        Printer();

        int GetPrinterNumber() const;
        void SetPrinterNumber(int pNumber);
        void AddProcessToPrinterQueue(PCB* pcbBlock);
        void PrintingCompelete(CPU& cpu);
        friend ostream& operator<<(ostream& out, Printer& printer);

      private:

        int printerNumber;
        queue<PCB*> printerQueue;
};

class Disk {

    public:
        Disk();


        int GetDiskNumber() const;
        void SetDiskNumber(int dNumber);
        void AddProcessToDiskQueue(PCB* pcbBlock);
        void TaskCompelete(CPU& cpu);
        friend ostream& operator<<(ostream& out, Disk& disk);

    private:

        int diskNumber;
        queue<PCB*> diskQueue;

};

#endif // IODEVICES_H


