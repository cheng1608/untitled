#ifndef ENEMYBASE_H
#define ENEMYBASE_H

#include "player.h"

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QSoundEffect>
#include <QUrl>
#include <qmath.h>
#include<QRandomGenerator>

class EnemyBase : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    EnemyBase(Player *pl, QGraphicsScene *scene, QObject *parent = nullptr);
    void hurt(qreal damage);

    static QTimer *enemyTimer;

signals:
    void enemyDeath();

protected:
    QRectF mapbounds;
    int timeBuffer;//时间缓冲器，用来实现一些寻路之类的时间推迟
    Player *enemyPlayer;
    QGraphicsScene *enemyScene;
    qreal speed;
    qreal health;
    int xp;

    bool isHurt=0;
    QTimer hurtTimer;
    void hurtReload();
    virtual void death();
    virtual void load()=0;

    virtual void Pathfinding()=0;

    void hitBoxCheck();

};

#endif // ENEMYBASE_H
