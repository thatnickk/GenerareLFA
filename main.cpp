#include <bits/stdc++.h>

using namespace std;

vector<char> simb;
map<char, vector<string>> expr;
vector<string> results;
int n;

void generare(vector<char> cuvant){
    if(cuvant.size() > n + 1){
        return;
    }

    bool hasSymb = false;
    for (int i = 0; i < cuvant.size(); i++)
        for (int j = 0; j < simb.size(); j++)
            if(cuvant[i] == simb[j])
                hasSymb = true;

    if(cuvant.size() == n && !hasSymb){
        string cuv = "";
        bool already = false;
        for (int i = 0; i < cuvant.size(); i++)
            cuv += cuvant[i];
        for (int i = 0; i < results.size(); i++){
            if (cuv == results[i]){
                already = true;
                break;
            }
        }
        if(!already){
            results.push_back(cuv);
        }
    }
    else{
        for(int i = 0; i < cuvant.size(); i++){
            bool esteSimbol = false;
            for (int j = 0; j < simb.size(); j++){
                if (cuvant[i] == simb[j])
                    esteSimbol = true;
            }

            if(esteSimbol){
                for (auto expressions : expr[cuvant[i]]){
                    vector<char> redo;
                    for (int j = 0; j < i; j++){
                        redo.push_back(cuvant[j]);
                    }
                    for (auto expression : expressions){
                        if(expression)
                            redo.push_back(expression);
                    }
                    for (int j = i + 1; j < cuvant.size(); j++){
                        redo.push_back(cuvant[j]);
                    }
                    generare(redo);
                }
            }
        }
    }

}

int main()
{
    ifstream fin("generare.in");
    string linie;
    getline(fin,linie);
    for (int i = 0; i < linie.size(); i++){
        if (linie[i] != ' ')
            simb.push_back(linie[i]);
    }
    getline(fin,linie);
    while (linie != "endoff"){
        vector<string> aux;
        char symbol = linie[0];
        string tranz = "";
        for (int i = 2; i < linie.size(); i++){
            tranz+=linie[i];
        }
        if(tranz == "eps"){
            tranz = "";
        }
        expr[symbol].push_back(tranz);
        getline(fin,linie);
    }

    cout << "dimensiune:";
    cin >> n;
    vector<char> init;
    for (auto expression : expr['S']){
        for (int i = 0; i < expression.size(); i++){
            init.push_back(expression[i]);
        }
        generare(init);
        init.clear();
    }

    for(int i = 0; i < results.size(); i++){
        cout << results[i] << ' ';
    }
    return 0;
}
