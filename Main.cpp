
// /!\ there needs to be a surface or an element set called SURFACE_EXT which contains all the boundary nodes

#include "Main.h"

int main(int argc, char** argv) {

    string FilePathIN;
    string FilePathOUT;
    string FilePath;
    char* PathChar;
    
    PathChar=argv[1];
    if (PathChar == NULL)
    {
        FilePath="/home/max/file.inp";
    }
    else
    {
        FilePath=string(PathChar);
    }
    FilePathIN = FilePath;
    FilePathOUT = FilePath.erase(FilePath.size()-4,FilePath.size()) + "_collocation.inp";
    
    time_t tstart, tend;
    tstart = time(0);
    
    std::cout << "File loaded : " << FilePathIN << endl;
    
    INPFile NewFile;
    std::cout << "Reading file ..." << endl;
    NewFile.ReadFile(FilePathIN);
    std::cout << "Processing data ..." << endl;
    NewFile.ProcessData();
    std::cout << "Writing new file ..." << endl;
    NewFile.WriteFile(FilePathOUT);
    
    tend = time(0);
    std::cout << "Done, time spent : " << difftime(tend, tstart) << "s" << endl;
    std::cout << "Output file : " << FilePathOUT << endl;
    
    return 0;
}