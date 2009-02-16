#include "Window.h"
#include "Capture.h"
#include "Classifier.h"
#include "ui_Window.h"

#include <QMouseEvent>

Window::Window( QWidget *parent )
    : QWidget( parent )
    , ui( new Ui::WindowForm )
{
    ui->setupUi( this );
    ui->originalImage->installEventFilter( this );

    // create the capture
    m_capture = new Capture( this );
    connect( m_capture, SIGNAL(gotImage(const QImage &)),
             this, SLOT(slotProcessImage(const QImage &)) );

    // create and train the classifier
    m_classifier = new Classifier( QSize( 30, 30 ), this );
    for ( int i = 0; i < 7; i++ )
        m_classifier->addClass( i, QImage( QString( ":/data/class%1.png" ).arg( i ), "PNG" ) );
}

Window::~Window()
{
    delete m_capture;
    delete m_classifier;
    delete ui;
}

bool Window::eventFilter( QObject * object, QEvent * event )
{
    // intercept clicks on the Original image label
    if ( object == ui->originalImage && event->type() == QEvent::MouseButtonPress ) {
        QMouseEvent * me = static_cast<QMouseEvent *>( event );

        QPixmap p = ui->originalImage->pixmap()->copy( me->pos().x() - 15, me->pos().y() - 15, 30, 30 );
        m_classifier->classify( p.toImage() );

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
