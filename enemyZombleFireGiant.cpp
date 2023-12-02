#include "enemyZombleFireGiant.h"
#include"fire.h"

EnemyZombleFireGiant::EnemyZombleFireGiant(Player *pl, QGraphicsScene *scene, QObject *parent)
    : EnemyBase(pl, scene, parent),attack_ceil(60)
{
    // 加载动画
    m_movie = new QMovie(":/images/Zomble_walk.gif");
    m_movie->setParent(this);
    m_movie->setSpeed(10);
    m_movie->start();

    setTransformOriginPoint(8, 10);

    timeBuffer = 0;
    // 基本数据
    health = 200;
    xp = 2;
    speed = 1;

    connect(enemyTimer, &QTimer::timeout, this, &EnemyZombleFireGiant::FireSkill);
    attack_count=0;
}

void EnemyZombleFireGiant::Pathfinding (){
    if (!enemyPlayer)return;

    // 计算出 Enemy 到 Player 的方向
    QLineF line(pos(), enemyPlayer->pos());
    // 计算出移动的距离和方向
    qreal dx = cos(line.angle() * M_PI / 180) * speed;
    qreal dy = -sin(line.angle() * M_PI / 180) * speed;
    QPointF newPos = pos() + QPointF(dx, dy);

    if (mapbounds.contains(newPos)) {
        if (dx > 0) {
            newPos = pos() + QPointF(speed, 0);
        }
        else {
            newPos = pos() + QPointF(-speed, 0);
        }
    }
    if (mapbounds.contains(newPos)) {
        if (dy > 0) {
            newPos = pos() + QPointF(0, speed);
        }else {
            newPos = pos() + QPointF(0, -speed);
        }
    }
    if (mapbounds.contains(newPos)){
        newPos = pos() + QPointF(0, 0);
    }
    // 移动 Enemy
    setPos(newPos);
    timeBuffer++;

}

void EnemyZombleFireGiant::load()
{
    QImage img(m_movie->currentImage());

    if (isHurt)
    {
        uchar *pixels = img.bits();
        int width = img.width();
        int height = img.height();
        int bytesPerLine = img.bytesPerLine();
        for (int y = 0; y < height; ++y)
        {
            uchar *line = pixels + y * bytesPerLine;
            for (int x = 0; x < width; ++x)
            {
                uchar alpha = line[x * 4 + 3];
                if (alpha != 0)
                {
                    line[x * 4] = 255;
                    line[x * 4 + 1] = 255;
                    line[x * 4 + 2] = 255;
                }
            }
        }
    }

    // 确定角度
    qreal angle = QLineF(pos(), enemyPlayer->pos()).angle();

    QPixmap pixmap = QPixmap::fromImage(img);
    QTransform transform;
    transform.scale(2, 2); // 将图像宽度和高度都扩大一倍

    // 镜像处理
    if ((angle > 90 && angle < 270) || (angle < -90 && angle > -270))
    {
        // 水平镜像
        transform.scale(-1, 1);
    }

    pixmap = pixmap.transformed(transform);
    setPixmap(pixmap);
}


void EnemyZombleFireGiant::FireSkill()
{
    attack_count++;
    qreal dist = QLineF(pos(), enemyPlayer->pos()).length();
    if (dist > 400){
        return;
    }
    if (attack_count < attack_ceil) {
        return;
    }
    attack_count = 0;
    qreal angle = -QLineF(pos(), enemyPlayer->pos()).angle();
    angle -= 30;
    for (int i = 0; i < 3; ++i) {

        QPointF tmpBias(200, 200);
        QPointF realPos=tmpBias+pos();//让子弹从中心点射出

        Fire *bullet = new Fire(realPos, angle + 30*i, 3, 1, 0, enemyScene, enemyPlayer, enemyScene);
        bullet->setScale(2);
        bullet->setParentItem(this->parentItem());
        enemyScene->addItem(bullet);
    }
}




