#include "magicFire.h"
#include "FireBallNomal.h"
#include <QRandomGenerator>

MagicFire::MagicFire(Player *pl, QGraphicsScene *scene, QObject *parent)
    : MagicBase{pl, scene, parent}
{
    pix = QPixmap(":/images/images/weapon/wp_dmr.png");
    setPixmap(pix);
    setTransformOriginPoint(boundingRect().center());
    spread = 3;
    setScale(3);
}

void MagicFire::cast(){
    if (!is_fire && fire_count >= (100.0 / fire_rate_boost)) return;
    fire_count++;
    if (!is_fire) return;
    if (fire_count < (100.0 / (fire_rate_boost + 0.35 * barrage + 0.3 ))) return;
    fire_count = 0;
    sfx_fire->play();
    for (int i = 0; i < 1 + round_boost; ++i) {
        QPointF center_pos = pos() + QPointF(100,100);
        FireBallNomal* bullet = new FireBallNomal(center_pos, rotation(), 10, 10, penetration, m_scene, parent());
        bullet->setRotation(bullet->rotation() + QRandomGenerator::global()->bounded((int)(-spread*10), (int)(spread*10)) * 0.1);
        bullet->setParentItem(parentItem());
        bullet->setScale(3);
        m_scene->addItem(bullet);
    }
}
