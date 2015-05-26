#include "include/TheBrick/BrickInstance.h"
#include "include/TheBrick/Conversion.h"

namespace TheBrick
{
    // **************************************************************************
    // **************************************************************************
    CBrickInstance::CBrickInstance(CBrick& a_pBrick, ong::World& a_pWorld, PuRe_Color a_pColor)
    {
        this->m_pBrick = &a_pBrick;
        for (size_t i = 0; i < this->m_pBrick->GetColliderData().size(); i++)
        {
            this->m_pCollider.push_back(a_pWorld.createCollider(this->m_pBrick->GetColliderData()[i]));
        }
        this->m_Color = a_pColor;
        a_pBrick.AddInstance(*this);
    }

    // **************************************************************************
    // **************************************************************************
    CBrickInstance::~CBrickInstance()
    {
        this->m_pBrick->DeleteInstance(*this);
    }

    // **************************************************************************
    // **************************************************************************
    void CBrickInstance::Draw(PuRe_IGraphics* a_pGraphics, PuRe_Camera* a_pCamera)
    {
        this->m_pBrick->Draw(a_pGraphics, a_pCamera, TheBrick::OngToPuRe(this->m_Transform.p), TheBrick::OngToPuRe(this->m_Transform.q).GetMatrix(), this->m_Color);
    }

    // **************************************************************************
    // **************************************************************************
    void CBrickInstance::RotateAroundPivotOffset(PuRe_QuaternionF a_Quaternion)
    {
        //Get
        PuRe_Vector3F pivotOffset = this->m_pBrick->GetPivotOffset();
        ong::Transform currentTransform = this->GetTransform();
        ong::Transform newTransform;
        //Rotation
        newTransform.q = PuReToOng(a_Quaternion) * currentTransform.q;
        //Position
        PuRe_MatrixF rotTransform = PuRe_MatrixF::Translation(-pivotOffset) * a_Quaternion.GetMatrix() * PuRe_MatrixF::Translation(pivotOffset);
        newTransform.p = currentTransform.p + ong::vec3(0, 0, 0) * PuReToOng(rotTransform) - PuReToOng(pivotOffset * OngToPuRe(newTransform.q).GetMatrix());
        //Set
        this->SetTransform(newTransform);
    }
}