#include "dataora.h"

DataOra::DataOra(int o, int m, int s, int gg, int mm, int aa): Data(gg, mm, aa) {
    setOre(o);
    setMinuti(m);
    setSecondi(s);
}

DataOra::DataOra(int o, int m, int s): Data() {
    setOre(o);
    setMinuti(m);
    setSecondi(s);
}

DataOra::DataOra(): Data() {
    ore = 0;
    minuti = 0;
    secondi = 0;
}

//Overloading dell'operatore di uguaglianza
bool DataOra::operator ==(const DataOra& dataora) const {
    return ((Data)*this == (Data)dataora) &&
            Ore() == dataora.Ore() && Minuti() == dataora.Minuti() && Secondi() == dataora.Secondi();
}

//Calcola le ore trascorse tra due date
int oreTotali(const DataOra& do1, const DataOra& do2) {
    DataOra mezzanotte;
    Data succ = do1; succ++;

    //ore trascorse tra l'orario del giorno di partenza e le 00.00 del giorno seguente
    int ore_trascorse = (mezzanotte - do1).Ore();
    return ore_trascorse + (diffGiorni(succ, do2, "g") * 24) + do2.Ore();
}

int DataOra::Ore() const { return ore; }

void DataOra::setOre(int h) {
    if(h >= 0 && h <=23) { ore = h; }
    else {
        throw TimeException("Ore non valide", "Le ore deve essere comprese tra 0 e 23.");
    }
}

int DataOra::Minuti() const { return minuti; }

void DataOra::setMinuti(int m) {
    if(m >= 0 && m <= 59) { minuti = m; }
    else {
        throw TimeException("Minuti non validi", "I minuti devono essere compresi tra 0 e 59.");
    }
}

int DataOra::Secondi() const { return secondi; }

void DataOra::setSecondi(int s) {
    if(s >= 0 && s <= 59) { secondi = s; }
    else {
        throw TimeException("Secondi non validi", "I secondi devono essere compresi tra 0 e 59.");
    }
}

void DataOra::setOrario(int h, int m, int s) {
    setOre(h);
    setMinuti(m);
    setSecondi(s);
}

//Overloading dell'operatore di disuguaglianza
bool DataOra::operator !=(const DataOra& o) const{
    return !(*this == o);
}

//Overloading dell'operatore minore
bool DataOra::operator <(const DataOra& o) const {
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
DataOra DataOra::operator -(const DataOra& o) {
    int h, m, s;
    int sum1, sum2, sum;
    sum1 = (ore)*3600 + (minuti)*60 + secondi;
    sum2 = (o.Ore())*3600 + (o.Minuti())*60 + o.Secondi();
    if (sum1 > sum2)
        sum = sum1 - sum2;
    else
        sum = sum2 - sum1;
    s = sum % 60;
    sum = sum / 60;
    m = sum % 60;
    h = sum / 60;
    return DataOra(h, m, s);
}

//overloading dell'operatore di somma
DataOra DataOra::operator +(const DataOra& o) const {
    int h, m, s;
    int sum;
    sum = (ore + o.Ore())*3600 + (minuti + o.Minuti())*60 + secondi + o.Secondi();
    s = sum % 60;
    sum = sum / 60;
    m = sum % 60;
    h = sum / 60;
    return DataOra(h, m, s);
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
QString DataOra::toString() const {
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
