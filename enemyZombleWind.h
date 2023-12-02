#ifndef ENEMYZOMBLEWIND_H
#define ENEMYZOMBLEWIND_H

#include"enemyBase.h"

class EnemyZombleWind:public EnemyBase
{
    Q_OBJECT
public:
    explicit EnemyZombleWind(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);
private:
    QMovie* m_movie;

    bool isHighSpeed;

    void load() ;
    void Pathfinding ();
};



#endif // ENEMYZOMBLEWIND_H
