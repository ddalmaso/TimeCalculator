#ifndef DATASETT_H
#define DATASETT_H

#include "data.h"

enum settimana {dom, lun, mar, mer, giov, ven, sab};

//DataSett è un tipo che oltre alle proprietà di Data memorizza anche il giorno della settimana

class DataSett: public Data {
private:
    settimana giorno_settimana;
public:
    DataSett();
    settimana GiornoSettimana() const;
    QString toString() const;   //override
};

#endif // DATASETT_H
