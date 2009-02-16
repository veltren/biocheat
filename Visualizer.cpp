#include "Visualizer.h"
#include <QPainter>

Visualizer::Visualizer( QWidget * parent )
    : QFrame( parent )
{
}

void Visualizer::setOriginalPixmap( const QPixmap & pixmap )
{
    m_origPixmap = pixmap;
    update();
}

void Visualizer::setPixmapCursorPos( const QPoint & pos )
{
    m_pixCursorPos = pos;
    update();
}

QPoint Visualizer::pixmapCursorPos() const
{
    return m_pixCursorPos;
}

QPixmap Visualizer::originalPixmap() const
{
    return m_origPixmap;
}

void Visualizer::paintEvent( QPaintEvent * event )
{
    QFrame::paintEvent( event );

    QPainter p( this );
    QPoint offset( (width() - m_origPixmap.width()) / 2, (height() - m_origPixmap.height()) / 2 );

    // draw pixmap
    p.setCompositionMode( QPainter::CompositionMode_Source );
    p.drawPixmap( offset, m_origPixmap );
    p.setCompositionMode( QPainter::CompositionMode_SourceOver );

    // draw cursor
    if ( !m_pixCursorPos.isNull() )
        p.fillRect( offset.x() + m_pixCursorPos.x() - 2, offset.y() + m_pixCursorPos.y() - 2, 5, 5, Qt::white );
}
