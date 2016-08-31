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
    QPoint pos = event->pos();
    int h_drag = pos.x() - last_cursor_pos.x();
    int v_drag = pos.y() - last_cursor_pos.y();

    Qt::MouseButtons btns = event->buttons();

    if(btns & Qt::LeftButton)
        emit leftDrag(h_drag, v_drag);

    if(btns & Qt::MiddleButton)
        emit midDrag(h_drag, v_drag);

    last_cursor_pos = event->pos();
}

void Input::mouseWheelEvent(QWheelEvent * event)
{
    int delta = event->delta();
    emit wheel(delta);
}