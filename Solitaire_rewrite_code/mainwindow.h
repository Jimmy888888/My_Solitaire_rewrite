#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMovie>
#include <QLabel>
#include <QObject>
#include <QIcon>
#include <QPushButton>
#include <QPixmap>
#include <QString>

#include "table.h"
#include "frequently_used.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton *qbutton_Start;
    Table *table_CardTable;

private slots:
    void clicked_startButton();

};
#endif // MAINWINDOW_H
