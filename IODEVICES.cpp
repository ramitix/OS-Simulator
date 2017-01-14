//Ramy Atalla
#include "IODEVICES.h"


Printer::Printer(){
        printerNumber = 0 ;
}

void Printer::SetPrinterNumber(int pNumber){
        printerNumber = pNumber;
}


int Printer::GetPrinterNumber() const{
        return printerNumber;
}

void Printer::AddProcessToPrinterQueue(PCB* pcbBlock){
        pcbBlock->SetProcessPrinterNumber(printerNumber);
        printerQueue.push(pcbBlock);
}
void Printer:: PrintingCompelete(CPU& cpu){
        if (!printerQueue.empty()) {
            printerQueue.front()->SetProcessState("READY");
            printerQueue.front()->SetProcessPrinterNumber(0);
            printerQueue.front()->SetProcessPrinterFileName("N/A");
            printerQueue.front()->SetProcessPrinterFileSize(0);
            cpu.AddToReadyQueue(printerQueue.front());
            printerQueue.pop();
        }
}
ostream& operator<<(ostream& out, Printer& printer){
        out<< "PRINTER_"<<printer.GetPrinterNumber()<< endl;
        queue<PCB*> printerOutput = printer.printerQueue;
        int index = 0;
        while (!printerOutput.empty()) {
            if (index == 0){
                cout <<"\t\t\t\tPRINTER SNAPSHOT:"<<endl;
                cout <<"\t\t\t\tPRINTING : PID [ "<< printerOutput.front()->GetProcessID() <<" ]";
                cout <<"\t\t File_NAME [ "<< printerOutput.front()->GetProcessPrinterFileName() <<" ]";
                cout <<"\t\t File_Size [ "<< printerOutput.front()->GetProcessPrinterFileSize() <<" ]"<<endl;
            }else{
                cout << "\t\t\t\tWAITING  : PID [ "<<printerOutput.front()->GetProcessID() <<" ]";
                cout <<"\t\t File_NAME [ "<< printerOutput.front()->GetProcessPrinterFileName() <<" ]";
                cout <<"\t\t File_Size [ "<<printerOutput.front()->GetProcessPrinterFileSize()<<" ]";
            }
            printerOutput.pop();
            index++;
        }
        return out;
}



Disk::Disk(){
    diskNumber = 0;
}

void Disk::SetDiskNumber(int dNumber){
    diskNumber = dNumber;
}

int Disk:: GetDiskNumber() const{
        return diskNumber;
}
void Disk:: AddProcessToDiskQueue(PCB* pcbBlock){
         pcbBlock->SetProcessDiskNumber(diskNumber);
         diskQueue.push(pcbBlock);
}

void Disk:: TaskCompelete(CPU& cpu){
         if (!diskQueue.empty()) {
            diskQueue.front()->SetProcessState("READY");
            diskQueue.front()->SetProcessDiskNumber(0);
            diskQueue.front()->SetProcessDiskFileName("N/A");
            diskQueue.front()->SetProcessDiskFileSize(0);
            cpu.AddToReadyQueue(diskQueue.front());
            diskQueue.pop();
}
}
ostream& operator<<(ostream& out, Disk& disk){
        out<< "DISK_"<<disk.GetDiskNumber()<< endl;
        queue<PCB*> diskOutput = disk.diskQueue;
        int index = 0;
        while (!diskOutput.empty()) {
            if (index == 0){
                cout <<"\t\t\t\tDISK SNAPSHOT:"<<endl;
                cout <<"\t\t\t\tW/R ON DISK : PID [ "<< diskOutput.front()->GetProcessID() <<" ]";
                cout <<"\t\t File_NAME [ "<< diskOutput.front()->GetProcessDiskFileName() <<" ]";
                cout <<"\t\t File_Size [ "<< diskOutput.front()->GetProcessDiskFileSize() <<" ]"<<endl;
            }else{
                cout << "\t\t\t\tWAITING    : PID [ "<<diskOutput.front()->GetProcessID() <<" ]";
                cout <<"\t\t File_NAME [ "<< diskOutput.front()->GetProcessDiskFileName() <<" ]";
                cout <<"\t\t File_Size [ "<<diskOutput.front()->GetProcessDiskFileSize()<<" ]";
            }
            diskOutput.pop();
            index++;

        }
       return out;
}








