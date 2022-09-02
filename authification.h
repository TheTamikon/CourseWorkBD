#ifndef AUTHIFICATION_H
#define AUTHIFICATION_H

#include <QMainWindow>
struct Login{
    QString log;
    QString pas;
};
namespace Ui {
class authification;
}

class authification : public QMainWindow
{
    Q_OBJECT

public:
    explicit authification(QWidget *parent = nullptr);
    ~authification();

private slots:
    void on_pushButton_clicked();

private:
    Ui::authification *ui;
};

#endif // AUTHIFICATION_H
