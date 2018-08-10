#ifndef INPFILE_H
#define INPFILE_H

#include "Main.h"
using namespace std;

class INPFile {
public:
    void ReadFile(string);
    void ProcessData();
    void WriteFile(string);
    
    vector<float> getNormal(int, string);
    void implementNormal(int, string);
    void normalizeNormals();
    string printNormal(string);
    
    float SurfArea(int);
    vector<long> getPointsSurf(int);
    vector<long> getPointsElem(int, string, bool);
    
private:
    
    string PartName = "none";
    string InstanceName = "none";
    string EYoung="1";  //Young Modulus
    string nu="0";      //Poisson coefficient
    
    vector<vector<string>> NodesCoordinates;    //Vector containing the coordinates of each nodes [NodeNum, X, Y, Z]
    long NbNodes=0;
    vector<vector<string>> Elements;    //Vector containing the Elements, their type and the nodes composing them [ElemNum, type, Node1, Node2, ...]
    long NbElem=0;
    vector<vector<string>> Nsets;   //Vector containing each NodeSet [Name, NbNodes, Node1, Node2 ... ]
    long NbNsets=0;
    vector<vector<string>> Elsets;  //Vector containing each ElementSet [Name, NbElem, Elem1, Elem2 ... ]
    long NbElsets=0;
    vector<vector<string>> Surf;    //Vector containing the Elsets forming a surface [Name, Elset1, Elset2 ... ]
    long NbSurf=0;
    vector<vector<string>> BCs;     //Vector containing NodeSets and their limit condition [Name, Direction(1,2,3) or "ENCASTRE"]
    long NbBCs=0;
    vector<vector<string>> Loads;   //Vector containing NodeSets and the loading applied [Name, Direction, Value]
    long NbLoads=0;
    vector<vector<string>> Press;   //Vector containing SurfaceName and the pressure applied [Name, Value]
    long NbPress=0;
    vector<float> DimNodes = {0, 0, 0, 0, 0, 0};    //Dimension of the box containing the model [Xmin, Xmax, Ymin ...]

    vector<vector<float>> Normals;  //Vector containing the normal of each boundary node [NodeNum, X, Y, Z];
    vector<vector<string>> BCD; //Vector containing the Nodes with Dirichlet boundary conditions [NodeNum, Xconstraint (1/0), Yconstraint, Zconstraint]
    vector<vector<string>> BCN; //Vector containing the Nodes with Neumann boundary conditions [NodeNum, 1, ValorX, 2, ValorY, 3, ValorZ]
    long NbDir=0; //Number of nodes with Dirichlet boundary conditions
    long NbNeu=0; //Number of nodes with Neumann boundary conditions
    
    long numTempo=0;
    
    string trim(string);
    string split(string, char, int);
    string ToString(double,int,bool);    

};

#endif /* INPFILE_H */

