#include "Window.h"
#include "ui_Window.h"
#include <QMouseEvent>

Window::Window( QWidget *parent )
    : QWidget( parent )
    , ui( new Ui::WindowForm )
{
    ui->setupUi( this );
    ui->originalImage->installEventFilter( this );

    m_capture = new Capture( this );
    connect( m_capture, SIGNAL(gotImage(const QImage &)),
             this, SLOT(slotProcessImage(const QImage &)) );
}

Window::~Window()
{
    delete ui;
}

bool Window::eventFilter( QObject * object, QEvent * event )
{
    // intercept clicks on the Original image label
    if ( object == ui->originalImage && event->type() == QEvent::MouseButtonPress ) {
        QMouseEvent * me = static_cast<QMouseEvent *>( event );
        qWarning( "%d %d", me->pos().x(), me->pos().y() );
    }

    return false;
}

void Window::slotProcessImage( const QImage & image )
{
    // show original image
    ui->originalImage->setPixmap( QPixmap::fromImage( image ) );
    ui->originalImage->setFixedSize( image.size() );

    // process image

    // show results
}
