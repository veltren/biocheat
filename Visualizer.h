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
