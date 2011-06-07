/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtOpenGL module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QPLATFORM_GL_CONTEXT_H
#define QPLATFORM_GL_CONTEXT_H

#include <QtCore/qnamespace.h>
#include <QtGui/qguiglformat_qpa.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

class Q_GUI_EXPORT QPlatformGLSurface
{
public:
    QPlatformGLSurface(const QGuiGLFormat &format = QGuiGLFormat())
        : m_format(format)
    {
    }

    virtual ~QPlatformGLSurface() {}

    QGuiGLFormat format() const
    {
        return m_format;
    }

protected:
    void setFormat(const QGuiGLFormat &format)
    {
        m_format = format;
    }

private:
    QGuiGLFormat m_format;
};

class Q_GUI_EXPORT QPlatformGLContext
{
public:
    virtual ~QPlatformGLContext() {}

    virtual QGuiGLFormat format() const = 0;

    virtual void swapBuffers(const QPlatformGLSurface &surface) = 0;

    virtual bool makeCurrent(const QPlatformGLSurface &surface) = 0;
    virtual void doneCurrent() = 0;

    virtual void (*getProcAddress(const QByteArray &procName)) () = 0;
};

QT_END_NAMESPACE

QT_END_HEADER


#endif // QPLATFORM_GL_CONTEXT_H
