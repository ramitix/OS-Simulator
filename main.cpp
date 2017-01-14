//Ramy Atalla

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
#include "CPU.h"

using namespace std;


void GeneratingSystem(int numberOfPrinters, int numberOfDisks,long int memorySize);
void RunningSystem(int numberOfPrinters, int numberOfDisks,long int memorySize);


int main()
{
    int Printers=0;
    int Disks=0;
    long int Memory=0;

    cout << "\t\t  _________________________OPERATING SYSTEM SIMULATION_________________________" <<endl<<endl;
    cout << "\t\t                                 SUMMURY OF INPUTS" <<endl;
    cout << "\t\t [A]: Creates a process"<<"              |     "<<"[S]: Snapshots of: " <<endl;
    cout << "\t\t [t]:terminates process in the CPU"<<"   |         "<<"[r]: ready queue"<<endl;
    cout << "\t\t [pX]: CPU sends job to printer X"<<"    |         "<<"[i]: I/O devices"<<endl;
    cout << "\t\t [PX]: Printer X job Compeletion"<<"     |         "<<"[m]: Memory"<<endl;
    cout << "\t\t [dX]: CPU sends job to disk X"<<"       |"<<endl;
    cout << "\t\t [DX]: Disk Y job Compeletion"<<"        |"<<endl<<endl;

    GeneratingSystem(Printers, Disks, Memory);

    return 0;
}
void GeneratingSystem(int numberOfPrinters, int numberOfDisks,long int memorySize){
        cout <<endl<<"\tBUILDING UP THE SYSTEM..."<<endl;
        cout <<"\t>PLEASE ENTER THE AMOUNT OF I/O DEVICES IN THE SYSTEM"<<endl;
        cout << "\t\t>Printers  : ";
        cin >> numberOfPrinters;
        cout << "\t\t>Disks     : ";
        cin >> numberOfDisks;
        cout <<"\t>PLEASE ENTER THE AMOUNT OF MEMORY IN THE SYSTEM (in Bytes)"<<endl;
        cout << "\t\t>RAM       : ";
        cin >> memorySize;
        cout << endl;
        RunningSystem(numberOfPrinters, numberOfDisks, memorySize);
}
void RunningSystem(int numberOfPrinters, int numberOfDisks,long int memorySize){
        int processSize;
        int fileSizePrinter;
        int fileSizeDisk;
        string input;
        string fileNamePrinter;
        string fileNameDisk;
        vector<Printer> printers;
        vector<Disk> disks;
        int processID = 1;
        int processPriority = 0;
        int n = 1;

        CPU cpu;
        Memory Memory(memorySize);

        for (int i=1; i<=numberOfPrinters; i++){
            Printer printer;
            printer.SetPrinterNumber(i);
            printers.push_back(printer);
        }
        for (int i=1; i<=numberOfDisks; i++){
            Disk disk;
            disk.SetDiskNumber(i);
            disks.push_back(disk);
        }

        cout<< "\tSYSTEM IS RUNNING"<<endl;

        while(n!=0){
            cout << "\t\t> Please enter an input : ";
            cin >> input;
            while(input != "A" &&input != "S" && input[0] != 'p' && input[0] != 'P'&& input[0] != 'd' && input[0] != 'D' && input!="t"){
                    cout << "\t\t> Please enter an input : ";
                    cin >> input;
            }
            if(input == "A"){
                cout << "\t\t> Enter the Size of your new Process : ";
                cin >> processSize;
                cout << "\t\t> Enter the Priority of your new Process : ";
                cin >> processPriority;
                cout << endl<<"\t\t> Creating new process ..." <<endl<<endl;
               // cout<<Memory.GetFreeMemory()<<endl;
                if(processSize > Memory.GetFreeMemory()){
                        cout << "\t\t > ERROR: YOUR PROCESS SIZE IS BIGGER THAN THE FREE MEMORY" <<endl;
                    }else{
                        PCB* newProcess = new PCB(processSize);
                        newProcess->SetProcessID(processID);
                        newProcess->SetProcessState("READY");
                        newProcess->SetProcessPriority(processPriority);
                        cpu.AddToReadyQueue(newProcess);
                        Memory.InsertToMemory(newProcess,cpu);
                        processID++;
                        cout << "\t\t> Process Created succesfully" <<endl<<endl;
                    }


            }else if(input == "t"){
                    cout << "\t\t> Terminating the process in the CPU ..." <<endl;
                    cpu.TerminateProcess(Memory);


            }else if(input[0] == 'p' ){
                int printerNumber = (int)input[1]-48;
               // cout<<printerNumber;
                if(printerNumber > numberOfPrinters){
                     cout << "\t\t>ERROR: Printer does't exist "<<endl<<endl;
                }else{
                     cout << "\t\t>Please enter the NAME of the file to print: ";
                     cin >> fileNamePrinter;
                     cout << "\t\t>Please enter the SIZE of the file to print: ";
                     cin >>fileSizePrinter;
                     cpu.AddProcessToPrinter(printerNumber,fileNamePrinter,fileSizePrinter,printers);

                }


            }else if(input[0] == 'd'){
                int diskNumber = (int)input[1]-48;
                if(diskNumber > numberOfDisks){
                     cout << "\t\t>ERROR: Disk does't exist "<<endl<<endl;
                }else{
                     cout << "\t\t>Please enter the NAME of the file to disk: ";
                     cin >> fileNameDisk;
                     cout << "\t\t>Please enter the SIZE of the file to disk: ";
                     cin >>fileSizeDisk;
                     cpu.AddProcessToDisk(diskNumber,fileNameDisk,fileSizeDisk,disks);

                }


            }else if(input[0] == 'P'){
                int printerNumber = (int)input[1]-48;
              //  cout<<printerNumber;
                if(printerNumber > numberOfPrinters){
                     cout << "\t\t>ERROR: Printer does't exist "<<endl<<endl;
                }else{
                     printers[printerNumber-1].PrintingCompelete(cpu);
                     cout << "\t\t> PRINTER: Process at Printer "<<printerNumber << " compeleted " <<endl<<endl;
                }


            }else if(input[0] == 'D'){
                int diskNumber = (int)input[1]-48;
                if(diskNumber > numberOfDisks){
                     cout << "\t\t>ERROR: Disk does't exist "<<endl<<endl;
                }else{
                     disks[diskNumber-1].TaskCompelete(cpu);
                     cout << "\t\t> Disk: Process at disk "<<diskNumber << " compeleted " <<endl<<endl;
                }


            }else if(input == "S"){
                cout << "\t\t> Please enter one input [ r ] or [ i ] or [ m ] : ";
                cin >>input;
                while(input!="r" && input!="i" && input!="m"){
                    cout << "\t\t> Please enter one input [ r ] or [ i ] or [ m ] : ";
                    cin >> input;
                }
                if(input == "r"){
                    cout << cpu;
                }else if( input == "i"){
                    cout << "\t\t> PRINTERS SNAPSHOT"<<endl;
                    for (int i=0; i<printers.size(); i++) {
                        cout << "\t\t\t"<< printers[i] << endl;
                    }
                    cout <<endl<<endl;
                    cout << "\t\t> DISKS SNAPSHOT"<<endl;
                    for (int i=0; i<disks.size(); i++) {
                        cout << "\t\t\t"<< disks[i] << endl;
                    }
                }else if(input == "m"){
                    cout << Memory;

                }
            }
        }
}
