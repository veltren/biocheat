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

    Q_SIGNALS:
        void gotImage( const QImage & image );

    protected:
        void timerEvent( QTimerEvent * event );

    private:
        QBasicTimer m_timer;
        QList<QImage> m_images;
        int m_currentIndex;
};

#endif
