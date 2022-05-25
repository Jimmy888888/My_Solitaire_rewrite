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
#include "scoreboard.h"

class Table : public QMainWindow
{
    Q_OBJECT
public:
    explicit Table(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    CardBePressed get_thePressedCard(QList<Card *> qlist_cards, QMouseEvent *event);
    QList<Card *> set_PutBackToStart0(QList<Card *> qlist_cards, CardBePressed CardBePressed_PressedCard, QList<QPointF> qlist_StartCardsPos, int int_maxZorder);
    QList<Card *> set_PutToStart1(QList<Card *> qlist_cards, CardBePressed CardBePressed_PressedCard, QList<QPointF> qlist_StartCardsPos, int int_maxZorder);
    QList<int> get_MoveAbelCard(QList<Card *> qlist_cards, CardBePressed CardBePressed_PressedCard);
    QList<Card *> set_MoveAbelCardState(QList<Card *> qlist_cards, QList<int> qlist_MoveAbelCards, QMouseEvent *event, int int_maxZorder);
    int get_onWhichStackPos(QList<Card *> qlist_cards, QList<int> qlist_MoveAbelCards, QList<QPointF> qlist_StackCardsPos);
    QList<Card *> releaseOn_StackCards(QList<Card *> qlist_cards, QList<int> qlist_MoveAbelCards, QList<QPointF> qlist_StackCardsPos, int int_onWhichStack);
    QList<Card *> releaseOn_PlayCards(QList<Card *> qlist_cards, QList<int> qlist_MoveAbelCards, QList<QPointF> qlist_PlayCardsPos);
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
    CardBePressed CardBePressed_PressedCard;
    QList<int> qlist_MoveAbelCards;
    int int_maxZorder = 52;
    int int_score = 0;
    QPushButton *qpushbotton_score;
    Scoreboard *scoreboard_score;

private slots:
    void clicked_startButton();

};

#endif // TABLE_H
