#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QMessageBox>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "browser.h"
#include "browserwindow.h"
#include "tabwidget.h"

QUrl commandLineUrlArgument()
{
    const QStringList args = QCoreApplication::arguments();
    for (const QString &arg : args.mid(1)) {
        if (!arg.startsWith(QLatin1Char('-')))
            return QUrl::fromUserInput(arg);
    }
    return QUrl(QStringLiteral("http://www.5566.net/sp.htm"));
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setSearch(int margc, char *margv[])
{
    argc=margc;
    argv = margv;
}
void MainWindow::init()
{
    connectMysql();
    QAction *pTrailingAction = new QAction(this);
    pTrailingAction->setIcon(QIcon(":/image/search.png"));
    ui->lineEdit->addAction(pTrailingAction, QLineEdit::TrailingPosition);
    connect(pTrailingAction, SIGNAL(triggered(bool)), this, SLOT(onSearch()));
    m_form = new Form();
    connect(m_form,SIGNAL(Login(QString,QString)),this,SLOT(setLP(QString,QS tring)));
    connect(m_form,SIGNAL(clearLogin()),this,SLOT(clearLP()));
    connect(ui->upButton,SIGNAL(clicked()),this,SLOT(slot_upButton()));
    connect(ui->downButton,SIGNAL(clicked()),this,SLOT(slot_DownButton()));
    setLogo();
    ui->listWidget_2->setViewMode(QListView::IconMode);
    ui->listWidget_2->setViewMode(QListWidget::IconMode);//设置内容为图片
    ui->listWidget_2->setIconSize(QSize(120, 110));//设置图片的大小
    ui->listWidget_2->setSpacing(10);
    ui->listWidget_2->setResizeMode(QListWidget::Adjust);
    ui->listWidget_2->setFlow(QListView::TopToBottom);
    setRecommend();
}
void MainWindow::connectMysql()
{
    database=QSqlDatabase::addDatabase("QMYSQL","Video");//创建数据库连接，并为其命名testConnect
    database.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    database.setDatabaseName("video");
    database.setPort(3306);                 //连接数据库端口号，与设置一致
    database.setUserName("root");          //数据库用户名，与设置一致
    database.setPassword("111111");    //数据库密码，与设置一致
    if(!database.open())
    {
        QMessageBox::information(NULL,QString::fromLocal8Bit("123"),QString::fromLocal8Bit("连接服务器失败，请稍后重试"));
        return;
    }
}

void MainWindow::onSearch()
{
    QMessageBox::about(NULL,"dsfsdf",ui->lineEdit->text());
}

void MainWindow::on_personalCenter_clicked(bool checked)
{
    m_form->setDatabase(database);
    if(m_login.isEmpty()&&m_password.isEmpty())
    {m_form->setstack(0);}
    else
    {m_form->setstack(2);
    }
    m_form->show();
}
void MainWindow::setLP(QString login,QString password)
{
    m_login =login;
    m_password = password;
}
void MainWindow::clearLP()
{
    m_login.clear();
    m_password.clear();

}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    switch(index.row())
    {
    case 0:
        setLogo();
        break;
    default:
        break;
    }
}
void MainWindow::setLogo()
{
    QSqlQuery query(database);
    query.exec("select * from tvplay ORDER BY RAND() LIMIT 7");
    QSqlRecord rec = query.record();
    while(query.next())
    {
        QVector<QString>pic;
        for(int i=0;i<rec.count();i++)
        {
            QString str=query.value(i).toString();
            pic.append(str);
        }
        m_pictureLogo.append(pic);
    }
    m_qTimer = new QTimer();

    connect(this->m_qTimer, SIGNAL(timeout()), this, SLOT(showPictureSlot()));

    m_qTimer->start(3000);
    ui->pushButton1->setText(m_pictureLogo[0][3]);
    ui->pushButton2->setText(m_pictureLogo[1][3]);
    ui->pushButton3->setText(m_pictureLogo[2][3]);
    ui->pushButton4->setText(m_pictureLogo[3][3]);
    ui->pushButton5->setText(m_pictureLogo[4][3]);
    ui->pushButton6->setText(m_pictureLogo[5][3]);
    ui->pushButton7->setText(m_pictureLogo[6][3]);
    QPixmap pixmap=networkPicture(m_pictureLogo[0][2]);
    //ui->firstLogo->setScaledContents(true);
    ui->firstLogo->setPixmap(pixmap); // 你在QLabel显示图片
}
 QPixmap MainWindow::networkPicture(QString picture)
{
    QUrl url(picture);
        QNetworkAccessManager manager;
        QEventLoop loop;
        QNetworkReply *reply = manager.get(QNetworkRequest(url));
        //请求结束并下载完成后，退出子事件循环
        QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        //开启子事件循环
        loop.exec();
        QByteArray jpegData = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(jpegData);
        return pixmap;
}
 void MainWindow::showPictureSlot()
 {

     ui->firstLogo->setPixmap(networkPicture(m_pictureLogo[m_imgNumber][2]));
     switch(m_imgNumber)
     {
     case 0:
         ui->pushButton7->setStyleSheet("QPushButton{color: rgb(255, 255, 255);}");
         ui->pushButton1->setStyleSheet("QPushButton{color: rgb(243, 131, 18);}");
         break;
     case 1:

         ui->pushButton1->setStyleSheet("QPushButton{color: rgb(255, 255, 255);}");
         ui->pushButton2->setStyleSheet("QPushButton{color: rgb(243, 131, 18);}");

         break;
     case 2:

         ui->pushButton2->setStyleSheet("QPushButton{color: rgb(255, 255, 255);}");
         ui->pushButton3->setStyleSheet("QPushButton{color: rgb(243, 131, 18);}");

         break;
     case 3:

         ui->pushButton3->setStyleSheet("QPushButton{color: rgb(255, 255, 255);}");
         ui->pushButton4->setStyleSheet("QPushButton{color: rgb(243, 131, 18);}");

         break;
     case 4:
         ui->pushButton4->setStyleSheet("QPushButton{color: rgb(255, 255, 255);}");
         ui->pushButton5->setStyleSheet("QPushButton{color: rgb(243, 131, 18);}");
         break;
     case 5:
         ui->pushButton5->setStyleSheet("QPushButton{color: rgb(255, 255, 255);}");
         ui->pushButton6->setStyleSheet("QPushButton{color: rgb(243, 131, 18);}");
         break;
     case 6:
         ui->pushButton6->setStyleSheet("QPushButton{color: rgb(255, 255, 255);}");
         ui->pushButton7->setStyleSheet("QPushButton{color: rgb(243, 131, 18);}");
         break;
     case 7:
         ui->pushButton7->setStyleSheet("QPushButton{color:rgb(255, 255, 255);}");
         ui->pushButton1->setStyleSheet("QPushButton{color: rgb(243, 131, 18);}");
         break;
     default:
         break;
     }
     if (6 == m_imgNumber)
     {
         m_imgNumber = 0;
         return;
     }
        ++m_imgNumber;

 }

 void MainWindow::setRecommend()
 {
     QSqlQuery query(database);
     int j=0;
     query.exec("select * from tvplay ORDER BY RAND() LIMIT 100");
     QSqlRecord rec = query.record();

     while(query.next())
     {
         QVector<QString>pic;
         for(int i=0;i<rec.count();i++)
         {
             QString str=query.value(i).toString();
             pic.append(str);
         }

         m_picture.append(pic);
         if(j<7)
         {
             QListWidgetItem *item =   new QListWidgetItem(QIcon(networkPicture(pic[2])),pic[3]);
             item->setTextColor(QColor(255, 255, 255, 255));
             ui->listWidget_2->addItem(item);
             j++;
         }
     }

 }
void MainWindow::slot_upButton()
{
    if(beginNumber >= mRow)
        beginNumber -= mRow;
    ui->listWidget_2->clear();
    for(int i=0;i<mRow;i++)
    {
        QListWidgetItem *item =   new QListWidgetItem(QIcon(networkPicture(m_picture[beginNumber+i][2])),m_picture[beginNumber+i][3]);
        item->setTextColor(QColor(255, 255, 255, 255));
        ui->listWidget_2->addItem(item);
    }
}
void MainWindow::slot_DownButton()
{
    if(beginNumber <= 90)
        beginNumber += mRow;
    ui->listWidget_2->clear();
    for(int i=0;i<mRow;i++)
    {
        QListWidgetItem *item =  new QListWidgetItem(QIcon(networkPicture(m_picture[beginNumber+i][2])),m_picture[beginNumber+i][3]);
        item->setTextColor(QColor(255, 255, 255, 255));
        ui->listWidget_2->addItem(item);
    }
}

void MainWindow::on_listWidget_2_clicked(const QModelIndex &index)
{
    qDebug()<<index.row();
}

void MainWindow::on_browerser_clicked()
{
    QUrl url = commandLineUrlArgument();
     Browser browser;
     BrowserWindow *window = browser.createWindow();
     window->tabWidget()->setUrl(url);
}
