#include "kwAnimation.h"
#include "kwTransform.h"
#include "kwTime.h"
#include "kwAnimator.h"
#include "kwGameObject.h"
#include "kwImage.h"

namespace kw
{
    Animation::Animation()
        : mAnimator(nullptr)
        , mSheetImage(nullptr)
        , mTime(0.0f)
        , mbComplete(false)
        , mSpriteIndex(0)
    {

    }

    Animation::~Animation()
    {
    }

    void Animation::Initialize()
    {
    }

    void Animation::Update()
    {
        if (mbComplete == true)
            return;

        mTime += Time::DeltaTime();
        if (mSpriteSheet[mSpriteIndex].duration < mTime)
        {
            mTime = 0.0f;

            if (mSpriteSheet.size() <= mSpriteIndex + 1)
            {
                mbComplete = true;
            }
            else
            {
                mSpriteIndex++;
            }
        }
    }

    void Animation::Render(HDC hdc)
    {
        Transform* tr
            = mAnimator->GetOwner()->GetComponent<Transform>();
        Vector2 scale = tr->GetScale();

        // 이미지가 그려질 좌표는 오브젝트 좌표의 위쪽 중간에 그려진다.
        // 캐릭터의 발을 기준으로 포지션을 계산
        Vector2 pos = tr->GetPos();
        pos += mSpriteSheet[mSpriteIndex].offset;
        pos.x -= mSpriteSheet[mSpriteIndex].size.x / 2.0f;
        pos.y -= mSpriteSheet[mSpriteIndex].size.y;

        TransparentBlt(hdc, pos.x, pos.y
            , mSpriteSheet[mSpriteIndex].size.x * scale.x
            , mSpriteSheet[mSpriteIndex].size.y * scale.y
            , mSheetImage->GetHdc()
            , mSpriteSheet[mSpriteIndex].leftTop.x, mSpriteSheet[mSpriteIndex].leftTop.y
            , mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y,
            RGB(255, 0, 255));
    }

    void Animation::Create(Image* sheet, Vector2 leftTop
        , UINT coulmn, UINT row, UINT spriteLength
        , Vector2 offset, float duration)
    {
        mSheetImage = sheet;

        //UINT coulmn = mSheetImage->GetWidth() / size.x;
        Vector2 size = Vector2::One;
        size.x = mSheetImage->GetWidth() / (float)coulmn;
        size.y = mSheetImage->GetHeight() / (float)row;

        for (size_t i = 0; i < spriteLength; i++)
        {
            Sprite spriteInfo;

            spriteInfo.leftTop.x = leftTop.x + (size.x * i);
            spriteInfo.leftTop.y = leftTop.y;
            spriteInfo.size = size;
            spriteInfo.offset = offset;
            spriteInfo.duration = duration;

            mSpriteSheet.push_back(spriteInfo);
        }
    }

    void Animation::Reset()
    {
        mSpriteIndex = 0;
        mTime = 0.0f;
        mbComplete = false;
    }
}