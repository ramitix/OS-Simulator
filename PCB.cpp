//Ramy Atalla
#include "PCB.h"


PCB::PCB( ){
        processID = 0;
        processPriority = -1;
        processState = "EMPTY";
        processSize = 0;
        processMemStart = -1;
        processMemEnd = -1;
        processPrinterNumber = 0;
        processDiskNumber = 0;
        processPrinterFileName = "N/A" ;
        processDiskFileName = "N/A";
        processPrinterFileSize = 0;
        processDiskFileSize = 0;
}
PCB::PCB( long int size){
        processID = 0;
        processPriority = -1;
        processState = "EMPTY";
        processSize = size;
        processMemStart = -1;
        processMemEnd = -1;
        processPrinterNumber = 0;
        processDiskNumber = 0;
        processPrinterFileName = "N/A" ;
        processDiskFileName = "N/A";
        processPrinterFileSize = 0;
        processDiskFileSize = 0;
}



void PCB::SetProcessID(int id){
        processID = id;
}

void PCB::SetProcessPriority(int priority){
        processPriority = priority;
}

void PCB::SetProcessState(string state){
        processState = state;
}

void PCB::SetProcessSize( long int size){
        processSize = size;
}

void PCB::SetProcessMemStart( long int start){
    processMemStart = start;
}

void PCB::SetProcessMemEnd( long int end){
        processMemEnd = end;
}

void PCB::SetProcessPrinterNumber(int printerNo){
        processPrinterNumber = printerNo;
}
void PCB::SetProcessDiskNumber(int diskNo){
        processDiskNumber = diskNo;
}
void PCB::SetProcessPrinterFileName(string fileName){
        processPrinterFileName = fileName;
}

void PCB::SetProcessDiskFileName(string fileName){
        processDiskFileName = fileName;
}
void PCB::SetProcessPrinterFileSize(int fileSize){
        processPrinterFileSize = fileSize;
}
void PCB::SetProcessDiskFileSize(int fileSize){
        processDiskFileSize = fileSize;
}


int PCB::GetProcessID()const{
        return processID;
}

int PCB::GetProcessPriority()const{
        return processPriority;
}

string PCB::GetProcessState()const{
        return processState;
}

 long int PCB::GetProcessSize()const{
        return processSize;
}

 long int PCB::GetProcessMemStart()const{
        return processMemStart;
}
 long int PCB::GetProcessMemEnd()const{
        return processMemEnd;
}
int PCB::GetProcessPrinterNumber()const{
        return  processPrinterNumber;
}
int PCB::GetProcessDiskNumber()const{
        return processDiskNumber;
}
string PCB::GetProcessPrinterFileName()const{
        return processPrinterFileName;
}
string PCB::GetProcessDiskFileName()const{
        return processDiskFileName;
}
int PCB::GetProcessPrinterFileSize()const{
        return processPrinterFileSize;
}
int PCB::GetProcessDiskFileSize()const{
        return processDiskFileSize;
}


ostream& operator<<(ostream& out, PCB& pcb){
        cout <<setw(7)<<"(" <<pcb.GetProcessID()<<")"<<setw(9)<< pcb.GetProcessPriority()<<setw(9)<< pcb.GetProcessState()<<setw(10)<< pcb.GetProcessSize()<<" ["<<setw(9)<<pcb.GetProcessMemStart()<<" - "<<setw(10)<< pcb.GetProcessMemEnd()<< " ]"<<setw(9)<< pcb.GetProcessPrinterNumber()<<setw(9)<< pcb.GetProcessPrinterFileName()<<setw(9)<< pcb.GetProcessPrinterFileSize()<<setw(9)<< pcb.GetProcessDiskNumber()<<setw(9)<< pcb.GetProcessDiskFileName()<<setw(9)<< pcb.GetProcessDiskFileSize()<<endl;
        return out;
}




