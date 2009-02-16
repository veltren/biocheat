#include "Window.h"
#include "Capture.h"
#include "Classifier.h"
#include "ui_Window.h"

#include <QImage>
#include <QMouseEvent>
#include <QDesktopWidget>

#define DEFAULT_WIDTH 260
#define DEFAULT_HEIGHT 330

Window::Window( QWidget *parent )
    : QWidget( parent )
    , ui( new Ui::WindowForm )
{
    // create ui
    ui->setupUi( this );
    ui->originalImage->installEventFilter( this );
    QDesktopWidget dw;
    ui->xOffset->setMaximum( dw.width() );
    ui->xOffset->setValue( (dw.width() - DEFAULT_WIDTH) / 2 );
    ui->yOffset->setMaximum( dw.height() );
    ui->yOffset->setValue( (dw.height() - DEFAULT_HEIGHT) / 2 );
    ui->regionWidth->setMaximum( dw.width() );
    ui->regionWidth->setValue( DEFAULT_WIDTH );
    ui->regionHeight->setMaximum( dw.height() );
    ui->regionHeight->setValue( DEFAULT_HEIGHT );
    connect( ui->xOffset, SIGNAL(valueChanged(int)), this, SLOT(slotCapParamsChanged()) );
    connect( ui->yOffset, SIGNAL(valueChanged(int)), this, SLOT(slotCapParamsChanged()) );
    connect( ui->regionWidth, SIGNAL(valueChanged(int)), this, SLOT(slotCapParamsChanged()) );
    connect( ui->regionHeight, SIGNAL(valueChanged(int)), this, SLOT(slotCapParamsChanged()) );
    connect( ui->frequency, SIGNAL(valueChanged(int)), this, SLOT(slotCapParamsChanged()) );

    // create and train the classifier
    m_classifier = new Classifier( QSize( 30, 30 ), this );
    for ( int i = 0; i < 7; i++ )
        m_classifier->addClass( i, QImage( QString( ":/data/class%1.png" ).arg( i ), "PNG" ) );

    // create the capture
    m_capture = new Capture( this );
    connect( m_capture, SIGNAL(gotPixmap(const QPixmap &)),
             this, SLOT(slotProcessPixmap(const QPixmap &)) );
    slotCapParamsChanged();
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

void Window::slotCapParamsChanged()
{
    QRect captureRect( ui->xOffset->value(), ui->yOffset->value(), ui->regionWidth->value(), ui->regionHeight->value() );
    int adjW = captureRect.width() % 30;
    int adjH = captureRect.height() % 30;
    m_capture->setGeometry( captureRect.adjusted( 0, 0, adjW, adjH ) );
    m_capture->setFrequency( ui->frequency->value() );
}

void Window::slotProcessPixmap( const QPixmap & pixmap )
{
    // show original image
    ui->originalImage->setPixmap( pixmap );
    ui->originalImage->setFixedSize( pixmap.size() );

    // process image

    // show results
}
