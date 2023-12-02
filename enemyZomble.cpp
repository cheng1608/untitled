#include "enemyZomble.h"

EnemyZomble::EnemyZomble(Player *pl, QGraphicsScene *scene, QObject *parent)
    : EnemyBase{pl, scene, parent}{
    // 加载动画
    m_movie = new QMovie(":/images/Zomble_walk.gif");
    m_movie->setParent(this);
    m_movie->setSpeed(10);
    m_movie->start();

    setTransformOriginPoint(8, 10);

    timeBuffer=0;
    // 基本数据
    health = 30;
    xp = 1;
    speed = 1;
    isHighSpeed=0;
}


void EnemyZomble::Pathfinding (){
    if (!enemyPlayer)return;

    // 计算出 Enemy 到 Player 的方向
    QLineF line(pos(), enemyPlayer->pos());
    // 计算出移动的距离和方向
    qreal dx = cos(line.angle() * M_PI / 180) * speed;
    qreal dy = -sin(line.angle() * M_PI / 180) * speed;
    QPointF newPos = pos() + QPointF(dx, dy);

    if(timeBuffer>10){
        timeBuffer=0;
        if(isHighSpeed)isHighSpeed=0;
        else isHighSpeed=1;
    }

    if (isHighSpeed==0) {
        int random = QRandomGenerator::global()->bounded(0, 100);
        //退火
        if(10>random){
            switch(random%4){
            case 0:
                newPos = pos() + QPointF(speed, 0);
                break;
            case 1:
                newPos = pos() + QPointF(-speed, 0);
                break;
            case 2:
                newPos = pos() + QPointF(0, speed);
                break;
            case 3:
                newPos = pos() + QPointF(0, -speed);
                break;
            default:
                newPos = pos();
                break;
            }
            setPos(newPos);
            return;
        }
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
            }
            else {
                newPos = pos() + QPointF(0, -speed);
            }
        }
        if (mapbounds.contains(newPos)){
            newPos = pos() + QPointF(0, 0);
        }
        // 移动 Enemy
        setPos(newPos);
        timeBuffer++;
    }else{
        if (mapbounds.contains(newPos)) {
            if (dx > 0) {
                newPos = pos() + QPointF(speed*10, 0);
            }
            else {
                newPos = pos() + QPointF(-speed*10, 0);
            }
        }
        if (mapbounds.contains(newPos)) {
            if (dy > 0) {
                newPos = pos() + QPointF(0, speed*10);
            }else {
                newPos = pos() + QPointF(0, -speed*10);
            }
        }
        if (mapbounds.contains(newPos)){
            newPos = pos() + QPointF(0, 0);
        }
        // 移动 Enemy
        setPos(newPos);
        timeBuffer++;
    }

}

void EnemyZomble::load(){
    QImage img(m_movie->currentImage());

    if (isHurt) {
        uchar *pixels = img.bits();
        int width = img.width();
        int height = img.height();
        int bytesPerLine = img.bytesPerLine();
        for (int y = 0; y < height; ++y) {
            uchar *line = pixels + y * bytesPerLine;
            for (int x = 0; x < width; ++x) {
                uchar alpha = line[x * 4 + 3];
                if (alpha != 0) {
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
    // 镜像处理
    if ((angle > 90 && angle < 270) || (angle < -90 && angle > -270)) {
        //水平镜像
        pixmap = pixmap.transformed(QTransform().scale(-1, 1));
    }
    // 设置显示图像
    setPixmap(pixmap);
}



