#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QTimer>
#include <QList>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QSettings>
#include <QFontDatabase>
#include <QApplication>
#include <QSoundEffect>
#include<QSettings>

#include"player.h"
#include "magicBase.h"

class GameEngine : public QGraphicsView
{
    Q_OBJECT

public:
    GameEngine(QString magic);
    void load(); // 加载贴图
    void updateBackground();
    void endgame_lose();

signals:
    void Endgame();

private:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void enemyGenerator();
    int enemyNumberNow;

    Player *mainPlayer;

    QTimer *mainTimer;

    MagicBase *mainMagic;
    QGraphicsScene *mainScene;
    QGraphicsScene *end_scene;
    QGraphicsPixmapItem *mainBackground;

    QPointF mousePos;
    QString magic;
};

#endif // GAMEENGINE_H
