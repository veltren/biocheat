#ifndef __Visualizer_h__
#define __Visualizer_h__

#include <QFrame>
#include <QPixmap>
#include <QPaintEvent>

class Visualizer : public QFrame
{
    Q_OBJECT
    public:
        Visualizer( QWidget * parent = 0 );

        void setOriginalPixmap( const QPixmap & pixmap );
        QPixmap originalPixmap() const;

    protected:
        void paintEvent( QPaintEvent * event );

    private:
        QPixmap m_origPixmap;
};

#endif
