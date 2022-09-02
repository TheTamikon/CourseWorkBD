#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QtSql/QSqlQuery>

namespace Ui {
class client;
}

class client : public QMainWindow
{
    Q_OBJECT

public:
    explicit client(QString login, QWidget *parent = nullptr);
    ~client();

private slots:
    void on_pushButton_clicked();

    void on_tableView1_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

private:
    Ui::client *ui;
    QSqlQueryModel *model1 = new QSqlQueryModel;
    QSqlQueryModel *model2 = new QSqlQueryModel;
    QString department;
    QString fio;
    QSqlQuery query;
    int idx;
    QString log="";
};

#endif // CLIENT_H
