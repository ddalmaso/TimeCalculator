#include "datasett.h"

DataSett::DataSett() {
    int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    int year = Anno(); year -= Mese() < 3;
    giorno_settimana = settimana(((year + year/4 - year/100 + year/400 + t[Mese()-1] + Giorno()) % 7));
}

//Ritorna il giorno della settimana come numero intero
settimana DataSett::GiornoSettimana() const { return giorno_settimana; }

//Restituisce una stringa contenente il giorno della settimana
QString DataSett::toString() const {
    int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    int year = Anno(); year -= Mese() < 3;
    return Settimana[((year + year/4 - year/100 + year/400 + t[Mese()-1] + Giorno()) % 7)];
}

