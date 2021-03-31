#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QMouseEvent>
#include <QSqlDatabase>
#include <QTimer>
#include "form.h"
#include "web.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connectMysql();
    void init();
    QPixmap networkPicture(QString picture);
    void setLogo();
    void setRecommend();
    void clicked();
    void setSearch(int margc, char *margv[]);
public slots:
    void onSearch();
    void setLP(QString login, QString password);
    void clearLP();
    void slot_upButton();
    void slot_DownButton();
    void showPictureSlot();
private slots:
    void on_personalCenter_clicked(bool checked);

    void on_listWidget_clicked(const QModelIndex &index);

    void on_listWidget_2_clicked(const QModelIndex &index);

    void on_browerser_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
    QString m_login;
    QString m_password;
    Form *m_form;
    int beginNumber=0;
    int m_imgNumber=0;
    int mRow=7;
     QVector<QVector<QString>>m_picture;
     QVector<QVector<QString>>m_pictureLogo;
     QTimer *m_qTimer;
     web *m_web;
     char **argv;
     int argc;
};
#endif // MAINWINDOW_H
