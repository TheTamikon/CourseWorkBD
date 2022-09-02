#include "client.h"
#include "ui_client.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QDebug>

client::client(QString login, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::client)
{
    log=login;
    ui->setupUi(this);
    query.exec(QString("SELECT t.id,t.position,d.name,d.id FROM mydb.teacher t JOIN mydb.department d ON d.id = t.d_id WHERE t.login='%1';").arg(login));
    query.first();
    ui->label_fio->setText(query.value(0).toString());
    ui->label_position->setText("Должность: "+query.value(1).toString());
    ui->label_dep->setText("Кафедра: "+query.value(2).toString());
    department = query.value(3).toString();
    fio = query.value(0).toString();

    model1->setQuery(QString("SELECT s.id, s.name,p.student_group,p.d_id,p.control,p.all_hours,p.id FROM mydb.plan p JOIN mydb.subject s ON s.id = p.s_id JOIN mydb.teacher t ON t.id = p.t_id WHERE t.login='%1';").arg(login));
    model1->setHeaderData(0, Qt::Horizontal, tr("Сокращение"));
    model1->setHeaderData(1, Qt::Horizontal, tr("Предмет"));
    model1->setHeaderData(2, Qt::Horizontal, tr("Группа"));
    model1->setHeaderData(3, Qt::Horizontal, tr("Кафедра группы"));
    model1->setHeaderData(4, Qt::Horizontal, tr("Форма контроля"));
    model1->setHeaderData(5, Qt::Horizontal, tr("Часы"));
    model1->setHeaderData(6, Qt::Horizontal, tr("План"));
    ui->tableView1->setModel(model1);
    ui->tableView1->setColumnHidden(0, true);
    ui->tableView1->setColumnHidden(6, true);
    ui->tableView1->show();

    model2->setQuery(QString("SELECT s.name,s.lec_hours,s.prac_hours,s.lab_hours FROM mydb.plan p JOIN mydb.subject s ON s.id = p.s_id JOIN mydb.teacher t ON t.id = p.t_id WHERE t.login='%1' GROUP BY s.id;").arg(login));
    model2->setHeaderData(0, Qt::Horizontal, tr("Предмет"));
    model2->setHeaderData(1, Qt::Horizontal, tr("Лекции"));
    model2->setHeaderData(2, Qt::Horizontal, tr("Практика"));
    model2->setHeaderData(3, Qt::Horizontal, tr("Лабораторные"));
    ui->tableView2->setModel(model2);
    ui->tableView2->show();
    ui->pushButton->setDisabled(true);
}

client::~client()
{
    delete ui;
}

void client::on_pushButton_clicked()
{
    query.exec(QString("CALL mydb.move('%1', %2, '%3', '%4','%5','%6','%7',%8);").arg(department)
                                                                              .arg(model1->data(model1->index(idx, 6)).toInt())
                                                                              .arg(fio)
                                                                              .arg(model1->data(model1->index(idx, 0)).toString())
                                                                              .arg(model1->data(model1->index(idx, 3)).toString())
                                                                              .arg(model1->data(model1->index(idx, 2)).toString())
                                                                              .arg(model1->data(model1->index(idx, 4)).toString())
                                                                              .arg(model1->data(model1->index(idx, 5)).toString()));
}

void client::on_tableView1_clicked(const QModelIndex &index)
{
    ui->pushButton->setDisabled(false);
    idx = ui->tableView1->selectionModel()->currentIndex().row();
}

void client::on_pushButton_2_clicked()
{
    model1->clear();
    model1->setQuery(QString("SELECT s.id, s.name,p.student_group,p.d_id,p.control,p.all_hours,p.id FROM mydb.plan p JOIN mydb.subject s ON s.id = p.s_id JOIN mydb.teacher t ON t.id = p.t_id WHERE t.login='%1';").arg(log));
    model1->setHeaderData(0, Qt::Horizontal, tr("Сокращение"));
    model1->setHeaderData(1, Qt::Horizontal, tr("Предмет"));
    model1->setHeaderData(2, Qt::Horizontal, tr("Группа"));
    model1->setHeaderData(3, Qt::Horizontal, tr("Кафедра группы"));
    model1->setHeaderData(4, Qt::Horizontal, tr("Форма контроля"));
    model1->setHeaderData(5, Qt::Horizontal, tr("Часы"));
    model1->setHeaderData(6, Qt::Horizontal, tr("План"));
    ui->tableView1->setModel(model1);
    ui->tableView1->setColumnHidden(0, true);
    ui->tableView1->setColumnHidden(6, true);
    ui->tableView1->show();
    model2->clear();
    model2->setQuery(QString("SELECT s.name,s.lec_hours,s.prac_hours,s.lab_hours FROM mydb.plan p JOIN mydb.subject s ON s.id = p.s_id JOIN mydb.teacher t ON t.id = p.t_id WHERE t.login='%1' GROUP BY s.id;").arg(log));
    model2->setHeaderData(0, Qt::Horizontal, tr("Предмет"));
    model2->setHeaderData(1, Qt::Horizontal, tr("Лекции"));
    model2->setHeaderData(2, Qt::Horizontal, tr("Практика"));
    model2->setHeaderData(3, Qt::Horizontal, tr("Лабораторные"));
    ui->tableView2->setModel(model2);
    ui->tableView2->show();

    ui->pushButton->setDisabled(true);
}
