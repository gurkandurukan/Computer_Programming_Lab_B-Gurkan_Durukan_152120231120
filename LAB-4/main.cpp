#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

class MoneyStack {
private:
    MoneyBundle* top;
    int size;

public:
    MoneyStack() : top(nullptr), size(0) {}

    bool isEmpty() { return top == nullptr; }
    int getSize() { return size; }

    void push(string serial, string currency, int yuz, int elli, int yirmi) {
        MoneyBundle* yeni = new MoneyBundle();
        yeni->serialNumber = serial;
        yeni->currencyType = currency;
        yeni->billCounts[0] = yuz;
        yeni->billCounts[1] = elli;
        yeni->billCounts[2] = yirmi;
        yeni->next = top;
        top = yeni;
        size++;
        cout << "Kasa'ya eklendi -> Seri: " << serial << " Para Birimi: " << currency << endl;
    }

    MoneyBundle* peek() {
        return top;
    }

    void popAndFree() {
        if (isEmpty()) return;
        MoneyBundle* temp = top;
        top = top->next;
        delete temp;
        size--;
    }

    void display() {
        if (isEmpty()) {
            cout << "  Kasa bos." << endl;
            return;
        }
        MoneyBundle* temp = top;
        int i = 1;
        while (temp != nullptr) {
            cout << "  " << i << ". Seri: " << temp->serialNumber
                 << " | " << temp->currencyType
                 << " | 100: " << temp->billCounts[0]
                 << " | 50: " << temp->billCounts[1]
                 << " | 20: " << temp->billCounts[2] << endl;
            temp = temp->next;
            i++;
        }
    }

    ~MoneyStack() {
        while (!isEmpty()) {
            popAndFree();
        }
    }
};

struct Customer {
    string customerName;
    string transactionType;
    int request[3];
};

#define MAX 5

class CustomerQueue {
private:
    Customer arr[MAX];
    int front;
    int rear;
    int count;

public:
    CustomerQueue() : front(0), rear(0), count(0) {}

    bool isEmpty() { return count == 0; }
    bool isFull() { return count == MAX; }
    int getCount() { return count; }

    void enqueue(string isim, string islem, int r100, int r50, int r20) {
        if (isFull()) {
            cout << "Kuyruk dolu! " << isim << " eklenemedi." << endl;
            return;
        }
        arr[rear].customerName = isim;
        arr[rear].transactionType = islem;
        arr[rear].request[0] = r100;
        arr[rear].request[1] = r50;
        arr[rear].request[2] = r20;
        rear = (rear + 1) % MAX;
        count++;
        cout << "Musteri eklendi -> " << isim << " | " << islem << endl;
    }

    Customer dequeue() {
        Customer bos = {"", "", {0,0,0}};
        if (isEmpty()) return bos;
        Customer servisEdilen = arr[front];
        front = (front + 1) % MAX;
        count--;
        return servisEdilen;
    }

    void display() {
        if (isEmpty()) {
            cout << "  Kuyruk bos." << endl;
            return;
        }
        int idx = front;
        for (int i = 0; i < count; i++) {
            cout << "  " << i + 1 << ". " << arr[idx].customerName
                 << " | " << arr[idx].transactionType
                 << " (Talep: 100x" << arr[idx].request[0]
                 << ", 50x" << arr[idx].request[1]
                 << ", 20x" << arr[idx].request[2] << ")" << endl;
            idx = (idx + 1) % MAX;
        }
    }
};

class BankBranch {
private:
    MoneyStack kasa;
    CustomerQueue kuyruk;

public:
    void paraDemetiEkle(string serial, string currency, int yuz, int elli, int yirmi) {
        kasa.push(serial, currency, yuz, elli, yirmi);
    }

    void musteriEkle(string isim, string islem, int r100, int r50, int r20) {
        kuyruk.enqueue(isim, islem, r100, r50, r20);
    }

    void islemYap() {
        if (kuyruk.isEmpty() || kasa.isEmpty()) {
            cout << "Islem yapilamaz: Musteri veya nakit eksik." << endl;
            return;
        }

        MoneyBundle* b = kasa.peek();
        Customer m = kuyruk.dequeue();

        bool yeterli = true;
        for(int i=0; i<3; i++) {
            if(b->billCounts[i] < m.request[i]) yeterli = false;
        }

        if (yeterli) {
            for(int i=0; i<3; i++) b->billCounts[i] -= m.request[i];
            cout << m.customerName << " islemi tamamlandi. Demetten para dusuldu." << endl;

            if(b->billCounts[0] == 0 && b->billCounts[1] == 0 && b->billCounts[2] == 0) {
                cout << "Demet tukendi ve kasadan cikarildi." << endl;
                kasa.popAndFree();
            }
        } else {
            cout << "HATA: Demette yeterli banknot yok! Musteri siradan cikarildi." << endl;
        }
    }

    void hepsiniGoster() {
        cout << "\nBANKA DURUMU " << endl;
        kasa.display();
        kuyruk.display();
    }
};

int getValidatedInt(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Gecersiz giris!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    BankBranch bank;
    int secim = -1;

    while (secim != 0) {
        cout << "\n1. Demet Ekle\n2. Musteri Ekle\n3. Islem Yap\n4. Goster\n0. Cikis\nSecim: ";
        secim = getValidatedInt("");

        if (secim == 1) {
            string s, c;
            cout << "Seri No: "; getline(cin, s);
            cout << "Birim: "; getline(cin, c);
            int y = getValidatedInt("100: ");
            int e = getValidatedInt("50: ");
            int yi = getValidatedInt("20: ");
            bank.paraDemetiEkle(s, c, y, e, yi);
        } else if (secim == 2) {
            string n, t;
            cout << "Isim: "; getline(cin, n);
            cout << "Tur: "; getline(cin, t);
            int y = getValidatedInt("100 talebi: ");
            int e = getValidatedInt("50 talebi: ");
            int yi = getValidatedInt("20 talebi: ");
            bank.musteriEkle(n, t, y, e, yi);
        } else if (secim == 3) {
            bank.islemYap();
        } else if (secim == 4) {
            bank.hepsiniGoster();
        }
    }
    return 0;
}
