#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui/QWidget>

namespace Ui
{
    class WidgetClass;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::WidgetClass *ui;
};

#endif // WINDOW_H
