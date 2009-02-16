#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui/QWidget>

namespace Ui
{
    class WindowForm;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
    Ui::WindowForm *ui;
};

#endif // WINDOW_H
