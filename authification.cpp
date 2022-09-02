#include "authification.h"
#include "ui_authification.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QMessageBox>
#include "client.h"
#include "admin.h"
#include <QLinkedList>
#include <QtDebug>

authification::authification(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::authification)
{
    ui->setupUi(this);
}

authification::~authification()
{
    delete ui;
}

void authification::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("postgres");
    db.setHostName("localhost");
    db.setUserName("visitor");
    db.setPassword("visitor");
    if (!db.open())
    {
       QMessageBox::warning(this, "Error", db.lastError().text());
    }
    QString login=ui->lineLogin->text();
    QString password=ui->linePassword->text();
    QSqlQuery query;
    query.exec("SELECT login, password FROM mydb.department;");
    bool flag = false;
    QString userRole;
    while (query.next())
    {
        if((login == query.value(0).toString()) && (password == query.value(1).toString()))
        {
            userRole="kafedra";
            flag=true;
            db.close();
            db.setDatabaseName("postgres");
            db.setHostName("localhost");
            db.setUserName(userRole);
            db.setPassword(userRole);
            db.open();
            admin *a=new admin(login);
            a->show();
            this->close();
        }
    }
    if(!flag)
    {
        query.exec("SELECT login, password FROM mydb.teacher;");
        while (query.next())
        {
            if((login == query.value(0).toString()) && (password == query.value(1).toString()))
            {
                userRole="teacher";
                flag=true;
                db.close();
                db.setDatabaseName("postgres");
                db.setHostName("localhost");
                db.setUserName(userRole);
                db.setPassword(userRole);
                db.open();
                client *c=new client(login);
                c->show();
                this->close();
            }
        }
    }
    if(!flag) QMessageBox::information(this, "ERROR", "Неверные данные");
}
