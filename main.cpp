#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <algorithm>
#include <list>
#include <math.h>

using namespace std;


class Heuristica_1 {
public:
    short posicao_Errada = 0;
    short verifica(short config_final[4][4],  short dados_entrada[4][4]){
        for ( int i = 0; i < 4 ; ++i) {
            for ( int j = 0; j < 4; j++) {
                if (config_final[i][j] != dados_entrada[i][j])
                    posicao_Errada++;
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
    short posicao_errada = 0;
    short verifica(short config_final[4][4],  short dados_entrada[4][4]){
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                short pos = dados_entrada[i][j];
                if (pos != 0 && dados_entrada[i][j] != config_final[i][j]){
                    if (pos == 1)
                        posicao_errada+= std::abs(0 - i) + std::abs(3 - j);
                    if (pos == 2)
                        posicao_errada+= std::abs(0 - i) + std::abs(2 - j);
                    if (pos == 3)
                        posicao_errada+= std::abs(0 - i) + std::abs(1 - j);
                    if (pos == 4)
                        posicao_errada+= std::abs(0 - i) + std::abs(0 - j);
                    if (pos == 5)
                        posicao_errada+= std::abs(1 - i) + std::abs(0 - j);
                    if (pos == 6)
                        posicao_errada+= std::abs(1 - i) + std::abs(1 - j);
                    if (pos == 7)
                        posicao_errada+= std::abs(1 - i) + std::abs(2 - j);
                    if (pos == 8)
                        posicao_errada+= std::abs(1 - i) + std::abs(3 - j);
                    if (pos == 9)
                        posicao_errada+= std::abs(2 - i) + std::abs(3 - j);
                    if (pos == 10)
                        posicao_errada+= std::abs(2 - i) + std::abs(2 - j);
                    if (pos == 11)
                        posicao_errada+= std::abs(2 - i) + std::abs(1 - j);
                    if (pos == 12)
                        posicao_errada+= std::abs(2 - i) + std::abs(0 - j);
                    if (pos == 13)
                        posicao_errada+= std::abs(3 - i) + std::abs(0 - j);
                    if (pos == 14)
                        posicao_errada+= std::abs(3 - i) + std::abs(1 - j);
                    if (pos == 15)
                        posicao_errada+= std::abs(3 - i) + std::abs(2 - j);
                }
                //posicao_errada += std::abs(floor((pos - 1)%4) - j) + std::abs(floor(pos/4.1) - i);
            }
        }
        return posicao_errada;
    }

};


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

    // We need the operator== to compare 2 types.
    bool operator==(const PosAposMovimento &rhs) const {
        return hash == rhs.hash;
    }
    bool operator!=(const PosAposMovimento &rhs) const {
        return !operator==(rhs);
    }


    void setHash() {
        string key = "";
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; ++j) {
                key+=transformaEmChar(dados_entrada[i][j]);
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
                return "!";
            case 1:
                return "$";
            case 2:
                return "@";
            case 3:
                return "H";
            case 4:
                return "E";
            case 5:
                return "D";
            case 6:
                return "C";
            case 7:
                return "F";
            case 8:
                return "B";
            case 9:
                return "G";
            case 10:
                return "U";
            case 11:
                return "S";
            case 12:
                return "T";
            case 13:
                return "A";
            case 14:
                return "V";
            case 15:
                return "O";
            default:
                return "W";
        }
    }
};

int calculaHeuristica(short config_final[4][4], short solucao_possivel[4][4], short codigo){
    Heuristica_1 h1;
    Heuristica_2 h2;
    Heuristica_3 h3;
    int resultado;

    if (codigo == 1)
        resultado = h1.verifica(config_final, solucao_possivel);
    if (codigo == 2)
        resultado = h2.verifica(solucao_possivel);
    if (codigo == 3)
        resultado = h3.verifica(config_final, solucao_possivel);
    if(codigo == 4)
        resultado = (0.17D * calculaHeuristica(config_final, solucao_possivel, (short)1) + 0.03D * calculaHeuristica(config_final, solucao_possivel, (short) 2) + 0.08D * calculaHeuristica(config_final, solucao_possivel, (short) 3));

    return resultado;
}

struct comparer {
    bool operator()(const PosAposMovimento &rhs, const PosAposMovimento &rhz) const {
        return rhs.funcaoF <= rhz.funcaoF;
    }
} compareTo;


std::list<PosAposMovimento> geraSucessores (PosAposMovimento posAposMovimento){
    std::list<PosAposMovimento> sucessores;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (posAposMovimento.dados_entrada[i][j] == 0){
                if (i != 0 && (!posAposMovimento.temPai || posAposMovimento.origem != -1)){
                    PosAposMovimento up;
                    up.movimentos = posAposMovimento.movimentos + 1;
                    for (int k = 0; k < 4; ++k) {
                        for (int l = 0; l < 4; ++l) {
                            up.dados_entrada[k][l] = posAposMovimento.dados_entrada[k][l];
                        }
                    }

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
                    for (int k = 0; k < 4; ++k) {
                        for (int l = 0; l < 4; ++l) {
                            down.dados_entrada[k][l] = posAposMovimento.dados_entrada[k][l];
                        }
                    }

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
                    for (int k = 0; k < 4; ++k) {
                        for (int l = 0; l < 4; ++l) {
                            left.dados_entrada[k][l] = posAposMovimento.dados_entrada[k][l];
                        }
                    }

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
                    for (int k = 0; k < 4; ++k) {
                        for (int l = 0; l < 4; ++l) {
                            right.dados_entrada[k][l] = posAposMovimento.dados_entrada[k][l];
                        }
                    }

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

long A_Star(std::map<string, PosAposMovimento> A, std::map<string, PosAposMovimento> F, string HASH_SOLUCAO, short config_final[4][4], std::map<string, PosAposMovimento> auxiliar,
            short CODIGO_HEURISTICA){

    PosAposMovimento novaSolucao;
    std::list<PosAposMovimento> sucessores;
    string fooToString;
    //A.sort(compareTo);
    while (!A.empty()){
        //cout << A.begin()->first << endl;
        //system("pause");
        //A.sort(compareTo);
        novaSolucao =  A.begin()->second;//*std::min_element(A.begin(), A.end(), compareTo);
        /*for (std::map<string,PosAposMovimento>::iterator it=A.begin(); it!=A.end(); ++it)
            std::cout << it->first << " => " << it->second.movimentos << '\n';*/
        A.erase(A.begin()->first);//A.remove(novaSolucao);
        auxiliar.erase(novaSolucao.getHash());

        //cout << calculaHeuristica(config_final, novaSolucao.dados_entrada, 2) << endl;
        //system("pause");


        if(novaSolucao.getHash() == HASH_SOLUCAO){
            return novaSolucao.movimentos;
        }


        F[novaSolucao.getHash()] = novaSolucao;

        sucessores = geraSucessores(novaSolucao);


        while (!sucessores.empty()){
            PosAposMovimento sol = sucessores.front();
            sucessores.pop_front();
            //sol.setHash();

            try {
                PosAposMovimento fechado = F.at(sol.getHash());

                if (sol.movimentos < fechado.movimentos){
                    F.erase(fechado.getHash());
                    sol.h_linha = calculaHeuristica(config_final, sol.dados_entrada, CODIGO_HEURISTICA);
                    sol.funcaoF = sol.movimentos + sol.h_linha;
                    if (sol.funcaoF <= 9)
                        fooToString = "!" + std::to_string(sol.funcaoF);
                    else fooToString = std::to_string(sol.funcaoF);
                    A[fooToString + "-" + sol.getHash()] = sol;
                    auxiliar[sol.getHash()] = sol;
                }
            }
            catch (const std::out_of_range& oor) {
                try{
                    PosAposMovimento aberto = auxiliar.at(sol.getHash());
                    if(sol.movimentos < aberto.movimentos){
                        if (sol.funcaoF <= 9)
                            fooToString = "!" + std::to_string(sol.funcaoF);
                        else fooToString = std::to_string(sol.funcaoF);
                        A.erase(fooToString+ "-"+sol.getHash());
                        auxiliar.erase(aberto.getHash());
                        sol.h_linha = calculaHeuristica(config_final, sol.dados_entrada, CODIGO_HEURISTICA);
                        sol.funcaoF = sol.movimentos + sol.h_linha;
                        if (sol.funcaoF <= 9)
                            fooToString = "!" + std::to_string(sol.funcaoF);
                        else fooToString = std::to_string(sol.funcaoF);
                        A[fooToString + "-" +sol.getHash()] = sol;
                        auxiliar[sol.getHash()] = sol;
                    }
                } catch (const std::out_of_range& oor){
                    sol.h_linha = calculaHeuristica(config_final, sol.dados_entrada, CODIGO_HEURISTICA);
                    sol.funcaoF = sol.movimentos + sol.h_linha;
                    if (sol.funcaoF <= 9)
                        fooToString = "!" + std::to_string(sol.funcaoF);
                    else fooToString = std::to_string(sol.funcaoF);
                    A[fooToString+ "-"+sol.getHash()] = sol;
                    auxiliar[sol.getHash()] = sol;
                }

            }
        }

    }
    return 0;
}


int main(){
    static string HASH_SOLUCAO = "EH@$DCFBTSUGAVO!";
    static short CODIGO_HEURISTICA = 2;

    short config_final[4][4] = {{4, 3, 2, 1}, {5, 6, 7, 8}, {12, 11, 10, 9}, {13, 14, 15, 0}};
    PosAposMovimento posAposMovimento;
    std::map<string, PosAposMovimento> A;
    std::map<string, PosAposMovimento> F;
    std::map<string, PosAposMovimento> auxiliar;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            short valor;
            cin >> valor;
            posAposMovimento.dados_entrada[i][j] = valor;
        }
    }

    posAposMovimento.h_linha = calculaHeuristica(config_final, posAposMovimento.dados_entrada, CODIGO_HEURISTICA);
    posAposMovimento.funcaoF = 0;
    posAposMovimento.setHash();
    string fooToString;
        fooToString = "!" + std::to_string(posAposMovimento.funcaoF);
    A[fooToString+"-"+posAposMovimento.getHash()] = posAposMovimento;
    auxiliar[posAposMovimento.hash] = posAposMovimento;
    /*int resultado = A_Star(A, F, HASH_SOLUCAO, config_final, auxiliar, CODIGO_HEURISTICA);
    if (resultado == 0){
        return 0;
    }
    else*/
    cout <<  A_Star(A, F, HASH_SOLUCAO, config_final, auxiliar, CODIGO_HEURISTICA);
}