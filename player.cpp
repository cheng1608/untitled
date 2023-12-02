#include "player.h"

Player::Player(QGraphicsView *view,QObject *parent):QObject{parent},speed(5),mainView(view)
{

    standingRole = new QMovie(this);
    standingRole->setFileName(":/images/pl_idle.gif");
    standingRole->setSpeed(33);
    standingRole->start();

    movingRole = new QMovie(this);
    movingRole->setFileName(":/images/pl_run.gif");
    movingRole->setSpeed(67);
    movingRole->start();


    load();

    mapbounds = QRectF(0, 0, 3800, 2200);

    // 无敌帧计时器
    isInvincible=0;
    invincibleTimer = new QTimer(this);
    connect(invincibleTimer, &QTimer::timeout, this, &Player::resetInvincible);

    maxHP=10;
    nowHP=10;
}

void Player::addVelocity(int dx, int dy){
    // 防止叠加
    if (velocityVector.x() != dx){
        velocityVector.setX(velocityVector.x() + dx);
    }
    if (velocityVector.y() != dy){
        velocityVector.setY(velocityVector.y() + dy);
    }
}

void Player::setVelocityX(int dx){
    velocityVector.setX(dx);
}

void Player::setVelocityY(int dy){
    velocityVector.setY(dy);
}

void Player::updateCoordinate(){
    QPointF newPos = this->pos() + QPointF(velocityVector.x() * speed , velocityVector.y() * speed );
    if (!mapbounds.contains(newPos)){
        newPos = this->pos() + QPointF(velocityVector.x() * speed , 0);
    }
    if (!mapbounds.contains(newPos)){
        newPos = this->pos() + QPointF(0, velocityVector.y() * speed);
    }
    if (!mapbounds.contains(newPos)){
        newPos = this->pos() + QPointF(0, 0);
    }
    setPos(newPos);
}

QPointF Player::getCoordinateBias(){
    QPointF newPos = this->pos() + QPointF(velocityVector.x() * speed , velocityVector.y() * speed );
    if (!mapbounds.contains(newPos)){
        newPos = this->pos() + QPointF(velocityVector.x() * speed , 0);
    }
    if (!mapbounds.contains(newPos)){
        newPos = this->pos() + QPointF(0, velocityVector.y() * speed);
    }
    if (!mapbounds.contains(newPos)){
        newPos = this->pos() + QPointF(0, 0);
    }
    return pos() - newPos;
}

void Player::load(){
    if (velocityVector.x() == 0 && velocityVector.y() == 0){
        QImage img(standingRole->currentPixmap().toImage());
        if (mainView->mapFromGlobal(QCursor::pos()).x() < 640){
            img = img.transformed(QTransform().scale(-1, 1));
        }
        QPixmap pix(QPixmap::fromImage(img));

        // 放大贴图
        int scaleFactor = 1;  // 缩放因子
        QSize scaledSize = pix.size() * scaleFactor;
        pix = pix.scaled(scaledSize, Qt::KeepAspectRatio);

        setPixmap(pix);
    } else {
        QImage img(movingRole->currentPixmap().toImage());
        if (velocityVector.x() < 0){
            img = img.transformed(QTransform().scale(-1, 1));
        }
        QPixmap pix(QPixmap::fromImage(img));

        int scaleFactor = 1;
        QSize scaledSize = pix.size() * scaleFactor;
        pix = pix.scaled(scaledSize, Qt::KeepAspectRatio);

        setPixmap(pix);
    }
}

QRectF Player::boundingRect() const
{
    //碰撞箱
    const qreal boundingRectWidth=100;
    const qreal boundingRectHeight=160;
    return QRectF(50,20,boundingRectWidth, boundingRectHeight);
}


void Player::hurt(){
    if (isInvincible){
        qDebug() << "invincible";
        return;
    }
    nowHP--;
    qDebug() << "damage";
    isInvincible = true;
    invincibleTimer->start(100);
    if (nowHP <= 0){
        emit playerDeath();
    }
}

int Player::getHealth(){
    return nowHP;
}

void Player::setHealth(int hp){
    nowHP=hp;
}

void Player::resetInvincible(){
    isInvincible = false;
    invincibleTimer->stop();
}



