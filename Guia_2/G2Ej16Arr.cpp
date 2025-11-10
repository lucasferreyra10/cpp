
/*
Id.Programa: G2Ej16Arr.cpp
Autor......: Dev. Lucas Ferreyra
Fecha......: mayo-2025
Comentario.: Completar matriz 5x5 con un recorrido de caballo (1..25) respetando celdas prefijadas:
             a(2,1)=8; a(1,4)=12; a(3,1)=1; a(3,4)=20; a(4,3)=18; a(5,2)=4.
             Se usa backtracking.
*/

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int N=5;
int dx[8] = {2,2,1,1,-1,-1,-2,-2};
int dy[8] = {1,-1,2,-2,2,-2,1,-1};

int board[N][N];
bool usedVal[26];

bool inb(int r,int c){return r>=0&&r<N&&c>=0&&c<N;}

bool checkPref(int r,int c,int k){
    // Prefijados segun enunciado (indice 1-based)
    int rr=r+1, cc=c+1;
    if (rr==2 && cc==1) return k==8;
    if (rr==1 && cc==4) return k==12;
    if (rr==3 && cc==1) return k==1;
    if (rr==3 && cc==4) return k==20;
    if (rr==4 && cc==3) return k==18;
    if (rr==5 && cc==2) return k==4;
    return true;
}

bool backtrack(int r,int c,int k){
    if (!checkPref(r,c,k)) return false;
    board[r][c]=k;
    if (k==25) return true;
    for (int m=0;m<8;++m){
        int nr=r+dx[m], nc=c+dy[m];
        if (inb(nr,nc) && board[nr][nc]==0){
            if (backtrack(nr,nc,k+1)) return true;
        }
    }
    board[r][c]=0;
    return false;
}

int main(){
    for (int i=0;i<N;++i) for (int j=0;j<N;++j) board[i][j]=0;

    // intentar iniciar desde la celda que contiene 1 segun prefijado: (3,1) 1-based -> (2,0) 0-based
    int sr=2-1, sc=1-1; // cuidado: enunciado dice a3,1 = 1 -> (3,1). Ajuste:
    sr=3-1; sc=1-1;

    if (!backtrack(sr,sc,1)){
        cout << "No se encontro solucion con las restricciones dadas.\n";
        return 0;
    }

    cout << "Recorrido de caballo 5x5 respetando celdas prefijadas:\n";
    for (int i=0;i<N;++i){
        for (int j=0;j<N;++j){
            cout << setw(3) << board[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
