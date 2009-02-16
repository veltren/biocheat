#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPixmap>
class Capture;
class Classifier;

namespace Ui { class WindowForm; }

class Window : public QWidget
{
    Q_OBJECT
    public:
        Window( QWidget * parent = 0 );
        ~Window();

    protected:
        bool eventFilter( QObject * object, QEvent * event );

    private:
        Ui::WindowForm * ui;
        Capture * m_capture;
        Classifier * m_classifier;

    private Q_SLOTS:
        void slotCapParamsChanged();
        void slotProcessPixmap( const QPixmap & pixmap );
};

#endif
