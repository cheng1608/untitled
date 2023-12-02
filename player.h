#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QVector2D>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QFont>
#include <QPixmap>
#include <QTimer>
#include <QMovie>
#include <QSoundEffect>
#include <QUrl>

class Player :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Player(QGraphicsView *view, QObject *parent = nullptr);
    void load(); // 加载贴图
    QRectF boundingRect() const override;// 碰撞箱

    void addVelocity(int dx, int dy);
    void setVelocityX(int dx);
    void setVelocityY(int dy);
    void updateCoordinate();
    QPointF getCoordinateBias();


    void hurt();
    void resetInvincible();

    int getHealth();
    void setHealth(int hp);

signals:
    void playerHurt();
    void playerDeath();

private:
    int speed;
    QGraphicsView *mainView;
    QMovie *standingRole;
    QMovie *movingRole;
    QRectF mapbounds;
    QVector2D velocityVector;//当前速度向量

    bool isInvincible;//受伤后 无敌
    QTimer *invincibleTimer;
    qreal invincibleTime;

    int nowHP;
    int maxHP;
};

#endif // PLAYER_H
