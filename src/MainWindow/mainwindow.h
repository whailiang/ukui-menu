/*
 * Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QPaintEvent>
#include <QPainter>
#include <QtMath>
#include <QEvent>
#include <QSpacerItem>
#include <QKeyEvent>
#include "src/Interface/ukuimenuinterface.h"
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QSettings>
#include <QPropertyAnimation>
#include <QFileInfo>
#include "src/Style/style.h"
#include "src/SideBarWidget/sidebarwidget.h"
#include "src/MainViewWidget/mainviewwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setFrameStyle();//设置QFrame样式
    void loadMainWindow();

private:
    Ui::MainWindow *ui;

    bool is_fullscreen=false;
    UkuiMenuInterface* pUkuiMenuInterface=nullptr;
    QSettings* setting=nullptr;

    QFrame* line=nullptr;//垂直分割线
    //主窗口样式
    QFrame* frame=nullptr;
    QHBoxLayout* mainlayout=nullptr;
    //侧边栏
    SideBarWidget* sidebarwid=nullptr;
    //主视图
    MainViewWidget* mainviewwid=nullptr;
    QPropertyAnimation* pEnterAnimation=nullptr;
    QPropertyAnimation* pLeaveAnimation=nullptr;

    QPropertyAnimation* pAnimation=nullptr;
    bool WinFlag = false;

protected:
    void initMainWindow();
    bool event(QEvent *event);//鼠标点击窗口外部事件
//    void paintEvent(QPaintEvent*);//添加阴影
    void keyPressEvent(QKeyEvent* e);//查询框响应键盘事件

private Q_SLOTS:
    void XkbEventsPress(const QString &keycode);
    void XkbEventsRelease(const QString &keycode);
    void showFullScreenWidget();//加载全屏窗口
    void showDefaultWidget();//显示默认窗口
    void recvHideMainWindowSlot();//接收隐藏主窗口信号
    void monitorResolutionChange(QRect rect);//监控屏幕分辨率
    void primaryScreenChangedSlot(QScreen *screen);
    void panelChangedSlot(QString key);
    void stateChangedSlot(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
};

#endif // MAINWINDOW_H
