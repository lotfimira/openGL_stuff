#include "grid_qt_gui_vs2012.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>

Grid_QT_GUI_VS2012::Grid_QT_GUI_VS2012(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QGLFormat gl_format;
    gl_format.setVersion(4,2);
    gl_format.setProfile(QGLFormat::CompatibilityProfile);

    gl_format.setSamples(8);

    _gl_widget = new MyGlWidget(gl_format, this);

    QWidget * c = centralWidget();
    c->layout()->addWidget(_gl_widget);
}

Grid_QT_GUI_VS2012::~Grid_QT_GUI_VS2012()
{
}

