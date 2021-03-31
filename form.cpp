#include "form.h"
#include "ui_form.h"

#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QMessageBox>
Form::Form(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{

    ui->setupUi(this);
    init();
}

Form::~Form()
{
    delete ui;
}
void Form::init()
{
    QRegExp regExp1("[0-9]{6,10}");
    ui->lineEdit_3->setValidator(new QRegExpValidator(regExp1, ui->lineEdit_3));
    ui->lineEdit_3->setPlaceholderText(QString::fromLocal8Bit("输入6-10位数字"));
    QRegExp regExp2("[\\w]{0,10}");
    ui->lineEdit_4->setValidator(new QRegExpValidator(regExp2, ui->lineEdit_4));
    ui->lineEdit_4->setPlaceholderText(QString::fromLocal8Bit("最多设置10位"));
    QRegExp regExp3("[^\u4E00-\u9FA5]{6,20}");
    ui->lineEdit_5->setValidator(new QRegExpValidator(regExp3, ui->lineEdit_5));
    ui->lineEdit_5->setPlaceholderText(QString::fromLocal8Bit("输入6-20位随意数字、字母、符号"));
    QRegExp regExp4("[^\u4E00-\u9FA5]{6,20}");
    ui->lineEdit_6->setValidator(new QRegExpValidator(regExp4, ui->lineEdit_6));
    ui->lineEdit_6->setPlaceholderText(QString::fromLocal8Bit("输入6-20位随意数字、字母、符号"));
    QRegExp regExp5("[0-9]{11}");
    ui->lineEdit_7->setValidator(new QRegExpValidator(regExp5, ui->lineEdit_7));
    ui->lineEdit_7->setPlaceholderText(QString::fromLocal8Bit("输入11位手机号"));
    ui->lineEdit_8->setPlaceholderText(QString::fromLocal8Bit("提示问题"));
    //    QRegExp regExp6("[0-9]{6,10}");
    //    ui->lineEdit_8->setValidator(new QRegExpValidator(regExp6, ui->lineEdit_8));
    ui->lineEdit_5->setContextMenuPolicy(Qt::NoContextMenu);//设置无右键菜单
    ui->lineEdit_5->setEchoMode(QLineEdit::Password);//设置密码隐藏
    ui->lineEdit_5->setStyleSheet("QLineEdit{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid gray;}"
                                  "QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}");
    ui->lineEdit_6->setContextMenuPolicy(Qt::NoContextMenu);//设置无右键菜单
    ui->lineEdit_6->setEchoMode(QLineEdit::Password);//设置密码隐藏
    ui->lineEdit_6->setStyleSheet("QLineEdit{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid gray;}"
                                  "QLineEdit:hover{border-width:1px;border-radius:4px;font-size:12px;color:black;border:1px solid rgb(70,200,50);}");
}
void Form::setstack(int num)
{
    if(num==0)
    ui->stackedWidget->setCurrentIndex(0);
    ui->login->setFocus();
}

void Form::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Form::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Form::setDatabase(QSqlDatabase database)
{
    m_database = database;
    QSqlQuery query(database);
    query.exec("select * from pusers");
    qDebug()<<query.result();
    QSqlRecord rec =query.record();
    qDebug()<<rec.count();
}


void Form::on_determine_clicked()
{
    QSqlQuery query(m_database);
    query.prepare("insert into pusers values(?,?,?,?,?,?,?)");
    query.bindValue(0,ui->lineEdit_3->text());
    query.bindValue(1,ui->lineEdit_4->text());
    query.bindValue(2,ui->lineEdit_5->text());
    query.bindValue(3,ui->lineEdit_6->text());
    query.bindValue(4,0);
    query.bindValue(5,ui->lineEdit_7->text());
    query.bindValue(6,ui->lineEdit_8->text());
    bool success = query.exec();
    if(!success)
    {
        QMessageBox::about(NULL,"jieguo","shibai");
    }else
    {
        QMessageBox::information(NULL,"jieguo",QString::fromLocal8Bit("注册成功"));
    }
}

void Form::on_login_clicked()
{
    qDebug()<<"sdfsd";
     m_login =ui->lineEdit->text();
     m_pwd =ui->lineEdit_2->text();

    if(!m_login.isEmpty()&&!m_pwd.isEmpty())
      {
        QSqlQuery query(m_database);
        QString data=QString("select * from pusers  where (account='%1' and password='%2')").arg(m_login).arg(m_pwd);
        query.exec(data);
        qDebug()<<query.size();
        if (query.size()>0)
        {
            QMessageBox::about(NULL,"123",QString::fromLocal8Bit("登录成功"));
            ui->stackedWidget->setCurrentIndex(2);
            emit Login(m_login,m_pwd);
        }
    }
}
void Form::sendLogin(QString login,QString pwd)
{

}

void Form::on_logout_clicked()
{
    int result = QMessageBox::information(NULL, "Title", QString::fromLocal8Bit("是否退出登录"),
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(result==QMessageBox::Yes)
    {
        m_login.clear();
        m_pwd.clear();
        emit clearLogin();
        ui->stackedWidget->setCurrentIndex(0);
    }

}

void Form::on_detection_clicked()
{
    if(ui->lineEdit_3->text().size()>5)
        ui->lineEdit_3->setStyleSheet("QLineEdit{background-color: rgb(212, 255, 253);}");
    else
        ui->lineEdit_3->setStyleSheet("QLineEdit{background-color: rgb(255, 161, 163);}");
    if(!ui->lineEdit_4->text().isEmpty())
        ui->lineEdit_4->setStyleSheet("QLineEdit{background-color: rgb(212, 255, 253);}");
    else
        ui->lineEdit_4->setStyleSheet("QLineEdit{background-color: rgb(255, 161, 163);}");
    if(ui->lineEdit_5->text().size()>5)
        ui->lineEdit_5->setStyleSheet("QLineEdit{background-color: rgb(212, 255, 253);}");
    else
        ui->lineEdit_5->setStyleSheet("QLineEdit{background-color: rgb(255, 161, 163);}");
    if(ui->lineEdit_6->text().size()>5)
        ui->lineEdit_6->setStyleSheet("QLineEdit{background-color: rgb(212, 255, 253);}");
    else
        ui->lineEdit_6->setStyleSheet("QLineEdit{background-color: rgb(255, 161, 163);}");
    if(ui->lineEdit_7->text().size()==11)
        ui->lineEdit_7->setStyleSheet("QLineEdit{background-color: rgb(212, 255, 253);}");
    else
        ui->lineEdit_7->setStyleSheet("QLineEdit{background-color: rgb(255, 161, 163);}");

    if(!ui->lineEdit_8->text().isEmpty())
        ui->lineEdit_8->setStyleSheet("QLineEdit{background-color: rgb(212, 255, 253);}");
    else
        ui->lineEdit_8->setStyleSheet("QLineEdit{background-color: rgb(255, 161, 163);}");
//    if(!ui->lineEdit_5->text().isEmpty()&&!ui->lineEdit_6->text().isEmpty())
//            if(ui->lineEdit_5->text()!=ui->lineEdit_6->text())
//                QMessageBox::information(NULL,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("密码前后不一致"));
}

void Form::on_reset_clicked()
{
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_3->setStyleSheet("QLineEdit{background-color: rgb(255, 255, 255);}");
    ui->lineEdit_4->setStyleSheet("QLineEdit{background-color: rgb(255, 255, 255);}");
    ui->lineEdit_5->setStyleSheet("QLineEdit{background-color: rgb(255, 255, 255);}");
    ui->lineEdit_6->setStyleSheet("QLineEdit{background-color: rgb(255, 255, 255);}");
    ui->lineEdit_7->setStyleSheet("QLineEdit{background-color: rgb(255, 255, 255);}");
    ui->lineEdit_8->setStyleSheet("QLineEdit{background-color: rgb(255, 255, 255);}");
}
