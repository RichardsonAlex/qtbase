/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qclipboard.h"

#ifndef QT_NO_CLIPBOARD

#include "qmimedata.h"
#include "private/qguiapplication_p.h"
#include "qplatformclipboard_qpa.h"

QT_BEGIN_NAMESPACE

QT_USE_NAMESPACE

void QClipboard::clear(Mode mode)
{
    setMimeData(0,mode);
}


bool QClipboard::event(QEvent *e)
{
    return QObject::event(e);
}

const QMimeData* QClipboard::mimeData(Mode mode) const
{
    QPlatformClipboard *clipboard = QGuiApplicationPrivate::platformIntegration()->clipboard();
    if (!clipboard->supportsMode(mode)) return 0;
    return clipboard->mimeData(mode);
}

void QClipboard::setMimeData(QMimeData* src, Mode mode)
{
    QPlatformClipboard *clipboard = QGuiApplicationPrivate::platformIntegration()->clipboard();
    if (!clipboard->supportsMode(mode)) return;

    clipboard->setMimeData(src,mode);

    emitChanged(mode);
}

bool QClipboard::supportsMode(Mode mode) const
{
    QPlatformClipboard *clipboard = QGuiApplicationPrivate::platformIntegration()->clipboard();
    return clipboard->supportsMode(mode);
}

bool QClipboard::ownsMode(Mode mode) const
{
    if (mode == Clipboard)
        qWarning("QClipboard::ownsClipboard: UNIMPLEMENTED!");
    return false;
}

void QClipboard::connectNotify( const char * )
{
}

void QClipboard::ownerDestroyed()
{
}

#endif // QT_NO_CLIPBOARD

QT_END_NAMESPACE
