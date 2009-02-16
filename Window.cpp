#include "Window.h"
#include "Capture.h"
#include "Classifier.h"
#include "Recognizer.h"
#include "SimpleHinter.h"
#include "ui_Window.h"

#include <QImage>
#include <QDesktopWidget>

#define DEFAULT_WIDTH 252
#define DEFAULT_HEIGHT 330

Window::Window( QWidget *parent )
    : QWidget( parent )
    , ui( new Ui::WindowForm )
{
    // create ui
    ui->setupUi( this );
    QDesktopWidget dw;
    ui->xOffset->setMaximum( dw.width() );
    ui->yOffset->setMaximum( dw.height() );
    ui->regionWidth->setMaximum( dw.width() );
    ui->regionHeight->setMaximum( dw.height() );
    ui->xOffset->setValue( (dw.width() - DEFAULT_WIDTH) / 2 );
    ui->yOffset->setValue( (dw.height() - DEFAULT_HEIGHT) / 2 );
    ui->regionWidth->setValue( DEFAULT_WIDTH );
    ui->regionHeight->setValue( DEFAULT_HEIGHT );
    connect( ui->xOffset, SIGNAL(valueChanged(int)), this, SLOT(slotCapParamsChanged()) );
    connect( ui->yOffset, SIGNAL(valueChanged(int)), this, SLOT(slotCapParamsChanged()) );
    connect( ui->regionWidth, SIGNAL(valueChanged(int)), this, SLOT(slotCapParamsChanged()) );
    connect( ui->regionHeight, SIGNAL(valueChanged(int)), this, SLOT(slotCapParamsChanged()) );
    connect( ui->frequency, SIGNAL(valueChanged(int)), this, SLOT(slotCapParamsChanged()) );
    connect( ui->hBlocks, SIGNAL(valueChanged(int)), this, SLOT(slotRecParamsChanged()) );
    connect( ui->vBlocks, SIGNAL(valueChanged(int)), this, SLOT(slotRecParamsChanged()) );

    // create and train the classifier
    m_classifier = new Classifier( QSize( 30, 30 ), this );
    for ( int i = 0; i < 7; i++ )
        m_classifier->addClass( i, QImage( QString( ":/data/class%1.png" ).arg( i ), "PNG" ) );

    // create the recognizer
    m_recognizer = new Recognizer( m_classifier, this );
    slotRecParamsChanged();

    // create the hinter
    m_hinter = new SimpleHinter( this );

    // create the capture
    m_capture = new Capture( this );
    connect( m_capture, SIGNAL(gotPixmap(const QPixmap &, const QPoint &)),
             this, SLOT(slotProcessPixmap(const QPixmap &, const QPoint &)) );
    slotCapParamsChanged();
}

Window::~Window()
{
    delete m_hinter;
    delete m_recognizer;
    delete m_capture;
    delete m_classifier;
    delete ui;
}

void Window::slotCapParamsChanged()
{
    QRect captureRect( ui->xOffset->value(), ui->yOffset->value(), ui->regionWidth->value(), ui->regionHeight->value() );
    int adjW = captureRect.width() % 30;
    int adjH = captureRect.height() % 30;
    m_capture->setGeometry( captureRect.adjusted( 0, 0, adjW, adjH ) );
    m_capture->setFrequency( ui->frequency->value() );
}

void Window::slotRecParamsChanged()
{
    m_recognizer->setup( ui->hBlocks->value(), ui->vBlocks->value() );
}

void Window::slotProcessPixmap( const QPixmap & pixmap, const QPoint & cursor )
{
    // show original image
    ui->visualizer->setMinimumSize( pixmap.size() );
    ui->visualizer->setPixmapCursorPos( cursor );
    if ( ui->display1->isChecked() )
        ui->visualizer->setOriginalPixmap( pixmap );

    // process image
    bool displayRec = ui->display2->isChecked();
    RecoResult rr = m_recognizer->recognize( pixmap, displayRec );
    if ( displayRec )
        ui->visualizer->setOriginalPixmap( m_recognizer->output() );

    // show results
    if ( ui->display3->isChecked() ) {
        m_hinter->process( rr, pixmap );
        ui->visualizer->setOriginalPixmap( m_hinter->output() );
    }
}
