
/*

    right now pare ca merge if-ul

*/

#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<vector>

using namespace std;

ifstream fin("pseudocod.txt");

map<string, int> ints;
map<string, char> chars;

map<string, bool> seen_ints; // daca exista un int cu numele

std::streampos pos; // tine minte unde incepe linia

int solve_expresie_aritmetica(vector<string> v){

    cout << "se rezolva ecuatia aritmetica : ";
    for(auto e : v)
        cout << e << " ";
    cout << endl;

    // (x+2) % 3 - 4

    // rezolvam prima data parantezele

    // BIG TO DO : codul de acum presupune ca in v sunt numai numere si operatori, dar pot si si variabile

    bool stop = 0;
    int i, j, x;
    vector<string> aux;
    string xaux;

    int nrd=0, nri=0; // nr deschise, nr inchise

    vector<int> vint;

    auto first = v.begin();
    auto last = v.begin();

    auto firstint = vint.begin();
    auto lastint = vint.begin();

    

    while(!stop){

        aux.clear();
        stop = 1;

        for(i=0;i<v.size();i++){

            if(v[i][0] == '('){

                

                stop = 0;
                //v[i].erase(v[i].begin()); // sterge paranteza

                nrd = nri =  0;

                first = v.begin() + i; // pointer

                for(j=i;j<v.size();j++){

                    aux.push_back(v[j]);

                    string aux2 = v[j];

                    while(!aux2.empty() && aux2[aux2.size()-1] == ')'){
                        nri++;
                        aux2.pop_back();
                    }
                    
                    string aux3 = v[j];
                    while(!aux3.empty() && aux3[0] == '('){
                        nrd++;
                        aux3.erase(aux3.begin());
                    }

                    if(nrd - nri == 0){
                        //aux[aux.size()-1].pop_back(); // sterge paranteza
                        //v[j].pop_back(); // just in case

                        v[j] = aux2; //just in case

                        v[i].erase(v[i].begin());
                        v[j].pop_back(); // stergem parantezele ecuatiei curente

                        aux[0].erase(aux[0].begin());
                        aux[aux.size()-1].pop_back();

                        x = solve_expresie_aritmetica(aux);
                        aux.clear();

                        //cout << "i j " << i << " " << j << endl;

                        last = v.begin() + j; // pointer

                        break;
                    }

                }

                if(nrd - nri != 0){
                    cout << "EROARE : parantezele nu sunt corecte\n";
                    exit(0);
                }

                /*************
                cout << "inainte de rezolvarea parantezelor : ";
                for(auto e : v)
                    cout << e << " ";
                cout << endl;
                *************/

                v.erase(first, last+1); // sterge [first, last+1)

                /*************
                cout << "dupa stergere : ";
                for(auto e : v)
                    cout << e << " ";
                cout << endl;
                *************/

                //cout << "x : " << x << endl;

                xaux.clear();
                /// transforma pe x in string 
                while(x){
                    xaux.insert(xaux.begin(), char('0'+x%10));
                    x /= 10;
                }

                //cout << "xaux : " << xaux << endl;

                v.insert(v.begin() + i, xaux); // insereaza rezultatul parantezei pe pozitia i

                /*************
                cout << "dupa rezolvarea parantezelor : ";
                for(auto e : v)
                    cout << e << " ";
                cout << endl;
                *************/

                break;

            }

        }

    }

    
    //acum nu mai avem paranteze (sper)

    // 5 + 2 - 33 * -1

    // metoda prostului : trecem prin toate numerele, daca vedem o operatie de gradul doi o facem, pana cand nu mai avem
    // dupa operatiile de gradul 1
    // in niciun caz nu e O(n^2) 
    // poate candva o fac O(n) (nu cred)

    for(string e : v){

        if(isdigit(e[0])){
            vint.push_back(stoi(e));
        }
        else{
            vint.push_back(-1); // operator, nu ar trebuie sa afecteze operatiile. e pus doar ca sa fie de aceiasi lungime cu v[]
        }

    }

    /*
    cout << "vint : \n";
    for(int e : vint)
        cout << e << " ";
    cout << "\n\n";
    */

    stop = 0;
    while(!stop){

        stop = 1;

        for(i=0;i+2<v.size();i++){

            if(v[i+1] == "*" || v[i+1] == "/"){

                // operatie de gradul 2

                if(v[i+1] == "*")
                    vint[i] *= vint[i+2];
                else
                    vint[i] /= vint[i+2];

                v.erase(v.begin()+i+1, v.begin()+i+3);
                vint.erase(vint.begin()+i+1, vint.begin()+i+3);
                stop = 0;
                break;

            }

        }

    }

    stop = 0;
    while(!stop){

        stop = 1;

        for(i=0;i+2<v.size();i++){

            if(v[i+1] == "+" || v[i+1] == "-"){

                // operatie de gradul 2

                if(v[i+1] == "+")
                    vint[i] += vint[i+2];
                else
                    vint[i] -= vint[i+2];

                /**********
                cout << "v : \n";
                for(auto e : v)
                    cout << e <<  " ";
                cout << "\n";
                cout << "vint : \n";
                for(auto e : vint)
                    cout << e <<  " ";
                cout << "\n\n";
                **********/
                v.erase(v.begin()+i+1, v.begin()+i+3);
                vint.erase(vint.begin()+i+1, vint.begin()+i+3); // stege de la i+1 la i+2

                /**********
                cout << "v : \n";
                for(auto e : v)
                    cout << e <<  " ";
                cout << "\n";
                cout << "vint : \n";
                for(auto e : vint)
                    cout << e <<  " ";
                cout << "\n\n";
                **********/
                stop = 0;
                break;

            }

        }

    }

    // rezultatul in vint[0] probabil

    if(v.size() > 1){
        // probelma
        cout << "EROARE : evaluarea ecuatiei nu s-a facut corect\n";
        for(auto e : vint)
         cout << e << " ";
        cout << endl;
        exit(0);
    }

    cout << "un rezultat : " << vint[0] << endl;
    return vint[0];

    cout << "EROARE 0129";
    return 0;

}   

bool solve_expresie_comparatie(vector<string> v){

    // (x+2) % 3 - 4 < 3 + 21 % 2

    // gata probabil

    vector<string> v1, v2;
    bool h = 0;
    int x1, x2;
    string op="nush";

    for(string e : v){

        if(e == "=" || e == "<" ||e == ">" ||e == "<=" ||e == ">="){
            h = 1;
            op = e;
            continue;
        }

        if(!h)
            v1.push_back(e);
        else
            v2.push_back(e);

    }

    x1 = solve_expresie_aritmetica(v1);
    x2 = solve_expresie_aritmetica(v2);

    //cout << "x1 : " << x1 << " x2 : " << x2 << " op : " << op << endl;

    if(op == "=")
        return x1 == x2;
    
    if(op == "<")
        return x1 < x2;    

    if(op == ">")
        return x1 > x2;

    if(op == "<=")
        return x1 <= x2;
    
    if(op == ">=")
        return x1 >= x2;
    

    cout << "EROARE : nu stiu exact ce";
    exit(0);

}

bool solve_expresie_logica(vector<string> cuvinte){

    /// (x + 1) % 2 = 0 & y + 1 < -3

    // pas 1 : impartim in bucati dupa opi logici
    // pas 2 : impartim dupa opi de comparatie (=, >, <, etc.)
    // pas 3 : impartim in bucati dupa opi (ceilalti, cred ca aritmetici)

    // gata probabil


    // to do : nu merg paranteze pe asta. trebuie facut ceva asemanator cu solve_expresie_aritmatica, in care rezolv recursiv niste paranteze

    vector<string> aux;
    bool h, frst=1;
    int x;
    string auxop = "nush";

    for(string e:cuvinte){

        if(e == "&" || e == "|"){
            x = solve_expresie_comparatie(aux);

            cout << "rezultat prima conditie : " << x << endl;

            aux.clear();
            auxop = e;
            if(e == "&"){
                if(frst){
                    frst = 0;
                    h = x;
                }
                else
                    h &= x;
            }
            else{
                if(frst){
                    frst = 0;
                    h = x;
                }
                else
                    h |= x;
            }
        }
        else

          aux.push_back(e);

    }

    if(!aux.empty()){
        x = solve_expresie_comparatie(aux);
            aux.clear();
            if(auxop == "&"){
                if(frst){
                    frst = 0;
                    h = x;
                }
                else
                    h &= x;
            }
            else{
                if(frst){
                    frst = 0;
                    h = x;
                }
                else
                    h |= x;
            }
    }

    return h;

}

string next_line(){

    string linie;
    pos = fin.tellg(); // tine minte unde incepe linia
    getline(fin, linie);

    if(linie == "")
        return next_line();
    else
       fin.seekg(pos); // merge inapoi la pos

    return linie;

}

void solve_bucata_cod(string oprire){

    string s, linie, input, x, y, op, linie1;
    int i, j;
    vector<string> cuvinte;
    bool h;


    while(getline(fin, linie)){

        cout << "linie : " << linie << endl;

        if(linie == oprire) // || linie[0] == "altfel" || linie[0] == "sfarsit"
            return;

        if(linie.empty())
            continue;

        cuvinte.clear();
        s.clear();

        for(i=0;i<linie.size();i++){

            if(linie[i] == ' '){
                if(!s.empty())
                  cuvinte.push_back(s);
                s.clear();
            }

            else{
                s.push_back(linie[i]);
            }

        }

        if(!s.empty())
            cuvinte.push_back(s);
        s.clear();

        if(cuvinte[0] == "sfarsit")
            return;

        if(cuvinte[0] == "citeste"){

            s = cuvinte[1];
            
            cin >> input;

            if(isdigit(input[0])){
                // am citit un int
                ints[s] = stoi(input);
                seen_ints[s] = 1;
            }
            if(isalpha(input[0])){
                // to do restul tipurilor de variabile
            }

            continue;

        }
        
        if(cuvinte[0] == "afiseaza"){
            s = cuvinte[1];
            if(seen_ints[s]){
                cout << ints[s] << "\n";
            }
            else{
                cout << "EROARE : nu exista nicio variabila cu numele " << s << "\n";
            }
            continue;
        }

        if(cuvinte.size() > 1 && (cuvinte[1] == "<-" || cuvinte[1] == "←")){

            // atribuire : 
            x = cuvinte[0];
            // cuvinte[1] = "<-"
            y = cuvinte[2];

            if(!seen_ints[x]){
                //cout << "EROARE : nu exista nicio variabila cu numele " << x << "\n";
                //continue;
        
            }
            if(isalpha(y[0]) && !seen_ints[y]){
                cout << "EROARE : nu exista nicio variabila cu numele (nedefinit) " << y << "\n";
                continue;
            }

            seen_ints[x] = 1;
            if(isdigit(y[0]))
                ints[x] = stoi(y);
            else
                ints[x] = ints[y];
        }

        if(cuvinte[0] == "daca"){ //if
            
            // daca (a + b) + 10 = 12 + 4 atunci

            vector<string> expr;
            bool hh;

            for(int ii = 1; ii < cuvinte.size() && cuvinte[ii] != "atunci";ii++){

                expr.push_back(cuvinte[ii]);

            }

            //cout << "expresie if : "; for(auto e : expr) cout << e << " ";

            hh = solve_expresie_logica(expr);

            cout << "rezultat if " << hh << endl;

            if(hh){
                solve_bucata_cod("sfarsit daca");
                string nl = next_line(); // to do, functie care citeste urmatoare linie *si da citirea inapoi*

                cout << "\n next line " << nl << "\n";

                if(nl == "altfel"){
                    // citeste pana la sfarsit altfel
                    while(getline(fin, linie)){
                        if(linie == "sfarsit altfel")
                            break;
                    }
                }
            }
            else{

                // sarim peste continutul if-ului
                while(getline(fin, linie)){
                    if(linie == "sfarsit daca")
                    break;
                }

                string nl = next_line();
                if(nl == "altfel"){
                    solve_bucata_cod("sfarsit altfel");
                }

            }

        }

        if(cuvinte[0] == "pentru"){ //for

            continue;
        }
        
        if(cuvinte[0] == "cat"){ //while

            continue;
        }
        if(cuvinte[0] == "sfarsit"){ //paranteza inchisa

            continue;
        }
        
    }

    //cout << "ints : \n";
    //for(auto e : ints)
    //    cout << e.first << " " << e.second << endl;

}

void test(){

    vector<string> expresie;

    expresie.push_back("(1");
    expresie.push_back("+");
    expresie.push_back("2)");
    expresie.push_back("*");
    expresie.push_back("3");
    expresie.push_back("=");
    expresie.push_back("3");
    expresie.push_back("*");
    expresie.push_back("(2");
    expresie.push_back("+");
    expresie.push_back("2)");

    expresie.push_back("&");

    expresie.push_back("(1");
    expresie.push_back("+");
    expresie.push_back("2)");
    expresie.push_back("*");
    expresie.push_back("3");
    expresie.push_back("<=");
    expresie.push_back("3");
    expresie.push_back("*");
    expresie.push_back("(2");
    expresie.push_back("+");
    expresie.push_back("1)");

    // solve_expresie_comparatie cred ca merge in mare parte
    
    //cout << solve_expresie_logica(expresie);

    solve_bucata_cod("CEVA CE NU SE ATINGE");


}

int main(){



    cout << "\n";

    test();

    //solve_bucata_cod("nush");

    cout << "\n";

}