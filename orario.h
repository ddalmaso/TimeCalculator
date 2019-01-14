#ifndef ORARIO_H
#define ORARIO_H

#include <QString>
#include "timeexception.h"

// Un oggetto Orario rappresenta un preciso orario del giorno.

class Orario {
private:
    int ore;       // 0 - 23
    int minuti;    // 0 - 59
    int secondi;   // 0 - 59
public:
    Orario();
    Orario(int o, int m, int s);
    Orario(const Orario&) = default; //costruttore di copia
    Orario& operator=(const Orario&) = default; //assegnazione
    ~Orario() = default;  //distruttore
    int Ore() const;
    int Minuti() const;
    int Secondi() const;
    void setOre(int h);
    void setMinuti(int m);
    void setSecondi(int s);
    void setOrario(int h, int m, int s);
    QString toString() const;
    bool operator==(const Orario&);
    bool operator!=(const Orario&);
    bool operator<(const Orario&) const;
    Orario operator-(const Orario&);
    Orario operator+(const Orario&) const;
};

#endif // ORARIO_H
