#ifndef __Recognizer_h__
#define __Recognizer_h__

#include <QObject>
#include <QPixmap>
#include "Classifier.h"

struct RecoResult {
    int rows;
    int columns;
    int total;
    int valid;
    int invalid;

    QVector<int> values;
};

class Recognizer : public QObject
{
    Q_OBJECT
    public:
        Recognizer( Classifier * classifier, QObject * parent = 0 );

        // init
        void setup( int hBlocks, int vBlocks );

        // do the job
        RecoResult recognize( const QPixmap & pixmap, bool verbose = false );
        QPixmap output() const;

    private:
        Classifier * m_classifier;
        int m_hBlocks;
        int m_vBlocks;
        QPixmap m_outPix;

};

#endif
