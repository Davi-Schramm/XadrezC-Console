#include <iostream>

using namespace std;

void display(string *mesa, bool player);
void mesaprepare(string *mesa);
void menu();
bool checkapeao(string *mesa, int x1,int y1,int x2, int y2,char cor);
bool checktorre(string *mesa, int x1,int y1,int x2, int y2,char cor);
bool checkcavalo(string *mesa, int x1,int y1,int x2, int y2,char cor);
bool checkbispo(string *mesa, int x1,int y1,int x2, int y2,char cor);
bool checkrainha(string *mesa, int x1,int y1,int x2, int y2,char cor);
bool checkrei(string *mesa, int x1,int y1,int x2, int y2,char cor);

int main(){
    string mesa[100];
    bool game = true;
    mesaprepare(mesa);
    menu();
    bool jogadoronoff = false;
    while(game){
        display(mesa, jogadoronoff);
        if(jogadoronoff)
            jogadoronoff = false;
        else
            jogadoronoff = true;
    }

    return 0;
}

void menu(){
    cout << "Bem vindo ao Xadrez do Davi :)\n";
    cout << "Este e um projeto pequeno e bobo em C++\n";
    cout << "Nao fique com raiva se encontrar algum erro ou bug\n";
    cout << "O jogo eh para ser jogado atraves de selecao de index por pecas\n";
    cout << "Portanto, em cada jogada eh printado uma mesa paralela com todas as localizacoes!\n";
    cout << "Insira qualquer letra e clique enter para continuar!\n";
    string con;
    cin >> con;
}

void display(string *mesa, bool player){
    for(int i = 0;i<10;i++){
        for(int j = 0;j<18;j++){    
            cout << mesa[i][j];
            ///*
            if(j%2==0){
                if(i == 0 || i == 9)
                    cout << '-';
                else
                    cout << ' ';
            }
            //*/
        }
        cout << "    "; 
        if(i == 0 || i == 9)
            cout << "---------------------------";
        else{
            for(int j = 0;j<18;j++){
                if(j == 0 || j == 17)
                    cout << '|';
                else if(j%2 != 0){
                    if(j == 1)
                        cout << ' ';
                    cout << i << (j/2)+1 << ' ';
                }
            }
        }
        cout << '\n';
    }
    while(1){
        cout << "Vez do jogador ";
        if(player)
            cout << "Preto ";
        else
            cout << "Branco ";
        cout << "Jogar: {Insira no modelo: <index da peca> <index aonde vai>}\n";
        string get1,get2;
        cin >> get1 >> get2;
        // validate input
        if(get1[2] == '\0' && get2[2] == '\0'){
            if((int)get1[0] < 49 || (int)get1[0] > 56){
                cout << "INVALIDO! Tente inserir o input como {22 33}\n";
            }
            else if((int)get1[1] < 49 || (int)get1[1] > 56){
                cout << "INVALIDO! Tente inserir o input como {22 33}\n";
            }
            else if((int)get2[0] < 49 || (int)get2[0] > 56){
                cout << "INVALIDO! Tente inserir o input como {22 33}\n";
            }
            else if((int)get2[1] < 49 || (int)get2[1] > 56){
                cout << "INVALIDO! Tente inserir o input como {22 33}\n";
            }
            else{
                int x1 = (int)get1[0]-48;
                int y1 = (int)get1[1]-48;
                int x2 = (int)get2[0]-48;
                int y2 = (int)get2[1]-48;
                cout << mesa[x1][y1*2-1] << mesa[x1][y1*2] << '\n';
                string peca = "";
                peca += mesa[x1][y1*2-1];
                peca += mesa[x1][y1*2];
                //verificar cor!
                if(peca[1] == 'b' && player)
                    cout << "INVALIDO! Tente jogar na sua cor!\n";
                else if(peca[1] == 'p' && !player)
                    cout << "INVALIDO! Tente jogar na sua cor!\n";
                else{
                    //verifica se eh peça possivel de mexer
                    bool possible = false;
                    if(peca[0] == 'T'){
                        if(player)
                            possible = checktorre(mesa,x1,y1,x2,y2,'p');
                        else
                            possible = checktorre(mesa,x1,y1,x2,y2,'b');
                    }
                    else if(peca[0] == 'C'){
                        if(player)
                            possible = checkcavalo(mesa,x1,y1,x2,y2,'p');
                        else
                            possible = checkcavalo(mesa,x1,y1,x2,y2,'b');
                    }
                    else if(peca[0] == 'B'){
                        if(player)
                            possible = checkbispo(mesa,x1,y1,x2,y2,'p');
                        else
                            possible = checkbispo(mesa,x1,y1,x2,y2,'b');
                    }
                    else if(peca[0] == 'Q'){
                        if(player)
                            possible = checkrainha(mesa,x1,y1,x2,y2,'p');
                        else
                            possible = checkrainha(mesa,x1,y1,x2,y2,'b');
                    }
                    else if(peca[0] == 'K'){
                        if(player)
                            possible = checkrei(mesa,x1,y1,x2,y2,'p');
                        else
                            possible = checkrei(mesa,x1,y1,x2,y2,'b');
                    }
                    else if(peca[0] == 'P'){
                        if(player)
                            possible = checkapeao(mesa,x1,y1,x2,y2,'p');
                        else
                            possible = checkapeao(mesa,x1,y1,x2,y2,'b');
                    }
                    else{
                        cout << "INVALIDO! Tente inserir o input como {22 33}\n";
                        cout << "PECA ESCOLHIDA: " << peca << " \n";
                    }
                    if(possible){
                        //trocar a peça de lugar e colocar no seu lugar "..";
                        mesa[x2][y2*2-1] = mesa[x1][y1*2-1];
                        mesa[x2][y2*2] = mesa[x1][y1*2];
                        mesa[x1][y1*2] = '.';
                        mesa[x1][y1*2-1] = '.';
                        break;
                    }
                    else{
                        cout << "JOGADA INVALIDA!\n";
                    }

                }
            }
        }
        else{
            cout << "INVALIDO! Tente inserir o input como {22 33}\n";
        }
    }
}
bool checkapeao(string *mesa, int x1,int y1,int x2, int y2,char cor){
    if(cor == 'b'){
        int diferenca = y1-y2;
        int xdif = x1-x2;
        if(abs(xdif) == 1){
            if(mesa[x2][y2*2] == 'p')
                return true;
            else
                return false;        
        }
        else if(xdif == 0){
            if(diferenca != 1){
                if(diferenca == 2 && y1 == 7){
                    if(mesa[x2][y2*2] == '.' && mesa[x2][(y2-1)*2] == '.')
                        return true;
                }
                return false;
            }
            if(mesa[x2][y2*2] == '.'){
                return true;
            }
            else return false;
        }
        else{
            return false;
        }
    }
    else{
        int diferenca = y2-y1;
        int xdif = x1-x2;
        if(abs(xdif) == 1){
            if(mesa[x2][y2*2] == 'b')
                return true;
            else
                return false;   
        }
        else if(xdif == 0){
            if(diferenca != 1){
                if(diferenca == 2 && y1 == 2){
                    if(mesa[x2][y2*2] == '.' && mesa[x2][(y2-1)*2] == '.')
                        return true;
                }
                return false;
            }
            if(mesa[x2][y2*2] == '.'){
                return true;
            }
            else return false;
        }
        else{
            return false;
        }
    }
}
bool checktorre(string *mesa, int x1,int y1,int x2, int y2,char cor){
    int xdif = abs(x1-x2);
    int ydif = abs(y1-y2);
    if(xdif && ydif || xdif == ydif)
        return false;
    else{
        bool error = false;
        if(x1 > x2){
            //vai estar subindo
            for(int i = 1;i<=xdif;i++){
                if(mesa[x1-i][y2*2] != '.' && i != xdif){
                    error = true;
                }
                else if(i == xdif){
                    if(cor == mesa[x1-i][y2*2])
                        error = true;
                }
            }
        }
        else if(y1 > y2){
            //vai estar indo para ESQUERDA
            for(int i = 1;i<=ydif;i++){
                if(mesa[x1][y1*2-i*2] != '.' && i != ydif){
                    error = true;
                }
                else if(i == ydif){
                    if(cor == mesa[x1][y1*2-i*2])
                        error = true;
                }
            }
        }
        else if(x2 > x1){
            //vai estar descendo
            for(int i = 1;i<=xdif;i++){
                if(mesa[x1+i][y2*2] != '.' && i != xdif){
                    error = true;
                }
                else if(i == xdif){
                    if(cor == mesa[x1+i][y2*2])
                        error = true;
                }
            }
        }
        else{
            //vai estar indo para DIREITA
            for(int i = 1;i<=ydif;i++){
                if(mesa[x1][y1*2+i*2] != '.' && i != ydif){
                    error = true;
                }
                else if(i == ydif){
                    if(cor == mesa[x1][y1*2+i*2])
                        error = true;
                }
            }
        }
        if(error)
            return false;
        else
            return true;
    }

}
bool checkcavalo(string *mesa, int x1,int y1,int x2, int y2,char cor){
    int xdif = abs(x1-x2);
    int ydif = abs(y1-y2);
    if(!xdif && !ydif || (xdif == 1 && ydif != 2) || (ydif == 1 && xdif != 2) || (xdif != 1 && ydif != 1))
        return false;
    else{
        if(mesa[x2][y2*2] != cor)
            return true;
        else
            return false;
    }
}
bool checkbispo(string *mesa, int x1,int y1,int x2, int y2,char cor){
    int xdif = abs(x1-x2);
    int ydif = abs(y1-y2);
    if(xdif != ydif || (xdif == 0 && ydif == 0)){
        return false;
    }   
    else{
        if(x1 > x2 && y1 > y2){
            for(int i = 1;i<=xdif;i++){
                if(mesa[x1-i][y1*2-i*2] != '.' && i != xdif){
                    return false;
                }
                else if(i == xdif){
                    if(i == xdif && mesa[x1-i][y1*2-i*2] != cor)
                        return true;
                    else
                        return false;
                }
            }
        }
        else if(x1 > x2 && y1 < y2){
            for(int i = 1;i<=xdif;i++){
                if(mesa[x1-i][y1*2+i*2] != '.' && i != xdif){
                    return false;
                }
                else if(i == xdif){
                    if(i == xdif && mesa[x1-i][y1*2+i*2] != cor)
                        return true;
                    else
                        return false;
                }
            }
        }
        else if(x1 < x2 && y1 > y2){
            for(int i = 1;i<=xdif;i++){
                if(mesa[x1+i][y1*2-i*2] != '.' && i != xdif){
                    return false;
                }
                else if(i == xdif){
                    if(i == xdif && mesa[x1+i][y1*2-i*2] != cor)
                        return true;
                    else
                        return false;
                }
            }
        }
        else if(x1 < x2 && y1 < y2){
            for(int i = 1;i<=xdif;i++){
                if(mesa[x1+i][y1*2+i*2] != '.' && i != xdif){
                    return false;
                }
                else if(i == xdif){
                    if(i == xdif && mesa[x1+i][y1*2+i*2] != cor)
                        return true;
                    else
                        return false;
                }
            }
        }
    }
}
bool checkrainha(string *mesa, int x1,int y1,int x2, int y2,char cor){
    int xdif = abs(x1-x2);
    int ydif = abs(y1-y2);
    if(xdif == 0 && ydif == 0)
        return false;
    else if(xdif != ydif){
        if(xdif > 0 && ydif > 0)
            return false;
        else if(xdif == ydif){
            checkbispo(mesa,x1,y1,x2,y2,cor);
        }
        else{
            checktorre(mesa,x1,y1,x2,y2,cor);
        }
    }
    else{
        if(xdif == ydif){
            checkbispo(mesa,x1,y1,x2,y2,cor);
        }
        else{
            checktorre(mesa,x1,y1,x2,y2,cor);
        }
    }


}
bool checkrei(string *mesa, int x1,int y1,int x2, int y2,char cor){
    int xdif = abs(x1-x2);
    int ydif = abs(y1-y2);
    if(xdif > 1 || ydif > 1)
        return false;
    else{
        if(mesa[x2][y2*2] != cor)
            return true;
        else
            return false;
    }
}
void mesaprepare(string *mesa){
    
        for(int i = 0;i<10;i++){
            for(int j = 0;j<18;j++){    
                if(i == 0 || i == 9 || j == 0 || j == 17){
                    if(i == 0 || i == 9)
                        mesa[i]+= "-";
                    else
                        mesa[i]+="|";
                }
                else{
                    mesa[i] += ".";
                }
            }
        }
        string linhap[10] = {"Tp","Cp","Bp","Qp","Kp","Bp","Cp","Tp"};
        string linhab[10] = {"Tb","Cb","Bb","Qb","Kb","Bb","Cb","Tb"};
        string peaop = "Pp";
        string peaob = "Pb";
        for(int i = 1;i<9;i++){
            mesa[i][1] = linhap[i-1][0];
            mesa[i][2] = linhap[i-1][1];
            mesa[i][3] = peaop[0];
            mesa[i][4] = peaop[1];
            mesa[i][15] = linhab[i-1][0];
            mesa[i][16] = linhab[i-1][1];
            mesa[i][13] = peaob[0];
            mesa[i][14] = peaob[1];
        }

}
