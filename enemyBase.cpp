#include "enemyBase.h"


QRectF mapbounds = QRectF(0, 0, 3800, 2200);

QTimer* EnemyBase::enemyTimer=nullptr;


EnemyBase::EnemyBase(Player *pl, QGraphicsScene *scene, QObject *parent)
    : QObject{parent}, enemyPlayer(pl), enemyScene(scene)
{
    connect(this, &EnemyBase::enemyDeath, this, &EnemyBase::death);
    connect(enemyTimer,&QTimer::timeout,this,&EnemyBase::Pathfinding);
    connect(enemyTimer,&QTimer::timeout,this,&EnemyBase::load);
    connect(enemyTimer,&QTimer::timeout,this,&EnemyBase::hitBoxCheck);

    connect(&hurtTimer, &QTimer::timeout, this, &EnemyBase::hurtReload);
    connect(this, &EnemyBase::enemyDeath, this, &EnemyBase::death);

}

void EnemyBase::hurt(qreal damage){
    health -= damage;
    isHurt = true;
    hurtTimer.start(50);
    if (health <= 0) {
        emit enemyDeath();
    }
}

void EnemyBase::hitBoxCheck()
{
    if (collidesWithItem(enemyPlayer)){
        enemyPlayer->hurt();
    }
}

void EnemyBase::death(){
    enemyScene->removeItem(this);
    deleteLater();
}

void EnemyBase::hurtReload()
{
    isHurt = false;
    hurtTimer.stop();
}
