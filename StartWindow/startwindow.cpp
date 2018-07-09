#include "startwindow.h"
#include "ui_startwindow.h"
#include "MainWindow/mainwindow.h"
#include "HelpMenu/helpmenu.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Museum Project");
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_museumPushButton_clicked()
{
    /* Создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных
     * */
    MainWindow* addMainWindow = new MainWindow();
    connect(addMainWindow, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));
    addMainWindow->show();
}

void StartWindow::on_eventPushButton_clicked()
{
    MainWindow* addMainWindow = new MainWindow();
    connect(addMainWindow, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));
    addMainWindow->show();
}

void StartWindow::on_aboutPushButton_clicked()
{
    HelpMenu* addHelpMenu = new HelpMenu();
    connect(addHelpMenu, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));
    addHelpMenu->show();
}

void StartWindow::on_exitPushButton_clicked()
{
    StartWindow::close();
}

