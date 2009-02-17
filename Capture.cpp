/***************************************************************************
 * Copyright (c) 2009 Enrico Ros                                           *
 *         2009 Enrico Ros <enrico.ros@gmail.com>                          *
 *                                                                         *
 * Permission is hereby granted, free of charge, to any person             *
 * obtaining a copy of this software and associated documentation          *
 * files (the "Software"), to deal in the Software without                 *
 * restriction, including without limitation the rights to use,            *
 * copy, modify, merge, publish, distribute, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the               *
 * Software is furnished to do so, subject to the following                *
 * conditions:                                                             *
 *                                                                         *
 * The above copyright notice and this permission notice shall be          *
 * included in all copies or substantial portions of the Software.         *
 *                                                                         *
 ***************************************************************************/

#include "Capture.h"
#include <QCoreApplication>
#include <QDirIterator>
#include <QImage>
#include <QTimerEvent>
#ifdef Q_WS_X11
#include <QX11Info>
#else
#include <QApplication>
#endif
#include <QDesktopWidget>
#include <QPixmap>

Capture::Capture( QObject * parent )
    : QObject( parent )
    , m_fps( 0 )
#if 0
    , m_currentIndex( 0 )
#endif
{
#if 0
    // TEMP load PNGs
    QString testDir = QCoreApplication::applicationDirPath() + QDir::separator() + "tests";
    QDirIterator it( testDir, QStringList() << "*.png", QDir::Files | QDir::NoDotAndDotDot );
    while ( it.hasNext() )
        m_images.append( QImage( it.next(), "PNG" ) );
    Q_ASSERT( m_images.size() );
#endif
}

void Capture::setGeometry( const QRect & geometry )
{
    m_geometry = geometry;
}

QRect Capture::geometry() const
{
    return m_geometry;
}

void Capture::setFrequency( int fps )
{
    m_fps = fps;
    m_timer.start( 1000 / m_fps, this );
}

int Capture::frequency() const
{
    return m_fps;
}

void Capture::timerEvent( QTimerEvent * event )
{
    if ( event->timerId() != m_timer.timerId() || m_geometry.isNull() )
        return QObject::timerEvent( event );

    QPixmap grabbedPixmap = QPixmap::grabWindow(
#ifdef Q_WS_X11
            QX11Info::appRootWindow(),
#else
            QApplication::desktop()->winId(),
#endif
            m_geometry.left(), m_geometry.top(), m_geometry.width(), m_geometry.height() );


    emit gotPixmap( grabbedPixmap, QCursor::pos() - QPoint( m_geometry.topLeft() ) );

#if 0
    emit gotImage( m_images[ 4-m_currentIndex ] );

    // TEMP
    m_timer.stop();

    // rotate index
    if ( ++m_currentIndex >= m_images.size() )
        m_currentIndex = 0;
#endif
}
