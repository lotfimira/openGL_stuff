#pragma once

#include <QObject>
#include <QPoint>
#include <QMouseEvent>

class Input : public QObject
{
Q_OBJECT

private:
    QPoint last_cursor_pos;

signals:
    void leftDrag(int h_drag, int v_drag);
    void midDrag(int h_drag, int v_drag);
    void wheel(int delta);

public:
    Input();
    virtual ~Input();

public slots:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseWheelEvent(QWheelEvent * event);
};