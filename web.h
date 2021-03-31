#ifndef WEB_H
#define WEB_H

#include <QDialog>
#include <QWebEngineView>

namespace Ui {
class web;
}

class web : public QDialog
{
    Q_OBJECT

public:
    explicit web(QWidget *parent = nullptr);
    ~web();

    //QWebEngineView *forward(QWebEnginePage::WebWindowType type);

public slots:
    void forward();
private:
    Ui::web *ui;
    QWebEngineView  *m_webView;
};

#endif // WEB_H
