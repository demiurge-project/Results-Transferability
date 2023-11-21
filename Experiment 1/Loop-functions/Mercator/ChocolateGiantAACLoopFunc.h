/*
 * Aggregation with Ambient Clues for the RVR
 *
 * @author Miquel Kegeleirs - <Miquel.Kegeleirs@ulb.be>
 */

#ifndef CHOCOLATE_GIANT_AAC_LOOP_FUNC_H
#define CHOCOLATE_GIANT_AAC_LOOP_FUNC_H

#include "../../src/RVRCoreLoopFunctions.h"
#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/robots/rvr/simulator/rvr_entity.h>

using namespace argos;

class ChocolateGiantAACLoopFunction : public RVRCoreLoopFunctions {

   public:
      ChocolateGiantAACLoopFunction();
      ChocolateGiantAACLoopFunction(const ChocolateGiantAACLoopFunction& orig);
      virtual ~ChocolateGiantAACLoopFunction();

      virtual void Init(TConfigurationNode& t_tree);
      virtual void Destroy();
      virtual void Reset();
      virtual void PostStep();
      virtual void PostExperiment();

      Real GetObjectiveFunction();

      virtual CColor GetFloorColor(const CVector2& c_position_on_plane);

      virtual CVector3 GetRandomPosition();

    private:
      Real m_fRadius;
      CVector2 m_cCoordBlackSpot;
      CVector2 m_cCoordWhiteSpot;

      Real m_fObjectiveFunction;
};

#endif
