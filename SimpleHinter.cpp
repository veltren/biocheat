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

#include "SimpleHinter.h"
#include <QPainter>

SimpleHinter::SimpleHinter( QObject * parent )
    : QObject( parent )
{
}

#define INBOUND( a, b ) ((a) >= 0 && (b) >= 0 && (a) < W && (b) < H)
#define VALUE( a, b ) R.values[ (a) + (b) * W ]
#define SWAP( x1, y1, dx, dy ) \
    if ( INBOUND( x1 + dx, y1 + dy ) ) { \
        int v1 = VALUE( x, y ); \
        int v2 = VALUE( x + dx, y + dy ); \
        VALUE( x, y ) = v2; \
        VALUE( x + dx, y + dy ) = v1; \
        int count = crossCount( R, x1 + dx, y1 + dy, W, H ); \
        if ( count >= 3 ) { \
            HintResult hr; \
            hr.fromX = x1; \
            hr.fromY = y1; \
            hr.toX = x1 + dx; \
            hr.toY = y1 + dy; \
            hr.count = count; \
            results.append( hr ); \
        } \
        VALUE( x, y ) = v1; \
        VALUE( x + dx, y + dy ) = v2; \
    }

bool lowerHint( const HintResult & h1, const HintResult & h2 )
{
    return h1.count > h2.count;
}

HintResults SimpleHinter::process( const RecoResult & recoResult, const QPixmap & origPixmap, bool highlight )
{
    // geometry consts
    RecoResult R = recoResult;
    const int W = R.columns;
    const int H = R.rows;

    // SOLVE with BRUTE FORCE:
    // swap each piece in the 4 directions and check if something is acheived
    HintResults results;
    for ( int y = 0; y < H; y++ ) {
        for ( int x = 0; x < W; x++ ) {
            if ( VALUE( x, y ) == -1 )
                continue;
            SWAP( x, y, -1, +0 );
            SWAP( x, y, +1, +0 );
            SWAP( x, y, +0, -1 );
            SWAP( x, y, +0, +1 );
        }
    }
    qSort( results.begin(), results.end(), lowerHint );

    // regen the output pixmap
    if ( m_outPix.size() != origPixmap.size() )
        m_outPix = QPixmap( origPixmap.size() );
    m_outPix.fill( Qt::transparent );
    QFont font;
    font.setBold( true );
    font.setPixelSize( 18 );
    QPainter pp( &m_outPix );
    pp.setOpacity( 0.8 );
    pp.drawPixmap( 0, 0, origPixmap );
    pp.setOpacity( 1.0 );
    pp.setFont( font );

    // draw each hint result
    const int pw = origPixmap.width();
    const int ph = origPixmap.height();
    const int icoW = 32;
    const int icoH = 32;
    bool gotMore = false;
    static int frameCnt = 0;
    bool redLine = frameCnt > 5;
    if ( ++frameCnt > 10 )
        frameCnt = 0;
    foreach ( const HintResult & hint, results ) {
        // display only 4s or 5s if above 3
        if ( hint.count > 3 && highlight )
            gotMore = true;
        else if ( gotMore )
            break;

        float x1 = ((float)hint.fromX + 0.5) * (float)pw / (float)recoResult.columns;
        float y1 = ((float)hint.fromY + 0.5) * (float)ph / (float)recoResult.rows;
        float x2 = ((float)hint.toX + 0.5) * (float)pw / (float)recoResult.columns;
        float y2 = ((float)hint.toY + 0.5) * (float)ph / (float)recoResult.rows;
        QRect rect( (int)x1 - icoW / 2, (int)y1 - icoH / 2, icoW, icoH );

        // draw hilight and line
        if ( redLine ) {
            pp.setPen( QPen( Qt::red, 2 ) );
            pp.drawRect( rect );
        }
        pp.setPen( QPen( Qt::white, 2 ) );
        pp.drawLine( x1, y1, x2, y2 );

        // draw number
        if ( hint.count > 3 ) {
           pp.setPen( Qt::white );
           pp.drawText( rect, Qt::AlignCenter, QString::number( hint.count ) );
        }
    }

    return results;
}

int SimpleHinter::crossCount( const RecoResult & R, int x, int y, int W, int H )
{
    int value = VALUE( x, y );

    // go top & bottom
    int vCount = 1;
    int step = y - 1;
    while ( step >= 0 && VALUE( x, step ) == value ) { vCount++; step--; }
    step = y + 1;
    while ( step < H && VALUE( x, step ) == value ) { vCount++; step++; }

    // go right & left
    int hCount = 1;
    step = x + 1;
    while ( step < W && VALUE( step, y ) == value ) { hCount++; step++; }
    step = x - 1;
    while ( step >= 0 && VALUE( step, y ) == value ) { hCount++; step--; }

    // return the longest line
    return qMax( vCount, hCount );
}

QPixmap SimpleHinter::output() const
{
    return m_outPix;
}
