#include "kwAnimation.h"
#include "kwTransform.h"
#include "kwTime.h"
#include "kwAnimator.h"
#include "kwGameObject.h"
#include "kwImage.h"
#include "kwCamera.h"

namespace kw
{
    Animation::Animation()
        : mAnimator(nullptr)
        , mSheetImage(nullptr)
        , mTime(0.0f)
        , mbComplete(false)
        , mSpriteIndex(0)
        , mAnimationName(L"")
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
        GameObject* obj = mAnimator->GetOwner();
        Transform* tr = obj->GetComponent<Transform>();
        Vector2 scale = tr->GetScale();
        bool isFlip = obj->GetFlipX();

        std::wstring playAnimName = mAnimationName + std::to_wstring(mSpriteIndex);
        Image* playAnimImage = Image::Create(playAnimName, mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y);

        Vector2 LeftTop = mSpriteSheet[mSpriteIndex].leftTop;

        Vector2 pos = tr->GetPos();
        if (obj->IsUI() == false)
        {
            pos = Camera::CalculatePos(pos);
        }
        
        pos.y += mSpriteSheet[mSpriteIndex].offset.y;

        if (isFlip)
        {
            pos.x -= mSpriteSheet[mSpriteIndex].offset.x;
            playAnimName += L"Flip";
        }
        else
        {
            pos.x += mSpriteSheet[mSpriteIndex].offset.x;
        }

        // 피벗이 중하단인경우
        if (obj->GetPivot() == GameObject::ePivot::LowCenter)
        {
            pos.x -= mSpriteSheet[mSpriteIndex].size.x / 2.0f;
            pos.y -= mSpriteSheet[mSpriteIndex].size.y;
        }
        // 피벗이 정중앙인경우
        else if (obj->GetPivot() == GameObject::ePivot::MiddleCenter)
        {
            pos.x -= mSpriteSheet[mSpriteIndex].size.x / 2.0f;
            pos.y -= mSpriteSheet[mSpriteIndex].size.y / 2.0f;
        }
        
        if (isFlip)
        {
            StretchBlt(
                playAnimImage->GetHdc(),
                playAnimImage->GetWidth(), 0, -1 * playAnimImage->GetWidth() -1, playAnimImage->GetHeight(),
                mSheetImage->GetHdc(),
                LeftTop.x, LeftTop.y, playAnimImage->GetWidth(), playAnimImage->GetHeight(),
                SRCCOPY);
        }
        else
        {
            BitBlt(playAnimImage->GetHdc()
                , 0, 0
                , playAnimImage->GetWidth(), playAnimImage->GetHeight()
                , mSheetImage->GetHdc(), LeftTop.x, LeftTop.y, SRCCOPY);
        }

        TransparentBlt(hdc, pos.x, pos.y
            , mSpriteSheet[mSpriteIndex].size.x * scale.x
            , mSpriteSheet[mSpriteIndex].size.y * scale.y
            , playAnimImage->GetHdc()
            , 0, 0
            , mSpriteSheet[mSpriteIndex].size.x, mSpriteSheet[mSpriteIndex].size.y,
            RGB(255, 0, 255));

        // 알파 블렌드 코드.
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