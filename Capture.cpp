#include "Capture.h"
#include <QCoreApplication>
#include <QDirIterator>
#include <QImage>
#include <QTimerEvent>

Capture::Capture( QObject * parent )
    : QObject( parent )
    , m_currentIndex( 0 )
{
    // load PNGs
    QString testDir = QCoreApplication::applicationDirPath() + QDir::separator() + "tests";
    QDirIterator it( testDir, QStringList() << "*.png", QDir::Files | QDir::NoDotAndDotDot );
    while ( it.hasNext() )
        m_images.append( QImage( it.next(), "PNG" ) );
    Q_ASSERT( m_images.size() );

    // start timer TEMP
    m_timer.start( 2000, this );
}

void Capture::timerEvent( QTimerEvent * event )
{
    if ( event->timerId() != m_timer.timerId() )
        return QObject::timerEvent( event );

    emit gotImage( m_images[ m_currentIndex ] );

    // TEMP
    m_timer.stop();

    // rotate index
    if ( ++m_currentIndex >= m_images.size() )
        m_currentIndex = 0;
}

