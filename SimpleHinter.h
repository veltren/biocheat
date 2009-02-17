/***************************************************************************
 * Copyright (c) 2009 Enrico Ros                                           *
 *         2009 Enrico Ros <enrico.ros@gmail.com>                          *
 *                                                                         *
 * Permission is hereby granted, free of charge, to any person             *
 * obtaining a copy of this software and associated documentation          *
 * files (the "Software"), to deal in the Software without                 *
 * restriction, including without limitation the rights to use,            *
 * copy, modify, merge, publish, distribute, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the               *
 * Software is furnished to do so, subject to the following                *
 * conditions:                                                             *
 *                                                                         *
 * The above copyright notice and this permission notice shall be          *
 * included in all copies or substantial portions of the Software.         *
 *                                                                         *
 ***************************************************************************/

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
