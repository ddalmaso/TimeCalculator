#include "data.h"
#include "datasett.h"
#include <string>
#include <stdexcept>
#include <QDate>
#include <QMessageBox>

using namespace std;

int Data::Giorni_Del_Mese[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

QString Data::Settimana[] = {"Domenica", "Lunedi", "Martedi", "Mercoledi",
                                             "Giovedi", "Venerdi", "Sabato"};
int Data::Anno_Min = 1900;

//Restituisce true se l'anno è Bisestile, false altrimenti
bool Data::Bisestile(int anno) const {
    return ((anno % 4 == 0 && anno % 100 != 0) || (anno % 400 == 0));
}

//Restituisce true se la data corrisponde al Lunedì dell'Angelo, false altrimenti
bool Data::Pasquetta() const {
    int giorno, mese;
    int a, b, c, d, e, m, n;
    Data r;

    switch(this->anno/100)
    {
        case 15:	// 1583 - 1599 (FALL THROUGH)
        case 16:	// 1600 - 1699
            m=22; n=2; 	break;

        case 17:	// 1700 - 1799
            m=23; n=3; break;

        case 18:	// 1800 - 1899
            m=23; n=4; break;

        case 19:	// 1900 - 1999 (FALL THROUGH)
        case 20:	// 2000 - 2099
            m=24; n=5;break;

        case 21:	// 2100 - 2199
            m=24; n=6; break;

        case 22:	// 2200 - 2299
            m=25; n=0; break;

        case 23:	// 2300 - 2399
            m=26; n=1; break;

        case 24:	// 2400 - 2499
            m=25; n=1; break;
    }

    a=this->anno%19;
    b=this->anno%4;
    c=this->anno%7;
    d=(19*a+m)%30;
    e=(2*b+4*c+6*d+n)%7;
    giorno=d+e;

    if (d+e<10)
    {
        giorno+=22;
        mese=3;
    }

    else
    {
        giorno-=9;
        mese=4;

        if ((giorno==26)||((giorno==25)&&(d==28)&&(e==6)&&(a>10)))
        {
            giorno-=7;
        }
    }

    r.giorno=giorno;
    r.mese=mese;
    r.anno=this->anno;
    r++;

    return *(this) == r;
}

//Restituisce true se la data corrisponde a una festività, false altrimenti.
//Non considera le domeniche come giorni festivi
bool Data::Festivo() const {
    if(Pasquetta() ||   //Pasquetta
            ((giorno == 1) && (mese == 1)) || //Capodanno
            ((giorno == 6) && (mese == 1)) || //Epifania
            ((giorno == 25) && (mese == 4)) ||    //festa della Liberazione
            ((giorno == 1) && (mese == 5)) || //festa dei lavoratori
            ((giorno == 2) && (mese == 6)) || //festa della Repubblica
            ((giorno == 15) && (mese == 8)) ||    //Ferragosto
            ((giorno == 1) && (mese == 11)) ||    //giorni di Tutti i Santi
            ((giorno == 8) && (mese == 12)) ||   //festa dell'Immacolata Concezione
            ((giorno == 25) && (mese == 12)) ||   //giorno di Natale
            ((giorno == 26) && (mese == 12))) {  //giorno di Santo Stefano
        return true;
    }
    return false;
}

/*Metodo privato di test date
 *
 * Controlla la veridicità di una data rispetto a:
 * - giorno in [1,32]
 * - mese in [1,12]
 * - anno >= 1900
 * - mese in {4,6,9,11} -> giorno <= 30
 * - mese = 2 && Bisestile(anno) -> giorno <= 29
 * - mese = 2 && !Bisestile(anno) -> giorno <= 28
 *
 * altrimenti verrà lanciata un'eccezione
 */
void Data::controlla_Data(int giorno, int mese, int anno) {
    if(giorno < 1)
        throw DateException("Errore nei giorni", "Il giorno non può essere < 1.");
    else if (giorno > 31) throw DateException("Errore nei giorni", "Il giorno non può essere > 31.");

    if(mese < 1)
        throw DateException("Errore nei mesi", "Il mese non può essere < 1.");
    else if(mese > 12)
        throw DateException("Errore nei mesi", "Il mese non può essere > 12.");

    if(anno < 1900)
        throw DateException("Errore negli anni", "L'anno non può essere < 1900.");

    if((mese == 4 || mese == 6 || mese == 9 || mese == 11) && giorno > 30)
        throw DateException("Errore <giorno/mese>",
                            "La coppia <"+QString::number(giorno)+"/"+QString::number(mese)+"> non è valida. Il giorno deve essere in [1,30].");
    else if(giorno == 2 && Bisestile(anno) && giorno > 29)
        throw DateException("Errore <giorno/mese>",
                            "La coppia <"+QString::number(giorno)+"/"+QString::number(mese)+"> (bisestile) non è valida. Il giorno deve essere in [1,29].");
    else if(mese == 2 && !Bisestile(anno) && giorno > 28)
        throw DateException("Errore <giorno/mese>",
                            "La coppia <"+QString::number(giorno)+"/"+QString::number(mese)+"> (non bisestile) non è valida. Il giorno deve essere in [1,28].");
}

//Controlla la validità della data
bool Data::DataValida() const {
    if(anno >= Anno_Min && mese >= 1 && mese <= 12) {
        int ultimoGiornoDelMese = Giorni_Del_Mese[mese-1];
        if(mese == 2 && Bisestile(anno)) {
            ultimoGiornoDelMese = 29;
        }
        return (giorno >= 1 && giorno <= ultimoGiornoDelMese);
    } else {
        return false;
    }
}

//Imposta la data corrente di defaut
Data::Data() {
    anno = QDate::currentDate().year();
    mese = QDate::currentDate().month();
    giorno = QDate::currentDate().day();
}

Data::Data(int g, int m, int a) {
    controlla_Data(g, m, a);
    anno = a;
    mese = m;
    giorno = g;
}

int Data::Anno() const { return anno; }

int Data::Mese() const { return mese; }

int Data::Giorno() const { return giorno; }

void Data::setGiorno(int g) { giorno = g; }

void Data::setMese(int m) { mese = m; }

void Data::setAnno(int a) { anno = a; }

void Data::setData(int g, int m, int a) {
    giorno = g;
    mese = m;
    anno = a;
}

//Overloading dell'operatore di uguaglianza
bool Data::operator ==(const Data& d2) const {
    if (!this->DataValida()) { return false; };
    if (!d2.DataValida()) { return false; };
    return ((this->Anno() == d2.Anno())
            && (this->Mese() == d2.Mese())
            && (this->Giorno() == d2.Giorno()));
}

//Overloading dell'operatore di disuguaglianza
bool Data::operator !=(const Data& d2) const {
    return !(*this == d2);
}

//Overloading dell'operatore minore
bool Data::operator <(const Data& d2) const {
    if (!this->DataValida()) { return false; };
    if (!d2.DataValida()) { return false; };

    if(anno < d2.anno) return true;
    if(anno == d2.anno)
    {
        if(mese < d2.mese) return true;
        if(mese == d2.mese){
            if(giorno < d2.giorno) return true;
        }
    }
    return false;
}

//Overloading dell'operatore di sottrazione
Data Data::operator -(const Data& d) const {
    Data ris;
    static int increment[12] = { 1, -2, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

    int daysInc = 0;

    if (Giorno() - d.Giorno() < 0)
    {
        int month = Mese() - 2; // -1 da zero, -1 mese precedente
        if (month < 0)
            month = 11; // Il precedente mese è Dicembre
        daysInc = increment[month];
        if ((month == 1) && (Anno() % 4 == 0))
            daysInc++; // Incremento i giorni per l'anno bisestile
    }

    int total1 = d.Anno()*360 + d.Mese()*30 + d.Giorno();
    int total2 = Anno()*360 + Mese()*30 + Giorno();
    int diff = total2 - total1;
    int years = diff/360;
    int months = (diff - years*360)/30;
    int days = diff - years*360 - months*30 + daysInc;

    // Calcoli extra
    if (d.Giorno() == 1 && Giorno() == 31) {
        months--;
        days = 30;
    }

    ris.setData(days, months, years);
    return ris;
}

//Metodo che restituisce la data successiva alla data d
Data next_Date(const Data& d){
    Data ndata;
    if (!d.DataValida()) { return ndata; }

    ndata.setData(d.Giorno()+1, d.Mese(), d.Anno());
    if (ndata.DataValida()) return ndata;

    ndata.setData(1, d.Mese()+1, d.Anno());
    if (ndata.DataValida()) return ndata;

    ndata.setData(1, 1, d.Anno()+1);
    return ndata;
}

//Metodo che restituisce la data precedente alla data d
Data previous_Date(const Data& d) {
    Data ndata;
    if (!d.DataValida()) { return ndata; } //ritorno data corrente

    ndata.setData(d.Giorno()-1, d.Mese(), d.Anno());
    if (ndata.DataValida()) return ndata;

    ndata.setData(31, d.Mese()-1, d.Anno());
    if (ndata.DataValida()) return ndata;

    ndata.setData(30, d.Mese()-1, d.Anno());
    if (ndata.DataValida()) return ndata;

    ndata.setData(29, d.Mese()-1, d.Anno());
    if (ndata.DataValida()) return ndata;

    ndata.setData(28, d.Mese()-1, d.Anno());
    if (ndata.DataValida()) return ndata;

    ndata.setData(31, 12, d.Anno()-1);
    return ndata;
}

//Operatore postfisso di decremento
Data Data::operator --(int) {
    Data d = *this;
    *this = previous_Date(*this);
    return d;
}

//Operatore postfisso di incremento
Data Data::operator ++(int) {
    Data d = *this;
    *this = next_Date(d);
    return d;
}

inline int Cifre(int n) {
    int count = 0;
    while (n){
        n /= 10;
        count++;
    }
    return count;
}

//Restituisce la Stringa nella forma ggmmaaaa
QString Data::toString() const {
    QString res = "";
    if(Cifre(giorno) <= 1)
        res = "0" + QString::number(giorno);
    else
        res = QString::number(giorno);
    if(Cifre(mese) <= 1)
        res += "0" + QString::number(mese);
    else
        res += QString::number(mese);
    res += QString::number(anno);
    return res;
}

int diffGiorni(const Data& d1, const Data& d2, string tipo) {
    //cella[0] -> giorni; cella[1] -> lavorativi; cella[2] -> festivi
    //cella[3] -> sabati; cella[4] -> domeniche
    int days[5] = {};

    Data* dt1 = const_cast<Data*>(&d1);
    dt1 = new DataSett();

    while(*dt1 != d2) {
        if(!dt1->Festivo())
            days[1]++;
        else
            days[2]++;

        if(dt1->toString() == "Sabato") days[3]++;
        if(dt1->toString() == "Domenica") days[4]++;

        (*dt1)++;
        days[0]++;
    }

    if(tipo == "l") return days[1]-days[4]; //ritorno i lavorativi (togliendo le domeniche)
    if(tipo == "f") return days[2]; //ritorno i festivi
    if(tipo == "s") return days[3]; //ritorno i sabati
    if(tipo == "d") return days[4]; //ritorno le domeniche
    return days[0]; //ritorno i giorni totali
}

