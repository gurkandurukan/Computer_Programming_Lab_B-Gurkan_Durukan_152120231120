 #include <iostream>
#include <string>

using namespace std;

struct Page {
    string url;
    string title;
    int accessTime[3];
    Page *next;
    Page *prev;
};

class BrowserHistory {
private:
    Page *head;
    Page *tail;
    Page *current;

public:
    BrowserHistory() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    void visit(string u, string t, int h, int m, int s) {
        Page *newPage = new Page;
        newPage->url = u;
        newPage->title = t;
        newPage->accessTime[0] = h;
        newPage->accessTime[1] = m;
        newPage->accessTime[2] = s;
        newPage->next = nullptr;
        newPage->prev = nullptr;

        if (head == nullptr) {
            head = tail = current = newPage;
        } else {
            tail->next = newPage;
            newPage->prev = tail;
            tail = newPage;
            current = newPage;
        }
        cout << "-> Visited: " << t << "\n";
    }

    void back() {
        if (current != nullptr && current->prev != nullptr) {
            current = current->prev;
            cout << "-> Went back to: " << current->title << "\n";
        } else {
            cout << "-> Cannot go back further.\n";
        }
    }

    void forward() {
        if (current != nullptr && current->next != nullptr) {
            current = current->next;
            cout << "-> Went forward to: " << current->title << "\n";
        } else {
            cout << "-> Cannot go forward further.\n";
        }
    }

    void deleteEntry() {
        if (current == nullptr) return;

        Page *temp = current;

        if (head == tail) {
            head = nullptr;
            tail = nullptr;
            current = nullptr;
        }
        else if (current == head) {
            head = head->next;
            head->prev = nullptr;
            current = head;
        }
        else if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
            current = tail;
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->prev;
        }

        cout << "-> Deleted: " << temp->title << "\n";
        delete temp;
    }

    void displayHistory() {
        if (head == nullptr) {
            cout << "-> History is empty.\n";
            return;
        }

        cout << "\nBrowser History\n";
        Page *temp = head;
        while (temp != nullptr) {
            if (temp == current) {
                cout << "[CURRENT] ";
            } else {
                cout << "          ";
            }

            cout << temp->title << " (" << temp->url << ") - Time: ";

            for (int i = 0; i < 3; i++) {
                if (temp->accessTime[i] < 10) cout << "0";
                cout << temp->accessTime[i];
                if (i < 2) cout << ":";
            }
            cout << "\n";

            temp = temp->next;
        }

    }

    void clearMemory() {
        Page *temp = head;
        while (temp != nullptr) {
            Page *nextPage = temp->next;
            delete temp;
            temp = nextPage;
        }
        head = nullptr;
        tail = nullptr;
        current = nullptr;
        cout << "-> Memory cleared. No leaks.\n";
    }
};

int main() {
    BrowserHistory browser;
    string cmd;

    while (true) {
        cout << "\nCommand (VISIT, BACK, FORWARD, DELETE, DISPLAY, EXIT): ";
        cin >> cmd;

        if (cmd == "VISIT") {
            string url, title;
            int h, m, s;
            cout << "URL: "; cin >> url;
            cout << "Title: "; cin >> title;
            cout << "Time (H M S): "; cin >> h >> m >> s;
            browser.visit(url, title, h, m, s);
        }
        else if (cmd == "BACK") {
            browser.back();
        }
        else if (cmd == "FORWARD") {
            browser.forward();
        }
        else if (cmd == "DELETE") {
            browser.deleteEntry();
        }
        else if (cmd == "DISPLAY") {
            browser.displayHistory();
        }
        else if (cmd == "EXIT") {
            browser.clearMemory();
            break;
        }
        else {
            cout << "-> Invalid command.\n";
        }
    }

    return 0;
}
