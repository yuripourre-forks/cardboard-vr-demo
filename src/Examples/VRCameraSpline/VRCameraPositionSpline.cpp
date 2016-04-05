//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#include "VRCameraPositionSpline.h"
#include "Logger.h"

namespace Eegeo
{
    namespace VR
    {
        void VRCameraPositionSpline::AddPoint(const dv3& ecefEyePoint, const m33& orientation)
        {
            m_positionSpline.AddPoint(ecefEyePoint);
            
            v3 right = orientation.GetRow(0);
            v3 up = orientation.GetRow(1);
            v3 forward = orientation.GetRow(2);

            m_rightSpline.AddPoint(dv3(right.x, right.y, right.z));
            m_upSpline.AddPoint(dv3(up.x, up.y, up.z));
            m_forwardSpline.AddPoint(dv3(forward.x, forward.y, forward.z));
        }
        
        void VRCameraPositionSpline::setSlowDownFactor(float slowDownFactor){
            m_slowDownFactor = slowDownFactor;
        }
        
        void VRCameraPositionSpline::Clear()
        {
            m_positionSpline.Clear();
            m_rightSpline.Clear();
            m_upSpline.Clear();
            m_forwardSpline.Clear();
        }
        
        void VRCameraPositionSpline::Spew()
        {
            const std::vector<Geometry::CatmullRomSplinePoint>& rightPoints = m_rightSpline.GetPoints();
            const std::vector<Geometry::CatmullRomSplinePoint>& upPoints = m_upSpline.GetPoints();
            const std::vector<Geometry::CatmullRomSplinePoint>& forwardPoints = m_forwardSpline.GetPoints();
            const std::vector<Geometry::CatmullRomSplinePoint>& positionPoints = m_positionSpline.GetPoints();

            
            for(int i =0; i< rightPoints.size();i++)
            {
                const dv3 right = rightPoints.at(i).Position;
                const dv3 up = upPoints.at(i).Position;
                const dv3 forward = forwardPoints.at(i).Position;
                const dv3 position = positionPoints.at(i).Position;
                printf("orientation.SetFromBasis(Eegeo::v3(%f,%f,%f),Eegeo::v3(%f,%f,%f),Eegeo::v3(%f,%f,%f));\n", right.x,right.y,right.z,up.x,up.y,up.z,forward.x,forward.y,forward.z);
                printf("AddPoint(Eegeo::dv3(%f,%f,%f), orientation);\n",position.x,position.y,position.z);
            }
        }
        
        void VRCameraPositionSpline::Start()
        {
            
            if(m_positionSpline.GetNumberOfPoints() == 0)
            {
                return;
            }
            
            m_time = 0.0;
            m_playing = true;
        }
        
        void VRCameraPositionSpline::Stop()
        {
            m_playing = false;
        }
        
        void VRCameraPositionSpline::Update(float dt)
        {
            m_currentPlaybackSpeed = m_playbackSpeed * m_slowDownFactor;
            if(m_playing)
            {
                m_time += dt * m_currentPlaybackSpeed;
                if(m_time >= 1.0)
                {
                    Stop();
                }
                
                m_time = Math::Clamp01(m_time);
            }
        }
        
        void VRCameraPositionSpline::GetCurrentCameraPosition(dv3& interpolatedPositionEcef, m33& interpolatedOrientation) const
        {
            m_positionSpline.GetInterpolatedPositionInPlace(m_time, interpolatedPositionEcef);
            dv3 forward;
            dv3 up;
            dv3 right;
            m_forwardSpline.GetInterpolatedPositionInPlace(m_time, forward);
            m_upSpline.GetInterpolatedPositionInPlace(m_time, up);
            m_rightSpline.GetInterpolatedPositionInPlace(m_time, right);
            interpolatedOrientation.SetRow(0, right.Norm().ToSingle());
            interpolatedOrientation.SetRow(1, up.Norm().ToSingle());
            interpolatedOrientation.SetRow(2, forward.Norm().ToSingle());
            
        }
        
        void VRCameraPositionSpline::NextSpline()
        {
            const int MaxSpline = 1;
            ++m_currentSpline;
            if (m_currentSpline > MaxSpline)
            {
                m_currentSpline = 0;
            }
            SetSpline(m_currentSpline);
        }
        
        void VRCameraPositionSpline::SetSpline(int splineId)
        {
            Clear();
            
            float p = 1.0f;
            m33 orientation;
            switch(splineId)
            {
                case 0: // NY
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.003297,-0.301644,0.953413),Eegeo::v3(0.728825,0.652078,0.208825),Eegeo::v3(0.684698,-0.695559,-0.217691));
                    AddPoint(Eegeo::dv3(4645944.411084, 4162311.163091, 1332741.260517), orientation);
                    orientation.SetFromBasis(Eegeo::v3(-0.003297,-0.301644,0.953413),Eegeo::v3(0.728825,0.652078,0.208825),Eegeo::v3(0.684698,-0.695559,-0.217691));
                    AddPoint(Eegeo::dv3(4645465.299021, 4162797.875165, 1332893.588509), orientation);
                    orientation.SetFromBasis(Eegeo::v3(-0.003297,-0.301644,0.953413),Eegeo::v3(0.728825,0.652078,0.208825),Eegeo::v3(0.684698,-0.695559,-0.217691));
                    AddPoint(Eegeo::dv3(4644833.347104, 4163439.851552, 1333094.510118), orientation);
                    orientation.SetFromBasis(Eegeo::v3(-0.003297,-0.301644,0.953413),Eegeo::v3(0.728825,0.652078,0.208825),Eegeo::v3(0.684698,-0.695559,-0.217691));
                    AddPoint(Eegeo::dv3(4644239.922460, 4164042.689519, 1333283.182439), orientation);
                    orientation.SetFromBasis(Eegeo::v3(-0.003297,-0.301644,0.953413),Eegeo::v3(0.728825,0.652078,0.208825),Eegeo::v3(0.684698,-0.695559,-0.217691));
                    AddPoint(Eegeo::dv3(4643677.358429, 4164614.177336, 1333462.042993), orientation);
                    orientation.SetFromBasis(Eegeo::v3(0.622116,-0.501066,-0.601582),Eegeo::v3(0.727658,0.653615,0.208093),Eegeo::v3(-0.288928,0.567207,-0.771233));
                    AddPoint(Eegeo::dv3(4643274.312695, 4164792.927187, 1333528.844561), orientation);
                    orientation.SetFromBasis(Eegeo::v3(0.068765,0.233774,-0.969854),Eegeo::v3(0.727139,0.653852,0.209162),Eegeo::v3(-0.683033,0.719609,0.125021));
                    AddPoint(Eegeo::dv3(4643042.347450, 4164609.062235, 1333691.663462), orientation);
                    
                    break;
                    
                case 1: // SF
                    
                     orientation.SetFromBasis(Eegeo::v3(0.449058,0.122659,0.885043),Eegeo::v3(0.667273,0.612706,-0.423481),Eegeo::v3(0.594215,-0.780735,-0.193294));
                     AddPoint(Eegeo::dv3(4256102.665643, 3908033.687894, -2700980.817413), orientation);
                     orientation.SetFromBasis(Eegeo::v3(0.317570,0.280255,0.905873),Eegeo::v3(0.667276,0.612702,-0.423481),Eegeo::v3(0.673713,-0.738955,-0.007569));
                     AddPoint(Eegeo::dv3(4256121.872745, 3908040.075322, -2700843.217141), orientation);
                     orientation.SetFromBasis(Eegeo::v3(0.091987,0.496432,0.863187),Eegeo::v3(0.667288,0.612690,-0.423479),Eegeo::v3(0.739096,-0.614952,0.274904));
                     AddPoint(Eegeo::dv3(4256137.972563, 3908074.451393, -2700700.106807), orientation);
                     orientation.SetFromBasis(Eegeo::v3(-0.389510,0.771711,0.502735),Eegeo::v3(0.667321,0.612675,-0.423447),Eegeo::v3(0.634794,-0.170551,0.753626));
                     AddPoint(Eegeo::dv3(4256041.568475, 3908234.288441, -2700709.616101), orientation);
                     orientation.SetFromBasis(Eegeo::v3(-0.396365,0.773514,0.494541),Eegeo::v3(0.667322,0.612675,-0.423446),Eegeo::v3(0.630536,-0.162181,0.759028));
                     AddPoint(Eegeo::dv3(4255987.064053, 3908263.446745, -2700775.918628), orientation);
                     orientation.SetFromBasis(Eegeo::v3(-0.126863,0.653785,0.745968),Eegeo::v3(0.667305,0.612672,-0.423478),Eegeo::v3(0.733901,-0.444067,0.514000));
                     AddPoint(Eegeo::dv3(4255934.864160, 3908262.422243, -2700822.034474), orientation);
                     orientation.SetFromBasis(Eegeo::v3(0.058661,0.523607,0.849937),Eegeo::v3(0.667290,0.612674,-0.423498),Eegeo::v3(0.742484,-0.592000,0.313458));
                     AddPoint(Eegeo::dv3(4255880.366696, 3908290.190068, -2700867.734507), orientation);
                     orientation.SetFromBasis(Eegeo::v3(0.116586,0.475679,0.871858),Eegeo::v3(0.667287,0.612675,-0.423504),Eegeo::v3(0.735621,-0.631156,0.245983));
                     AddPoint(Eegeo::dv3(4255834.981675, 3908342.549457, -2700910.800525), orientation);
                     orientation.SetFromBasis(Eegeo::v3(0.234662,0.366726,0.900247),Eegeo::v3(0.667274,0.612676,-0.423518),Eegeo::v3(0.706879,-0.700098,0.100933));
                     AddPoint(Eegeo::dv3(4255780.004911, 3908424.134481, -2700938.035865), orientation);
                     orientation.SetFromBasis(Eegeo::v3(0.173796,0.424834,0.888432),Eegeo::v3(0.667280,0.612674,-0.423510),Eegeo::v3(0.724246,-0.666440,0.177001));
                     AddPoint(Eegeo::dv3(4255654.784223, 3908533.602955, -2700976.967388), orientation);
                     orientation.SetFromBasis(Eegeo::v3(0.231126,0.370224,0.899731),Eegeo::v3(0.667273,0.612674,-0.423521),Eegeo::v3(0.708045,-0.698255,0.105433));
                     AddPoint(Eegeo::dv3(4255550.596605, 3908624.779908, -2701009.221501), orientation);
                     orientation.SetFromBasis(Eegeo::v3(0.659192,-0.220850,0.718813),Eegeo::v3(0.667188,0.612709,-0.423605),Eegeo::v3(0.346873,-0.758822,-0.551246));
                     AddPoint(Eegeo::dv3(4255428.695225, 3908776.976528, -2700981.091835), orientation);
                     orientation.SetFromBasis(Eegeo::v3(0.727191,-0.659140,0.191653),Eegeo::v3(0.667089,0.612795,-0.423632),Eegeo::v3(-0.161787,-0.435910,-0.885333));
                     AddPoint(Eegeo::dv3(4255482.044510, 3908930.061602, -2700927.013249), orientation);
                     orientation.SetFromBasis(Eegeo::v3(-0.411068,-0.171086,-0.895407),Eegeo::v3(0.667069,0.613004,-0.423361),Eegeo::v3(-0.621319,0.771339,0.137860));
                     AddPoint(Eegeo::dv3(4255490.309183, 3908942.927425, -2700907.697746), orientation);
                    break;
            }
        }
    }
}
