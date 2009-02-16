#ifndef __SimpleHinter_h__
#define __SimpleHinter_h__

#include <QObject>
#include <QPixmap>
#include <QList>
#include "Recognizer.h"

struct HintResult {
    int fromX, fromY;
    int toX, toY;
    int count;
};
typedef QList<HintResult> HintResults;

class SimpleHinter : public QObject
{
    Q_OBJECT
    public:
        SimpleHinter( QObject * parent = 0 );

        HintResults process( const RecoResult & recoResult, const QPixmap & origPixmap, bool highlight );
        QPixmap output() const;

    private:
        int crossCount( const RecoResult & recoResult, int x, int y, int W, int H );
        QPixmap m_outPix;
};

#endif
