#include "timecalculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimeCalculator w;
    w.show();

    return a.exec();
}
