#ifndef _EDITORSHIPHANDLER_H_
#define _EDITORSHIPHANDLER_H_

#include <PuReEngine/Core.h>
#include <PuReEngine/Defines.h>
#include <Onager/World.h>

#include "Spaceship.h"
#include "Navigation.h"

#include "include/Space.h"

namespace TheBrick
{
    class CSpaceship;
    class CBrickInstance;
}

namespace Editor
{
    class CShipHandler
    {

    public:

    private:
        int m_playerIdx;

        sba::CNavigation* m_pNavigation;
        sba::CSpaceship* m_pCurrentSpaceship;

        PuRe_Vector2F m_PreviewOffset = PuRe_Vector2F(200.0f, 0.0f);
        PuRe_Vector2F m_TextOffset = PuRe_Vector2F(-400.0f, -100.0f);
        PuRe_Vector2F m_TextStep = PuRe_Vector2F(0.0f, -50.0f);
        float m_OuterPreviewInset = 100;


    public:
        sba::CSpaceship* GetCurrentSpaceShip()
        {
            return this->m_pCurrentSpaceship;
        }

    public:
        CShipHandler(int a_playerIdx);
        ~CShipHandler();

        void Update();
        void Render();

        void AddShip(const char* a_pName);
        void SaveCurrentShip();
        void ResetCurrentShip();
        void DeleteCurrentShip();

        TheBrick::CBrickInstance* AddBrickInstanceToCurrentShip(const TheBrick::CBrickInstance& a_pTemplate);

        void UpdateCurrentShipPreview();
    };
}

#endif /* _EDITORSHIPHANDLER_H_ */