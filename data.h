#ifndef DATA_H
#define DATA_H

#include "dateexception.h"
#include <string>
using std::string;

// Un oggetto Data rappresenta solo una data: nessun fuso orario,
// nessun problema di ora legale, ecc

class Data {
private:
    int anno;   // 1753 - 9999
    int mese;   // 1 - 12
    int giorno; // 1 - 31
    void controlla_Data(int giorno, int mese, int anno);
public:
    static int Anno_Min;
    static int Giorni_Del_Mese[];
    static QString Settimana[] ;

    Data();
    Data(int g, int m, int a);
    Data(const Data&) = default; //costruttore di copia
    Data& operator=(const Data&) = default; //assegnazione
    virtual ~Data() = default;  //distruttore polimorfo

    int Giorno() const;
    int Mese() const;
    int Anno() const;

    void setGiorno(int g);
    void setMese(int m);
    void setAnno(int a);
    void setData(int g, int m, int a);

    bool Bisestile(int anno) const;
    bool DataValida() const;
    bool Pasquetta() const;
    bool Festivo() const;

    virtual QString toString() const;  //metodo polimorfo

    bool operator==(const Data&) const;
    bool operator!=(const Data&) const;
    bool operator<(const Data&) const;
    Data operator-(const Data&) const;
    Data operator++(int);   //incremento postfisso
    Data operator--(int);   //decremento postfisso
};

//funzioni esterne alla classe
Data next_date(const Data&);
Data previous_date(const Data&);
int diffGiorni(const Data&, const Data&, string);

#endif // DATA_H

