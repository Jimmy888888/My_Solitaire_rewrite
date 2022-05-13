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
    QList<QPointF> qlist_StartCardsPos;
    QList<QPointF> qlist_StackCardsPos;
    QList<QPointF> qlist_PlayCardsPos;
    QList<QRect> qlist_setCardSitePosAndsize;
    QLabel *qlabel_cardSite;
    QList<QLabel *> qlist_cardSite;
    QList<SuitAndNumber> qlist_cardSuitsAndNumber;
    QList<PosSizeUpLow> qlist_setPosSizeUpLow;
    Card *card_cardMake;
    QList<Card *> qlist_cards;
    QPointF qpointf_movepos;
    QList<QPointF> qlist_cardMoveFixPos;
    QList<PosNum> qlist_PlaceCardPosAndNum;
    CardBePressed CardBePressed_PressedCard;
    QList<int> qlist_MoveAbelCards;
    int int_maxZorder = 52;

};

#endif // TABLE_H
