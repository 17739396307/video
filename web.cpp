#include "web.h"
#include "ui_web.h"

#include <QMessageBox>
#include <QStackedLayout>

web::web(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::web)
{
    ui->setupUi(this);
    m_webView = new QWebEngineView(this);
    ui->lineEdit->setText("https://v.qq.com/");
    QStackedLayout* layout = new QStackedLayout(ui->frame);
    ui->frame->setLayout(layout);
    layout->addWidget(m_webView);

//        connect(m_webView,SIGNAL(urlChanged(QUrl&)),this,SLOT(createWindows(QUrl&)));
    connect(ui->Go, &QPushButton::clicked, this, [this]() {
        QString url = ui->lineEdit->text();
        if (!url.isEmpty())
        {
            m_webView->load(url);
        }
    });
    connect(ui->Refresh, &QPushButton::clicked, this, [this]() {
        m_webView->reload();
    });
    show();
}


void  web::forward()
{
    QWebEngineView  *webView;
    QMessageBox::about(NULL,"sda","sfsdf");

}

web::~web()
{
    delete ui;
}
