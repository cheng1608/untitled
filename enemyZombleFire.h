#ifndef ENEMYZOMBLEFIRE_H
#define ENEMYZOMBLEFIRE_H

#include "enemyBase.h"
#include"fire.h"

class EnemyZombleFire : public EnemyBase
{
    Q_OBJECT
public:
    explicit EnemyZombleFire(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);

private:
    QMovie *m_movie;
    int timeBuffer;

    void load();
    void Pathfinding();
    void FireSkill();
    int attack_count;
    const int attack_ceil;
};

#endif // ENEMYZOMBLEFIRE_H
