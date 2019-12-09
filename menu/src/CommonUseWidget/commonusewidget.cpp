#include "commonusewidget.h"
#include "ui_commonusewidget.h"
#include "src/color.h"
#include <QDBusInterface>
#include <QDBusReply>
#include <QDir>
#include <QDebug>

CommonUseWidget::CommonUseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonUseWidget)
{
    ui->setupUi(this);
    init_widget();

}

CommonUseWidget::~CommonUseWidget()
{
    delete ui;
    delete pUkuiMenuInterface;
}

void CommonUseWidget::init_widget()
{
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground,true);
    char widgetcolor[100];
    sprintf(widgetcolor, "border:0px;background-color:%s;",MAINVIEWWIDGETCOLOR);
    this->setStyleSheet(QString::fromLocal8Bit(widgetcolor));
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setFixedSize(330,462);

    mainLayout=new  QHBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    applistWid=new QWidget(this);
    applistWid->setStyleSheet("border:0px;background: transparent;");
    applistWid->setFixedSize(this->width(),this->height());
    mainLayout->addWidget(applistWid);
    this->setLayout(mainLayout);

    pUkuiMenuInterface=new UkuiMenuInterface;

    QString path=QDir::homePath()+"/.config/ukui-menu/ukui-menu.ini";
    setting=new QSettings(path,QSettings::IniFormat);

    init_applist_widget();
    fill_app_tablewidget();
}

/**
 * 初始化应用列表界面
 */
void CommonUseWidget::init_applist_widget()
{
    QHBoxLayout* layout=new QHBoxLayout(applistWid);
    layout->setContentsMargins(2,0,2,0);
    listview=new ListView(this,applistWid->width()-4,applistWid->height(),0);
    layout->addWidget(listview);
    applistWid->setLayout(layout);
    connect(listview,SIGNAL(sendItemClickedSignal(QStringList)),this,SLOT(exec_app_name(QStringList)));
    connect(listview,SIGNAL(send_update_applist_signal()),this,SIGNAL(send_update_applist_signal()));

}

/**
 * 填充应用列表
 */
void CommonUseWidget::fill_app_tablewidget()
{
    char btncolor[300];
    sprintf(btncolor,"QPushButton{background:transparent;border:0px;color:#ffffff;font-size:14px;padding-left:0px;text-align: left center;}\
            QPushButton:hover{background-color:%s;}\
            QPushButton:pressed{background-color:%s;}", MAINVIEWBTNHOVER,MAINVIEWBTNPRESSED);

    QStringList keys;
    keys.clear();
    setting->beginGroup("application");
    keys=setting->childKeys();
    QStringList applist;
    applist.clear();
    for(int i=0;i<keys.count();i++)
    {
        int val=setting->value(keys.at(i)).toInt();
        if(val==2 || val==0)
            applist.append(keys.at(i));
    }

    data.clear();
    for(int i=0;i<applist.count();i++)
    {
        QString desktopfp=pUkuiMenuInterface->get_desktop_path_by_app_name(applist.at(i));
        data.append(QStringList()<<desktopfp<<"1");
    }

    m_delegate= new ItemDelegate(this,0);
    listview->setItemDelegate(m_delegate);
    listview->addData(data);
    setting->endGroup();
}

/**
 * 执行应用程序
 */
void CommonUseWidget::exec_app_name(QStringList arg)
{
    emit send_hide_mainwindow_signal();
    QString execpath=pUkuiMenuInterface->get_app_exec(arg.at(0));
    //    qDebug()<<execpath;
    //移除启动参数%u或者%U
    for(int i=0;i<execpath.length();i++)
    {
        if(execpath.at(i)=='%')
        {
            execpath.remove(i,2);
        }
    }
    QProcess *process=new QProcess(this);
    process->startDetached(execpath);
}


/**
 * 更新应用列表槽函数
 */
void CommonUseWidget::update_listview_slot()
{
    QStringList keys;
    keys.clear();
    setting->beginGroup("application");
    keys=setting->childKeys();
    QStringList applist;
    applist.clear();
    for(int i=0;i<keys.count();i++)
    {
        int val=setting->value(keys.at(i)).toInt();
        if(val==2 || val==0)
            applist.append(keys.at(i));
    }

    data.clear();
    for(int i=0;i<applist.count();i++)
    {
        QString desktopfp=pUkuiMenuInterface->get_desktop_path_by_app_name(applist.at(i));
        data.append(QStringList()<<desktopfp<<"1");
    }

    listview->updateData(data);
    setting->endGroup();

}
