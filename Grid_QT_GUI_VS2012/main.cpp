#include "grid_qt_gui_vs2012.h"
#include <QtWidgets/QApplication>
#include <ctime>

int main(int argc, char *argv[])
{
    // init random number generator
    srand (static_cast <unsigned> (time(0)));

    QApplication a(argc, argv);
    Grid_QT_GUI_VS2012 w;
    w.show();
    return a.exec();
}
