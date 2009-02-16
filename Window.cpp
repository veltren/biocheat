#include "Window.h"
#include "ui_Window.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::WidgetClass)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
