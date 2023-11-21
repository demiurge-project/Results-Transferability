/**
 * @file <ChocolateGiantAACLoopFunc.cpp>
 *
 * @author Miquel Kegeleirs - <Miquel.Kegeleirs@ulb.be>
 *
 * @license MIT License
 */

#include "ChocolateGiantAACLoopFunc.h"

/****************************************/
/****************************************/

ChocolateGiantAACLoopFunction::ChocolateGiantAACLoopFunction()
{
  m_fRadius = 1.17;
  m_cCoordBlackSpot = CVector2(0, 2.35);
  m_cCoordWhiteSpot = CVector2(0, -2.35);
  m_fObjectiveFunction = 0;
}

/****************************************/
/****************************************/

ChocolateGiantAACLoopFunction::ChocolateGiantAACLoopFunction(const ChocolateGiantAACLoopFunction &orig) {}

/****************************************/
/****************************************/

void ChocolateGiantAACLoopFunction::Init(TConfigurationNode& t_tree) {
    RVRCoreLoopFunctions::Init(t_tree);
}
/****************************************/
/****************************************/

ChocolateGiantAACLoopFunction::~ChocolateGiantAACLoopFunction() {}

/****************************************/
/****************************************/

void ChocolateGiantAACLoopFunction::Destroy() {}

/****************************************/
/****************************************/

void ChocolateGiantAACLoopFunction::Reset()
{
  m_fObjectiveFunction = 0;
  RVRCoreLoopFunctions::Reset();
}

/****************************************/
/****************************************/

argos::CColor ChocolateGiantAACLoopFunction::GetFloorColor(const argos::CVector2 &c_position_on_plane)
{
  CVector2 vCurrentPoint(c_position_on_plane.GetX(), c_position_on_plane.GetY());
  Real d = (m_cCoordBlackSpot - vCurrentPoint).Length();
  if (d <= m_fRadius)
  {
    return CColor::BLACK;
  }

  d = (m_cCoordWhiteSpot - vCurrentPoint).Length();
  if (d <= m_fRadius)
  {
    return CColor::WHITE;
  }

  return CColor::GRAY50;
}

/****************************************/
/****************************************/

void ChocolateGiantAACLoopFunction::PostStep()
{
  CSpace::TMapPerType &tRVRMap = GetSpace().GetEntitiesByType("rvr");
  CVector2 cRVRPosition(0, 0);
  for (CSpace::TMapPerType::iterator it = tRVRMap.begin(); it != tRVRMap.end(); ++it)
  {
    CRVREntity *pcRVR = any_cast<CRVREntity *>(it->second);
    if(m_bRealRobot)
    {
      cRVRPosition = GetRealPosition(*pcRVR);
    }
    else
    {
      cRVRPosition.Set(pcRVR->GetEmbodiedEntity().GetOriginAnchor().Position.GetX(),
                       pcRVR->GetEmbodiedEntity().GetOriginAnchor().Position.GetY());
    }
    Real fDistanceSpot = (m_cCoordBlackSpot - cRVRPosition).Length();
    if (fDistanceSpot <= m_fRadius)
    {
      m_fObjectiveFunction += 1;
    }
  }
}


/****************************************/
/****************************************/

Real ChocolateGiantAACLoopFunction::GetObjectiveFunction()
{
  if (m_bMinimizeScore) {
      return -m_fObjectiveFunction;
  }
  else {
      return m_fObjectiveFunction;
  }
}

/****************************************/
/****************************************/

CVector3 ChocolateGiantAACLoopFunction::GetRandomPosition()
{
  Real temp;
  Real a = m_pcRng->Uniform(CRange<Real>(0.0f, 1.0f));
  Real b = m_pcRng->Uniform(CRange<Real>(0.0f, 1.0f));
  // If b < a, swap them
  if (b < a)
  {
    temp = a;
    a = b;
    b = temp;
  }
  Real fPosX = b * m_fDistributionRadius * cos(2 * CRadians::PI.GetValue() * (a / b));
  Real fPosY = b * m_fDistributionRadius * sin(2 * CRadians::PI.GetValue() * (a / b));

  return CVector3(fPosX, fPosY, 0);
}

/****************************************/
/****************************************/

void ChocolateGiantAACLoopFunction::PostExperiment()
{
  if (m_bOutputInFile)
  {
    m_cOutFile << m_fObjectiveFunction << std::endl;
  }
  else
  {
    LOG << m_fObjectiveFunction << std::endl;
  }
}

REGISTER_LOOP_FUNCTIONS(ChocolateGiantAACLoopFunction, "chocolate_giant_aac_loop_functions");
