#include "grid_qt_gui_vs2012.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>
#include "MyGlWidget.h"

Grid_QT_GUI_VS2012::Grid_QT_GUI_VS2012(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QWidget * c = centralWidget();
    c->layout()->addWidget(new MyGlWidget());
}

Grid_QT_GUI_VS2012::~Grid_QT_GUI_VS2012()
{

}
