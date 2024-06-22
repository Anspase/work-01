#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Zvychka {
    string nazva;
    string opis;
    string chastota;
    bool vikonanaSyohodni;
};

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

void dodatiZvychku(vector<Zvychka>& zvychki) {
    setlocale(LC_CTYPE, "ukr");
    setlocale(LC_ALL, "");
    Zvychka novaZvychka;
    cout << YELLOW << "Введіть назву звички: " << RESET;
    getline(cin, novaZvychka.nazva);
    cout << YELLOW << "Введіть опис звички: " << RESET;
    getline(cin, novaZvychka.opis);
    cout << YELLOW << "Введіть частоту звички (щодня, щотижня, щомісяця): " << RESET;
    getline(cin, novaZvychka.chastota);
    novaZvychka.vikonanaSyohodni = false;

    zvychki.resize(zvychki.size() + 1);
    zvychki.back() = novaZvychka;

    cout << GREEN << "Звичку додано успішно!\n" << RESET;
}

void poznachitiZvychkuYakVikonanu(vector<Zvychka>& zvychki) {
    setlocale(LC_CTYPE, "ukr");
    setlocale(LC_ALL, "");
    if (zvychki.empty()) {
        cout << RED << "Список звичок порожній.\n" << RESET;
        return;
    }
    cout << "\n" << BLUE << "Список звичок:\n" << RESET;
    for (size_t i = 0; i < zvychki.size(); i++) {
        cout << i + 1 << ". " << zvychki[i].nazva << " (" << zvychki[i].chastota << ")\n";
    }
    int indexZvychki;
    cout << YELLOW << "Введіть номер звички, яку потрібно позначити як виконану: " << RESET;
    cin >> indexZvychki;
    cin.ignore();

    if (indexZvychki < 1 || indexZvychki > zvychki.size()) {
        cout << RED << "Неправильний номер звички.\n" << RESET;
        return;
    }
    zvychki[indexZvychki - 1].vikonanaSyohodni = true;
    cout << GREEN << "Звичку позначено як виконану!\n" << RESET;
}

void pokazatiProgres(const vector<Zvychka>& zvychki) {
    setlocale(LC_CTYPE, "ukr");
    setlocale(LC_ALL, "");
    if (zvychki.empty()) {
        cout << RED << "Список звичок порожній.\n" << RESET;
        return;
    }

    cout << BLUE << "\n+--------------------------------------------+\n";
    cout << "|               Прогрес звичок               |\n";
    cout << "+--------------------------------------------+\n";
    cout << "| Назва       | Частота      | Статус        |\n";
    cout << "+--------------------------------------------+\n" << RESET;

    for (const auto& zvychka : zvychki) {
        cout << "| " << zvychka.nazva << " | "
            << zvychka.chastota << " | ";
        if (zvychka.vikonanaSyohodni) {
            cout << GREEN << "Виконано  " << RESET << "|\n";
        }
        else {
            cout << RED << "Не виконано " << RESET << "|\n";
        }
    }
    cout << "+--------------------------------------------+\n";
}

void zberegtiZvychki(const vector<Zvychka>& zvychki) {
    setlocale(LC_CTYPE, "ukr");
    setlocale(LC_ALL, "");
    ofstream outfile("zvychki.txt");
    if (!outfile.is_open()) {
        cout << RED << "Помилка відкриття файлу.\n" << RESET;
        return;
    }

    for (const auto& zvychka : zvychki) {
        outfile << zvychka.nazva << endl;
        outfile << zvychka.opis << endl;
        outfile << zvychka.chastota << endl;
        outfile << zvychka.vikonanaSyohodni << endl;
    }
    outfile.close();
    cout << GREEN << "Дані збережено у файл zvychki.txt.\n" << RESET;
}

void zavantizhitiZvychki(vector<Zvychka>& zvychki) {
    setlocale(LC_CTYPE, "ukr");
    setlocale(LC_ALL, "");
    ifstream infile("zvychki.txt");
    if (!infile.is_open()) {
        cout << RED << "Помилка відкриття файлу.\n" << RESET;
        return;
    }

    Zvychka zvychka;
    string riadok;
    while (getline(infile, riadok)) {
        zvychka.nazva = riadok;
        getline(infile, zvychka.opis);
        getline(infile, zvychka.chastota);
        getline(infile, riadok);
        zvychka.vikonanaSyohodni = (riadok == "1");
        zvychki.resize(zvychki.size() + 1);
        zvychki.back() = zvychka;
    }
    infile.close();
    cout << GREEN << "Дані завантажено з файлу zvychki.txt.\n" << RESET;
}

void pokazatiMenu() {
    setlocale(LC_CTYPE, "ukr");
    setlocale(LC_ALL, "");
    cout << "\n" << MAGENTA << "===== Календар Звичок =====\n" << RESET;
    cout << CYAN << "1. Додати Звичку\n" << RESET;
    cout << CYAN << "2. Позначити Звичку як Виконану\n" << RESET;
    cout << CYAN << "3. Показати Прогрес\n" << RESET;
    cout << CYAN << "4. Зберегти Дані\n" << RESET;
    cout << CYAN << "5. Завантажити Дані\n" << RESET;
    cout << CYAN << "6. Вихід\n" << RESET;
    cout << YELLOW << "Введіть ваш вибір: " << RESET;
}

int main() {
    setlocale(LC_CTYPE, "ukr");
    setlocale(LC_ALL, "");

    vector<Zvychka> zvychki;
    zavantizhitiZvychki(zvychki);
    while (true) {
        pokazatiMenu();
        int vibir;
        cin >> vibir;
        cin.ignore();

        switch (vibir) {
        case 1:
            dodatiZvychku(zvychki);
            break;
        case 2:
            poznachitiZvychkuYakVikonanu(zvychki);
            break;
        case 3:
            pokazatiProgres(zvychki);
            break;
        case 4:
            zberegtiZvychki(zvychki);
            break;
        case 5:
            zavantizhitiZvychki(zvychki);
            break;
        case 6:
            cout << "Вихід...\n";
            return 0;
        default:
            cout << RED << "Неправильний вибір. Спробуйте знову.\n" << RESET;
        }
    }
}
