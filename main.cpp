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

namespace std
{
    template<typename T, size_t N>
    struct hash<array<T, N> >
    {
        typedef array<T, N> argument_type;
        typedef size_t result_type;

        result_type operator()(const argument_type& a) const
        {
            hash<T> hasher;
            result_type h = 0;
            for (result_type i = 0; i < N; ++i)
            {
                h = h * 31 + hasher(a[i]);
            }
            return h;
        }
    };
}

class PosAposMovimento{
public:
    std::array<short, 16> dados_entrada;
    int h_linha;
    long funcaoF;
    int origem = 0;
    int movimentos = 0;
    bool temPai = false;
};

int h1(std::array<short, 16> config_final,  std::array<short, 16> dados_entrada){
    int posicao_Errada = 0;
    for (short j = 0; j < 16; j++) {
        if (dados_entrada[j] != 0){
            if (config_final[j] != dados_entrada[j])
                posicao_Errada++;
        }
    }
    return posicao_Errada;
}


int converte_pos_correta(int i, std::array<short, 16> pos_correta){
    return pos_correta[i];
}

static int h2(std::array<short, 16> solucao_possivel, std::array<short, 16> pos_correta) {
    int peca_esperada = solucao_possivel[0];
    int r = 0, i;

    for (i = 0; i < 16; i++) {
        int pos = converte_pos_correta(i, pos_correta);
        if (peca_esperada == 0 + 1)
            peca_esperada = solucao_possivel[pos];
        else if (solucao_possivel[pos] != peca_esperada) {
            r++;
            peca_esperada = solucao_possivel[pos];
        }
        peca_esperada = (peca_esperada + 1) % 16;
    }
    return r;
}

int distancia_manhattan(int posicao_atual, int posicao_correta){
    auto ponto_atual_X = (int)((double)posicao_atual/(double)4);
    int ponto_atual_Y = posicao_atual%4;
    auto ponto_correto_X = (int)((double)posicao_correta/(double)4);
    int ponto_correto_Y = posicao_correta%4;
    int diferenca_X = std::abs(ponto_atual_X - ponto_correto_X);
    int diferenca_Y = std::abs(ponto_atual_Y - ponto_correto_Y);
    return diferenca_X + diferenca_Y;
}


int h3(std::array<short, 16> pos_correta, std::array<short, 16> solucao_possivel){
    int resultado = 0;
    for (int i = 0; i < 16; i++) {
        if (solucao_possivel[i] == 0) continue;
        resultado+= distancia_manhattan(i, converte_pos_correta(solucao_possivel[i] - 1, pos_correta));

    }return resultado;
}


 int calculaHeuristica(int cod, std::array<short, 16> pos_correta, std::array<short, 16> config_final, std::array<short, 16> solucao_possivel){
    int resultado = 0;
    if (cod == 1)
        resultado = h1(config_final, solucao_possivel);
    if (cod == 2)
        resultado = h2(solucao_possivel, pos_correta);
    if (cod == 3)
        resultado = h3(pos_correta, solucao_possivel);
    if(cod == 4)
        resultado = (int)((0.17D * (double)h1(config_final, solucao_possivel)) + (0.03D * (double)h2(solucao_possivel, pos_correta)) + (0.8D * (double)h3(pos_correta, solucao_possivel)));
    if(cod == 5)
        resultado = (std::max(std::max(h1(config_final, solucao_possivel), h2(solucao_possivel, pos_correta)), h3(pos_correta, solucao_possivel)));

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
        for (int j = 0; j < 16; j++) {
            auto ponto_atual_X = (int)((double)j/(double)4);
            int ponto_atual_Y = j%4;
            if (posAposMovimento.dados_entrada[j] == 0){
                if (ponto_atual_X != 0 && (!posAposMovimento.temPai || posAposMovimento.origem != -1)){
                    PosAposMovimento up;
                    up.movimentos = posAposMovimento.movimentos + 1;
                    up.dados_entrada = posAposMovimento.dados_entrada;

                    short aux = up.dados_entrada[j];
                    up.dados_entrada[j] = up.dados_entrada[j-4];
                    up.dados_entrada[j-4] = aux;
                    up.origem = 1;
                    up.temPai = true;
                    sucessores.push_back(up);
                }

                if (ponto_atual_X != 3 && (!posAposMovimento.temPai || posAposMovimento.origem != 1)){
                    PosAposMovimento down;
                    down.movimentos = posAposMovimento.movimentos + 1;
                    down.dados_entrada = posAposMovimento.dados_entrada;

                    short aux = down.dados_entrada[j];
                    down.dados_entrada[j] = down.dados_entrada[j+4];
                    down.dados_entrada[j+4] = aux;
                    down.origem = -1;
                    down.temPai = true;
                    sucessores.push_back(down);

                }

                if (ponto_atual_Y != 0 && (!posAposMovimento.temPai || posAposMovimento.origem != -2)){
                    PosAposMovimento left;
                    left.movimentos = posAposMovimento.movimentos + 1;
                    left.dados_entrada = posAposMovimento.dados_entrada;

                    short aux = left.dados_entrada[j];
                    left.dados_entrada[j] = left.dados_entrada[j-1];
                    left.dados_entrada[j - 1] = aux;
                    left.origem = 2;
                    left.temPai = true;
                    sucessores.push_back(left);
                }

                if (ponto_atual_Y != 3 && (!posAposMovimento.temPai || posAposMovimento.origem != 2)){
                    PosAposMovimento right;
                    right.movimentos = posAposMovimento.movimentos + 1;
                    right.dados_entrada = posAposMovimento.dados_entrada;

                    short aux = right.dados_entrada[j];
                    right.dados_entrada[j] = right.dados_entrada[j+1];
                    right.dados_entrada[j+1] = aux;
                    right.origem = -2;
                    right.temPai = true;
                    sucessores.push_back(right);
                }
            }
        }
    return sucessores;
}


long A_Star(std::priority_queue<PosAposMovimento, vector<PosAposMovimento>, comparer> &A, std::unordered_map<std::array<short, 16>, PosAposMovimento> &F, std::array<short, 16> config_final, std::array<short, 16> pos_correta, int cod){

    PosAposMovimento novaSolucao;
    std::list<PosAposMovimento> sucessores;

    while (!A.empty()){
        novaSolucao =  A.top();
        //std::cout<< novaSolucao.getHash() << " => " << novaSolucao.funcaoF << " => " << novaSolucao.movimentos << '\n';

        A.pop();

        //system("pause");

        if (novaSolucao.dados_entrada == config_final){
            return novaSolucao.movimentos;
        }


        F.insert({novaSolucao.dados_entrada, novaSolucao});

        sucessores = geraSucessores(novaSolucao);


        for (auto &sucessore : sucessores) {
            if (F.count(sucessore.dados_entrada) == 0){
                sucessore.h_linha = calculaHeuristica(cod, pos_correta, config_final, sucessore.dados_entrada);
                sucessore.funcaoF = sucessore.movimentos + sucessore.h_linha;
                A.push(sucessore);
            }

        }

    }
    return -1;
}


int main(){

    uint64_t currentUsedRAM(0);

    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    currentUsedRAM = info.WorkingSetSize;


    int cod = 3;
    std::array<short, 16> config_final = {4, 3, 2, 1, 5, 6, 7, 8, 12, 11, 10, 9, 13, 14, 15, 0};
    std::array<short, 16> pos_correta = {3, 2, 1, 0, 4, 5, 6, 7, 11, 10, 9, 8, 12, 13, 14, 15};
    PosAposMovimento posAposMovimento;
    std::priority_queue<PosAposMovimento, vector<PosAposMovimento>, comparer> A;
    std::unordered_map<std::array<short, 16>, PosAposMovimento>F{};

        for (short j = 0; j < 16; j++) {
            short valor;
            cin >> valor;
            posAposMovimento.dados_entrada[j] = valor;
        }

    posAposMovimento.h_linha = calculaHeuristica(cod, pos_correta, config_final, posAposMovimento.dados_entrada);
    posAposMovimento.funcaoF = posAposMovimento.h_linha;
    A.push(posAposMovimento);

    clock_t begin = clock();
    int resultado = A_Star(A, F, config_final, pos_correta, cod);
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