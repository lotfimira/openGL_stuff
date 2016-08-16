#include "Input.h"
//#include "Input.moc"


Input::Input()
{

}

Input::~Input()
{

}

void Input::mousePressEvent(QMouseEvent * event)
{
    last_cursor_pos = event->pos();
}

void Input::mouseReleaseEvent(QMouseEvent * event)
{
    last_cursor_pos = event->pos();
}

void Input::mouseMoveEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPoint pos = event->pos();
        int h_drag = pos.x() - last_cursor_pos.x();
        int v_drag = pos.y() - last_cursor_pos.y();

        emit drag(h_drag, v_drag);
    }

    last_cursor_pos = event->pos();
}