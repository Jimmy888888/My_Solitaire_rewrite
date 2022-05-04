#include "table.h"

Table::Table(QWidget *parent)
    : QMainWindow{parent}
{
    this->setWindowTitle("Game Start");
    this->setWindowIcon( QIcon( merge_filepath("pictures/icon.png")));
    this->setMinimumSize(400,700);
    this->setMaximumSize(400,700);
    this->setStyleSheet("QMainWindow {background: 'green';}");

    qlist_suits = get_cardsSuits();
//    for(int i=0; i < qlist_suits.length(); i++)
//    {
//        qDebug() << qlist_suits[i];
//    }

    card_tt = new Card(this,qlist_suits[0]);
    card_tt->setGeometry(10,100,110,160);
    card_tt->show();
    qlist_cards << (card_tt);

    card_tt =  new Card(this,qlist_suits[1]);
    card_tt->setGeometry(100,100,110,160);
    card_tt->show();
    qlist_cards << (card_tt);

    card_tt =  new Card(this,qlist_suits[2]);
    card_tt->setGeometry(110,100,110,160);
    card_tt->show();
    qlist_cards << (card_tt);

//randomly access the filename array
//and build new class for setGeometry(x,y,w,h)

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
