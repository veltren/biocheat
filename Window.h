#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPixmap>
class Capture;
class Classifier;
class Recognizer;
class SimpleHinter;

namespace Ui { class WindowForm; }

class Window : public QWidget
{
    Q_OBJECT
    public:
        Window( QWidget * parent = 0 );
        ~Window();

    private:
        Ui::WindowForm * ui;
        Capture * m_capture;
        Classifier * m_classifier;
        Recognizer * m_recognizer;
        SimpleHinter * m_hinter;

    private Q_SLOTS:
        void slotCapParamsChanged();
        void slotRecParamsChanged();
        void slotProcessPixmap( const QPixmap & pixmap, const QPoint & cursor );
};

#endif
