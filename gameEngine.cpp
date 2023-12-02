
#include "gameEngine.h"

#include"enemyZomble.h"
#include"enemyZombleFire.h"
#include"enemyZombleFireGiant.h"
#include"enemyZombleWind.h"

#include "FireBallBase.h"


#include "magicFire.h"



GameEngine::GameEngine(QString magic)
    :magic(magic)

{
    QFontDatabase::addApplicationFont(":/font/fusion-pixel-proportional.ttf");
    // 生成场景
    setFixedSize(1500, 1000);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mainScene = new QGraphicsScene(this);
    QColor bgColor = QColor(200, 200, 200);
    QSize bgSize = QSize(4000, 2400);

    // 创建纯色背景图像
    QPixmap bgPixmap(bgSize);
    bgPixmap.fill(bgColor);
    // 背景生成
    QPixmap background(":/images/game_background_3.png");
    mainBackground = new QGraphicsPixmapItem;
    mainBackground->setPixmap(bgPixmap);
    mainBackground->setZValue(-0x3ffffff);
    mainScene->addItem(mainBackground);
    mainScene->setSceneRect(0, 0, 1500, 1000);
    setScene(mainScene);

    // 角色生成
    mainPlayer = new Player(this, this);
    mainPlayer->setParentItem(mainBackground);
    mainScene->addItem(mainPlayer);
    // 移动player至地图中央
    mainPlayer->moveBy(2400+500, 1350+300);
    centerOn(mainPlayer->pos());
    mainBackground->moveBy(-2400, -1350);
    
    if(magic=="magicFire"){
        mainMagic = new MagicFire(mainPlayer, mainScene, this);
    }
    mainMagic->setParentItem(mainBackground);
    mainMagic->moveBy(2400+500+100,1350+300+100);

    // 主计时器(所有绑定放这里下面)
    mainTimer = new QTimer(this);



    // player移动和贴图加载
    connect(mainTimer, &QTimer::timeout, mainPlayer, &Player::updateCoordinate);
    connect(mainTimer, &QTimer::timeout, mainPlayer, &Player::load);
    connect(mainTimer, &QTimer::timeout, this, &GameEngine::updateBackground);
    connect(mainPlayer, &Player::playerDeath, this, &GameEngine::endgame_lose);

    EnemyBase::enemyTimer = mainTimer;//连接敌人计时器
    connect(mainTimer, &QTimer::timeout, this, &GameEngine::enemyGenerator);
    enemyNumberNow=0;
    

    FireBallBase::m_timer_static = mainTimer; // Bullet计时器
    // 武器移动，加载贴图，开火wwww
    connect(mainTimer, &QTimer::timeout, mainMagic, &MagicBase::updatePos);
    connect(mainTimer, &QTimer::timeout, mainMagic, &MagicBase::cast);

    mainTimer->start(10);

}

void GameEngine::updateBackground(){
    QPointF bias = mainPlayer->getCoordinateBias();
    mainBackground->moveBy(bias.x(), bias.y());
}

void GameEngine::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_W:
        mainPlayer->addVelocity(0, -1);
        break;
    case Qt::Key_S:
        mainPlayer->addVelocity(0, 1);
        break;
    case Qt::Key_A:
        mainPlayer->addVelocity(-1, 0);
        break;
    case Qt::Key_D:
        mainPlayer->addVelocity(1, 0);
    default:
        break;
    }
}

void GameEngine::keyReleaseEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_W:
        mainPlayer->addVelocity(0, 1);
        break;
    case Qt::Key_S:
        mainPlayer->addVelocity(0, -1);
        break;
    case Qt::Key_A:
        mainPlayer->addVelocity(1, 0);
        break;
    case Qt::Key_D:
        mainPlayer->addVelocity(-1, 0);
    default:
        break;
    }
}

void GameEngine::mouseMoveEvent(QMouseEvent *event)
{
    mainMagic->rotateToCursor(event->pos());
    QGraphicsView::mouseMoveEvent(event);
}

void GameEngine::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton:
        mainMagic->startCasting();
        break;
    default:
        break;
    }
    // 将事件传递给视图
    QGraphicsView::mousePressEvent(event);
}

void GameEngine::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton:
        mainMagic->stopCasting();
        break;
    default:
        break;
    }
    // 将事件传递给视图
    QGraphicsView::mouseReleaseEvent(event);
}

void GameEngine::enemyGenerator(){
    enemyNumberNow++;
    if(enemyNumberNow>5){
        return;//最高上限
    }

    QPointF enemyPos;
    qreal dist;
    do {
        enemyPos.setX(QRandomGenerator::global()->bounded(0, 4800));
        enemyPos.setY(QRandomGenerator::global()->bounded(0, 2700));
        dist = QLineF(mainPlayer->pos(), enemyPos).length();

    } while (dist < 450|| dist > 550);   // 不在视野范围或过近时重新生成

    EnemyBase *enemy = nullptr;


    int GenerateRandomNumber = QRandomGenerator::global()->bounded(0, 100);
    if(GenerateRandomNumber>60){
        enemy=new EnemyZombleFireGiant(mainPlayer,mainScene,this);
    }
    else{
        enemy=new EnemyZombleFire(mainPlayer,mainScene,this);
    }



    if (!enemy) return;
    enemy->setParentItem(mainBackground);
    enemy->setPos(enemyPos);
    enemy->setZValue(1);
    // 将敌人添加到场景中
    mainScene->addItem(enemy);
}

void GameEngine::endgame_lose() {
    // 读取样式表
    QFile file_sqr_pb(":/style/stylesheet/sqr_pb.qss");
    file_sqr_pb.open(QFile::ReadOnly);
    QString style_sqr_pb;
    if (file_sqr_pb.isOpen()) {
        style_sqr_pb = QLatin1String(file_sqr_pb.readAll());
        file_sqr_pb.close();
    }
    // 停止所有计时器
    mainTimer->stop();


    // 显示游戏结束界面
    end_scene = new QGraphicsScene(this);
    end_scene->setSceneRect(0, 0, 1280, 720);
    setScene(end_scene);
    end_scene->setFocus();
    // 背景
    end_scene->addPixmap(QPixmap(":/images/images/ABackground.png"));
    // 文字
    QGraphicsTextItem *end_text = new QGraphicsTextItem("You Lose!");
    end_text->setFont(QFont("fusion pixel proportional", 72));
    end_text->setDefaultTextColor(Qt::red);
    end_text->setPos(420, 260);
    end_scene->addItem(end_text);
    // 返回按钮
    QPushButton *return_btn = new QPushButton("back");
    end_scene->addWidget(return_btn);
    return_btn->move(120, 540);
    return_btn->setStyleSheet(style_sqr_pb);
    return_btn->resize(110, 110);
    connect(return_btn, &QPushButton::clicked, this, [=](){
        emit Endgame();
        deleteLater();
    });
}
