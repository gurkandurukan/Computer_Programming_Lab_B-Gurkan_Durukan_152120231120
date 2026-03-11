 #include <iostream>

#include <string>

using namespace std;

struct Node {
    string isim;
    Node* next;
};

Node* baslangic = NULL;

void ekle(string sarki)
 {
 Node* yeni =new Node();
yeni->isim = sarki;
yeni->next =baslangic;
baslangic = yeni;

    cout << "Eklendi: " << sarki << endl;

}

void listele()
 {
    Node* t =baslangic;
    int n = 1;

    if (t == NULL) {
        cout << "Liste bos." << endl;
        return;
    }

    cout << "\n muzik_listesi" << endl;
    while (t != NULL) {
        cout << n << ". " << t->isim << endl;
        t = t->next;
        n++;
    }
}

void ara(string s) {
    Node*t = baslangic;
    bool var_mi = false;

    while (t != NULL) {
        if (t->isim == s) {
            var_mi = true;
            break;
        }

    t = t->next;
    }

    if (var_mi)
        {
        cout << s << " listede var." << endl;
    } else {
        cout << s << " bulunamadi." << endl;
    }
}

int main()

{
    int sec;
    string ad;

    while (true) {
        cout << "\n1.Ekle\n2.Ara\n3.Listele\n4.Cikis\nSecim: ";

        cin >> sec;

        cin.ignore();


        if (sec == 1) {
            cout << "Sarki: ";
            getline(cin, ad);
            ekle(ad);
        }
        else if (sec == 2) {
            cout << "Aranan: ";
            getline(cin, ad);
            ara(ad);
        }
        else if (sec == 3) {
            listele();
        }
        else if (sec == 4) {
            break;
        }
    }

    return 0;
}
