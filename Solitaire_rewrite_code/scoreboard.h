#include "frequently_used.h"
#include <QLabel>
#include <QWidget>
#include <QPixmap>

#ifndef SCOREBOARD_H
#define SCOREBOARD_H


class Scoreboard : public QWidget
{
    Q_OBJECT
public:
    Scoreboard(int int_Club, int int_Diamond, int int_Spade, int int_Heart, int int_TotalScore);
    QLabel *qlabel_Club;
    QLabel *qlabel_Diamond;
    QLabel *qlabel_Spade;
    QLabel *qlabel_Heart;
    QLabel *qlabel_TotalScore;

};

#endif // SCOREBOARD_H
