#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
//creates the tableau
vector<vector<double>> createTableau(vector<vector<double>> v,vector<vector<double>> b,vector<vector<double>> c,int n,int m){
    vector<vector<double>> temp;
    vector<double> row;
    row.push_back(1);
    for(int i=0;i<n;i++){
        row.push_back(c[i][0]);
    }
    for(int i=0;i<=m;i++){
        row.push_back(0);
    }
    temp.push_back(row);
    row.clear();
    for(int i=0;i<m;i++){
        row.push_back(0);
        for(int j=0;j<n;j++){
            row.push_back(v[i][j]);
        }
        for(int j=0;j<m;j++){
            if(i==j){
                row.push_back(1);
            }
            else{
                row.push_back(0);
            }
        }
        row.push_back(b[i][0]);
        temp.push_back(row);
        row.clear();
    }
    return temp;
}

//finds the pivot element
pair<int,int> findPivot(vector<vector<double>> v){
    double row=0;
    int rowindex=0;
    for(int i=1;i<v[0].size()-1;i++){
        if(v[0][i]<row){
            row=v[0][i];
            rowindex=i;
        }
    }
    double column=12345678;
    int columnindex=0;
    for(int i=1;i<v.size();i++){
        if(v[i][v[1].size()-1]/v[i][rowindex]>0) {
            double x = v[i][v[1].size() - 1] / v[i][rowindex];
            if (column > x) {
                column = x;
                columnindex = i;
            }
        }
    }
    return make_pair(rowindex,columnindex);
}
//checks if current situation is an optimal solution
bool check(vector<vector<double>> v){
    for(int i=1;i<v[0].size()-1;i++){
        if(v[0][i]<0){
            return true;
        }
    }
    return false;
}
//takes the tableau and search for optimal solution
int compile(vector<vector<double>>& v,ofstream &out){
    while(check(v)){
        pair<int,int> p = findPivot(v);
        if(p.second==0){
            out<<"Unbounded.";
            return 1;
        }
        double divident =v[p.second][p.first];
        for(int i=0;i<v[p.second].size();i++){

            v[p.second][i]/=divident;
        }
        for(int j=0;j<v.size();j++) {
            if(j==p.second)
                continue;
            double multiplier = v[j][p.first];
            for (int i = 0; i < v[0].size(); i++) {
                v[j][i] -= v[p.second][i] * multiplier;
            }
        }
    }
    vector<int> list;
    out<<"[ ";
    for(int i=1;i<=v[0].size()-v.size()-1;i++){
        if(v[0][i]==0){
            out<<"x"<<i<<" ";
            list.push_back(i);
        }
    }
    out<<"]";
    out<<endl<<"z= "<<v[0][v[0].size()-1]<<" = [ ";
    vector<double> score;
    for(int i:list){
        for(int j=1;j<v.size();j++){
            if(v[j][i]==1){
                score.push_back(v[j][v[j].size()-1]);
            }
        }
    }
    int count =0;
    for(int i=1;i<=v[0].size()-v.size()-1;i++){
        if(list[count]==i){
            out<<score[count]<<" ";
            count++;
        }
        else{
            out<<0<<" ";
        }

    }
    out<<"] * x"<<endl;
    return 0;
}
//reads the data and creates the tableau
vector<vector<double>> execute(ifstream& inFile){
    vector<vector<double>> tableau;
    vector<vector<double>> temp;
    vector<vector<double>> c;
    vector<vector<double>> b;
    int n,m;
    inFile >> m;
    inFile >> n;
    for(int j=0;j<n;j++){
        double x;
        inFile>>x;
        vector<double> t;
        t.push_back(-1*x);
        c.push_back(t);
    }
    for(int i=0;i<m;i++){
        vector<double> row;
        for(int j=0;j<n;j++){
            double x;
            inFile>>x;
            row.push_back(x);
        }
        double y;
        vector<double> s;
        inFile>>y;
        s.push_back(y);
        b.push_back(s);
        temp.push_back(row);
    }
    tableau=createTableau(temp,b,c,n,m);
    return tableau;
}

int main() {
    vector<vector<double>> tableau1;
    vector<vector<double>> tableau2;
    vector<vector<double>> tableau3;
    ifstream inFile1("../Assignment3_Spring2020_Data1.txt");
    ifstream inFile2("../Assignment3_Spring2020_Data2.txt");
    ifstream inFile3("../Assignment3_Spring2020_Data3.txt");
    ofstream outFile1("../output1.txt");
    ofstream outFile2("../output2.txt");
    ofstream outFile3("../output3.txt");
    tableau1=execute(inFile1);
    tableau2=execute(inFile2);
    tableau3=execute(inFile3);

    compile(tableau1,outFile1);
    compile(tableau2,outFile2);
    compile(tableau3,outFile3);

    return 0;
}