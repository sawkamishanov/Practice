#ifndef DialogAddEvent_H
#define DialogAddEvent_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>

#include <DataBase/database.h>

namespace Ui {
class DialogAddEvent;
}

class DialogAddEvent : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddEvent(int row = -1, QWidget *parent = 0);
    ~DialogAddEvent();

signals:
    void signalReady();

private slots:
    void on_buttonBox_accepted();
    void updateButtons(int row);

private:
    Ui::DialogAddEvent *ui;
    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

private:
    void setupModel();
    void createUI();
    void accept();
};

#endif // DialogAddEvent_H
