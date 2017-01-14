//Ramy Atalla
#ifndef PCB_H
#define PCB_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <list>
#include <string>
#include <queue>
#include <algorithm>
#include "IODEVICES.h"
#include "Memory.h"
#include "CPU.h"

using namespace std;

class PCB {
            public:

                PCB();
                PCB( long int size);

                void SetProcessID(int id);
                void SetProcessPriority(int priority);
                void SetProcessState(string state);
                void SetProcessSize( long int size);
                void SetProcessMemStart( long int start);
                void SetProcessMemEnd( long int end);
                void SetProcessPrinterNumber(int printerNo);
                void SetProcessDiskNumber(int diskNo);
                void SetProcessPrinterFileName(string fileName);
                void SetProcessDiskFileName(string fileName);
                void SetProcessPrinterFileSize(int fileSize);
                void SetProcessDiskFileSize(int fileSize);

                int GetProcessID()const;
                int GetProcessPriority()const;
                string GetProcessState()const;
                long int GetProcessSize()const;
                long int GetProcessMemStart()const;
                long int GetProcessMemEnd()const;
                int GetProcessPrinterNumber()const;
                int GetProcessDiskNumber()const;
                string GetProcessPrinterFileName()const;
                string GetProcessDiskFileName()const;
                int GetProcessPrinterFileSize()const;
                int GetProcessDiskFileSize()const;


                friend ostream& operator<<(ostream& out, PCB& pcb);

            private :
                int processID;
                int processPriority;
                string processState;
                long int processSize;
                long int processMemStart;
                long int processMemEnd;
                int processPrinterNumber;
                int processDiskNumber;
                string processPrinterFileName;
                string processDiskFileName;
                int processPrinterFileSize;
                int processDiskFileSize;

};
#endif // PCB_H
