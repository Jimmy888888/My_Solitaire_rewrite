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
#include <QCloseEvent>
#include <QMessageBox>

#include "frequently_used.h"
#include "card.h"
#include "scoreboard.h"

class Table : public QMainWindow
{
    Q_OBJECT
public:
    Table(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    CardBePressed get_thePressedCard(QList<Card *> qlist_cards, QMouseEvent *event);
    QList<Card *> set_PutBackToStart0(QList<Card *> qlist_cards, CardBePressed CardBePressed_PressedCard, QList<QPointF> qlist_StartCardsArea , int int_maxZorder);
    QList<Card *> set_PutToStart1(QList<Card *> qlist_cards, CardBePressed CardBePressed_PressedCard, QList<QPointF> qlist_StartCardsArea , int int_maxZorder);
    QList<int> get_MoveAbelCard(QList<Card *> qlist_cards, CardBePressed CardBePressed_PressedCard);
    QList<Card *> set_MoveAbelCardState(QList<Card *> qlist_cards, QList<int> qlist_MoveAbelCards, QMouseEvent *event, int int_maxZorder);
    int get_onWhichStackPos(QList<Card *> qlist_cards, QList<int> qlist_MoveAbelCards, QList<QPointF> qlist_StackCardsArea );
    QList<Card *> releaseOn_StackCards(QList<Card *> qlist_cards, QList<int> qlist_MoveAbelCards, QList<QPointF> qlist_StackCardsArea , int int_onWhichStack);
    QList<Card *> releaseOn_PlayCards(QList<Card *> qlist_cards, QList<int> qlist_MoveAbelCards, QList<QPointF> qlist_PlayCardsArea );
    //Do something after Table closed
    void closeEvent (QCloseEvent *event);

private:
    QList<QPointF> qlist_StartCardsArea ;
    QList<QPointF> qlist_StackCardsArea ;
    QList<QPointF> qlist_PlayCardsArea ;
    QList<QRect> qlist_setCardSitePosAndsize;
    QLabel *qlabel_cardSite;
    QList<QLabel *> qlist_cardSite;
    QList<PosSizeUpLow> qlist_setPosSizeUpLow;
    QList<SuitAndNumber> qlist_cardSuitsAndNumber;
    Card *card_cardMake;
    QList<Card *> qlist_cards;
    QPointF qpointf_movepos;
    CardBePressed CardBePressed_PressedCard;
    QList<int> qlist_MoveAbelCards;
    int int_maxZorder = 52;
    int int_score = 0;
    QPushButton *qpushbutton_score;
    Scoreboard *scoreboard_score;

private slots:
    void clicked_startButton();
    void scoreBoardClose();

signals:
    void close_table();

};

#endif // TABLE_H
