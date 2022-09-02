#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QtSql/QSqlQuery>

namespace Ui {
class admin;
}

class admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit admin(QString login, QWidget *parent = nullptr);
    ~admin();

private slots:
    void on_tableView_2_clicked(const QModelIndex &index);

    void on_pushButton_dep_add_clicked();

    void on_pushButton_dep_up_t_clicked();

    void on_pushButton_dep_del_clicked();

    void on_pushButton_dep_up_clicked();

    void on_pushButton_t_add_clicked();

    void on_pushButton_t_up_t_clicked();

    void on_pushButton_t_del_clicked();

    void on_pushButton_t_up_clicked();

    void on_pushButton_p_add_clicked();

    void on_pushButton_p_up_t_clicked();

    void on_pushButton_p_del_clicked();

    void on_pushButton_p_up_clicked();

    void on_pushButton_s_sdd_clicked();

    void on_pushButton_s_up_t_clicked();

    void on_pushButton_s_del_clicked();

    void on_pushButton_s_up_clicked();

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_tableView_4_clicked(const QModelIndex &index);

    void on_tableView_5_clicked(const QModelIndex &index);

    void on_lineEdit_selectionChanged();

    void on_lineEdit_2_selectionChanged();

    void on_lineEdit_3_selectionChanged();

    void on_lineEdit_4_selectionChanged();

    void on_lineEdit_8_selectionChanged();

    void on_lineEdit_9_selectionChanged();

    void on_lineEdit_10_selectionChanged();

    void on_lineEdit_13_selectionChanged();

    void on_lineEdit_15_selectionChanged();

    void on_lineEdit_16_selectionChanged();

    void on_lineEdit_17_selectionChanged();

    void on_lineEdit_18_selectionChanged();

    void on_lineEdit_19_selectionChanged();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_comboBox_14_activated(int index);

private:
    Ui::admin *ui;
    QString log;
    QString dep;
    int idx1;
    int idx2;
    int idx3;
    int idx4;
    QSqlQueryModel *model1 = new QSqlQueryModel;
    QSqlQueryModel *model2 = new QSqlQueryModel;
    QSqlQueryModel *model3 = new QSqlQueryModel;
    QSqlQueryModel *model4 = new QSqlQueryModel;
    QSqlQueryModel *model5 = new QSqlQueryModel;
    QSqlQueryModel *model6 = new QSqlQueryModel;
    QSqlQuery query;
};

#endif // ADMIN_H
