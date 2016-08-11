#ifndef GRID_QT_GUI_VS2012_H
#define GRID_QT_GUI_VS2012_H

#include <QtWidgets/QMainWindow>
#include "ui_grid_qt_gui_vs2012.h"

class Grid_QT_GUI_VS2012 : public QMainWindow
{
    Q_OBJECT

public:
    Grid_QT_GUI_VS2012(QWidget *parent = 0);
    ~Grid_QT_GUI_VS2012();

private:
    Ui::Grid_QT_GUI_VS2012Class ui;
};

#endif // GRID_QT_GUI_VS2012_H
