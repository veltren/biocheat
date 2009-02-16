#ifndef CAPTURE_H
#define CAPTURE_H

#include <QObject>
#include <QBasicTimer>
#include <QList>
#include <QImage>

class Capture : public QObject
{
    Q_OBJECT
    public:
        Capture( QObject * parent );

        void setGeometry( const QRect & geometry );
        QRect geometry() const;
        void setFrequency( int fps );
        int frequency() const;

    Q_SIGNALS:
        void gotPixmap( const QPixmap & pixmap, const QPoint & cursorPos );

    protected:
        void timerEvent( QTimerEvent * event );

    private:
        QBasicTimer m_timer;
        QRect m_geometry;
        int m_fps;

        QList<QImage> m_images;
        int m_currentIndex;
};

#endif
