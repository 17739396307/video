#ifndef FORM_H
#define FORM_H

#include <QDialog>
#include <QSqlDatabase>
#include <QScrollBar>

namespace Ui {
class Form;
}

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QDialog *parent = nullptr);
    ~Form();
    void setstack(int num);
    void setDatabase(QSqlDatabase database);
    void sendLogin();
    void sendLogin(QString login, QString pwd);
    void init();
signals:
    void Login(QString login,QString password);
   void  clearLogin();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();


    void on_determine_clicked();

    void on_login_clicked();

    void on_logout_clicked();

    void on_detection_clicked();

    void on_reset_clicked();

private:
    Ui::Form *ui;
    QSqlDatabase m_database;
    QString m_login;
    QString m_pwd;

};

#endif // FORM_H
