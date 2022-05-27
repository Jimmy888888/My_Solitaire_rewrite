#include "scoreboard.h"

Scoreboard::Scoreboard(int int_Club, int int_Diamond, int int_Spade, int int_Heart, int int_TotalScore)
{
    this->setWindowTitle("Your Score");
    this->setMinimumSize(400,200);
    this->setMaximumSize(400,200);
    this->setStyleSheet("QWidget {background: 'white';}");
    //opacity 0~1
    this->setWindowOpacity(0.95);

    //display score
    //show how many club
    QPixmap qpixmap_Club(merge_filepath("pictures/club.png"));
    QLabel *qlabel_LogoClub = new QLabel(this);
    qlabel_LogoClub->setPixmap(qpixmap_Club);
    qlabel_LogoClub->setGeometry(10,5,30,30);
    QString qstring_Club = "Club : ";
    qstring_Club = qstring_Club + QString::number(int_Club);
    qlabel_Club = new QLabel(this);
    qlabel_Club->setGeometry(50,10,300,20);
    qlabel_Club->setText(qstring_Club);
    qlabel_Club->setStyleSheet("QLabel { font-size: 20pt; color:black;}");
    //show how many diamond
    QPixmap qpixmap_Diamond(merge_filepath("pictures/diamond.png"));
    QLabel *qlabel_LogoDiamond = new QLabel(this);
    qlabel_LogoDiamond->setPixmap(qpixmap_Diamond);
    qlabel_LogoDiamond->setGeometry(10,39,30,30);
    QString qstring_Diamond = "Diamond : ";
    qstring_Diamond = qstring_Diamond + QString::number(int_Diamond);
    qlabel_Diamond = new QLabel(this);
    qlabel_Diamond->setGeometry(50,44,300,20);
    qlabel_Diamond->setText(qstring_Diamond);
    qlabel_Diamond->setStyleSheet("QLabel { font-size: 20pt; color:red;}");
    //show how many spade
    QPixmap qpixmap_Spade(merge_filepath("pictures/spade.png"));
    QLabel *qlabel_LogoSpade = new QLabel(this);
    qlabel_LogoSpade->setPixmap(qpixmap_Spade);
    qlabel_LogoSpade->setGeometry(10,73,30,30);
    QString qstring_Spade = "Spade : ";
    qstring_Spade = qstring_Spade + QString::number(int_Spade);
    qlabel_Spade = new QLabel(this);
    qlabel_Spade->setGeometry(50,78,300,20);
    qlabel_Spade->setText(qstring_Spade);
    qlabel_Spade->setStyleSheet("QLabel { font-size: 20pt; color:black;}");
    //show how many heart
    QPixmap qpixmap_Heart(merge_filepath("pictures/heart.png"));
    QLabel *qlabel_LogoHeart = new QLabel(this);
    qlabel_LogoHeart->setPixmap(qpixmap_Heart);
    qlabel_LogoHeart->setGeometry(10,107,30,30);
    QString qstring_Heart = "Heart : ";
    qstring_Heart = qstring_Heart + QString::number(int_Heart);
    qlabel_Heart = new QLabel(this);
    qlabel_Heart->setGeometry(50,112,300,20);
    qlabel_Heart->setText(qstring_Heart);
    qlabel_Heart->setStyleSheet("QLabel { font-size: 20pt; color:red;}");
    //show how many total score
    QString qstring_TotalScore = "Total Score: ";
    qstring_TotalScore = qstring_TotalScore + QString::number(int_TotalScore);
    qlabel_TotalScore = new QLabel(this);
    qlabel_TotalScore->setGeometry(50,160,300,30);
    qlabel_TotalScore->setText(qstring_TotalScore);
    qlabel_TotalScore->setStyleSheet("QLabel { font-size: 35pt; color:grey;}");
}
