//
//  Player.cpp
//  KawazJet
//
//  Created by giginet on 2014/7/9.
//
//

#include "Player.h"
#include "Stage.h"

USING_NS_CC;

/// アニメーションが何フレームあるか
const int FRAME_COUNT = 4;
/// 横方向の加速度の最大値
const int ACCELERATION_LIMIT = 40;
/// 初期ジェット加速度
const Vec2 INITIAL_ACCELERATION = Vec2(200, 0);

bool Player::init()
{
    if (!Sprite::initWithFile("player.png")) {
        return false;
    }
    
    // 1フレームの画像サイズを取得する
    auto frameSize = Size(this->getContentSize().width / FRAME_COUNT,
                          this->getContentSize().height);
    // テクスチャの大きさを1フレーム分にする
    this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
    
    Vector<SpriteFrame *> frames;
    for (int i = 0; i < FRAME_COUNT; ++i) {
        // 1コマずつアニメーションを作成する
        auto frame = SpriteFrame::create("player.png", Rect(frameSize.width * i,
                                                            0,
                                                            frameSize.width,
                                                            frameSize.height));
        frames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(frames);
    animation->setDelayPerUnit(0.05);
    this->runAction(RepeatForever::create(Animate::create(animation)));
    
    auto body = PhysicsBody::createCircle(this->getContentSize().width / 2.0);
    // 剛体の回転を無効にする
    body->setRotationEnable(false);
    body->setCategoryBitmask((int)Stage::TileType::PLAYER);
    body->setCollisionBitmask((int)Stage::TileType::WALL);
    body->setContactTestBitmask(INT_MAX);
    this->setPhysicsBody(body);
    
    // 初期加速度を設定する
    _acceleration = INITIAL_ACCELERATION;
    
    this->scheduleUpdate();
    
    return true;
}

void Player::update(float dt)
{
    this->getPhysicsBody()->applyImpulse(_acceleration);
    auto v = this->getPhysicsBody()->getVelocity();
    if (v.x > ACCELERATION_LIMIT) {
        v.x = ACCELERATION_LIMIT;
        this->getPhysicsBody()->setVelocity(v);
    }
}