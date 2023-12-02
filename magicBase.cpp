
#include "magicBase.h"


QTimer *m_timer = nullptr;

MagicBase::MagicBase(Player *pl, QGraphicsScene *scene, QObject *parent)
    : QObject{parent}, m_scene(scene), m_player(pl)
{
    fire_rate_boost = 1;
    damage_boost = 1;
    speed_boost = 1;
    fire_count = 0;
    is_fire = 0;
    round_boost = 0;
    penetration = 0;
    barrage = false;

    sfx_fire = new QSoundEffect(this);
    sfx_fire->setVolume(0.5);
    sfx_fire->setSource(QUrl::fromLocalFile(":/sfx/sfx/single_shot.wav"));

}


void MagicBase::updatePos()
{
    setPos(m_player->pos());
}

void MagicBase::rotateToCursor(const QPointF &target){
    QPointF weaponPos = mapToScene(transformOriginPoint());
    double dx = target.x() - weaponPos.x() - 100;
    double dy = target.y() - weaponPos.y() - 100;//100是实际位置和图片对象的偏移量，这个比较麻烦很难搞啊啊
    setRotation(-qRadiansToDegrees(qAtan2(dx, dy))+90);
}

void MagicBase::setFireRateBoost(qreal fr)
{
    fire_rate_boost = fr;
}

void MagicBase::setDamageBoost(qreal dmg)
{
    damage_boost = dmg;
}

void MagicBase::setSpeedBoost(qreal sp)
{
    speed_boost = sp;
}

void MagicBase::startCasting()
{
    is_fire = true;
}

void MagicBase::stopCasting()
{
    is_fire = false;
}

qreal MagicBase::getFireRateBoost()
{
    return fire_rate_boost;
}

qreal MagicBase::getDamageBoost()
{
    return damage_boost;
}

qreal MagicBase::getSpeedBoost()
{
    return speed_boost;
}

int MagicBase::getRoundBoost() const
{
    return round_boost;
}

void MagicBase::setRoundBoost(int newRound_boost)
{
    round_boost = newRound_boost;
}

qreal MagicBase::getSpread() const
{
    return spread;
}

void MagicBase::setSpread(qreal newSpread)
{
    spread = newSpread;
}

int MagicBase::getPenetration() const
{
    return penetration;
}

void MagicBase::setPenetration(int newPenetration)
{
    penetration = newPenetration;
}

bool MagicBase::getBarrage() const
{
    return barrage;
}

void MagicBase::setBarrage(bool newBarrage)
{
    barrage = newBarrage;
}



