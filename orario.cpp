#include "orario.h"
#include <stdexcept>

using namespace std;

Orario::Orario() {
    ore = 0;
    minuti = 0;
    secondi = 0;
}

Orario::Orario(int h, int m, int s) {
    setOre(h);
    setMinuti(m);
    setSecondi(s);
}

int Orario::Ore() const { return ore; }

void Orario::setOre(int h) {
    if(h >= 0 && h <=23) { ore = h; }
    else {
        throw TimeException("Ore non valide", "Le ore deve essere comprese tra 0 e 23.");
    }
}

int Orario::Minuti() const { return minuti; }

void Orario::setMinuti(int m) {
    if(m >= 0 && m <= 59) { minuti = m; }
    else {
        throw TimeException("Minuti non validi", "I minuti devono essere compresi tra 0 e 59.");
    }
}

int Orario::Secondi() const { return secondi; }

void Orario::setSecondi(int s) {
    if(s >= 0 && s <= 59) { secondi = s; }
    else {
        throw TimeException("Secondi non validi", "I secondi devono essere compresi tra 0 e 59.");
    }
}

void Orario::setOrario(int h, int m, int s) {
    setOre(h);
    setMinuti(m);
    setSecondi(s);
}

//Overloading dell'operator di uguaglianza
bool Orario::operator ==(const Orario& o) {
    return Ore() == o.Ore() && Minuti() == o.Minuti() && Secondi() == o.Secondi();
}

//Overloading dell'operatore di disuguaglianza
bool Orario::operator !=(const Orario& o) {
    return !(*this == o);
}

//Overloading dell'operatore minore
bool Orario::operator <(const Orario& o) const {
    if(Ore() < o.Ore())
        return true;
    else {
        if(Ore() == o.Ore()) {
            if(Minuti() < o.Minuti())
                return true;
            else {
                if(Minuti() == o.Minuti()) {
                    if(Secondi() <= o.Secondi())
                        return true;
                }
            }
        }
    }
    return false;
}

//Overloading dell'operatore di sottrazione
Orario Orario::operator -(const Orario& o) {
    if(*(this) == o) return Orario();

    Orario fine = *this, inizio = o;
    Orario ris;

    if(fine.Secondi() < inizio.Secondi()) {
        fine.secondi += 60;
        if(!fine.Minuti()) fine.minuti = 59;
        else
            fine.minuti -= 1;
    }
    ris.setSecondi(fine.Secondi() - inizio.Secondi());

    if(fine.Minuti() < inizio.Minuti()) {
        fine.minuti += 60;
        if(!fine.Ore()) fine.ore = 23;
        else
            fine.ore -= 1;
    }
    ris.setMinuti(fine.Minuti() - inizio.Minuti());

    if(fine.Ore() < inizio.Ore())
        fine.ore += 24;
    else
        ris.setOre(fine.Ore() - inizio.Ore());

    return ris;
}

//overloading dell'operatore di somma
Orario Orario::operator +(const Orario& o) const {
    int h=0, m=0, s=0;
    s = Secondi() + o.Secondi();
    if (s > 59)
    { s -= 60; m++; }

    m += Minuti() + o.Minuti();
    if(m > 59) {
        m -= 60; h++;
    }

    h += Ore() + o.Ore();
    if(h > 23) { h -= 24; }

    return Orario(h, m, s);
}


inline int Cifre(int n) {
    int count = 0;
    while (n){
        n /= 10;
        count++;
    }
    return count;
}


//Restituisce la Stringa nella forma hhmmss
QString Orario::toString() const {
    QString res = "";
    if(Cifre(ore) <= 1)
        res = "0" + QString::number(ore);
    else
        res = QString::number(ore);
    if(Cifre(minuti) <= 1)
        res += "0" + QString::number(minuti);
    else
        res += QString::number(minuti);
    if(Cifre(secondi) <= 1)
        res += "0" + QString::number(secondi);
    else
        res += QString::number(secondi);
    return res;
}
