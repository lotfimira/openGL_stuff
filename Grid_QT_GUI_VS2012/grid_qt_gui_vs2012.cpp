#include "grid_qt_gui_vs2012.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>

Grid_QT_GUI_VS2012::Grid_QT_GUI_VS2012(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QWidget * c = centralWidget();
    _gl_widget = new MyGlWidget(this);
    c->layout()->addWidget(_gl_widget);

    prepareScene();
}

Grid_QT_GUI_VS2012::~Grid_QT_GUI_VS2012()
{
    cleanupScene();
}

void Grid_QT_GUI_VS2012::prepareScene()
{
    _gl_widget->makeCurrent();

    GroundPlaneAnisotropic * groundPlaneAnisotropic = new GroundPlaneAnisotropic();
    MeshList::instance()->addMesh(groundPlaneAnisotropic);
}

void Grid_QT_GUI_VS2012::cleanupScene()
{

}

