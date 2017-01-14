//Ramy Atalla
#include "Memory.h"

Memory::Memory( long int memorySize){
        freeMemory = memorySize;
        usedMemory = 0;
        totalMemory= memorySize;
        PCB* memoryBlock = new PCB(memorySize);
        memoryBlock->SetProcessMemStart(0);
        memoryBlock->SetProcessMemEnd(memorySize-1);
        memorySpace.push_back(memoryBlock);
}
 long int Memory::GetFreeMemory() const{
        return freeMemory;
}

 long int Memory::GetUsedMemory() const{
        return usedMemory;
}

 long int Memory::GetTotalMemory() const{
        return totalMemory;
}

void Memory::SetFreeMemory( long int memoryFree){
        freeMemory = memoryFree;
}
void Memory::SetUsedMemory( long int memoryUsed){
        usedMemory = memoryUsed;
}
void Memory::SetTotalMemory( long int memoryTotal){
        totalMemory = memoryTotal;
}

void Memory::MemoryFragmentationUpdate(){
            SetFreeMemory(0);
            SetUsedMemory(0);
            for (int i=0; i< memorySpace.size(); i++) {
            if (memorySpace[i]->GetProcessState() == "EMPTY"){
                freeMemory += memorySpace[i]->GetProcessSize();
            }else{
                usedMemory += memorySpace[i]->GetProcessSize();
        }
    }
}

void Memory::MemorySorting(){
        vector<PCB*> sortingVector;
        long int block=0;
        while(memorySpace.size() != sortingVector.size()){
                for(int i=0; i<memorySpace.size(); i++){
                    if(memorySpace[i]->GetProcessMemStart() == block){
                        sortingVector.push_back(memorySpace[i]);
                        block=memorySpace[i]->GetProcessMemEnd()+1;
                    }
                }
           }

        memorySpace.clear();
        memorySpace = sortingVector;
        MemoryFragmentationUpdate();
}

void Memory::InsertToMemory(PCB* pcb, CPU & cpu){

    int WorstFitBlock = -1;
     long int WorstFitBlockSize = 0;
  //   cout<<"memory checkpoint --1"<<endl;
    for (int i=0; i< memorySpace.size() ; i++){
        if(memorySpace[i]->GetProcessState()=="EMPTY" && memorySpace[i]->GetProcessID() == 0 && memorySpace[i]->GetProcessSize()>=pcb->GetProcessSize() )
        {
           //  cout<<"memory checkpoint --2"<<endl;
            if (memorySpace[i]->GetProcessSize()>WorstFitBlockSize ){
              WorstFitBlockSize= memorySpace[i]->GetProcessSize();
              WorstFitBlock = i;
           //    cout<<"memory checkpoint --3"<<endl;
            }
        }
    }

    if(WorstFitBlock != -1 && WorstFitBlockSize != 0){
    //         cout<<"memory checkpoint --4"<<endl;
        pcb->SetProcessMemStart(memorySpace[WorstFitBlock]->GetProcessMemStart());
        pcb->SetProcessMemEnd(memorySpace[WorstFitBlock]->GetProcessMemStart()+pcb->GetProcessSize()-1);
        memorySpace[WorstFitBlock]->SetProcessMemStart(pcb->GetProcessMemEnd()+1);
        memorySpace[WorstFitBlock]->SetProcessSize(memorySpace[WorstFitBlock]->GetProcessSize()-pcb->GetProcessSize());
        memorySpace.push_back(pcb);
  //   cout<<"memory checkpoint --5"<<endl;
        MemorySorting();
        cout << "\t\t> Memory: NEW PROCESS INSERTED INTO MEMOERY " << endl;
    }else{

            cout << "\t\t> Memory: THERE IS NO MEMORY FOR THE NEW PROCESS " << endl;
        }
}


void Memory::DeleteAndMergeMemory(int terminatedProcessId){

        int memoryBlock=0;
        for (int i=0; i< memorySpace.size(); i++) {
                if(terminatedProcessId == memorySpace[i]->GetProcessID() ){
                    memoryBlock = i;
                    memorySpace[memoryBlock]->SetProcessID(0);
                    memorySpace[memoryBlock]->SetProcessState("EMPTY");
                }
            }

    if (memorySpace[memoryBlock]->GetProcessMemStart()==0 && memorySpace[memoryBlock]->GetProcessMemEnd() < totalMemory-1 && memorySpace[memoryBlock]->GetProcessID() == 0 && memorySpace[memoryBlock]->GetProcessState() == "EMPTY") {
         for (int x=0; x< memorySpace.size(); x++) {
                if(memorySpace[x]->GetProcessMemStart() == memorySpace[memoryBlock]->GetProcessMemEnd()+1 && memorySpace[x]->GetProcessID() == 0 && memorySpace[x]->GetProcessState() == "EMPTY" ){
                    memorySpace[x]->SetProcessMemStart(memorySpace[memoryBlock]->GetProcessMemStart());
                    memorySpace[x]->SetProcessSize(memorySpace[x]->GetProcessSize() + memorySpace[memoryBlock]->GetProcessSize());
                    memorySpace.erase(memorySpace.begin()+memoryBlock);
                    MemoryFragmentationUpdate();
                }
         }
    }

    if (memorySpace[memoryBlock]->GetProcessMemEnd()==totalMemory-1 && memorySpace[memoryBlock]->GetProcessID() == 0 && memorySpace[memoryBlock]->GetProcessState() == "EMPTY") {
         for (int x=0; x< memorySpace.size(); x++) {
                if(memorySpace[x]->GetProcessMemEnd() == memorySpace[memoryBlock]->GetProcessMemStart()-1 && memorySpace[x]->GetProcessID() == 0 && memorySpace[x]->GetProcessState() == "EMPTY" ){
                    memorySpace[x]->SetProcessMemEnd(memorySpace[memoryBlock]->GetProcessMemEnd());
                    memorySpace[x]->SetProcessSize(memorySpace[x]->GetProcessSize()+memorySpace[memoryBlock]->GetProcessSize());
                    memorySpace.erase(memorySpace.begin()+memoryBlock);
                    MemoryFragmentationUpdate();
                }
         }
    }

    if (memorySpace[memoryBlock]->GetProcessMemStart()>0 && memorySpace[memoryBlock]->GetProcessMemEnd() < totalMemory-1 && memorySpace[memoryBlock]->GetProcessID() == 0 && memorySpace[memoryBlock]->GetProcessState() == "EMPTY") {
         for (int x=0; x< memorySpace.size(); x++) {
                  for (int y=0; y< memorySpace.size(); y++) {
                if(memorySpace[x]->GetProcessMemEnd() == memorySpace[memoryBlock]->GetProcessMemStart()+1 && memorySpace[y]->GetProcessMemStart() == memorySpace[memoryBlock]->GetProcessMemEnd()+1 &&memorySpace[x]->GetProcessID() == 0 && memorySpace[x]->GetProcessState() == "EMPTY" &&memorySpace[y]->GetProcessID() == 0 && memorySpace[y]->GetProcessState() == "EMPTY"){
                    memorySpace[x]->SetProcessMemEnd(memorySpace[y]->GetProcessMemEnd());
                    memorySpace[x]->SetProcessSize(memorySpace[x]->GetProcessSize()+memorySpace[memoryBlock]->GetProcessSize()+memorySpace[y]->GetProcessSize());
                    memorySpace.erase(memorySpace.begin()+memoryBlock);
                    memorySpace.erase(memorySpace.begin()+y);
                    MemoryFragmentationUpdate();
                }
            }
        }
    }

        if (memorySpace[memoryBlock]->GetProcessID() == 0 && memorySpace[memoryBlock]->GetProcessState() == "EMPTY") {
         for (int x=0; x< memorySpace.size(); x++) {
                if(memorySpace[x]->GetProcessMemEnd() == memorySpace[memoryBlock]->GetProcessMemStart()-1 && memorySpace[x]->GetProcessID() == 0 && memorySpace[x]->GetProcessState() == "EMPTY" ){
                    memorySpace[x]->SetProcessMemEnd(memorySpace[memoryBlock]->GetProcessMemEnd());
                    memorySpace[x]->SetProcessSize(memorySpace[x]->GetProcessSize()+memorySpace[memoryBlock]->GetProcessSize());
                    memorySpace.erase(memorySpace.begin()+memoryBlock);
                    MemoryFragmentationUpdate();
                }

                if(memorySpace[x]->GetProcessMemStart() == memorySpace[memoryBlock]->GetProcessMemEnd()+1 && memorySpace[x]->GetProcessID() == 0 && memorySpace[x]->GetProcessState() == "EMPTY" ){
                    memorySpace[x]->SetProcessMemStart(memorySpace[memoryBlock]->GetProcessMemStart());
                    memorySpace[x]->SetProcessSize(memorySpace[x]->GetProcessSize()+memorySpace[memoryBlock]->GetProcessSize());
                    memorySpace.erase(memorySpace.begin()+memoryBlock);
                    MemoryFragmentationUpdate();
                }
         }
    }
}

vector<PCB*> Memory::GetMemory()const{
        return memorySpace;
}

ostream& operator << (ostream& out, Memory& memory){

    cout << endl<<"\t\t> MEMORY: Free MEMORY  : "<<memory.GetFreeMemory()  <<endl;
    cout << "\t\t> MEMORY: Used MEMORY  : "<<memory.GetUsedMemory()  <<endl;
    cout << "\t\t> MEMORY: Total MEMORY : "<<memory.GetTotalMemory() <<endl<<endl;
    cout << "\t\tMEMORY SNAPSHOT TABLE:"<<endl<<endl;
    cout <<setw(9)<<"PID"<<setw(5)<<"  PRIORITY"<<setw(8)<<"STATE"<<setw(8)<<"SIZE"<<setw(28)<<"MEMORY BLOCK [Start-End]"<<setw(10)<<"PRINTER"<<setw(10)<<"P.F.NAME" <<setw(10)<<"P.F.SIZE" <<setw(8)<<"DISK"<< setw(10) <<"D.F.NAME" << setw(10) <<"D.F.SIZE" <<endl;
    for (int i=0; i<memory.GetMemory().size(); i++) {
        out << *(memory.GetMemory()[i]);
    }
    cout <<endl;
    return out;

}

