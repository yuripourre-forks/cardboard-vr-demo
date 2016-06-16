// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DeadZoneMenuController.h"
#include "DeadZoneMenuItem.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            
            DeadZoneMenuController::DeadZoneMenuController(IDeadZoneMenuItemObservable& DeadZoneMenuItemObservable, IDeadZoneMenuItemViewFactory& viewFactory, IUIInteractionObservable& p_IUIInteractionObservable , IUICameraProvider& p_UICameraProvider)
            : m_DeadZoneMenuItemRepository(DeadZoneMenuItemObservable)
            , m_viewFactory(viewFactory)
            , m_pIUIInteractionObservable(p_IUIInteractionObservable)
            , m_UICameraProvider(p_UICameraProvider)
            {
                
                shouldReposition = false;
                m_DeadZoneMenuItemRepository.AddDeadZoneMenuObserver(this);
            }
            
            DeadZoneMenuController::~DeadZoneMenuController()
            {
                m_DeadZoneMenuItemRepository.RemoveDeadZoneMenuObserver(this);
                
                for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
                {
                    DeadZoneMenuItemView* pView = it->second;
                    m_pIUIInteractionObservable.UnRegisterInteractableItem(pView);
                    Eegeo_DELETE pView;
                }
                m_viewsByModel.clear();
            }
            
            void DeadZoneMenuController::Update(float deltaTime)
            {
                if(shouldReposition)
                {    
                    PositionItems();
                }
                
                for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
                {
                    DeadZoneMenuItemView* view = it->second;
                    view->Update(deltaTime);
                }
            }
            
            void DeadZoneMenuController::OnDeadZoneMenuItemAdded(DeadZoneMenuItem& DeadZoneMenuItem)
            {
                Eegeo_ASSERT(!HasViewForModel(DeadZoneMenuItem), "Attempt to add duplicate model to DeadZoneMenuController.");
                
                DeadZoneMenuItemView* pView = m_viewFactory.CreateViewForDeadZoneMenuItem(DeadZoneMenuItem);
                m_viewsByModel[&DeadZoneMenuItem] = pView;
                
                m_pIUIInteractionObservable.RegisterInteractableItem(pView);
                shouldReposition = true;
            }
            
            void DeadZoneMenuController::OnDeadZoneMenuItemRemoved(DeadZoneMenuItem& DeadZoneMenuItem)
            {
                Eegeo_ASSERT(HasViewForModel(DeadZoneMenuItem), "Attempt to remove unknown model from DeadZoneMenuController.");
                DeadZoneMenuItemView* pView = GetViewForModel(DeadZoneMenuItem);
                
                m_viewsByModel.erase(&DeadZoneMenuItem);
                m_pIUIInteractionObservable.UnRegisterInteractableItem(pView);
                
                Eegeo_DELETE(pView);
            }
            
            
            void DeadZoneMenuController::PositionItems()
            {
                
                shouldReposition = false;
                
                int halfCount = (int) m_viewsByModel.size()/2;
                
                Eegeo::dv3 center = m_UICameraProvider.GetRenderCameraForUI().GetEcefLocation();
                
                Eegeo::v3 right(m_UICameraProvider.GetOrientation().GetRow(0));
                Eegeo::v3 forward(m_UICameraProvider.GetOrientation().GetRow(2));
                
                for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
                {
                    DeadZoneMenuItemView* view = it->second;
                    Eegeo::dv3 position(center + (forward*-350) + (right*(50*halfCount)));
                    view->SetEcefPosition(position);
                    halfCount --;
                    
                }
            }
            
            DeadZoneMenuItemView* DeadZoneMenuController::GetViewForModel(const DeadZoneMenuItem& jp) const
            {
                TViewsByModel::const_iterator foundJP = m_viewsByModel.find(const_cast<DeadZoneMenuItem*>(&jp));
                
                if(foundJP != m_viewsByModel.end())
                {
                    return foundJP->second;
                }
                
                return NULL;
            }
            
            bool DeadZoneMenuController::HasViewForModel(const DeadZoneMenuItem& jp) const
            {
                return (GetViewForModel(jp) != NULL);
            }
            
            
        }
    }
}
