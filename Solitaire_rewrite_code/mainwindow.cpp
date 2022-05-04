#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("Menu");
    this->setWindowIcon( QIcon( merge_filepath("pictures/icon.png")));
    this->setMinimumSize(400,700);
    this->setMaximumSize(400,700);
    this->setStyleSheet("QMainWindow {background: 'white';}");


    QLabel *qlabel_GifLogo = new QLabel(this);
    qlabel_GifLogo->setGeometry(0,0,400,300);//ui's top left coordinate: x=0 y=0
    QMovie *qmovie_GifLogo = new QMovie( merge_filepath("pictures/mainlogo.gif"));
    qlabel_GifLogo->setMovie(qmovie_GifLogo);
    qmovie_GifLogo->start();


    QLabel *qlabel_tital = new QLabel(this);
    qlabel_tital->setGeometry(25,250,350,185);
    QPixmap qpixmap_tital( merge_filepath("pictures/tital.png"));
    qlabel_tital->setPixmap( qpixmap_tital);
    qlabel_tital->show();

    // Create the button, make "this" the parent
    qbutton_Start = new QPushButton(this);
    qbutton_Start->setGeometry(100,600,200,50);
    qbutton_Start->setText("START");
    // Connect button signal to appropriate slot
    connect(qbutton_Start, &QPushButton::released, this, &MainWindow::clicked_startButton);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clicked_startButton()
{
  table_CardTable = new Table();
  table_CardTable->show();
}

