#include "INPFile.h"

void INPFile::ReadFile (string Value) {

    ifstream File;
    string str=" ";
    char Path[Value.length()+1];
    strncpy(Path, Value.c_str(),Value.length()+1);
    long i;
    File.open(Path, ios::in);
    getline(File,str);
    
    while (split(str,',',0)!="** OUTPUT REQUESTS") {
        
        //std::cout << str << endl;
        
        if (split(str,',',0)=="*Part") {
            PartName = split(split(str,',',1),'=',1);
            getline(File,str);
        }
        
        else if (split(str,',',0)=="*Node") {
            i=0;
            getline(File, str);
            while(str[0]!='*') {
                NodesCoordinates.push_back(vector<string>(4));
                NodesCoordinates [i][0] = split(str,',',0);
                for (int j=1; j<4; j++) {
                    NodesCoordinates [i][j] = split(str,',',j);
                    if (i==0)
                        DimNodes[2*(j-1)]=stof(split(str,',',j));
                    else if (i==1)
                        if (stof(split(str,',',j))<DimNodes[2*(j-1)]) {
                            DimNodes[2*j-1]=DimNodes[2*(j-1)];
                            DimNodes[2*(j-1)]=stof(split(str,',',j));
                        }
                        else DimNodes[2*j-1]=stof(split(str,',',j));
                    else {
                        if (stof(split(str,',',j))<DimNodes[2*(j-1)]) DimNodes[2*(j-1)]=stof(split(str,',',j));
                        if (stof(split(str,',',j))>DimNodes[2*j-1]) DimNodes[2*j-1]=stof(split(str,',',j));
                    }
                }
                i++; getline(File, str);
            }
            NbNodes = i;
        }
        
        else if (split(str,',',0)=="*Element") {
            string type = split(split(str,',',1),'=',1);
            getline(File,str);
            while (str[0]!='*') {
                vector<string> temp;
                temp.push_back(split(str,',',0));
                temp.push_back(type);
                i=1;
                while (split(str,',',i)!="") {
                    temp.push_back(split(str,',',i));
                    i++;
                    if (i==16 && type=="C3D20R") {getline(File,str); i=0;}
                }
                Elements.push_back(temp);
                NbElem++;
                getline(File,str);
            }
        }
        
        else if (split(str,',',0)=="*Instance" && split(split(str,',',2),'=',1)==PartName) {
            InstanceName=split(split(str,',',1),'=',1);
            getline(File, str);
        }
        
        else if (split(str,',',0)=="*Nset") {
            if (split(str,',',3)=="generate" || split(str,',',4)=="generate")  {
                Nsets.push_back(vector<string>(2));
                Nsets[NbNsets][0] = split(split(str,',',1),'=',1);
                i=0;
                getline(File,str);
                for (int j=stoi(split(str,',',0)); j<stoi(split(str,',',1))+1; j+=stoi(split(str,',',2))) {
                    Nsets[NbNsets].push_back(to_string(j));
                    i++;
                }
                Nsets[NbNsets][1] = to_string(i);
                NbNsets++;
                getline(File,str);
            }
            else {
                Nsets.push_back(vector<string>(2));
                Nsets[NbNsets][0] = split(split(str,',',1),'=',1);
                i=0;
                long j=0;
                getline(File,str);
                while(str[0]!='*' && split(str,',',i)!="") {
                    Nsets[NbNsets].push_back(split(str,',',i));
                    i++; j++;
                    if (i==16) {getline(File,str); i=0;}
                    else if (split(str,',',i)=="" || split(str,',',i)[1]==NULL) getline(File,str);
                }
                Nsets[NbNsets][1]=to_string(j);
                NbNsets++;
            }
        }
        
        else if (split(str,',',0)=="*Elset") {
            if (split(str,',',3)=="generate" || split(str,',',4)=="generate")  {
                Elsets.push_back(vector<string>(2));
                Elsets[NbElsets][0] = split(split(str,',',1),'=',1);
                i=0;
                getline(File,str);
                for (long j=stoi(split(str,',',0)); j<stoi(split(str,',',1))+1; j+=stoi(split(str,',',2))) {
                    Elsets[NbElsets].push_back(to_string(j));
                    i++;
                }
                Elsets[NbElsets][1] = to_string(i);
                NbElsets++;
                getline(File,str);
            }
            else {
                Elsets.push_back(vector<string>(2));
                Elsets[NbElsets][0] = split(split(str,',',1),'=',1);
                i=0;
                long j=0;
                getline(File,str);
                while(str[0]!='*' && split(str,',',i)!="") {
                    Elsets[NbElsets].push_back(split(str,',',i));
                    i++; j++;
                    if (i==16) {getline(File,str); i=0;}
                    else if (split(str,',',i)=="" || split(str,',',i)[1]==NULL) getline(File,str);
                }
                Elsets[NbElsets][1]=to_string(j);
                NbElsets++;
            }
        }
        
        else if (split(str,',',0)=="*Boundary") {
            getline(File,str);
            while(str[0]!='*') {
                BCs.push_back(vector<string>(2));
                for(i=0; i<2; i++) {
                    BCs[NbBCs][i]=split(str,',',i);
                }
                NbBCs++;
                getline(File,str);
            }
        }
        
        else if (split(str,',',0)=="*Cload") {
            getline(File,str);
            while(str[0]!='*') {
                Loads.push_back(vector<string>(3));
                for(i=0; i<3; i++) {
                    Loads[NbLoads][i]=split(str,',',i);
                }
                NbLoads++;
                getline(File,str);
            }
        }
        
        else if (split(str,',',0)=="*Dsload") {
            getline(File,str);
            while(str[0]!='*') {
                Press.push_back(vector<string>(2));
                Press[NbPress][0]=split(str,',',0);
                Press[NbPress][1]=split(str,',',2);
                NbPress++;
                getline(File,str);
            }
        }
        
        else if (split(str,',',0)=="*Surface") {
            vector<string> temp(2);
            i=0;
            temp[0]=split(split(str,',',2),'=',1);
            getline(File,str);
            while (str[0]!='*') {
                temp.push_back(split(str,',',0));
                getline(File,str);
                i++;
            }
            temp[1]=to_string(i);
            Surf.push_back(temp);
            NbSurf++;
        }
        
        else if (split(str,',',0)=="*Elastic") {
            getline(File,str);
            EYoung = split(str,',',0);
            nu = split(str,',',1);
            getline(File,str);
        }
        
        else getline(File,str);
    }
    std::cout << "Number of nodes : " << NbNodes << endl;
    std::cout << "Number of elements : " << NbElem << endl;
    File.close();
    
}


void INPFile::ProcessData() {
    
    // initialize the Normals vector at [NumNode, 0, 0, 0] (for each node)
    Normals = vector<vector<float>> (NbNodes, vector<float>(4));
    for (long i=0; i<NbNodes; i++) {
        Normals[i][0] = i+1;
    }
    
    long i=0;
    int NumSurf=-1;
    while (NumSurf==-1 && i<NbSurf) {   // search for the surface called SURFACE_EXT
        if (Surf[i][0]=="SURFACE_EXT") NumSurf = i; else i++;
    }
    
    if (NumSurf!=-1) {
        for (int i=0; i<stoi(Surf[NumSurf][1]); i++) {
            numTempo=0;
            string NameElset = Surf[NumSurf][i+2];
            string SurfType = NameElset;
            int k = SurfType.size();
            while (SurfType[k]!='_') k--;
            SurfType.erase(0, k+1);
            
            long j=0;
            int NumElset=-1;
            while (NumElset==-1 && j<NbElsets) {
                if (Elsets[j][0]==NameElset) NumElset=j; else j++;
            }
            if (NumElset!=-1) {
                for (long j=0; j<stol(Elsets[NumElset][1]); j++) {
                    int NumElem = stoi(Elsets[NumElset][j+2]);
                    implementNormal(NumElem, SurfType);
                }
            }
        }
        numTempo = 0;
    }
    
    else {  // search for the Elset called SURFACE_EXT
        i=0;
        int NumElset=-1;
        while (NumElset==-1 && i<NbElsets) {
            if (Elsets[i][0]=="SURFACE_EXT") NumElset = i; else i++;
        }
        if (NumElset!=-1) {
            for (long j=0; j<stol(Elsets[NumElset][1]); j++) {
                int NumElem = stoi(Elsets[NumElset][j+2]);
                implementNormal(NumElem, " ");
            }
        }
        else std::cout << "Error, no surface nor element set containing the boundary nodes is defined" << endl;
    }
    normalizeNormals();
    
    
    for (long i=0; i<NbNodes; i++) {    // initialize the BCN vector at [NumNode, 1, 0, 2, 0, 3, 0] (all boundary nodes)
        if (!(Normals[i][1]==0 && Normals[i][2]==0 && Normals[i][3]==0)) {
            BCN.push_back(vector<string>(7));
            BCN[NbNeu][0]=to_string(int (Normals[i][0]));
            for (int h=1; h<4; h++) {
                BCN[NbNeu][2*h]='0';
                BCN[NbNeu][2*h-1]=to_string(h);
            }
            NbNeu++;
        }
    }
    
    
    for (int j=0;j<NbNsets;j++) {
        string name = Nsets[j][0];
        vector<int> BCNset;
        int k=0;
        while(k<NbBCs) {    // compute all the constraints
            if (BCs[k][0]==name) {BCNset.push_back(k);}
            k++;
        }
        if (BCNset.size()!=0) {
            for (int z=0; z<BCNset.size(); z++) {
                k=0;
                for (long i=0;i<stoi(Nsets[j][1]);i++) {
                    
                    long p=-1;
                    long a=0;
                    while(a<NbDir && p==-1)
                        if (Nsets[j][i+2]==BCD[a][0]) p=a; else a++;
                    if (p==-1) {
                        BCD.push_back(vector<string>(4));
                        BCD[NbDir][0] = Nsets[j][i+2];
                        for (int h=1;h<4;h++) BCD[NbDir][h]='0';
                        p = NbDir; NbDir++;
                    }
                    
                    a=0;
                    int numNode=-1;
                    while (numNode==-1 && a<NbNeu)
                        if (BCN[a][0]==BCD[p][0]) numNode=a; else a++;
                    
                    if (BCs[BCNset[z]][1]=="ENCASTRE" || BCs[BCNset[z]][1]=="PINNED") {
                        for (int h=1; h<4; h++) { BCD[p][h]='1'; BCN[numNode][2*h-1]="-1";}
                    }
                    else if (BCs[BCNset[z]][1]=="XSYMM") { BCD[p][1] = '1'; BCN[numNode][1]="-1";}
                    else if (BCs[BCNset[z]][1]=="YSYMM") { BCD[p][2] = '1'; BCN[numNode][3]="-1";}
                    else if (BCs[BCNset[z]][1]=="ZSYMM") { BCD[p][3] = '1'; BCN[numNode][5]="-1";}
                    else if (BCs[BCNset[z]][1]=="XASYMM") { BCD[p][2] = '1'; BCD[p][3] = '1'; BCN[numNode][3]="-1"; BCN[numNode][5]="-1";}
                    else if (BCs[BCNset[z]][1]=="YASYMM") { BCD[p][1] = '1'; BCD[p][3] = '1'; BCN[numNode][1]="-1"; BCN[numNode][5]="-1";}
                    else if (BCs[BCNset[z]][1]=="ZASYMM") { BCD[p][1] = '1'; BCD[p][2] = '1'; BCN[numNode][1]="-1"; BCN[numNode][3]="-1";}
                    else { BCD[p][stoi(BCs[BCNset[z]][1])]='1'; BCN[numNode][2*stoi(BCs[BCNset[z]][1])-1]="-1";}
                    
                    
                    
                }
            }
        }
        BCNset.clear(); k=0;
        while(k<NbLoads) {      // compute all the punctual loads
            if (Loads[k][0]==name) BCNset.push_back(k);
            k++;
        }
        if (BCNset.size()!=0) {
            for (int z=0; z<BCNset.size(); z++) {
                k=0;
                for (long i=0; i<stoi(Nsets[j][1]); i++) {
                    long numNode=-1;
                    long a=0;
                    while(a<NbNeu && numNode==-1)
                        if (Nsets[j][i+2]==BCN[a][0]) numNode=a; else a++;
                    if (numNode!=-1) {
                        BCN [numNode] [2*stoi(Loads[BCNset[z]][1])-1] ='1';
                        BCN [numNode] [2*stoi(Loads[BCNset[z]][1])] = to_string( stof(BCN[numNode][2*stoi(Loads[BCNset[z]][1])]) + stof(Loads[BCNset[z]][2])); 
                    }
                    else {
                        std::cout << "Error, a force is applied on a non-boundary point" << endl;;
                        std::cout << "   Nset : " << Nsets[j][0] << ", Point : " << Nsets[j][i+2] << endl;
                    }
                } 
            }
        }
    }
    
    for (int i=0; i<NbPress; i++) {     // compute all the stresses / surface loads
        int a=0;
        int numSurf=-1;
        while (numSurf==-1 && a<NbSurf)
            if (Press[i][0]==Surf[a][0]) numSurf=a; else a++;
        if (numSurf!=-1) {
            vector<long> pts = getPointsSurf(numSurf);
            float area = SurfArea(numSurf);
            for (long j=0; j<pts.size(); j++) {
                for (long k=0; k<NbNeu; k++) {
                    if (BCN[k][0]==to_string(pts[j]))
                        for (int h=1; h<4; h++) {
                            BCN[k][2*h] = to_string ( stof(BCN[k][2*h]) - Normals[pts[j]-1][h]*stof(Press[i][1])*area/pts.size()); }
                }
            }
        }
    }
    
    // sort by node number
    std::sort(BCD.begin(),BCD.end(),[](const vector<string> &a, const vector<string> &b){ return stol(a[0])< stol(b[0]); });
    std::sort(BCN.begin(),BCN.end(),[](const vector<string> &a, const vector<string> &b){ return stol(a[0])< stol(b[0]); });
    
}



void INPFile::WriteFile (string Value) {

    char Path[Value.length()+1];
    strncpy(Path, Value.c_str(),Value.length()+1);
    std::ofstream *outfile;
    outfile= new std::ofstream(Path);

    *outfile << "#ANALYSIS_TYPE=" << "3D"<< endl;
    *outfile << "#PARAMETERS" << endl;
    *outfile << "E=" << EYoung << endl;
    *outfile << "nu=" << nu << endl;
    *outfile << "supexp=" << "0.75" << endl;
    *outfile << "#THREAD=" << "4" << endl;
    *outfile << "#WINDOW_TYPE=" << "SPLINE_3"<< endl;
    *outfile << "#METHOD=" << "GFD"<< endl;   
    *outfile << "#SOLVER=" << "DIRECT_MUMPS"<< endl;
    *outfile << "#DIMENSION=" << "3" << endl;
    *outfile << "#SUP_SIZE=" << "50,100" << endl;

    *outfile << "#NODE_DATA" << endl;
    for (long i=0; i<NbNodes; i++) {
        for (int j=0; j<3; j++) *outfile << NodesCoordinates[i][j] << ", " ;
        *outfile << NodesCoordinates[i][3] << endl;
    }

    *outfile << "#BOUNDARY_DIRICHLET" << endl;    
    for (long i=0; i<NbDir; i++) {
        *outfile << BCD[i][0];
        for (int j=1; j<4; j++) {
            if (BCD[i][j]=="1") *outfile << ", "<< j << ", 0" ;
        }
        *outfile << endl;
    }

    *outfile << "#BOUNDARY_NEUMANN" << endl;
    numTempo=0;
    for (long i=0; i<NbNeu; i++) {
        string line = "";
        *outfile << BCN[i][0];
        for (int j=1; j<4; j++) if (BCN[i][2*j-1]!="-1") line += ", " + to_string(j) + ", " + BCN[i][2*j];
        *outfile << printNormal(BCN[i][0]) << line << endl;
    }
    
    *outfile << "#FILE_END" << endl;
    outfile->close();
}



vector<float> INPFile::getNormal(int ElemNum, string Surf) {
          
    vector<float> AB(3);
    vector<float> BC(3);
    vector<float> normale(3);
    
    vector<long> pts = getPointsElem(ElemNum, Surf, false);
    
    for (int i=0; i<3; i++) {
        AB[i] = stof(NodesCoordinates[pts[1]-1][i+1])-stof(NodesCoordinates[pts[0]-1][i+1]);
        BC[i] = stof(NodesCoordinates[pts[3]-1][i+1])-stof(NodesCoordinates[pts[2]-1][i+1]);
    }
    
    normale[0] = AB[1]*BC[2]-AB[2]*BC[1];
    normale[1] = AB[2]*BC[0]-AB[0]*BC[2];
    normale[2] = AB[0]*BC[1]-AB[1]*BC[0];

    return normale;
    
}


void INPFile::implementNormal(int ElemNum, string Surf) {
    
    vector<float> normale = getNormal(ElemNum, Surf);
    
    float length = 0;
    for (int i=0; i<3; i++) length+=pow(normale[i],2);
    length = sqrt(length);
    
    vector<long> pts = getPointsElem(ElemNum, Surf, true);

    for (int i=0; i<3; i++) {
        for (long j=0; j<pts.size(); j++) {
            Normals[pts[j]-1][i+1] += normale[i]/length; }
        Normals[pts[3]-1][i+1] -= normale[i]/length;
    }
    
}


void INPFile::normalizeNormals() {
    
    for (long i=0; i<NbNodes; i++) {
        if (!(Normals[i][1]==0 && Normals[i][2]==0 && Normals[i][3]==0)) {
            float length = 0;
            for (int j=1; j<4; j++) length += pow(Normals[i][j],2); 
            length = sqrt(length);
            for (int j=1; j<4; j++) Normals[i][j]= Normals[i][j]/length;
        }
    }
    
}


float INPFile::SurfArea(int numSurf) {

    float surfArea = 0;
    
    for (int i=0; i<stoi(Surf[numSurf][1]); i++) {
        
        string NameElset = Surf[numSurf][i+2];
        string SurfType = NameElset;
        SurfType.erase(0, NameElset.size()-2);
        
        long j=0;
        int NumElset=-1;
        while (NumElset==-1 && j<NbElsets) {
            if (Elsets[j][0]==NameElset) NumElset=j; else j++;
        }
        
        if (NumElset!=-1) {
            
            for (long j=0; j<stoi(Elsets[NumElset][1]); j++) {
                
                int NumElem = stoi(Elsets[NumElset][j+2]);
                string ElemType = Elements[NumElem-1][1];
                
                numTempo=0;
                vector<float> vectore = getNormal(NumElem, SurfType);
                
                float length=0;
                for (int k=0; k<3; k++) length+=pow(vectore[k],2);
                
                if (ElemType == "CPS3" || ElemType == "C3D10" || ElemType =="C3D4" || ((ElemType == "C3D6" || ElemType == "C3D15") && (SurfType == "S1" || SurfType == "S2"))) { //triangular surface
                    surfArea += 0.5*sqrt(length); }
                else if (ElemType == "C3D8R" || ElemType == "C3D20R" || ((ElemType == "C3D6" || ElemType == "C3D15") && (SurfType != "S1" && SurfType != "S2"))) { //quadrilateral surface
                    surfArea += sqrt(length);}
                
            }
        }
    }
    return surfArea;
    
}


vector<long> INPFile::getPointsSurf(int numSurf) {
    
    vector<long> pts;
    
    for (int i=0; i<stoi(Surf[numSurf][1]); i++) {
        
        string NameElset = Surf[numSurf][i+2];
        string SurfType = NameElset;
        SurfType.erase(0, NameElset.size()-2);
        
        long j=0;
        int NumElset=-1;
        while (NumElset==-1 && j<NbElsets)
            if (Elsets[j][0]==NameElset) NumElset=j; else j++;
        
        if (NumElset!=-1) {
            for (int j=0; j<stoi(Elsets[NumElset][1]); j++) {
                int NumElem = stoi(Elsets[NumElset][j+2]);
                vector<long> ptsElem = getPointsElem(NumElem, SurfType, true);
                for (int k=0; k<ptsElem.size(); k++) {
                    bool disp = true;
                    int l=0;
                    while (disp && l<pts.size())
                        if (pts[l]==ptsElem[k]) disp=false; else l++;
                    if (disp)
                        pts.push_back(ptsElem[k]);
                }
            }
        }
    }
    
    return pts;
    
}


vector<long> INPFile::getPointsElem(int numElem, string SurfType, bool all) {
    
    vector<long> pts;
    string ElemType;
    
    long a = numTempo;
    long l=-1;
    while (l==-1)
        if (stoi(Elements[a][0])==numElem) l=a; else a++;
    numTempo = a;
    ElemType = Elements[l][1];
    
    if (ElemType == "CPS3") {   //2D triangular element
        pts.push_back(stol(Elements[l][3]));
        pts.push_back(stol(Elements[l][2]));
        pts.push_back(stol(Elements[l][4]));
        pts.push_back(stol(Elements[l][3]));
    }
    
    else if (ElemType == "C3D10" || ElemType=="C3D4") {     //3D tetrahedral element
        
        if (SurfType=="S1") {
            pts.push_back(stol(Elements[l][2]));
            pts.push_back(stol(Elements[l][3]));
            pts.push_back(stol(Elements[l][4]));
            pts.push_back(stol(Elements[l][3]));
            if (ElemType == "C3D10" && all) {               // if quadratic
                pts.push_back(stol(Elements[l][6]));
                pts.push_back(stol(Elements[l][7]));
                pts.push_back(stol(Elements[l][8]));
            }
        }
        else if (SurfType == "S2") {
            pts.push_back(stol(Elements[l][3]));
            pts.push_back(stol(Elements[l][2]));
            pts.push_back(stol(Elements[l][5]));
            pts.push_back(stol(Elements[l][3]));
            if (ElemType == "C3D10" && all) {
                pts.push_back(stol(Elements[l][6]));
                pts.push_back(stol(Elements[l][9]));
                pts.push_back(stol(Elements[l][10]));
            }
        }
        else if (SurfType == "S3") {
            pts.push_back(stol(Elements[l][4]));
            pts.push_back(stol(Elements[l][3]));
            pts.push_back(stol(Elements[l][5]));
            pts.push_back(stol(Elements[l][4]));
            if (ElemType == "C3D10" && all) {
                pts.push_back(stol(Elements[l][7]));
                pts.push_back(stol(Elements[l][10]));
                pts.push_back(stol(Elements[l][11]));
            }
        }
        else if (SurfType == "S4") {
            pts.push_back(stol(Elements[l][2]));
            pts.push_back(stol(Elements[l][4]));
            pts.push_back(stol(Elements[l][5]));
            pts.push_back(stol(Elements[l][4]));
            if (ElemType == "C3D10" && all) {
                pts.push_back(stol(Elements[l][8]));
                pts.push_back(stol(Elements[l][9]));
                pts.push_back(stol(Elements[l][11]));
            }
        }
    }
    
    else if (ElemType == "C3D8R" || ElemType == "C3D20R") {     //3D hexahedral element
        
        if (SurfType == "S1") {
            pts.push_back(stol(Elements[l][2]));
            pts.push_back(stol(Elements[l][3]));
            pts.push_back(stol(Elements[l][4]));
            pts.push_back(stol(Elements[l][3]));
            pts.push_back(stol(Elements[l][5]));
            if (ElemType == "C3D20R" && all) {
                pts.push_back(stol(Elements[l][10]));
                pts.push_back(stol(Elements[l][11]));
                pts.push_back(stol(Elements[l][12]));
                pts.push_back(stol(Elements[l][13]));
            }
        }
        else if (SurfType == "S2") {
            pts.push_back(stol(Elements[l][7]));
            pts.push_back(stol(Elements[l][6]));
            pts.push_back(stol(Elements[l][8]));
            pts.push_back(stol(Elements[l][7]));
            pts.push_back(stol(Elements[l][9]));
            if (ElemType == "C3D20R" && all) {
                pts.push_back(stol(Elements[l][14]));
                pts.push_back(stol(Elements[l][15]));
                pts.push_back(stol(Elements[l][16]));
                pts.push_back(stol(Elements[l][17]));
            }
        }
        else if (SurfType == "S3") {
            pts.push_back(stol(Elements[l][3]));
            pts.push_back(stol(Elements[l][2]));
            pts.push_back(stol(Elements[l][6]));
            pts.push_back(stol(Elements[l][2]));
            pts.push_back(stol(Elements[l][7]));
            if (ElemType == "C3D20R" && all) {
                pts.push_back(stol(Elements[l][10]));
                pts.push_back(stol(Elements[l][14]));
                pts.push_back(stol(Elements[l][18]));
                pts.push_back(stol(Elements[l][19]));
            }
        }
        else if (SurfType == "S4") {
            pts.push_back(stol(Elements[l][4]));
            pts.push_back(stol(Elements[l][3]));
            pts.push_back(stol(Elements[l][7]));
            pts.push_back(stol(Elements[l][3]));
            pts.push_back(stol(Elements[l][8]));
            if (ElemType == "C3D20R" && all) {
                pts.push_back(stol(Elements[l][11]));
                pts.push_back(stol(Elements[l][15]));
                pts.push_back(stol(Elements[l][19]));
                pts.push_back(stol(Elements[l][20]));
            }
        }
        else if (SurfType == "S5") {
            pts.push_back(stol(Elements[l][5]));
            pts.push_back(stol(Elements[l][4]));
            pts.push_back(stol(Elements[l][8]));
            pts.push_back(stol(Elements[l][4]));
            pts.push_back(stol(Elements[l][9]));
            if (ElemType == "C3D20R" && all) {
                pts.push_back(stol(Elements[l][12]));
                pts.push_back(stol(Elements[l][16]));
                pts.push_back(stol(Elements[l][20]));
                pts.push_back(stol(Elements[l][21]));
            }
        }
        else if (SurfType == "S6") {
            pts.push_back(stol(Elements[l][2]));
            pts.push_back(stol(Elements[l][5]));
            pts.push_back(stol(Elements[l][6]));
            pts.push_back(stol(Elements[l][2]));
            pts.push_back(stol(Elements[l][9]));
            if (ElemType == "C3D20R" && all) {
                pts.push_back(stol(Elements[l][13]));
                pts.push_back(stol(Elements[l][17]));
                pts.push_back(stol(Elements[l][18]));
                pts.push_back(stol(Elements[l][21]));
            }
        }
    }
    
    else if (ElemType == "C3D6" || ElemType == "C3D15") {   // 3D wedge/triangular prism element
        
        if (SurfType == "S1") {
            pts.push_back(stol(Elements[l][2]));
            pts.push_back(stol(Elements[l][3]));
            pts.push_back(stol(Elements[l][4]));
            pts.push_back(stol(Elements[l][3]));
            if (ElemType == "C3D15" && all) {
                pts.push_back(stol(Elements[l][8]));
                pts.push_back(stol(Elements[l][9]));
                pts.push_back(stol(Elements[l][10]));
            }
        }
        else if (SurfType == "S2") {
            pts.push_back(stol(Elements[l][6]));
            pts.push_back(stol(Elements[l][5]));
            pts.push_back(stol(Elements[l][7]));
            pts.push_back(stol(Elements[l][6]));
            if (ElemType == "C3D15" && all) {
                pts.push_back(stol(Elements[l][11]));
                pts.push_back(stol(Elements[l][12]));
                pts.push_back(stol(Elements[l][13]));
            }
        }
        else if (SurfType == "S3") {
            pts.push_back(stol(Elements[l][3]));
            pts.push_back(stol(Elements[l][2]));
            pts.push_back(stol(Elements[l][5]));
            pts.push_back(stol(Elements[l][2]));
            pts.push_back(stol(Elements[l][6]));
            if (ElemType == "C3D15" && all) {
                pts.push_back(stol(Elements[l][8]));
                pts.push_back(stol(Elements[l][11]));
                pts.push_back(stol(Elements[l][14]));
                pts.push_back(stol(Elements[l][15]));
            }
        }
        else if (SurfType == "S4") {
            pts.push_back(stol(Elements[l][4]));
            pts.push_back(stol(Elements[l][3]));
            pts.push_back(stol(Elements[l][6]));
            pts.push_back(stol(Elements[l][3]));
            pts.push_back(stol(Elements[l][7]));
            if (ElemType == "C3D15" && all) {
                pts.push_back(stol(Elements[l][9]));
                pts.push_back(stol(Elements[l][12]));
                pts.push_back(stol(Elements[l][15]));
                pts.push_back(stol(Elements[l][16]));
            }
        }
        else if (SurfType == "S3") {
            pts.push_back(stol(Elements[l][4]));
            pts.push_back(stol(Elements[l][7]));
            pts.push_back(stol(Elements[l][2]));
            pts.push_back(stol(Elements[l][4]));
            pts.push_back(stol(Elements[l][5]));
            if (ElemType == "C3D15" && all) {
                pts.push_back(stol(Elements[l][10]));
                pts.push_back(stol(Elements[l][13]));
                pts.push_back(stol(Elements[l][14]));
                pts.push_back(stol(Elements[l][16]));
            }
        }
        
    }
    
    return pts;
    
}



string INPFile::printNormal(string num) {
    
    string line = "";
    long numNode=-1;
    long a=numTempo;
    while (a<NbNodes && numNode==-1)
        if (long(Normals[a][0])==stol(num)) numNode=a; else a++; 
    numTempo = a;
    
    for (int i=1; i<4; i++)
        line += ", " + to_string(Normals[numNode][i]);
    
    return line;
}


string INPFile::split(string str, char delimiter, int Location)
//Split the path
{
    string internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;
    int i=0;
    while (getline(ss, tok, delimiter))
    {
	if (i==Location)
        {
            internal=tok;
            break;
        }
        i++;
    }
    return trim(internal);
}


string INPFile::trim(string str)
//Function Trim (remove spaces from name start and end)
{
    string::size_type pos = str.find_last_not_of('\r');
    if (pos != string::npos) {str.erase(pos + 1); }
    pos = str.find_last_not_of(' ');
    if (pos != string::npos) {str.erase(pos + 1); }
    pos = str.find_first_not_of(' ');
    if (pos != string::npos) {str.erase(0, pos); }
    return str;
}


string INPFile::ToString(double Value, int Precision, bool Last)
{
    std::stringstream out;
    string TempStr;
    out << Value;
    TempStr=out.str();
    if (Last==false)
    {
        TempStr=TempStr + " ";
    }
    return TempStr;
}

