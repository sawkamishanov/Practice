#ifndef HELPMENU_H
#define HELPMENU_H

#include <QWidget>

namespace Ui {
class HelpMenu;
}

class HelpMenu : public QWidget
{
    Q_OBJECT

public:
    explicit HelpMenu(QWidget *parent = 0);
    ~HelpMenu();

private slots:
    void on_OKButton_clicked();

private:
    Ui::HelpMenu* ui;
};

#endif // HELPMENU_H
