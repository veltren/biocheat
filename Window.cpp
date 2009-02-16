#include "Window.h"
#include "ui_Window.h"

Window::Window( QWidget *parent )
    : QWidget( parent )
    , ui( new Ui::WindowForm )
{
    ui->setupUi( this );
}

Window::~Window()
{
    delete ui;
}
