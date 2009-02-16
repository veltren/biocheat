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

QPixmap Visualizer::originalPixmap() const
{
    return m_origPixmap;
}

void Visualizer::paintEvent( QPaintEvent * event )
{
    QFrame::paintEvent( event );

    QPainter p( this );
    QPoint offset( (width() - m_origPixmap.width()) / 2, (height() - m_origPixmap.height()) / 2 );
    p.setCompositionMode( QPainter::CompositionMode_Source );
    p.drawPixmap( offset, m_origPixmap );
    p.setCompositionMode( QPainter::CompositionMode_SourceOver );
}
