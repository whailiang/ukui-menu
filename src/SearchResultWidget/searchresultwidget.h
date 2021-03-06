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

#ifndef SEARCHRESULTWIDGET_H
#define SEARCHRESULTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QDesktopWidget>
#include <QLabel>
#include <QToolButton>
#include <QScrollBar>
#include <QPushButton>
#include "src/Interface/ukuimenuinterface.h"
//#include "searchappthread.h"
#include "src/UtilityFunction/listview.h"
#include "src/UtilityFunction/itemdelegate.h"

namespace Ui {
class SearchResultWidget;
}

class SearchResultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchResultWidget(QWidget *parent = nullptr);
    ~SearchResultWidget();
    void updateAppListView(QStringList desktopfplist);
    /**
     * @brief moveScrollBar移动滚动条
     * @param type为0时表示向上移动，为1时表示向下移动
     */
    void moveScrollBar(int type);

private:
    Ui::SearchResultWidget *ui;

    UkuiMenuInterface* pUkuiMenuInterface=nullptr;

    QHBoxLayout* mainLayout=nullptr;
    ListView* listview=nullptr;
    QVector<QStringList> data;

protected:
    void initWidget();

private Q_SLOTS:
    void execApplication(QStringList arg);//执行应用程序

Q_SIGNALS:
    void sendUpdateAppListSignal(QString desktopfp,int type);//向常用软件模块发送更新应用列表信号
    void sendHideMainWindowSignal();//向MainViewWidget发送隐藏主窗口信号
};

#endif // SEARCHRESULTWIDGET_H
