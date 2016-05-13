#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ofstream ofs("input.cnf");
int n;

int countClauses(){
        int count = 0;
        //makeLine
        count += n;
        //makeHorizontal
        count += n*(n-1)/2*n;
        //makeVertical
        count += n*(n-1)/2*n;
        //makeDiagonal
        for(int i=2;i<=n;i++){
                if(i!=n){
                        count += i*(i-1)*2;
                }
                else{
                        count += i*(i-1);
                }
        }
        return count;
}

void makeLine(){
        for(int i=0;i<n;i++){
                for(int j=1;j<=n;j++){
                        ofs << i*n+j << " ";
                }
                ofs << "0" << endl;
        }
        return;
}
void makeHorizontalConstraint(){
        for(int i=0;i<n;i++){
                for(int j=1;j<n;j++){
                        for(int k=j+1;k<=n;k++){
                                ofs << -(i*n+j) << " " << -(i*n+k) << " 0" << endl;
                        }
                }
        }
        return;
}
void makeVerticalConstraint(){
        for(int i=1;i<=n;i++){
                for(int j=0;j<n;j++){
                        for(int k=j+1;k<n;k++){
                                ofs << -(i+n*j) << " " << -(i+n*k) << " 0" << endl;
                        }
                }
        }
        return;
}
void makeDiagonalConstraint(){
        for(int i=1;i<2*n;i++){
                if(i==1 || i==2*n-1)
                        continue;
                int howmany = n - abs(i-n);
                if(i<=n){
                        for(int j=0;j<howmany;j++){
                                for(int k=j+1;k<howmany;k++){
                                        ofs << -(i+(n-1)*j) << " " << -(i+(n-1)*k) << " 0" << endl;
                                }
                        }
                }
                else{
                        int first = n + n*(i-n);
                        for(int j=0;j<howmany;j++){
                                for(int k=j+1;k<howmany;k++){
                                        ofs << -(first+(n-1)*j) << " " << -(first+(n-1)*k) << " 0" << endl;
                                }
                        }
                }
        }
        for(int i=1;i<2*n;i++){
                if(i==1 || i==2*n-1)
                        continue;
                int howmany = n - abs(i-n);
                if(i<=n){
                        int first = n-i+1;
                        for(int j=0;j<howmany;j++){
                                for(int k=j+1;k<howmany;k++){
                                        ofs << -(first+(n+1)*j) << " " << -(first+(n+1)*k) << " 0" << endl;
                                }
                        }
                }
                else{
                        int first = 1 + n*(i-n);
                        for(int j=0;j<howmany;j++){
                                for(int k=j+1;k<howmany;k++){
                                        ofs << -(first+(n+1)*j) << " " << -(first+(n+1)*k) << " 0" << endl;
                                }
                        }
                }
        }
        return;
}

int main(){
        cin >> n;
        int x = countClauses();
        ofs << "c This cfn is made by makeNQueenCFN.cc" << endl;
        ofs << "c" << endl;
        ofs << "p cnf " << n*n << " " << x << endl;
        makeLine();
        makeHorizontalConstraint();
        makeVerticalConstraint();
        makeDiagonalConstraint();
}