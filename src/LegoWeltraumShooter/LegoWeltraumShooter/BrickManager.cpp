#include "include/BrickManager.h"
namespace Game
{
    // **************************************************************************
    // **************************************************************************
    CBrickManager::CBrickManager()
    {

    }

    // **************************************************************************
    // **************************************************************************
    CBrickManager::~CBrickManager()
    {

    }

    // **************************************************************************
    // **************************************************************************
    void CBrickManager::Load(const char* a_pFolder)
    {
        
    }

    // **************************************************************************
    // **************************************************************************
    CBrick* CBrickManager::GetBrick(int32 a_id)
    {
        #ifdef DEBUG
            try //Bounds checking
            {
                return this->m_bricks.at(a_id);
            }
            catch (std::out_of_range)
            {
                return nullptr;
            }
        #else
            return this->m_bricks[a_id];
        #endif
    }
}