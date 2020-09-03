/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QGuiApplication>
#include <QVulkanFunctions>
#include <QVulkanInstance>
#include <QWindow>

namespace src_gui_vulkan_qvulkaninstance {

struct Window {
    void setVulkanInstance(QVulkanInstance *instance) { Q_UNUSED(instance); }
    void show();
};
Window *window = nullptr;


//! [0]
    int main(int argc, char **argv)
    {
        QGuiApplication app(argc, argv);

        QVulkanInstance inst;
        if (!inst.create())
            return 1;

        // ...
        window->setVulkanInstance(&inst);
        window->show();

        return app.exec();
    }
//! [0]


void wrapper0() {
//! [1]
    QVulkanInstance inst;

    // Enable validation layer, if supported. Messages go to qDebug by default.
    inst.setLayers(QByteArrayList() << "VK_LAYER_LUNARG_standard_validation");

    bool ok = inst.create();
    if (!ok) {
        // ... Vulkan not available
    }

    if (!inst.layers().contains("VK_LAYER_LUNARG_standard_validation")) {
        // ... validation layer not available
    }
//! [1]
}


void wrapper1() {
//! [2]
    QVulkanInstance inst;

    if (inst.supportedLayers().contains("VK_LAYER_LUNARG_standard_validation")) {
        // ...
    }
    bool ok = inst.create();
    // ...
//! [2]

Q_UNUSED(ok);
} // wrapper1
} // src_gui_vulkan_qvulkaninstance


namespace src_gui_vulkan_qvulkaninstance2 {

//! [3]
class VulkanWindow : public QWindow
{
public:
    VulkanWindow() {
        setSurfaceType(VulkanSurface);
    }

    void exposeEvent(QExposeEvent *) {
        if (isExposed()) {
            if (!m_initialized) {
                m_initialized = true;
                // initialize device, swapchain, etc.
                QVulkanInstance *inst = vulkanInstance();
                QVulkanFunctions *f = inst->functions();
                uint32_t devCount = 0;
                f->vkEnumeratePhysicalDevices(inst->vkInstance(), &devCount, nullptr);
                // ...
                // build the first frame
                render();
            }
        }
    }

    bool event(QEvent *e) {
        if (e->type() == QEvent::UpdateRequest)
            render();
        return QWindow::event(e);
    }

    void render() {
       // ...
       requestUpdate(); // render continuously
    }

private:
    bool m_initialized = false;
};

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QVulkanInstance inst;
    if (!inst.create()) {
        qWarning("Vulkan not available");
        return 1;
    }

    VulkanWindow window;
    window.showMaximized();

    return app.exec();

}
//! [3]


} // src_gui_vulkan_qvulkaninstance2
