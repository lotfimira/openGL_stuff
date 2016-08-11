#include "grid_qt_gui_vs2012.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Grid_QT_GUI_VS2012 w;
    w.show();
    return a.exec();
}
