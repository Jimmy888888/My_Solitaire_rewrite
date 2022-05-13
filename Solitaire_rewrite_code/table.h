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
    CardBePressed get_thePressedCard(QList<Card *> qlist_cards, QMouseEvent *event);
    QList<Card *> releaseOn_PlayCards(QList<Card *> qlist_cards, QList<int> qlist_MoveAbelCards);
//input:qlist_cards qlist_PlayCardPosAndNum, output:qlist_cards, change: move up low
//for loop decide mouse release in playcards or stackcards or StartCard, than process_PlayCard process_StackCard process_StartCard

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
    CardBePressed CardBePressed_PressedCard;
    QList<int> qlist_MoveAbelCards;
    int int_maxZorder = 52;

};

#endif // TABLE_H
