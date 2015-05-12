#include "include\GameCamera.h"

namespace Game
{
    CGameCamera::CGameCamera(PuRe_Vector3F a_Position, PuRe_Vector3F a_Direction, PuRe_Vector3F a_Up, float a_FOV, float a_AspectRatio,
        PuRe_Vector2F a_NearFar, PuRe_Vector2F a_Resolution, PuReEngine::Core::CameraProjection a_UsedProjection) : PuRe_Camera(a_Position, a_Direction, a_Up, a_FOV, a_AspectRatio, a_NearFar, a_Resolution, a_UsedProjection)
    {

    }

    CGameCamera::CGameCamera(PuRe_Vector2F a_Resolution, PuReEngine::Core::CameraProjection a_UsedProjection) : PuRe_Camera(a_Resolution, a_UsedProjection)
    {

    }

    CGameCamera::~CGameCamera()
    {

    }

    void CGameCamera::Initialize()
    {
        this->SetFoV(45.0f);
        this->m_ZOffset = 5.0f;
    }

    void CGameCamera::Update(TheBrick::CSpaceship* a_pPlayer, PuRe_IInput* a_pInput, PuRe_Timer* a_pTimer)
    {
        //Seconds for frame independent movement
        float Seconds = a_pTimer->GetElapsedSeconds();

        this->m_ZOffset += a_pInput->GetMouseScroll();
        if (this->m_ZOffset < 5.0f)
            this->m_ZOffset = 5.0f;
        else if (this->m_ZOffset > 10.0f)
            this->m_ZOffset = 10.0f;

        this->SetPosition(TheBrick::OngToPuRe(a_pPlayer->m_Transform.p));

        PuRe_Vector3F cameraLook = PuRe_Vector3F();

        if (a_pInput->MouseIsPressed(a_pInput->LeftClick))
        {

            PuRe_Vector2F speed = a_pInput->GetRelativeMousePosition() * 10.0f;

            if (speed.X != 0.0f)
                cameraLook.X += speed.X*Seconds;
            if (speed.Y != 0.0f)
                cameraLook.Y += speed.Y*Seconds;
        }
        PuRe_Vector2F GamePadThumb = a_pInput->GetGamepadRightThumb(0);
        if (GamePadThumb.Length() > 1.0f)
            this->Rotate(cameraLook.Y + GamePadThumb.Y, cameraLook.X + GamePadThumb.X, cameraLook.Z);

        this->Move(PuRe_Vector3F(-0.5f, 0.5f, -this->m_ZOffset));
    }
}