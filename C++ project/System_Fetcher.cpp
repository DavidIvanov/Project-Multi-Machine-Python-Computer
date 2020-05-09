#include <stdio.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <iostream>
#include <string>

using namespace std;

class System_Info{
    
    public:
    System_Info(){
        //Fetch system info for each system and initialize 
        #ifdef __APPLE__
        //used to get cpu speed
        int mib_cpu[] = {CTL_HW, HW_CPU_FREQ};
        size_t len_cpu = sizeof(CPU_speed);
        sysctl(mib_cpu, 2, &CPU_speed, &len_cpu, NULL, 0);
        //used to get ram size
        int mib_ram [] = { CTL_HW, HW_MEMSIZE };
        size_t len_ram = sizeof(RAM_size);
        sysctl(mib_ram, 2, &RAM_size, &len_ram, NULL, 0);
        
        #elif _WIN32

        #elif __linux__

        #endif

    }

    unsigned int get_CPU_speed(){
        return CPU_speed;
    }

    int64_t get_RAM_size(){
        return RAM_size;
    }

    private:
    unsigned int CPU_speed;
    int64_t RAM_size;

};

class System{

    public:
    void process_job(Job pJob){
        //will take in a job object and will run the appropriate interpreter on it
    }

    private:
    bool isMasterSystem;
    System_Info* SI;
    
    System(System_Info pSI){ //system is private as it will be called on its own 
        *SI = pSI;
        //will need to check for messages to know but for now will just set to true
        isMasterSystem = true;
    }

    ~System(){
        free(SI);
    }

};



class Job{
    public:
    string scriptFilePath;
    string dataFilePath;

    Job(char* pScriptFilePath, char* pdataFilePath){
        //intialize the file that will be executed.
        scriptFilePath.copy(pScriptFilePath, sizeof(pScriptFilePath)/sizeof(*pScriptFilePath), 0);
        dataFilePath.copy(pdataFilePath, sizeof(pdataFilePath)/sizeof(*pdataFilePath), 0);
    }


};




int main (){
    System_Info sys = System_Info();
    cout<< sys.get_CPU_speed() << "\n";
    cout<< sys.get_RAM_size() << "\n";
    
}