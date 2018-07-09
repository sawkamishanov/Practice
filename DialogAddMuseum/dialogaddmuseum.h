#ifndef DialogAddMuseum_H
#define DialogAddMuseum_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>

#include <DataBase/database.h>

namespace Ui {
class DialogAddMuseum;
}

class DialogAddMuseum : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddMuseum(int row = -1, QWidget *parent = 0);
    ~DialogAddMuseum();

signals:
    void signalReady();

private slots:
    void on_buttonBox_accepted();
    void updateButtons(int row);

private:
    Ui::DialogAddMuseum *ui;
    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

private:
    void setupModel();
    void createUI();
    void accept();
};

#endif // DialogAddMuseum_H
