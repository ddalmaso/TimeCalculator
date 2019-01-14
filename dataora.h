#ifndef DATAORA_H
#define DATAORA_H

#include "data.h"
#include "timeexception.h"

// Un oggetto DataOra è un tipo che oltre alle proprietà di Data memorizza anche l'Orario.

class DataOra: public Data {
private:
    int ore;       // 0 - 23
    int minuti;    // 0 - 59
    int secondi;   // 0 - 59
public:
    DataOra();
    DataOra(int o, int m, int s);
    DataOra(int o, int m, int s, int gg, int mm, int aa);
    DataOra(const DataOra&) = default; //costruttore di copia
    DataOra& operator=(const DataOra&) = default; //assegnazione
    int Ore() const;
    int Minuti() const;
    int Secondi() const;
    void setOre(int h);
    void setMinuti(int m);
    void setSecondi(int s);
    void setOrario(int h, int m, int s);
    QString toString() const;   //override
    bool operator==(const DataOra&) const;
    bool operator!=(const DataOra&) const;
    bool operator<(const DataOra&) const;
    DataOra operator-(const DataOra&);
    DataOra operator+(const DataOra&) const;
};

int oreTotali(const DataOra&, const DataOra&);

#endif // DATAORA_H
