#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>

#include <DataBase/database.h>
#include <DialogWindow/DialogAddEvent.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addEventButton_clicked();
    void slotUpdateModels();
    /* К СЛОТу по редактировнию записи
     * добавляем СЛОТ по удалению записи.
     * Также добавляем СЛОТ для обработки вызова контекстного меню
     * */
    void slotEditRecord();
    void slotRemoveRecord();
    void slotCustomMenuRequested(QPoint pos);

private:
    Ui::MainWindow *ui;
    DataBase *db;
    QSqlTableModel *modelEvent;

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // MAINWINDOW_H
