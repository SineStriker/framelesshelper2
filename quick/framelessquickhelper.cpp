/*
 * MIT License
 *
 * Copyright (C) 2022 by wangwenx190 (Yuhang Zhao)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "framelessquickhelper.h"
#include <QtQml/qqmlengine.h>
#include "framelesshelperimageprovider.h"
#include "framelessquickutils.h"
#include <framelesswindowsmanager.h>

FRAMELESSHELPER_BEGIN_NAMESPACE

static constexpr const char FRAMELESSHELPER_QUICK_URI[] = "org.wangwenx190.FramelessHelper";

FramelessQuickHelper::FramelessQuickHelper(QObject *parent) : QObject(parent) {}

FramelessQuickHelper::~FramelessQuickHelper() = default;

void FramelessQuickHelper::registerTypes(QQmlEngine *engine)
{
    Q_ASSERT(engine);
    if (!engine) {
        return;
    }
    engine->addImageProvider(QStringLiteral("framelesshelper"), new FramelessHelperImageProvider);
    qmlRegisterSingletonType<FramelessQuickHelper>(FRAMELESSHELPER_QUICK_URI, 1, 0, "FramelessHelper", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine);
        Q_UNUSED(scriptEngine);
        const auto framelessHelper = new FramelessQuickHelper;
        return framelessHelper;
    });
    qmlRegisterSingletonType<FramelessQuickUtils>(FRAMELESSHELPER_QUICK_URI, 1, 0, "FramelessUtils", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
        Q_UNUSED(engine);
        Q_UNUSED(scriptEngine);
        const auto framelessUtils = new FramelessQuickUtils;
        return framelessUtils;
    });
}

void FramelessQuickHelper::addWindow(QWindow *window)
{
    Q_ASSERT(window);
    if (!window) {
        return;
    }
    FramelessWindowsManager::instance()->addWindow(window);
}

void FramelessQuickHelper::removeWindow(QWindow *window)
{
    Q_ASSERT(window);
    if (!window) {
        return;
    }
    FramelessWindowsManager::instance()->removeWindow(window);
}

FRAMELESSHELPER_END_NAMESPACE
