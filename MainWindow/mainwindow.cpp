#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Museum Project");
    /* Cоздание объект для работы с базой данных и инициализация подключения к базе данных
     * */
    db = new DataBase();
    db->connectToDataBase();

    /* Инициализируем модели для представления данных
     * с заданием названий колонок
     * */
    this->setupModel(EVENT,
                     QStringList() << trUtf8("id")
                                   << trUtf8("Название")
                                   << trUtf8("Тип")
                                   << trUtf8("Расположение")
                                   << trUtf8("Краткая информация")
                                   << trUtf8("Официальный сайт")
                                   << trUtf8("Возраст")
                                   << trUtf8("Дата"));
    /* Инициализируем внешний вид таблицы с данными
     * */
    this->createUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Производим инициализацию модели представления данных
     * */
    modelEvent = new QSqlTableModel(this);
    modelEvent->setTable(tableName);
    modelEvent->select();
    /* Устанавливаем названия колонок в таблице с сортировкой данных
     * */

    for(int i = 0, j = 0; i < modelEvent->columnCount(); ++i, ++j){
        modelEvent->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
}

void MainWindow::createUI()
{
    ui->EventTableView->setModel(modelEvent);
    ui->EventTableView->setColumnHidden(0, true);                              // Скрыть столбец ID
    ui->EventTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->EventTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->EventTableView->resizeColumnsToContents();
    ui->EventTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->EventTableView->horizontalHeader()->setStretchLastSection(true);

    // Устанавливаем Контекстное Меню
    ui->EventTableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->EventTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_editEventButton_triggered()));
    // Подключаем СЛОТ вызова контекстного меню
    connect(ui->EventTableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
}

/* Метод для активации диалога добавления записей
 * */
void MainWindow::on_addEventTable_triggered()
{
    /* Создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных
     * */
    DialogAddEvent* addEventDialog = new DialogAddEvent();
    connect(addEventDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    addEventDialog->setWindowTitle(trUtf8("Добавить запись"));
    addEventDialog->exec();
}

/* Метод для активации диалога редактирования записей
 * */
void MainWindow::on_editEventButton_triggered()
{
    /* Также создаем диалог и подключаем его сигнал завершения работы
     * к слоту обновления вида модели представления данных, но передаём
     * в качестве параметров строку записи
     * */
    DialogAddEvent* addEventDialog = new DialogAddEvent(ui->EventTableView->selectionModel()->currentIndex().row());
    connect(addEventDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

    /* Выполняем запуск диалогового окна
     * */
    addEventDialog->setWindowTitle(trUtf8("Редактировать запись"));
    addEventDialog->exec();
}

/* Метод для удаления записей
 * */
void MainWindow::on_deleteEventButton_triggered()
{
    /* Выясняем, какая из строк была выбрана
     * */
    int row = ui->EventTableView->selectionModel()->currentIndex().row();
    /* Проверяем, что строка была действительно выбрана
     * */
    if(row >= 0)
    {
        /* Задаём вопрос, стоит ли действительно удалять запись.
         * При положительном ответе удаляем запись
         * */
        if (QMessageBox::warning(this,
                                 trUtf8("Удаление записи"),
                                 trUtf8("Вы уверены, что хотите удалить эту запись?"),
                                 QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        {
            /* При отрицательном ответе делаем откат действий
             * и закрываем диалог без удаления записи
             * */
            QSqlDatabase::database().rollback();
            return;
        }
        else
        {
            /* В противном случае производим удаление записи.
             * При успешном удалении обновляем таблицу.
             * */
            if(!modelEvent->removeRow(row))
            {
                QMessageBox::warning(this, trUtf8("Уведомление"),
                                     trUtf8("Не удалось удалить запись\n"
                                            "Возможно она используется другими таблицами\n"
                                            "Проверьте все зависимости и повторите попытку"));
            }
            modelEvent->select();
            ui->EventTableView->setCurrentIndex(modelEvent->index(-1, -1));
        }
    }
}

void MainWindow::slotCustomMenuRequested(QPoint pos)
{
    /* Создаем объект контекстного меню */
    QMenu* menu = new QMenu(this);
    /* Создаём действия для контекстного меню */
    QAction* editEvent = new QAction(trUtf8("Редактировать"), this);
    QAction* deleteEvent = new QAction(trUtf8("Удалить"), this);
    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(editEvent, SIGNAL(triggered()), this, SLOT(on_editEventButton_triggered()));     // Обработчик вызова диалога редактирования
    connect(deleteEvent, SIGNAL(triggered()), this, SLOT(on_deleteEventButton_triggered())); // Обработчик удаления записи
    /* Устанавливаем действия в меню */
    menu->addAction(editEvent);
    menu->addAction(deleteEvent);
    /* Вызываем контекстное меню */
    menu->popup(ui->EventTableView->viewport()->mapToGlobal(pos));
}

/* Слот обновления модели представления данных
 * */
void MainWindow::slotUpdateModels()
{
    modelEvent->select();
    ui->EventTableView->resizeColumnsToContents();
}

/* Метод для поиска по названию
 * */
void MainWindow::on_findPushButton_clicked()
{
    modelEvent->setFilter(QString(EVENT_NAME " = '%1' ").arg(ui->FindLineEdit->text()));
    modelEvent->select();
}

/* Метод для очистки поиска
 * */
void MainWindow::on_clearPushButton_clicked()
{
    modelEvent->setFilter(0);
    modelEvent->select();
}

/* Метод для закрытия окна
 * */
void MainWindow::on_exitAction_triggered()
{
    MainWindow::close();
}

/* Метод для вызова справки
 * */
void MainWindow::on_aboutAction_triggered()
{
    HelpMenu* addHelpMenu = new HelpMenu();
    connect(addHelpMenu, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));
    addHelpMenu->show();
}

/* Метод для задания пути до БД
 * */
void MainWindow::on_getPathAction_triggered()
{
    db->setPathDB(QFileDialog::getOpenFileName(nullptr, trUtf8("Выберите файл:"), trUtf8("./"), trUtf8("Файл базы-данных (*.db)")));
    //qDebug() <<  db->getPathDB();
}
