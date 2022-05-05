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
        qlabel_cardSite->setGeometry(qlist_setCardSitePosAndsize[i]);
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
        card_cardMake = new Card(this,qlist_cardSuitsAndNumber[i].qstring_suit);
        card_cardMake->int_cardNumber = qlist_cardSuitsAndNumber[i].int_num;
        card_cardMake->setGeometry(qlist_setPosAndsize[i]);
        card_cardMake->show();
        qlist_cards << (card_cardMake);
    }


    //access 5 cards site's pos
    qpointf_cardSitePos = get_cardSitePos();
}

void Table::mousePressEvent(QMouseEvent *event)
{
//    qDebug() << "table pressed";
}

void Table::mouseReleaseEvent(QMouseEvent *event)
{
    //card can be put or not
}

void Table::mouseMoveEvent(QMouseEvent *event)
{
    for(int i=0; i<qlist_cards.length(); i++)
    {
        if(qlist_cards[i]->bool_isPressed == true)
        {
            if(qlist_cards[i]->bool_cardPosFixable == true)
            {
                qpointf_fixpos = event->pos() - qlist_cards[i]->qpointf_bePressedPos;
                qlist_cards[i]->raise();
                qlist_cards[i]->bool_cardPosFixable = false;
            }
            qpointf_movepos = event->pos() - qpointf_fixpos;
            qlist_cards[i]->move(qpointf_movepos.x(), qpointf_movepos.y());
        }
    }


}
