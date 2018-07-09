#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = 0);
    ~StartWindow();

private slots:
    void on_museumPushButton_clicked();

    void on_eventPushButton_clicked();

    void on_exitPushButton_clicked();

    void on_aboutPushButton_clicked();

private:
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H
