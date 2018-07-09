#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QFileDialog>

#include "DataBase/database.h"
#include "DialogAddEvent/DialogAddEvent.h"
#include "HelpMenu/helpmenu.h"

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
    void slotUpdateModels();
    /*
     * Слот для обработки вызова контекстного меню
     * */
    void slotCustomMenuRequested(QPoint pos);

    /*
     * Слоты для:
     * 1. Добавления записи
     * 2. Для редактирования записи
     * 3. Для удаления записи
     * 4. Для поиска записи
     * 5. Для очистки окна поиска
     * 6. Для закрытия окна
     * 7. Для вызова справки
     * 8. Для выбора пути БД
     * */
    void on_addEventTable_triggered();
    void on_editEventButton_triggered();
    void on_deleteEventButton_triggered();
    void on_findPushButton_clicked();
    void on_clearPushButton_clicked();
    void on_exitAction_triggered();
    void on_aboutAction_triggered();
    void on_getPathAction_triggered();

private:
    Ui::MainWindow* ui;
    DataBase* db;
    QSqlTableModel* modelEvent;

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // MAINWINDOW_H
