#include "DialogAddEvent.h"
#include "ui_DialogAddEvent.h"
#include <QDebug>

DialogAddEvent::DialogAddEvent(int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddEvent)
{
    ui->setupUi(this);

    /* Метода для инициализации модели,
     * из которой будут транслироваться данные
     * */
    setupModel();

    /* Если строка не задана, то есть равна -1,
     * тогда диалог работает по принципу создания новой записи.
     * А именно, в модель вставляется новая строка и работа ведётся с ней.
     * */
    if(id == -1)
    {
        model->insertRow(model->rowCount(QModelIndex()));
        mapper->toLast();
    /* В противном случае диалог настраивается на заданную запись
     * */
    }
    else
    {
        for (int row = 0; row < model->rowCount(); ++row)
              {
                  if (model->data(model->index(row, 0)).toInt() == id)
                  {
                      mapper->setCurrentModelIndex(model->index(row, 0));
                  }
              }
    }

    createUI();
}

DialogAddEvent::~DialogAddEvent()
{
    delete ui;
}

/* Метод настройки модели данных и mapper
 * */
void DialogAddEvent::setupModel()
{
    /* Инициализируем модель и делаем выборку из неё
     * */
    model = new QSqlTableModel(this);
    model->setTable(EVENT);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    /* Инициализируем mapper и привязываем
     * поля данных к объектам LineEdit
     * */
    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->NameLineEdit, 1);
    mapper->addMapping(ui->TypeComboBox, 2);
    mapper->addMapping(ui->LocationLineEdit, 3);
    mapper->addMapping(ui->InformationPlainTextEdit, 4);
    mapper->addMapping(ui->OfficialSiteLineEdit, 5);
    mapper->addMapping(ui->AgeComboBox, 6);
    mapper->addMapping(ui->DateTimeEdit, 7);

    /* Ручное подтверждение изменения данных
     * через mapper
     * */
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    /* Подключаем коннекты от кнопок пролистывания
     * к прилистыванию модели данных в mapper
     * */
    connect(ui->previousButton, SIGNAL(clicked()), mapper, SLOT(toPrevious()));
    connect(ui->nextButton, SIGNAL(clicked()), mapper, SLOT(toNext()));
    /* При изменении индекса в mapper изменяем состояние кнопок
     * */
    connect(mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));
}

/* Метод для установки валидатора
 * */
void DialogAddEvent::createUI()
{

}

void DialogAddEvent::on_buttonBox_accepted()
{
    /* SQL-запрос для проверки существования записи
     * с такими же учетными данными.
     * Если запись не существует или находится лишь индекс
     * редактируемой в данный момент записи,
     * то диалог позволяет вставку записи в таблицу данных
     * */
    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT " EVENT_NAME " FROM " EVENT " WHERE ( " EVENT_NAME " = '%1' ) AND id NOT LIKE '%3' )")
            .arg(ui->NameLineEdit->text(), model->data(model->index(mapper->currentIndex(),0), Qt::DisplayRole).toString());

    query.prepare(str);
    query.exec();
    query.next();

    /* Если запись существует, то диалог вызывает
     * предупредительное сообщение
     * */
    if(query.value(0) != 0)
        QMessageBox::information(this, trUtf8("Ошибка!"), trUtf8("Событие с таким именем уже существует!"));
    /* В противном случае производится вставка новых данных в таблицу
     * и диалог завершается с передачей сигнала для обновления
     * таблицы в главном окне
     * */
    else
    {
        mapper->submit();
        model->submitAll();
        emit signalReady();
        this->close();
    }
}

/* Метод изменения состояния активности кнопок пролистывания
 * */
void DialogAddEvent::updateButtons(int row)
{
    /* В том случае, если мы достигаем одного из крайних (самый первый или
     * самый последний) из индексов в таблице данных,
     * то мы изменяем состояние соответствующей кнопки на
     * состояние неактивна
     * */
    ui->previousButton->setEnabled(row > 0);
    ui->nextButton->setEnabled(row < model->rowCount() - 1);
}
