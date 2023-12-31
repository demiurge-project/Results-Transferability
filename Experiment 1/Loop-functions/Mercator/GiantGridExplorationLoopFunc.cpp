#include "GiantGridExplorationLoopFunc.h"

/****************************************/
/****************************************/

GiantGridExplorationLoopFunction::GiantGridExplorationLoopFunction()
{

    m_arenaSize = 9.65;
    m_gridSize = 10;
    m_grid.assign(m_gridSize, std::vector<int>(m_gridSize, 0));

    m_fObjectiveFunction = 0;
}

/****************************************/
/****************************************/

GiantGridExplorationLoopFunction::GiantGridExplorationLoopFunction(const GiantGridExplorationLoopFunction &orig) {}

/****************************************/
/****************************************/

GiantGridExplorationLoopFunction::~GiantGridExplorationLoopFunction() {}

/****************************************/
/****************************************/

void GiantGridExplorationLoopFunction::Destroy() {}

/****************************************/
/****************************************/

void GiantGridExplorationLoopFunction::Reset()
{
    RVRCoreLoopFunctions::Reset();

    m_grid.assign(m_gridSize, std::vector<int>(m_gridSize, 0));
    m_fObjectiveFunction = 0;
}

/****************************************/
/****************************************/

void GiantGridExplorationLoopFunction::Init(TConfigurationNode &t_tree)
{
    RVRCoreLoopFunctions::Init(t_tree);
}

argos::CColor GiantGridExplorationLoopFunction::GetFloorColor(const argos::CVector2 &c_position_on_plane)
{
    /*
    CVector2 vCurrentPoint(c_position_on_plane.GetX(), c_position_on_plane.GetY());
    if (abs(vCurrentPoint.GetX()) > m_arenaSize/2.0 || abs(vCurrentPoint.GetY()) > m_arenaSize/2.0 ) {
        return CColor::WHITE;
    }
    if ( (m_gridSize*(vCurrentPoint.GetX()/m_arenaSize+0.5)) - floor(m_gridSize*(vCurrentPoint.GetX()/m_arenaSize+0.5)) < 0.1) {
        return CColor::WHITE;
    }
    if ( (m_gridSize*(vCurrentPoint.GetY()/m_arenaSize+0.5)) - floor(m_gridSize*(vCurrentPoint.GetY()/m_arenaSize+0.5)) < 0.1) {
        return CColor::WHITE;
    }
    */
    return CColor::GRAY50;
}

CVector3 GiantGridExplorationLoopFunction::GetRandomPosition()
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

void GiantGridExplorationLoopFunction::PostStep()
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
        UInt32 X = (UInt32)m_gridSize * (cRVRPosition.GetX() / m_arenaSize + 0.5);
        UInt32 Y = (UInt32)m_gridSize * (cRVRPosition.GetY() / m_arenaSize + 0.5);
        if (X < m_gridSize && Y < m_gridSize && X >= 0 && Y >= 0)
	{
            m_grid[X][Y] = 0;
        }
    }

    UInt32 total = 0;
    for (UInt32 i = 0; i < m_gridSize; i++)
    {
        for (UInt32 j = 0; j < m_gridSize; j++)
        {
            total += m_grid[i][j];
            m_grid[i][j] += 1;
        }
    }

    m_fObjectiveFunction += Real(total);
}

/****************************************/
/****************************************/

void GiantGridExplorationLoopFunction::PostExperiment()
{
    m_fObjectiveFunction = -m_fObjectiveFunction / m_gridSize / m_gridSize;
    if (m_bOutputInFile)
    {
        m_cOutFile << m_fObjectiveFunction << std::endl;
    }
    else
    {
        LOG << m_fObjectiveFunction << std::endl;
    }
}

Real GiantGridExplorationLoopFunction::GetObjectiveFunction()
{
    if (m_bMinimizeScore) {
      return -m_fObjectiveFunction;
    }
    else {
        return m_fObjectiveFunction;
    }
}

REGISTER_LOOP_FUNCTIONS(GiantGridExplorationLoopFunction, "giant_grid_exploration_loop_functions");
