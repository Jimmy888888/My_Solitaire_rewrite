#include "table.h"

Table::Table(QWidget *parent)
    : QMainWindow{parent}
{
    this->setWindowTitle("Game Start");
    this->setWindowIcon( QIcon( merge_filepath("pictures/icon.png")));
    this->setMinimumSize(900,700);
    this->setMaximumSize(900,700);
    this->setStyleSheet("QMainWindow {background: 'green';}");

    //access card site's pos and size, and make 5 card sites on table, and save card sites in qlabel_cardSite
    qlist_setCardSitePosAndsize = get_cardSitePosAndSize();
    QPixmap qpixmap_cardSite(merge_filepath("pictures/card_site.png"));
    for(int i=0; i < qlist_setCardSitePosAndsize.length(); i++)
    {
        qlabel_cardSite = new QLabel(this);
        qlabel_cardSite->setGeometry(qlist_setCardSitePosAndsize[i].x, qlist_setCardSitePosAndsize[i].y, qlist_setCardSitePosAndsize[i].width, qlist_setCardSitePosAndsize[i].height);
        qlabel_cardSite->setPixmap(qpixmap_cardSite);
        qlist_cardSite << qlabel_cardSite;
    }

    //access card's suit filename, and card's number
    qlist_cardSuitsAndNumber = get_cardsSuitsAndNumber();
    //access card's inital pos and size
    qlist_setPosAndsize = get_initalPosAndSize();

    //generate 52 cards, and save cards in qlist_cards
    for(int i=0; i< qlist_cardSuitsAndNumber.length(); i++)
    {
        card_tt = new Card(this,qlist_cardSuitsAndNumber[i].qstring_suit);
        card_tt->int_cardNumber = qlist_cardSuitsAndNumber[i].int_num;
        card_tt->setGeometry(qlist_setPosAndsize[i].x, qlist_setPosAndsize[i].y, qlist_setPosAndsize[i].width, qlist_setPosAndsize[i].height);
        card_tt->show();
        qlist_cards << (card_tt);
    }

}

void Table::mousePressEvent(QMouseEvent *event)
{
//    qDebug() << "table pressed";
}

void Table::mouseReleaseEvent(QMouseEvent *event)
{
//    bool_cardPosFixable = true;
}

void Table::mouseMoveEvent(QMouseEvent *event)
{
    for(int i=0; i<qlist_cards.length(); i++)
    {
        if(qlist_cards[i]->bool_isPressed == true)
        {
            if(qlist_cards[i]->bool_cardPosFixable == true)
            {
                int_xfix = event->pos().x() - qlist_cards[i]->CardPos_pos.x;
                int_yfix = event->pos().y() - qlist_cards[i]->CardPos_pos.y;
                qlist_cards[i]->raise();
                qlist_cards[i]->bool_cardPosFixable = false;
    //            qDebug() << int_xfix << " " << int_yfix;
    //            qDebug() << event->pos();
    //            qDebug() << qlist_cards[0]->CardPos_pos.x << " " << qlist_cards[0]-CardPos_pos.y;
    //            qDebug() << "table mouseMove";
            }
            qlist_cards[i]->move(event->pos().x()-int_xfix, event->pos().y()-int_yfix);
    //        qDebug() << "card" << qlist_cards[0]->pos();
//            qDebug() << "table" << event->pos();
        }
    }


}
