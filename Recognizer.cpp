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

#include "Recognizer.h"
#include <QImage>
#include <QPixmap>
#include <QPainter>

Recognizer::Recognizer( Classifier * classifier, QObject * parent )
    : QObject( parent )
    , m_classifier( classifier )
    , m_hBlocks( 0 )
    , m_vBlocks( 0 )
{
}

void Recognizer::setup( int hBlocks, int vBlocks )
{
    m_hBlocks = hBlocks;
    m_vBlocks = vBlocks;
}

RecoResult Recognizer::recognize( const QPixmap & pixmap, float sensitivity, bool verbose )
{
    RecoResult rr;
    rr.rows = m_vBlocks;
    rr.columns = m_hBlocks;
    rr.total = rr.rows * rr.columns;
    rr.valid = 0;
    rr.invalid = rr.total;
    rr.values.resize( rr.total );

    // geometry consts
    const int pw = pixmap.width();
    const int ph = pixmap.height();
    const int cbw = m_classifier->tileSize().width();
    const int cbh = m_classifier->tileSize().height();
    const int bw = pw / m_hBlocks;
    const int bh = ph / m_vBlocks;
    if ( m_hBlocks < 1 || m_vBlocks < 1 || bw < cbw || bh < cbh ) {
        qWarning( "Recognizer::recognize: geometry contraints unsatisfied (%d %d, %d %d)", bw, cbw, bh, cbh );
        return rr;
    }

    // paint results on a new image
    if ( m_outPix.size() != pixmap.size() )
        m_outPix = QPixmap( pixmap.size() );
    if ( verbose )
        m_outPix.fill( Qt::transparent );
    QPainter pp( &m_outPix );

    // recognize loop
    QImage image = pixmap.toImage();
    int rridx = 0;
    for ( int y = 0; y < m_vBlocks; y++ ) {
        float yc = ((float)y + 0.5) * (float)ph / (float)m_vBlocks;
        for ( int x = 0; x < m_hBlocks; x++ ) {
            float xc = ((float)x + 0.5) * (float)pw / (float)m_hBlocks;
            QRect rect( (int)xc - cbw/2, (int)yc - cbh/2, cbw, cbh );
            ClassifyResult cr = m_classifier->classify( image.copy( rect ) );
            if ( cr.confidence < sensitivity )
                cr.index = -1;
            rr.values[ rridx++ ] = cr.index;
            if ( cr.confidence < sensitivity )
                continue;

            rr.valid++;
            rr.invalid--;

            if ( verbose ) {
                pp.setPen( Qt::red );
                pp.drawRect( rect );
                pp.setPen( Qt::white );
                pp.drawText( rect, Qt::AlignCenter, QString::number( cr.index ) );
                rect.setTop( rect.bottom() - 3 );
                rect.setWidth( (int)((float)rect.width() * cr.confidence ) );
                pp.setBrush( Qt::blue );
                pp.drawRect( rect );
                pp.setBrush( Qt::NoBrush );
            }
        }
    }

    // return the result
    return rr;
}

QPixmap Recognizer::output() const
{
    return m_outPix;
}
