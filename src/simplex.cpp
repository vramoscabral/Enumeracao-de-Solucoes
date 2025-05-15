#include <bits/stdc++.h>
using namespace std;

vector<string> combinacoes(int n, int m) {
    vector<string> c;
    int k = n - m;
    vector<int> comb(k);

    // Inicializa com a menor combinação: 0, 1, 2, ..., k-1
    for (int i = 0; i < k; ++i)
        comb[i] = i;

    while (true) {
        string s = "";
        for (int i = 0; i < k; ++i)
            s += to_string(comb[i]) + "_";
        s += "0";  // final fixo
        c.push_back(s);

        // Gera proxima combinação
        int i = k - 1;
        while (i >= 0 && comb[i] == n - k + i)
            --i;

        if (i < 0)
            break;

        ++comb[i];
        for (int j = i + 1; j < k; ++j)
            comb[j] = comb[j - 1] + 1;
    }

    return c;
}

bool existe(int* C_N, int j, int n, int m) {
    for (int i=0; i<n-m; i++) {
        if (j == C_N[i]) return true;
    }
    return false;
}

//função que calcula solução por solução (se houver)
pair<int, int> phase1simplex(string comb, int* C, int**A, int* b, int n, int m) {
    int* C_N = new int[n-m];
    int i=0, j, valor;
    stringstream ss(comb);
    string item;
    //Vetor coeficientes não básicos
    for (i=0; i<n-m; i++) {
        getline(ss, item, '_');
        valor = stoi(item);
        C_N[i] = valor;
    }
    //Vetor coeficientes básicos
    int* C_B = new int[m];
    int vcb=0;
    for (i=0; i<n; i++) {
        if(!existe(C_N, i, n, m)) {
            C_B[vcb] = i;
            vcb++;
        }
    }
    //matriz básica
    int** Bas = new int*[m];
    for (i=0; i<m; i++) {
        Bas[i] = new int[m];
    }
    for (i=0; i<m; i++) {
        for (j=0; j<m; j++) {
            Bas[j][i] = A[j][C_B[i]];
        }
    }
    //matriz nao básica
    int** Nbas = new int*[m];
    for (i=0; i<m; i++) {
        Nbas[i] = new int[n-m];
    }
    for (i=0; i<n-m; i++) {
        for (j=0; j<m; j++) {
            Nbas[j][i] = A[j][C_N[i]];
        }
    }

    cout << "Bas = " << endl; "[";
    for (i=0; i<m; i++) {
        for (j=0; j<m; j++) {
            cout << Bas[i][j] << " ";
        }
        cout << endl;
    }
    cout << "] \n";
    cout << "Nbas = " << endl; "[";
    for (i=0; i<m; i++) {
        for (j=0; j<n-m; j++) {
            cout << Nbas[i][j] << " ";
        }
        cout << endl;
    }
    cout << "] \n";

    int solucao, resultado;
    return make_pair(solucao, resultado);
}

int main() {
    fstream leitor("entrada.txt"); // ler arquivo
    if (!leitor.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    int n, m, i, j, r, nqnt; // n-> variaveis, m-> restricoes
    // i, j-> iteracao, r->numero a ser lido
    leitor >> n >> m;
    int* C = new int[n]; // coeficientes
    for (i=0; i<n; i++) {
        leitor >> r;
        C[i] = r;
    }

    //leitura e armazenamento das restrições e seus valores
    int** A = new int*[m]; // matriz A (Ax = B)
    for (i=0; i<m; i++) {
        A[i] = new int[n];
    }
    int* b = new int[m]; // matriz B (Ax = B)
    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            leitor >> r;
            A[i][j] = r;
        }
        leitor >> r;
        b[i] = r;
    }

    leitor.close();

    vector<string> c = combinacoes(n,m);
    pair<int, int> par;
    par = phase1simplex(c[0],C,A,b,n,m);
    /*int solt=0, solv=0, soln=0; // solucoes totais, solucoes validas, e nao validas
    pair<int, int> par;
    for (i=0; i<nqnt; i++) {
    }*/

    return 0;
}