#include "admin.h"
#include "ui_admin.h"
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QDebug>

admin::admin(QString login, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    log=login;
    model1->setQuery(QString("SELECT * FROM mydb.department d;"));
    model1->setHeaderData(0, Qt::Horizontal, tr("Сокращение"));
    model1->setHeaderData(1, Qt::Horizontal, tr("Название"));
    model1->setHeaderData(2, Qt::Horizontal, tr("Сколько преподавателей на кафедре"));
    model1->setHeaderData(3, Qt::Horizontal, tr("Сколько групп на кафедре"));
    model1->setHeaderData(4, Qt::Horizontal, tr("Заведующий кафедрой"));
    model1->setHeaderData(5, Qt::Horizontal, tr("Логин"));
    model1->setHeaderData(6, Qt::Horizontal, tr("Пароль"));
    ui->tableView_2->setModel(model1);
    ui->tableView_2->show();

    for(int i=0;i<model1->rowCount();i++){
    ui->comboBox_15->addItem(model1->data(model1->index(i, 0)).toString());
    }
    for(int i=0;i<model1->rowCount();i++){
    ui->comboBox_11->addItem(model1->data(model1->index(i, 0)).toString());
    }
    for(int i=0;i<model1->rowCount();i++){
    ui->comboBox_t5->addItem(model1->data(model1->index(i, 0)).toString());
    }
    model2->setQuery(QString("SELECT t.id,t.position,t.login,t.password,t.d_id FROM mydb.teacher t JOIN mydb.department d ON t.d_id = d.id WHERE d.login='%1';").arg(login));
    model2->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
    model2->setHeaderData(1, Qt::Horizontal, tr("Должность"));
    model2->setHeaderData(2, Qt::Horizontal, tr("Логин"));
    model2->setHeaderData(3, Qt::Horizontal, tr("Пароль"));
    model2->setHeaderData(4, Qt::Horizontal, tr("Кафедра"));
    ui->tableView_3->setModel(model2);
    ui->tableView_3->show();

    dep = model2->data(model2->index(0, 4)).toString();

    ui->comboBox_t2->addItem(model2->data(model2->index(0, 4)).toString());

    for(int i=0;i<model2->rowCount();i++){
    ui->comboBox_9->addItem(model2->data(model2->index(i, 0)).toString());
    }
    for(int i=0;i<model2->rowCount();i++){
    ui->comboBox_13->addItem(model2->data(model2->index(i, 0)).toString());
    }

    model3->setQuery(QString("SELECT p.id,p.t_id,p.s_id,p.d_id,p.student_group,p.control,p.all_hours FROM mydb.plan p JOIN mydb.teacher t ON t.id = p.t_id JOIN mydb.department d ON t.d_id = d.id WHERE d.login='%1';").arg(login));
    model3->setHeaderData(0, Qt::Horizontal, tr("План"));
    model3->setHeaderData(1, Qt::Horizontal, tr("Преподаватель"));
    model3->setHeaderData(2, Qt::Horizontal, tr("Дисциплина"));
    model3->setHeaderData(3, Qt::Horizontal, tr("Кафедра группы"));
    model3->setHeaderData(4, Qt::Horizontal, tr("Группа"));
    model3->setHeaderData(5, Qt::Horizontal, tr("Форма контроля"));
    model3->setHeaderData(6, Qt::Horizontal, tr("Часы"));
    ui->tableView_4->setModel(model3);
    ui->tableView_4->setColumnHidden(0, true);
    ui->tableView_4->show();

    model4->setQuery(QString("SELECT s.id, s.name,s.lec_hours,s.prac_hours,s.lab_hours FROM mydb.subject s JOIN mydb.plan p ON s.id = p.s_id JOIN mydb.teacher t ON t.id = p.t_id JOIN mydb.department d ON t.d_id = d.id WHERE d.login='%1' GROUP BY s.id;").arg(login));
    model4->setHeaderData(0, Qt::Horizontal, tr("Сокращение"));
    model4->setHeaderData(1, Qt::Horizontal, tr("Дисциплина"));
    model4->setHeaderData(2, Qt::Horizontal, tr("Лекции"));
    model4->setHeaderData(3, Qt::Horizontal, tr("Практики"));
    model4->setHeaderData(4, Qt::Horizontal, tr("Лабораторные"));
    ui->tableView_5->setModel(model4);
    ui->tableView_5->show();

    model5->setQuery(QString("SELECT s.id FROM mydb.subject s;"));
    for(int i=0;i<model5->rowCount();i++){
    ui->comboBox_14->addItem(model5->data(model5->index(i, 0)).toString());
    }

    for(int i=0;i<model5->rowCount();i++){
    ui->comboBox_10->addItem(model5->data(model5->index(i, 0)).toString());
    }

    ui->pushButton_dep_up->setDisabled(true);
    ui->pushButton_dep_del->setDisabled(true);
    ui->pushButton_t_up->setDisabled(true);
    ui->pushButton_t_del->setDisabled(true);
    ui->pushButton_p_up->setDisabled(true);
    ui->pushButton_p_del->setDisabled(true);
    ui->pushButton_s_up->setDisabled(true);
    ui->pushButton_s_del->setDisabled(true);
}

admin::~admin()
{
    delete ui;
}

void admin::on_tableView_2_clicked(const QModelIndex &index)
{
    ui->pushButton_dep_up->setDisabled(false);
    ui->pushButton_dep_del->setDisabled(false);
    idx1 = ui->tableView_2->selectionModel()->currentIndex().row();
    ui->comboBox_dep1->removeItem(0);
    ui->comboBox_dep1->addItem(model1->data(model1->index(idx1, 0)).toString());
    ui->lineEdit_5->setText(model1->data(model1->index(idx1, 1)).toString());
    ui->lineEdit_6->setText(model1->data(model1->index(idx1, 5)).toString());
    ui->lineEdit_7->setText(model1->data(model1->index(idx1, 6)).toString());
}

void admin::on_tableView_3_clicked(const QModelIndex &index)
{
    ui->pushButton_t_up->setDisabled(false);
    ui->pushButton_t_del->setDisabled(false);
    idx2 = ui->tableView_3->selectionModel()->currentIndex().row();
    ui->comboBox_t3->removeItem(0);
    ui->comboBox_t3->addItem(model2->data(model2->index(idx2, 0)).toString());
    ui->comboBox_t4->setCurrentIndex(ui->comboBox_t4->findText(model2->data(model2->index(idx2, 1)).toString()));
    ui->comboBox_t5->setCurrentIndex(ui->comboBox_t5->findText(model2->data(model2->index(idx2, 4)).toString()));
    ui->lineEdit_11->setText(model2->data(model2->index(idx2, 2)).toString());
    ui->lineEdit_12->setText(model2->data(model2->index(idx2, 3)).toString());
}

void admin::on_tableView_4_clicked(const QModelIndex &index)
{
    ui->pushButton_p_up->setDisabled(false);
    ui->pushButton_p_del->setDisabled(false);
    idx3 = ui->tableView_4->selectionModel()->currentIndex().row();
    ui->comboBox_13->setCurrentIndex(ui->comboBox_13->findText(model3->data(model3->index(idx3, 1)).toString()));
    ui->comboBox_14->setCurrentIndex(ui->comboBox_14->findText(model3->data(model3->index(idx3, 2)).toString()));
    ui->comboBox_15->setCurrentIndex(ui->comboBox_15->findText(model3->data(model3->index(idx3, 3)).toString()));

    ui->lineEdit_14->setText(model3->data(model3->index(idx3, 4)).toString());
}

void admin::on_tableView_5_clicked(const QModelIndex &index)
{
    ui->pushButton_s_up->setDisabled(false);
    ui->pushButton_s_del->setDisabled(false);
    idx4 = ui->tableView_5->selectionModel()->currentIndex().row();
    ui->comboBox_17->removeItem(0);
    ui->comboBox_17->addItem(model4->data(model4->index(idx4, 0)).toString());
    ui->lineEdit_20->setText(model4->data(model4->index(idx4, 1)).toString());
    ui->lineEdit_21->setText(model4->data(model4->index(idx4, 2)).toString());
    ui->lineEdit_22->setText(model4->data(model4->index(idx4, 3)).toString());
    ui->lineEdit_23->setText(model4->data(model4->index(idx4, 4)).toString());
}

void admin::on_pushButton_dep_add_clicked()
{
    query.exec(QString("CALL mydb.insert_department('%1','%2','%3','%4');").arg(ui->lineEdit->text())
                                                            .arg(ui->lineEdit_2->text())
                                                            .arg(ui->lineEdit_3->text())
                                                            .arg(ui->lineEdit_4->text()));
}

void admin::on_pushButton_dep_up_t_clicked()
{
    model1->clear();
    model1->setQuery(QString("SELECT * FROM mydb.department d;"));
    model1->setHeaderData(0, Qt::Horizontal, tr("Сокращение"));
    model1->setHeaderData(1, Qt::Horizontal, tr("Название"));
    model1->setHeaderData(2, Qt::Horizontal, tr("Сколько преподавателей на кафедре"));
    model1->setHeaderData(3, Qt::Horizontal, tr("Сколько групп на кафедре"));
    model1->setHeaderData(4, Qt::Horizontal, tr("Заведующий кафедрой"));
    model1->setHeaderData(5, Qt::Horizontal, tr("Логин"));
    model1->setHeaderData(6, Qt::Horizontal, tr("Пароль"));
    ui->tableView_2->setModel(model1);
    ui->tableView_2->show();
    ui->pushButton_dep_up->setDisabled(true);
    ui->pushButton_dep_del->setDisabled(true);
}

void admin::on_pushButton_dep_del_clicked()
{
    query.exec(QString("CALL mydb.delete_department('%1');").arg(model1->data(model1->index(idx1, 0)).toString()));
}

void admin::on_pushButton_dep_up_clicked()
{
    query.exec(QString("CALL mydb.update_department('%1','%2','%3','%4');").arg(ui->comboBox_dep1->currentText())
                                                            .arg(ui->lineEdit_5->text())
                                                            .arg(ui->lineEdit_6->text())
                                                            .arg(ui->lineEdit_7->text()));
}

void admin::on_pushButton_t_add_clicked()
{
    query.exec(QString("CALL mydb.insert_teacher('%1','%2','%3','%4','%5');").arg(ui->lineEdit_8->text())
                                                            .arg(ui->comboBox_t1->currentText())
                                                            .arg(ui->lineEdit_9->text())
                                                            .arg(ui->lineEdit_10->text())
                                                            .arg(ui->comboBox_t2->currentText()));
}

void admin::on_pushButton_t_up_t_clicked()
{
    model2->clear();
    model2->setQuery(QString("SELECT t.id,t.position,t.login,t.password,t.d_id FROM mydb.teacher t JOIN mydb.department d ON t.d_id = d.id WHERE d.login='%1';").arg(log));
    model2->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
    model2->setHeaderData(1, Qt::Horizontal, tr("Должность"));
    model2->setHeaderData(2, Qt::Horizontal, tr("Логин"));
    model2->setHeaderData(3, Qt::Horizontal, tr("Пароль"));
    model2->setHeaderData(4, Qt::Horizontal, tr("Кафедра"));
    ui->tableView_3->setModel(model2);
    ui->tableView_3->show();
    ui->pushButton_t_up->setDisabled(true);
    ui->pushButton_t_del->setDisabled(true);
}

void admin::on_pushButton_t_del_clicked()
{
    query.exec(QString("CALL mydb.delete_teacher('%1');").arg(model2->data(model2->index(idx2, 0)).toString()));
}

void admin::on_pushButton_t_up_clicked()
{
    query.exec(QString("CALL mydb.update_teacher('%1','%2','%3','%4','%5');").arg(ui->comboBox_t3->currentText())
                                                            .arg(ui->comboBox_t4->currentText())
                                                            .arg(ui->lineEdit_11->text())
                                                            .arg(ui->lineEdit_12->text())
                                                            .arg(ui->comboBox_t5->currentText()));
}

void admin::on_pushButton_p_add_clicked()
{
    model5->clear();
    model5->setQuery(QString("SELECT s.lec_hours,s.prac_hours,s.lab_hours FROM mydb.subject s WHERE s.id='%1';").arg(ui->comboBox_10->currentText()));

    query.exec(QString("CALL mydb.insert_plan('%1','%2','%3','%4','%5',%6, %7, %8);").arg(ui->comboBox_9->currentText())
                                                                        .arg(ui->comboBox_10->currentText())
                                                                        .arg(ui->comboBox_11->currentText())
                                                                        .arg(ui->lineEdit_13->text())
                                                                        .arg(ui->comboBox_12->currentText())
                                                                        .arg(model5->data(model5->index(0, 0)).toInt())
                                                                        .arg(model5->data(model5->index(0, 1)).toInt())
                                                                        .arg(model5->data(model5->index(0, 2)).toInt()));
}

void admin::on_pushButton_p_up_t_clicked()
{
    model3->clear();
    model3->setQuery(QString("SELECT p.id,p.t_id,p.s_id,p.d_id,p.student_group,p.control,p.all_hours FROM mydb.plan p JOIN mydb.teacher t ON t.id = p.t_id JOIN mydb.department d ON t.d_id = d.id WHERE d.login='%1';").arg(log));
    model3->setHeaderData(0, Qt::Horizontal, tr("План"));
    model3->setHeaderData(1, Qt::Horizontal, tr("Преподаватель"));
    model3->setHeaderData(2, Qt::Horizontal, tr("Дисциплина"));
    model3->setHeaderData(3, Qt::Horizontal, tr("Кафедра группы"));
    model3->setHeaderData(4, Qt::Horizontal, tr("Группа"));
    model3->setHeaderData(5, Qt::Horizontal, tr("Форма контроля"));
    model3->setHeaderData(6, Qt::Horizontal, tr("Часы"));
    ui->tableView_4->setModel(model3);
    ui->tableView_4->setColumnHidden(0, true);
    ui->tableView_4->show();
    ui->pushButton_p_up->setDisabled(true);
    ui->pushButton_p_del->setDisabled(true);
}

void admin::on_pushButton_p_del_clicked()
{
    query.exec(QString("CALL mydb.delete_plan('%1');").arg(model3->data(model3->index(idx3, 0)).toInt()));
}

void admin::on_pushButton_p_up_clicked()
{
    query.exec(QString("CALL mydb.update_plan(%1,'%2','%3','%4','%5','%6');").arg(model3->data(model3->index(idx3, 0)).toInt())
                                                                        .arg(ui->comboBox_13->currentText())
                                                                        .arg(ui->comboBox_14->currentText())
                                                                        .arg(ui->comboBox_15->currentText())
                                                                        .arg(ui->lineEdit_14->text())
                                                                        .arg(ui->comboBox_16->currentText()));
}

void admin::on_pushButton_s_sdd_clicked()
{
    query.exec(QString("CALL mydb.insert_subject('%1','%2',%3,%4,%5);").arg(ui->lineEdit_15->text())
                                                                        .arg(ui->lineEdit_16->text())
                                                                        .arg(ui->lineEdit_17->text().toInt())
                                                                        .arg(ui->lineEdit_18->text().toInt())
                                                                        .arg(ui->lineEdit_19->text().toInt()));
}

void admin::on_pushButton_s_up_t_clicked()
{
    model4->clear();
    model4->setQuery(QString("SELECT s.id, s.name,s.lec_hours,s.prac_hours,s.lab_hours FROM mydb.subject s JOIN mydb.plan p ON s.id = p.s_id JOIN mydb.teacher t ON t.id = p.t_id JOIN mydb.department d ON t.d_id = d.id WHERE d.login='%1' GROUP BY s.id;").arg(log));
    model4->setHeaderData(0, Qt::Horizontal, tr("Сокращение"));
    model4->setHeaderData(1, Qt::Horizontal, tr("Дисциплина"));
    model4->setHeaderData(2, Qt::Horizontal, tr("Лекции"));
    model4->setHeaderData(3, Qt::Horizontal, tr("Практики"));
    model4->setHeaderData(4, Qt::Horizontal, tr("Лабораторные"));
    ui->tableView_5->setModel(model4);
    ui->tableView_5->show();
    ui->pushButton_s_up->setDisabled(true);
    ui->pushButton_s_del->setDisabled(true);
}

void admin::on_pushButton_s_del_clicked()
{
    query.exec(QString("CALL mydb.delete_subject('%1');").arg(model4->data(model4->index(idx4, 0)).toString()));
}

void admin::on_pushButton_s_up_clicked()
{
    query.exec(QString("CALL mydb.update_subject('%1','%2',%3,%4,%5);").arg(ui->comboBox_17->currentText())
                                                                        .arg(ui->lineEdit_20->text())
                                                                        .arg(ui->lineEdit_21->text().toInt())
                                                                        .arg(ui->lineEdit_22->text().toInt())
                                                                        .arg(ui->lineEdit_23->text().toInt()));
}

void admin::on_lineEdit_selectionChanged()
{
    ui->lineEdit->setText("");
}

void admin::on_lineEdit_2_selectionChanged()
{
    ui->lineEdit_2->setText("");
}

void admin::on_lineEdit_3_selectionChanged()
{
    ui->lineEdit_3->setText("");
}

void admin::on_lineEdit_4_selectionChanged()
{
    ui->lineEdit_4->setText("");
}

void admin::on_lineEdit_8_selectionChanged()
{
    ui->lineEdit_8->setText("");
}

void admin::on_lineEdit_9_selectionChanged()
{
    ui->lineEdit_9->setText("");
}

void admin::on_lineEdit_10_selectionChanged()
{
    ui->lineEdit_10->setText("");
}

void admin::on_lineEdit_13_selectionChanged()
{
    ui->lineEdit_13->setText("");
}

void admin::on_lineEdit_15_selectionChanged()
{
    ui->lineEdit_15->setText("");
}

void admin::on_lineEdit_16_selectionChanged()
{
    ui->lineEdit_16->setText("");
}

void admin::on_lineEdit_17_selectionChanged()
{
    ui->lineEdit_17->setText("");
}

void admin::on_lineEdit_18_selectionChanged()
{
    ui->lineEdit_18->setText("");
}

void admin::on_lineEdit_19_selectionChanged()
{
    ui->lineEdit_19->setText("");
}

void admin::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if (ui->comboBox->currentIndex()==0)
    {
        model5->clear();
        ui->tableView->setModel(model5);
        ui->textBrowser->setText("");
    }
    if (ui->comboBox->currentIndex()==1)
    {
        model5->clear();
        model5->setQuery(QString("SELECT s.name, p.all_hours,CASE WHEN s.lec_hours=0 THEN 'Нет занятий' ELSE CAST(s.lec_hours AS varchar(3)) END lec_hours, CASE  WHEN s.prac_hours=0 THEN 'Нет занятий' ELSE CAST(s.prac_hours AS varchar(3)) END prac_hours, CASE  WHEN s.lab_hours=0 THEN 'Нет занятий' ELSE CAST(s.lab_hours AS varchar(3)) END lab_hours FROM mydb.subject s JOIN mydb.plan p ON s.id = p.s_id GROUP BY s.name, p.all_hours,s.lec_hours,s.prac_hours,s.lab_hours;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("Дисциплина"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Часы"));
        model5->setHeaderData(2, Qt::Horizontal, tr("Лекции"));
        model5->setHeaderData(3, Qt::Horizontal, tr("Практики"));
        model5->setHeaderData(4, Qt::Horizontal, tr("Лабораторные"));
        ui->tableView->setModel(model5);
        ui->tableView->show();
        ui->textBrowser->setText("Выводит дисциплины и сколько часов по ним, если часов 0, то выводит надпись, что нет занятий такого типа");
    }
    if (ui->comboBox->currentIndex()==2)
    {
        model5->clear();
        model5->setQuery(QString("SELECT * FROM mydb.work_view;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Должность"));
        model5->setHeaderData(2, Qt::Horizontal, tr(""));
        model5->setHeaderData(3, Qt::Horizontal, tr("Дисциплина"));
        model5->setHeaderData(4, Qt::Horizontal, tr(""));
        model5->setHeaderData(5, Qt::Horizontal, tr("Группа"));
        model5->setHeaderData(6, Qt::Horizontal, tr("Форма контроля"));
        model5->setHeaderData(7, Qt::Horizontal, tr("Часы"));
        ui->tableView->setModel(model5);
        ui->tableView->setColumnHidden(2, true);
        ui->tableView->setColumnHidden(4, true);
        ui->tableView->show();
        ui->textBrowser->setText("Многотабличное представление с критерием упорядочетельности");
    }
    if (ui->comboBox->currentIndex()==3)
    {
        model5->clear();
        model5->setQuery(QString("Select ROUND(AVG(p.all_hours),1), (Select ROUND(AVG(s.lec_hours),1) FROM mydb.subject s), (Select ROUND(AVG(s.prac_hours),1) FROM mydb.subject s), (Select ROUND(AVG(s.lab_hours),1) FROM mydb.subject s) FROM mydb.plan p;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("Среднее общее"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Среднее лекций"));
        model5->setHeaderData(2, Qt::Horizontal, tr("Среднее практик"));
        model5->setHeaderData(3, Qt::Horizontal, tr("Среднее лабораторных"));
        ui->tableView->setModel(model5);
        ui->tableView->show();
        ui->textBrowser->setText("Среднее количество часов");
    }
    if (ui->comboBox->currentIndex()==4)
    {
        model5->clear();
        model5->setQuery(QString("SELECT d.name,t.id,t.position,p.s_id,p.student_group FROM (SELECT id, position, d_id FROM mydb.teacher  WHERE position='Заведующий кафедрой') AS t JOIN mydb.plan p ON t.id=p.t_id JOIN mydb.department d ON d.id=t.d_id WHERE d.id='КБ-1';"));
        model5->setHeaderData(0, Qt::Horizontal, tr("Кафедра"));
        model5->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
        model5->setHeaderData(2, Qt::Horizontal, tr("Должность"));
        model5->setHeaderData(3, Qt::Horizontal, tr("Дисциплина"));
        model5->setHeaderData(4, Qt::Horizontal, tr("Группа"));
        ui->tableView->setModel(model5);
        ui->tableView->show();
        ui->textBrowser->setText("Нагрузка заведующего кафедрой КБ-1");
    }
    if (ui->comboBox->currentIndex()==5)
    {
        model5->clear();
        model5->setQuery(QString("Select s.name, p.all_hours FROM mydb.subject s JOIN mydb.plan p ON s.id=p.s_id WHERE p.all_hours<(select AVG(p.all_hours) FROM mydb.plan p) GROUP BY s.name,p.all_hours;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("Название"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Часы"));
        ui->tableView->setModel(model5);
        ui->tableView->show();
        ui->textBrowser->setText("Дисциплины, у которых общее кол-во часов меньше среднего");
    }
    if (ui->comboBox->currentIndex()==6)
    {
        model5->clear();
        model5->setQuery(QString("SELECT t.id, t.d_id, (SELECT COUNT(*) FROM mydb.plan p WHERE t.id=p.t_id) AS sum_plan FROM mydb.teacher t ORDER BY sum_plan DESC;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Кафедра"));
        model5->setHeaderData(0, Qt::Horizontal, tr("Кол-во нагрузки"));
        ui->tableView->setModel(model5);
        ui->tableView->show();
        ui->textBrowser->setText("Сколько нагрузки у каждого преподавателя");
    }
    if (ui->comboBox->currentIndex()==7)
    {
        model5->clear();
        model5->setQuery(QString("Select t.d_id, SUM(pp.c) FROM mydb.teacher t, LATERAL(select COUNT(*) AS c FROM mydb.plan p WHERE p.t_id=t.id) pp GROUP BY t.d_id;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("Кафедра"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Кол-во нагрузки"));
        ui->tableView->setModel(model5);
        ui->tableView->show();
        ui->textBrowser->setText("Сколько нагрузки у всех преподавателей с кафедры вместе");
    }
    if (ui->comboBox->currentIndex()==8)
    {
        model5->clear();
        model5->setQuery(QString("Select t.d_id, t.id FROM mydb.teacher t WHERE (select COUNT(*) FROM mydb.plan p WHERE p.t_id=t.id)=0 ORDER BY t.d_id;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("Кафедра"));
        model5->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
        ui->tableView->setModel(model5);
        ui->tableView->show();
        ui->textBrowser->setText("Кто на кафедре не имеет нагрузки");
    }
    if (ui->comboBox->currentIndex()==9)
    {
        model5->clear();
        model5->setQuery(QString("SELECT t.id AS name, COUNT(*) FROM mydb.plan p JOIN mydb.teacher t ON p.t_id=t.id GROUP BY t.id HAVING COUNT(*)<10;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Кол-во нагрузки"));
        ui->tableView->setModel(model5);
        ui->tableView->show();
        ui->textBrowser->setText("Преподаватели, у которых количество нагрузки меньше 10");
    }
    if (ui->comboBox->currentIndex()==10)
    {
        model5->clear();
        model5->setQuery(QString("SELECT t.id AS name FROM mydb.teacher t WHERE 'РПОЗОС'=any (SELECT p.s_id FROM mydb.plan p WHERE t.id=p.t_id AND p.d_id='КБ-2');"));
        model5->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
        ui->tableView->setModel(model5);
        ui->tableView->show();
        ui->textBrowser->setText("Преподаватели, которые ведут дисциплину РПОЗОС студентам с кафедры КБ-2");
    }
    if (ui->comboBox->currentIndex()==11)
    {
        model5->clear();
        model5->setQuery(QString("SELECT * FROM mydb.show_group('%1');").arg(dep));
        model5->setHeaderData(0, Qt::Horizontal, tr("Группа"));
        ui->tableView->setModel(model5);
        ui->tableView->show();
        ui->textBrowser->setText("Группы, которым ведут занятия преподаватели с кафедры "+dep);
    }
}

void admin::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    if (ui->comboBox_2->currentIndex()==0)
    {
        model5->clear();
        model5->setQuery(QString("SELECT * FROM mydb.work_view;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Должность"));
        model5->setHeaderData(2, Qt::Horizontal, tr(""));
        model5->setHeaderData(3, Qt::Horizontal, tr("Дисциплина"));
        model5->setHeaderData(4, Qt::Horizontal, tr(""));
        model5->setHeaderData(5, Qt::Horizontal, tr("Группа"));
        model5->setHeaderData(6, Qt::Horizontal, tr("Форма контроля"));
        model5->setHeaderData(7, Qt::Horizontal, tr("Часы"));
        ui->tableView->setModel(model5);
        ui->tableView->setColumnHidden(2, true);
        ui->tableView->setColumnHidden(4, true);
        ui->tableView->show();
    }
    if (ui->comboBox_2->currentIndex()==1)
    {
        model5->clear();
        model5->setQuery(QString("SELECT * FROM mydb.work_view ORDER BY fio;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Должность"));
        model5->setHeaderData(2, Qt::Horizontal, tr(""));
        model5->setHeaderData(3, Qt::Horizontal, tr("Дисциплина"));
        model5->setHeaderData(4, Qt::Horizontal, tr(""));
        model5->setHeaderData(5, Qt::Horizontal, tr("Группа"));
        model5->setHeaderData(6, Qt::Horizontal, tr("Форма контроля"));
        model5->setHeaderData(7, Qt::Horizontal, tr("Часы"));
        ui->tableView->setModel(model5);
        ui->tableView->setColumnHidden(2, true);
        ui->tableView->setColumnHidden(4, true);
        ui->tableView->show();
    }
    if (ui->comboBox_2->currentIndex()==2)
    {
        model5->clear();
        model5->setQuery(QString("SELECT * FROM mydb.work_view ORDER BY position;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Должность"));
        model5->setHeaderData(2, Qt::Horizontal, tr(""));
        model5->setHeaderData(3, Qt::Horizontal, tr("Дисциплина"));
        model5->setHeaderData(4, Qt::Horizontal, tr(""));
        model5->setHeaderData(5, Qt::Horizontal, tr("Группа"));
        model5->setHeaderData(6, Qt::Horizontal, tr("Форма контроля"));
        model5->setHeaderData(7, Qt::Horizontal, tr("Часы"));
        ui->tableView->setModel(model5);
        ui->tableView->setColumnHidden(2, true);
        ui->tableView->setColumnHidden(4, true);
        ui->tableView->show();
    }
    if (ui->comboBox_2->currentIndex()==3)
    {
        model5->clear();
        model5->setQuery(QString("SELECT * FROM mydb.work_view ORDER BY subject;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Должность"));
        model5->setHeaderData(2, Qt::Horizontal, tr(""));
        model5->setHeaderData(3, Qt::Horizontal, tr("Дисциплина"));
        model5->setHeaderData(4, Qt::Horizontal, tr(""));
        model5->setHeaderData(5, Qt::Horizontal, tr("Группа"));
        model5->setHeaderData(6, Qt::Horizontal, tr("Форма контроля"));
        model5->setHeaderData(7, Qt::Horizontal, tr("Часы"));
        ui->tableView->setModel(model5);
        ui->tableView->setColumnHidden(2, true);
        ui->tableView->setColumnHidden(4, true);
        ui->tableView->show();
    }
    if (ui->comboBox_2->currentIndex()==4)
    {
        model5->clear();
        model5->setQuery(QString("SELECT * FROM mydb.work_view ORDER BY student_group;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Должность"));
        model5->setHeaderData(2, Qt::Horizontal, tr(""));
        model5->setHeaderData(3, Qt::Horizontal, tr("Дисциплина"));
        model5->setHeaderData(4, Qt::Horizontal, tr(""));
        model5->setHeaderData(5, Qt::Horizontal, tr("Группа"));
        model5->setHeaderData(6, Qt::Horizontal, tr("Форма контроля"));
        model5->setHeaderData(7, Qt::Horizontal, tr("Часы"));
        ui->tableView->setModel(model5);
        ui->tableView->setColumnHidden(2, true);
        ui->tableView->setColumnHidden(4, true);
        ui->tableView->show();
    }
    if (ui->comboBox_2->currentIndex()==5)
    {
        model5->clear();
        model5->setQuery(QString("SELECT * FROM mydb.work_view ORDER BY control;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Должность"));
        model5->setHeaderData(2, Qt::Horizontal, tr(""));
        model5->setHeaderData(3, Qt::Horizontal, tr("Дисциплина"));
        model5->setHeaderData(4, Qt::Horizontal, tr(""));
        model5->setHeaderData(5, Qt::Horizontal, tr("Группа"));
        model5->setHeaderData(6, Qt::Horizontal, tr("Форма контроля"));
        model5->setHeaderData(7, Qt::Horizontal, tr("Часы"));
        ui->tableView->setModel(model5);
        ui->tableView->setColumnHidden(2, true);
        ui->tableView->setColumnHidden(4, true);
        ui->tableView->show();
    }
    if (ui->comboBox_2->currentIndex()==6)
    {
        model5->clear();
        model5->setQuery(QString("SELECT * FROM mydb.work_view ORDER BY all_hours;"));
        model5->setHeaderData(0, Qt::Horizontal, tr("ФИО"));
        model5->setHeaderData(1, Qt::Horizontal, tr("Должность"));
        model5->setHeaderData(2, Qt::Horizontal, tr(""));
        model5->setHeaderData(3, Qt::Horizontal, tr("Дисциплина"));
        model5->setHeaderData(4, Qt::Horizontal, tr(""));
        model5->setHeaderData(5, Qt::Horizontal, tr("Группа"));
        model5->setHeaderData(6, Qt::Horizontal, tr("Форма контроля"));
        model5->setHeaderData(7, Qt::Horizontal, tr("Часы"));
        ui->tableView->setModel(model5);
        ui->tableView->setColumnHidden(2, true);
        ui->tableView->setColumnHidden(4, true);
        ui->tableView->show();
    }
}

void admin::on_comboBox_14_activated(int index)
{
    if(ui->comboBox_14->count() > 0){
            for(int i = 0; i < ui->comboBox_14->count(); i++) ui->comboBox_14->removeItem(i);
        }
    model5->clear();
    model5->setQuery(QString("SELECT s.id FROM mydb.subject s;"));
    for(int i=0;i<model5->rowCount();i++){
    ui->comboBox_14->addItem(model5->data(model5->index(i, 0)).toString());
    }
}
