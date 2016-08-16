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
    void drag(int h_drag, int v_drag);

public:
    Input();
    virtual ~Input();

public slots:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
};