/*
 * Aggregation with Ambient Clues
 *
 * @author Antoine Ligot - <aligot@ulb.ac.be>
 */

#ifndef CHOCOLATE_AAC_LOOP_FUNC_H
#define CHOCOLATE_AAC_LOOP_FUNC_H

#include "../../../src/CoreLoopFunctions.h"
#include <argos3/core/simulator/space/space.h>
#include <argos3/plugins/robots/e-puck/simulator/epuck_entity.h>

using namespace argos;

class ChocolateAACLoopFunction : public CoreLoopFunctions {

   public:
      ChocolateAACLoopFunction();
      ChocolateAACLoopFunction(const ChocolateAACLoopFunction& orig);
      virtual ~ChocolateAACLoopFunction();

      virtual void Destroy();
      virtual void Init(TConfigurationNode &t_tree);
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
     /**
      * The path of the output file.
      */
      std::string m_strOutFile;

     /**
      * The stream associated to the output file.
      */
      std::ofstream m_cOutFile;
};

#endif
