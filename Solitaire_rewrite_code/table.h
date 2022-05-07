#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QMouseEvent>
#include <QList>

#include "frequently_used.h"
#include "card.h"

class Table : public QMainWindow
{
    Q_OBJECT
public:
    explicit Table(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private:
    QList<QLabel *> qlist_cardSite;
    QList<QRect> qlist_setCardSitePosAndsize;
    QLabel *qlabel_cardSite;
    QList<Card *> qlist_cards;
    QList<SuitAndNumber> qlist_cardSuitsAndNumber;
    QList<QRect> qlist_setPosAndsize;
    Card *card_cardMake;
    QPointF qpointf_fixpos, qpointf_movepos;
    QList<QPointF> qlist_cardSitePos;
    QList<QPointF> qlist_cardPlacedPos;
    CardBePressed CardBePressed_PCard;
    int int_maxZorder;
//    QString qstring_cardSuit[52] = {};

};

#endif // TABLE_H
