#include <cstdlib>
#include "repsta.hpp"

/*!
 * \brief The main function creates the Repsta class for the program to work.
 * \authors notidman
 * \version 0.1
 * \date 11-07-22
 * \copyright GNU General Public License v3.0
 */

int 
main(int argc, char *argv[]) {
  auto repsta{std::make_unique<reps::Repsta>(argc, argv)};
  return EXIT_SUCCESS;
}
