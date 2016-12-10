#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <algorithm>

using namespace std;

class Individuo {
public:
    Individuo();
    Individuo(int numero_caratteri);
    vector<pair<int, int> > caratteri;
    void random(vector<vector<int> > caratteri);
};

vector<Individuo> genera(vector<Individuo> pool, int numero_massimo_figli);
Individuo accoppia(Individuo a, Individuo b);
void log (vector<Individuo> pool);
void stampa (vector<vector<int> > caratteri, vector<Individuo> pool);

ifstream input;
ofstream output;

int main() {
    const int   NUMERO_CARATTERI = 100,
                NUMERO_MASSIMO_ALLELI = 10,
                NUMERO_GENERAZIONI = 10,
                NUMERO_MASSIMO_FIGLI = 7,
                POPOLAZIONE_INIZIALE = 1000,
                NUMERO_MINIMO_ALLELI = 2;

    /********************************************/
    //const int TASSO_DI_CRESCITA_DEMOGRAFICA = 2.2;
    /********************************************/
    
    vector<vector<int> > caratteri (NUMERO_CARATTERI);
    vector<Individuo> pool (POPOLAZIONE_INIZIALE);

    input.open("input.txt");
    output.open("output.txt");

    srand(time(NULL));

    for (int i = 0; i < caratteri.size(); i++) { // Per ogni valore del vettore caratteri...
        caratteri[i].resize(rand() % (NUMERO_MASSIMO_ALLELI - NUMERO_MINIMO_ALLELI) + NUMERO_MINIMO_ALLELI + 1); // Imposto la dimensione dell'i-esimo valore del vettore caratteri compreso tra 0 e NUMERO_MASSIMO_ALLELI

        for (int w = 0; w < caratteri[i].size(); w++) // Per ogni valore dell'i-esimo valore del vettore caratteri
            caratteri[i][w] = rand() % 101; //forza degli alleli
    }

    Individuo individuo (NUMERO_CARATTERI);
    for (int i = 0; i < pool.size(); i++) { // Per ogni valore del vettore pool...
        individuo.random(caratteri); // Randomizzo l'individuo e lo aggiungo
        pool[i] = individuo;
    }    

    for (int i = 0; i < NUMERO_GENERAZIONI; i++)
       pool = genera(pool, NUMERO_MASSIMO_FIGLI);
    
    //stampa(caratteri, pool);
    log(pool);

    input.close();
    output.close();

    return 0;
}

Individuo::Individuo() {
    this->caratteri.resize(0);
}

Individuo::Individuo(int numero_caratteri) {
    this->caratteri.resize(numero_caratteri);
}

void Individuo::random(vector<vector<int> > caratteri) {
    for (int i = 0; i < this->caratteri.size(); i++) {
        this->caratteri[i].first = rand() % caratteri[i].size();
        this->caratteri[i].second = rand() % caratteri[i].size();
    }
}

vector<Individuo> genera(vector<Individuo> pool, int numero_massimo_figli) {
    vector<Individuo> futuro;

    if (pool.size() < 2) return futuro;

    random_shuffle(pool.begin(), pool.end());

    if (pool.size() % 2 == 1) {
        futuro.push_back(pool.back());
        pool.pop_back();
    }

    Individuo figlio (pool[0].caratteri.size()); 
    for (int i = 0; i < pool.size(); i += 2) {
        for (int w = 0; w < rand() % numero_massimo_figli; w++) {
            figlio = accoppia(pool[i], pool[i + 1]);
            futuro.push_back(figlio);
        }
    }

    return futuro;
}

Individuo accoppia(Individuo a, Individuo b) {
    Individuo figlio (a.caratteri.size());

    for (int i = 0; i < a.caratteri.size(); i++) {
        switch(rand() % 2) {
            case 0:
                figlio.caratteri[i].first = a.caratteri[i].first;
                break;
            case 1:
                figlio.caratteri[i].first = b.caratteri[i].first;
                break;
        }

        switch(rand() % 2) {
            case 0:
                figlio.caratteri[i].second = a.caratteri[i].second;            
                break;
            case 1:
                figlio.caratteri[i].second = b.caratteri[i].second;            
                break;
        }
    }

    return figlio;
}

void log (vector<Individuo> pool) {
    for (int i = 0; i < pool.size(); i++) {
        output << i << ": {" << endl;
        for (int w = 0; w < pool[i].caratteri.size(); w++) {
            output << "\t" << w << ": " << pool[i].caratteri[w].first << "\t" << pool[i].caratteri[w].second << endl;
        }
        output << "}," << endl;
    }
    output << endl << "##########" << endl;
}

void stampa (vector<vector<int> > caratteri, vector<Individuo> pool) {
    output << caratteri.size() << endl;
    output << pool.size() << endl;

    for (int i = 0; i < caratteri.size(); i++) {
        output << caratteri[i].size() << " ";
        for (int w = 0; w < caratteri[i].size(); w++)
            output << caratteri[i][w] << " ";
        output << endl;
    }

    for (int i = 0; i < pool.size(); i++) {
        for (int w = 0; w < pool[i].caratteri.size(); w++)
            output << pool[i].caratteri[w].first << " " << pool[i].caratteri[w].second << " ";
        output << endl;
    }
}
