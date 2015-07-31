#ifndef _BRICKWORKER_H_
#define _BRICKWORKER_H_

#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>
#include <Onager/World.h>

#include "TheBrick/GameObject.h"
#include "TheBrick/Spaceship.h"

#include "EditorCamera.h"

namespace TheBrick
{
    class CGameObject;
    class CBrickInstance;
    class CSpaceship;
    class CBrick;
}

namespace Game
{
    class CHistory;

    class CBrickWorker
    {

    public:

    private:
        CEditorCamera* m_pCamera;

        float m_currentBrickRotation;
        float m_currentRotation;
        int m_maxBrickDistance;
        PuRe_Vector2F m_currentBrickPosition;
        PuRe_Vector2F m_currentPosition;
        float m_currentHeight;
        PuRe_Color m_currentBrickColor;
        bool m_canPlaceHere = false;
        float m_nubDockThreshold = 0.01f;
        float m_nubDirThreshold = 0.01f;

        bool m_placeBelow;

        CHistory* m_pHistory;

        int m_playerIdx;

        TheBrick::CGameObject* m_pCurrentBrickObject;
        TheBrick::CBrickInstance* m_pCurrentBrick;

        TheBrick::CSpaceship* m_pSpaceship;

        PuRe_IMaterial* m_pGridMaterial;
        PuRe_Model* m_pGridBrick;

        bool lastInputIsGamepad;

    public:
        CEditorCamera* GetCamera() const
        {
            return this->m_pCamera;
        }
        void DrawDebug(PuRe_IGraphics* a_pGraphics)
        {
            m_pCurrentBrickObject->Draw(a_pGraphics, m_pCamera);
            this->m_pSpaceship->Draw(a_pGraphics, m_pCamera);
        }

    public:
        CBrickWorker(int a_playerIdx);
        ~CBrickWorker();

        void Initialize(PuRe_IGraphics& a_pGraphics);
        void Update(PuRe_IGraphics& a_pGraphics, PuRe_IWindow& a_pWindow, PuRe_IInput& a_pInput, PuRe_Timer& a_pTimer, PuRe_SoundPlayer& a_pSoundPlayer, TheBrick::CBrick* a_pCurrentBrick, PuRe_Color& a_rCurrentColor);
        void Render();

    private:
        void UpdateTranslation(PuRe_IInput& a_pInput, PuRe_Vector3F a_cameraLook, float a_speed);
        void UpdateRotation(PuRe_IInput& a_pInput, float a_rotationPerClick);
        void UpdateHeight(PuRe_IInput& a_pInput);
        void ApplyToCurrentBrick();
        void UpdatePlacement(PuRe_IInput& a_pInput);
    };
}

#endif /* _BRICKWORKER_H_ */