#include "helpmenu.h"
#include "ui_helpmenu.h"

HelpMenu::HelpMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpMenu)
{
    ui->setupUi(this);
}

HelpMenu::~HelpMenu()
{
    delete ui;
}

void HelpMenu::on_OKButton_clicked()
{
    HelpMenu::close();
}
