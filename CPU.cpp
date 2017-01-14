//Ramy Atalla
#include "CPU.h"

bool SortingPriority(PCB* a,PCB* b){
    return (a->GetProcessPriority() < b->GetProcessPriority());
}

list<PCB*> CPU::GetReadyQueue()const{
        return readyQueue;
}

void CPU::AddToReadyQueue(PCB* process){
    //    cout<<"cpu checkpoint --1"<<endl;
        readyQueue.push_back(process);
    //     cout<<"cpu checkpoint --2"<<endl;
        readyQueue.front()->SetProcessState("READY");
        readyQueue.sort(SortingPriority); //sort(readyQueue.begin(),readyQueue.end(),SortingPriority);
    //     cout<<"cpu checkpoint --3"<<endl;
        readyQueue.front()->SetProcessState("RUNNING");
   //      cout<<"cpu checkpoint --4"<<endl;
        cout << "\t\t> CPU: NEW PROCESS ADDED TO THE READY QUEUE..."<<endl;
}

void CPU::TerminateProcess(Memory& memory){
        if(readyQueue.empty()){
            cout<< "\t\t> CPU: READY QUEUE IS EMPTY NO PROCESS TO TERMINATE..."<<endl;
        }else{
            readyQueue.front()->SetProcessState("EMPTY");
            readyQueue.front()->SetProcessPriority(-1);
            memory.DeleteAndMergeMemory(readyQueue.front()->GetProcessID());
            memory.DeleteAndMergeMemory(0);
            readyQueue.front()->SetProcessID(0);
            readyQueue.pop_front();
            if(!readyQueue.empty()){
                 readyQueue.front()->SetProcessState("RUNNING");
                 cout << "\t\t> Process Created succesfully" <<endl<<endl;
            }
        }
}

void CPU::AddProcessToPrinter(int number, string name , int size, vector<Printer> & printers){
            if (readyQueue.empty()) {
                cout << "\t\t> CPU: YOUR READY QUEUE IS EMPTY" <<endl;
            }else{
                    readyQueue.front()->SetProcessPrinterNumber(number);
                    readyQueue.front()->SetProcessPrinterFileName(name);
                    readyQueue.front()->SetProcessPrinterFileSize(size);
                    readyQueue.front()->SetProcessState("PRINTING");
                    printers[number-1].AddProcessToPrinterQueue(readyQueue.front());
                    readyQueue.pop_front();
                    cout << "\t\t\t> CPU: Process added to printer"<<number<<" succesfully" <<endl;
                    if(!readyQueue.empty()){
                    //    readyQueue.sort(SortingPriority);//sort(readyQueue.front(),readyQueue.back(),SortingPriority);
                        readyQueue.front()->SetProcessState("RUNNING");
                    }
            }
}

void CPU::AddProcessToDisk(int number, string name ,int size, vector<Disk>& disks){
            if (readyQueue.empty()) {
                cout << "\t\t > CPU: YOUR READY QUEUE IS EMPTY" <<endl;
            }else{
                    readyQueue.front()->SetProcessDiskNumber(number);
                    readyQueue.front()->SetProcessDiskFileName(name);
                    readyQueue.front()->SetProcessDiskFileSize(size);
                    readyQueue.front()->SetProcessState("W/R");
                    disks[number-1].AddProcessToDiskQueue(readyQueue.front());
                    readyQueue.pop_front();
                    cout << "\t\t\t\t> CPU: Process Left CPU to disk"<<number<<" succesfully" <<endl;
                    if(!readyQueue.empty()){
                      //  readyQueue.sort(SortingPriority);//sort(readyQueue.front(),readyQueue.back(),SortingPriority);
                        readyQueue.front()->SetProcessState("RUNNING");
                    }
            }
}



ostream& operator << (ostream& out, CPU& cpu){
        if(cpu.readyQueue.empty()){
           cout << "\t\t> CPU: YOUR READY QUEUE IS EMPTY" <<endl<<endl;
        }else{
            list<PCB*> cpuOutput = cpu.readyQueue;
            cout <<"\t\tREADY QUEUE SNAPSHOT TABLE:" <<endl<<endl;;
            cout <<setw(9)<<"PID"<<setw(5)<<"  PRIORITY"<<setw(8)<<"STATE"<<setw(8)<<"SIZE"<<setw(28)<<"MEMORY BLOCK [Start-End]"<<setw(10)<<"PRINTER"<<setw(10)<<"P.F.NAME" <<setw(10)<<"P.F.SIZE" <<setw(8)<<"DISK"<< setw(10) <<"D.F.NAME" << setw(10) <<"D.F.SIZE" <<endl;
            while (!cpuOutput.empty()) {
            out << *(cpuOutput.front());
            cpuOutput.pop_front();
        }
        cout <<endl;
        }
        return out;
    }

