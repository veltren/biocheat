#ifndef __Visualizer_h__
#define __Visualizer_h__

#include <QFrame>
#include <QPixmap>
#include <QPaintEvent>
#include <QPoint>

class Visualizer : public QFrame
{
    Q_OBJECT
    public:
        Visualizer( QWidget * parent = 0 );

        void setOriginalPixmap( const QPixmap & pixmap );
        QPixmap originalPixmap() const;

        void setPixmapCursorPos( const QPoint & pos );
        QPoint pixmapCursorPos() const;

    protected:
        void paintEvent( QPaintEvent * event );

    private:
        QPixmap m_origPixmap;
        QPoint m_pixCursorPos;
};

#endif
