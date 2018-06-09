#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <cmath>
#include <ctime>
#include <unordered_map>
#include <queue>
#include <array>
#include <unordered_set>
#include "windows.h"
#include "psapi.h"


using namespace std;


/*class Heuristica_1 {
public:
    short posicao_Errada = 0;
    short verifica(short config_final[4][4],  short dados_entrada[4][4]){
        for ( int i = 0; i < 4 ; ++i) {
            for ( int j = 0; j < 4; j++) {
                if (config_final[i][j] != 0){
                    if (config_final[i][j] != dados_entrada[i][j])
                        posicao_Errada++;
                }
            }
        }
        return posicao_Errada;
    }
};

class Heuristica_2 {

public:
    int verifica(short dados_entrada[4][4]){
        int posicao_Errada = 0;
        for (int k = 0; k < 4; ++k) {
            for (int i = 0; i < 4; ++i) {
                if (dados_entrada[k][i] != 0){
                    if (k == 0 || k== 2){
                        if (i == 0){
                            if (dados_entrada[k+1][i] != dados_entrada[k][i] + 1){
                                if (dados_entrada[k][i] == 15){
                                    if (dados_entrada[k+1][i] != 0){
                                        posicao_Errada++;
                                    }
                                }else{
                                    posicao_Errada++;
                                }
                            }
                        } else{
                            if(i != 3){
                                if (dados_entrada[k][i+1]+1 != dados_entrada[k][i] && dados_entrada[k][i+1] != 0)
                                    posicao_Errada++;
                            }
                        }
                    }
                    if (k == 1 || k == 3){
                        if (i != 3){
                            if (dados_entrada[k][i+1] != dados_entrada[k][i] + 1){
                                if (dados_entrada[k][i] == 15){
                                    if (dados_entrada[k][i+1] != 0){
                                        posicao_Errada++;
                                    }
                                }else{
                                    posicao_Errada++;
                                }
                            }

                        } else{
                            if (k != 3){
                                if (dados_entrada[k+1][i] != dados_entrada[k][i] + 1){
                                    if (dados_entrada[k][i] == 15){
                                        if (dados_entrada[k+1][i] != 0){
                                            posicao_Errada++;
                                        }
                                    }else{
                                        posicao_Errada++;
                                    }
                                }

                            }

                        }
                    }
                }

            }
        }
        return posicao_Errada;
    }
};

class Heuristica_3{
public:
    short resultado = 0;
    short verifica(short config_final[4][4],  short dados_entrada[4][4]){
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                short pos = dados_entrada[i][j];
                if (pos != 0 && dados_entrada[i][j] != config_final[i][j]){
                    if (pos == 1)
                        resultado+= std::abs(0 - i) + std::abs(0 - j);
                    if (pos == 2)
                        resultado+= std::abs(0 - i) + std::abs(1 - j);
                    if (pos == 3)
                        resultado+= std::abs(0 - i) + std::abs(2 - j);
                    if (pos == 4)
                        resultado+= std::abs(0 - i) + std::abs(3 - j);
                    if (pos == 5)
                        resultado+= std::abs(1 - i) + std::abs(3 - j);
                    if (pos == 6)
                        resultado+= std::abs(2 - i) + std::abs(3 - j);
                    if (pos == 7)
                        resultado+= std::abs(3 - i) + std::abs(3 - j);
                    if (pos == 8)
                        resultado+= std::abs(3 - i) + std::abs(2 - j);
                    if (pos == 9)
                        resultado+= std::abs(3 - i) + std::abs(1 - j);
                    if (pos == 10)
                        resultado+= std::abs(3 - i) + std::abs(0 - j);
                    if (pos == 11)
                        resultado+= std::abs(2 - i) + std::abs(0 - j);
                    if (pos == 12)
                        resultado+= std::abs(1 - i) + std::abs(0 - j);
                    if (pos == 13)
                        resultado+= std::abs(1 - i) + std::abs(1 - j);
                    if (pos == 14)
                        resultado+= std::abs(1 - i) + std::abs(2 - j);
                    if (pos == 15)
                        resultado+= std::abs(2 - i) + std::abs(2 - j);
                }
                //resultado += std::abs(floor((pos - 1)%4) - j) + std::abs(floor(pos/4.1) - i);
            }
        }
        return resultado;
    }

};*/


class PosAposMovimento{
public:
    short dados_entrada[4][4];
    int h_linha;
    long funcaoF;
    int origem = 0;
    //PosAposMovimento* pai;
    string hash;
    int movimentos = 0;
    bool temPai = false;
    /*size_t hashCode;*/


    /*void setHashCode(){
        std::hash<std::string> h;
        hashCode = h(hash);
    }*/

    // We need the operator== to compare 2 types.
    /*bool operator==(const PosAposMovimento &rhs) const {
        return hash == rhs.hash;
    }*/
    /*bool operator!=(const PosAposMovimento &rhs) const {
        return !operator==(rhs);
    }*/


    void setHash() {
        string key;
        for (auto &i : dados_entrada) {
            for (short j : i) {
                key+=transformaEmChar(j);
            }
        }
        this->hash = key;
    }

    string getHash(){
        return hash;
    }

    string transformaEmChar(short s) {
        switch (s) {
            case 0:
                return "P";
            case 1:
                return "D";
            case 2:
                return "C";
            case 3:
                return "B";
            case 4:
                return "A";
            case 5:
                return "E";
            case 6:
                return "F";
            case 7:
                return "G";
            case 8:
                return "H";
            case 9:
                return "L";
            case 10:
                return "K";
            case 11:
                return "J";
            case 12:
                return "I";
            case 13:
                return "M";
            case 14:
                return "N";
            case 15:
                return "O";
            default:
                return "W";
        }
    }
};

int calculaHeuristica(short config_final[4][4], short solucao_possivel[4][4]){
    //Heuristica_1 h1;
    //Heuristica_2 h2;
    //Heuristica_3 h3;
    int resultado = 0;

    //if (codigo == 1)
    //  resultado = h1.verifica(config_final, solucao_possivel);
    //if (codigo == 2)
    //    resultado = h2.verifica(solucao_possivel);
    //if (codigo == 3){
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            short pos = solucao_possivel[i][j];
            if (pos != 0 && solucao_possivel[i][j] != config_final[i][j]){
                if (pos == 1)
                    resultado+= std::abs(0 - i) + std::abs(3 - j);
                if (pos == 2)
                    resultado+= std::abs(0 - i) + std::abs(2 - j);
                if (pos == 3)
                    resultado+= std::abs(0 - i) + std::abs(1 - j);
                if (pos == 4)
                    resultado+= std::abs(0 - i) + std::abs(0 - j);
                if (pos == 5)
                    resultado+= std::abs(1 - i) + std::abs(0 - j);
                if (pos == 6)
                    resultado+= std::abs(1 - i) + std::abs(1 - j);
                if (pos == 7)
                    resultado+= std::abs(1 - i) + std::abs(2 - j);
                if (pos == 8)
                    resultado+= std::abs(1 - i) + std::abs(3 - j);
                if (pos == 9)
                    resultado+= std::abs(2 - i) + std::abs(3 - j);
                if (pos == 10)
                    resultado+= std::abs(2 - i) + std::abs(2 - j);
                if (pos == 11)
                    resultado+= std::abs(2 - i) + std::abs(1 - j);
                if (pos == 12)
                    resultado+= std::abs(2 - i) + std::abs(0 - j);
                if (pos == 13)
                    resultado+= std::abs(3 - i) + std::abs(0 - j);
                if (pos == 14)
                    resultado+= std::abs(3 - i) + std::abs(1 - j);
                if (pos == 15)
                    resultado+= std::abs(3 - i) + std::abs(2 - j);
            }
        }
    }
    //}
    //if(codigo == 4)
    //    resultado = (int)(0.1 * calculaHeuristica(config_final, solucao_possivel, (short)1) + 0.4 * calculaHeuristica(config_final, solucao_possivel, (short) 2) + 0.5 * calculaHeuristica(config_final, solucao_possivel, (short) 3));

    return resultado;
}

struct comparer {
    bool operator()(const PosAposMovimento &rhs, const PosAposMovimento &rhz) const {
        if (rhz.funcaoF < rhs.funcaoF)
            return true;
        else{
            if(rhz.funcaoF == rhs.funcaoF){
                return rhz.movimentos > rhs.movimentos;
            }else
                return false;
        }

        //return rhs.funcaoF > rhz.funcaoF;
    }
};




std::list<PosAposMovimento> geraSucessores (PosAposMovimento &posAposMovimento){
    std::list<PosAposMovimento> sucessores;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (posAposMovimento.dados_entrada[i][j] == 0){
                if (i != 0 && (!posAposMovimento.temPai || posAposMovimento.origem != -1)){
                    PosAposMovimento up;
                    up.movimentos = posAposMovimento.movimentos + 1;
                    std::copy(&posAposMovimento.dados_entrada[0][0], &posAposMovimento.dados_entrada[0][0]+4*4, &up.dados_entrada[0][0]);

                    short aux = up.dados_entrada[i][j];
                    up.dados_entrada[i][j] = up.dados_entrada[i-1][j];
                    up.dados_entrada[i - 1][j] = aux;

                    up.setHash();
                    //up.pai = &posAposMovimento;
                    up.origem = 1;
                    up.temPai = true;
                    sucessores.push_back(up);
                }

                if (i != 3 && (!posAposMovimento.temPai || posAposMovimento.origem != 1)){
                    PosAposMovimento down;
                    down.movimentos = posAposMovimento.movimentos + 1;
                    std::copy(&posAposMovimento.dados_entrada[0][0], &posAposMovimento.dados_entrada[0][0]+4*4, &down.dados_entrada[0][0]);

                    short aux = down.dados_entrada[i][j];
                    down.dados_entrada[i][j] = down.dados_entrada[i+1][j];
                    down.dados_entrada[i + 1][j] = aux;

                    down.setHash();
                    //down.pai = &posAposMovimento;
                    down.origem = -1;
                    down.temPai = true;
                    sucessores.push_back(down);

                }

                if (j != 0 && (!posAposMovimento.temPai || posAposMovimento.origem != -2)){
                    PosAposMovimento left;
                    left.movimentos = posAposMovimento.movimentos + 1;
                    std::copy(&posAposMovimento.dados_entrada[0][0], &posAposMovimento.dados_entrada[0][0]+4*4, &left.dados_entrada[0][0]);

                    short aux = left.dados_entrada[i][j];
                    left.dados_entrada[i][j] = left.dados_entrada[i][j-1];
                    left.dados_entrada[i][j - 1] = aux;

                    left.setHash();
                    //left.pai = &posAposMovimento;
                    left.origem = 2;
                    left.temPai = true;
                    sucessores.push_back(left);
                }

                if (j != 3 && (!posAposMovimento.temPai || posAposMovimento.origem != 2)){
                    PosAposMovimento right;
                    right.movimentos = posAposMovimento.movimentos + 1;
                    std::copy(&posAposMovimento.dados_entrada[0][0], &posAposMovimento.dados_entrada[0][0]+4*4, &right.dados_entrada[0][0]);

                    short aux = right.dados_entrada[i][j];
                    right.dados_entrada[i][j] = right.dados_entrada[i][j+1];
                    right.dados_entrada[i][j+1] = aux;

                    right.setHash();
                    //right.pai = &posAposMovimento;
                    right.origem = -2;
                    right.temPai = true;
                    sucessores.push_back(right);
                }
            }
        }
    }
    return sucessores;
}


long A_Star(std::priority_queue<PosAposMovimento, vector<PosAposMovimento>, comparer> &A, std::unordered_multimap<string, PosAposMovimento> &F, const string &HASH_SOLUCAO, short config_final[4][4]){

    PosAposMovimento novaSolucao;
    //PosAposMovimento sol;
    std::list<PosAposMovimento> sucessores;

    //long fooToString = 1;
    while (!A.empty()){
        //cout << A.begin()->first << endl;
        //system("pause");
        novaSolucao =  A.top();
        /*if (novaSolucao.funcaoF == 45 && novaSolucao.movimentos == 3){
            cout << novaSolucao.hash << endl;
        }*/
        //std::cout<< novaSolucao.getHash() << " => " << novaSolucao.funcaoF << " => " << novaSolucao.movimentos << '\n';
        //std::cout << novaSolucao.hashCode << " => " << novaSolucao.movimentos << '\n';
        /*for (std::map<string,PosAposMovimento>::iterator it=A.begin(); it!=A.end(); ++it)
            std::cout << it->first << " => " << it->second.movimentos << '\n';*/
        A.pop();//A.remove(novaSolucao);
        //auxiliar.erase(novaSolucao.getHash());

        //system("pause");



        //auto range = F.equal_range(novaSolucao.hash);
        if (novaSolucao.getHash() == HASH_SOLUCAO){
            //cout << F.size() << endl;
            //cout << A.size() << endl;
            return novaSolucao.movimentos;
        }




        F.insert({novaSolucao.hash, novaSolucao});
        //F[novaSolucao.hashCode] = novaSolucao;

        sucessores = geraSucessores(novaSolucao);


        for (auto &sucessore : sucessores) {
            //sol = sucessore;

            //sol.setHashCode();
            //auto myrange = F.equal_range(sucessore.hash);
            if (F.count(sucessore.hash) == 0){
                sucessore.h_linha = calculaHeuristica(config_final, sucessore.dados_entrada);
                sucessore.funcaoF = sucessore.movimentos + sucessore.h_linha;
                A.push(sucessore);
            }

            //else
            // cout << "Ja possui o no com f " << sol.funcaoF << " => " << sol.movimentos << endl;
        }
        //sucessores.clear();

    }
    return -1;
}


int main(){

    uint64_t currentUsedRAM(0);

    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    currentUsedRAM = info.WorkingSetSize;

    static string HASH_SOLUCAO = "ABCDEFGHIJKLMNOP";//"!#$0ABCDEFGHIJKL";

    //static short CODIGO_HEURISTICA = 3;


    short config_final[4][4] = {{4, 3, 2, 1}, {5, 6, 7, 8}, {12, 11, 10, 9}, {13, 14, 15, 0}};
    PosAposMovimento posAposMovimento;
    //std::map<string, PosAposMovimento> A;
    //std::unordered_map<string, PosAposMovimento> F;
    std::priority_queue<PosAposMovimento, vector<PosAposMovimento>, comparer> A;
    std::unordered_multimap<string, PosAposMovimento>F;
    //std::map<string, PosAposMovimento> auxiliar;

    for (auto &i : posAposMovimento.dados_entrada) {
        for (short &j : i) {
            short valor;
            cin >> valor;
            j = valor;
        }
    }

    posAposMovimento.h_linha = calculaHeuristica(config_final, posAposMovimento.dados_entrada);
    posAposMovimento.funcaoF = posAposMovimento.h_linha;
    posAposMovimento.setHash();
    //posAposMovimento.setHashCode();
    //string fooToString;
    //fooToString = "!" + std::to_string(posAposMovimento.funcaoF);
    A.push(posAposMovimento);

    //A[fooToString+"-"+posAposMovimento.getHash()] = posAposMovimento;
    //auxiliar[posAposMovimento.hash] = posAposMovimento;
    clock_t begin = clock();
    int resultado = A_Star(A, F, HASH_SOLUCAO, config_final);
    if (resultado == -1){
        return 0;
    }
    else
        cout <<  resultado;

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << endl << elapsed_secs << "s";
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    currentUsedRAM = info.WorkingSetSize - currentUsedRAM;
    cout << endl << ((double)currentUsedRAM/(double)1048576) << "MB " << currentUsedRAM << endl;
}