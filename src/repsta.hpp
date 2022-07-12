#pragma once
#include <memory>

#include "statisticscollector.hpp"

namespace reps 
{
  /*!
   * \brief Repsta is the main class of the program for its work
   */
  class Repsta final {
    private:
      std::unique_ptr<StatisticsCollector> m_collector; //! A class that collects statistics for display from the repository 
    public:
      /*!
       * \param[in] argc number of program options
       * \param[in] argv list of program options
       */
      Repsta(int argc, char *argv[]);

      Repsta(Repsta &&repsta) = default;
      Repsta& operator=(const Repsta &repsta) = delete;
      Repsta& operator=(Repsta &&repsta) = default;
  };
}
