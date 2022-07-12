#include "repsta.hpp"

#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <exception>
#include <fmt/core.h>
#include <fmt/color.h>
#include <stdexcept>
#include <iostream>

namespace reps {
  Repsta::Repsta(int argc, char *argv[]) {
    namespace po = boost::program_options; // shorthand for using namespace

    try {
      // create program option keys
      po::options_description desc("OPTIONS");
      desc.add_options()
        ("help,h", "produce help message.")
        ("version,v", "produce version message.")
        ("collection,c", "displays information about the repository.")
        ("logfile,l", po::value<std::string>() , "saves a log file on the system.");

      // I get the necessary keys from the user options
      po::variables_map vm;
      po::store(po::parse_command_line(argc, argv, desc), vm);
      po::notify(vm);
      
      // Display help
      if ( vm.count("help") ) {
        /* std::cout << desc; */
        fmt::print("\nTool for gathering statistics about a repository.\
          \n\nUSAGE:\n\n\trepsta [OPTIONS] [SUBCOMMAND]\n\n");
        std::cout << desc;
        exit(1);
      }
      // Collect info repository
      else if ( vm.count("collection") ) {
        fmt::print("Very interesting information.");
      }
      else if ( vm.count("logfile") ) {
        fmt::print("Log save here: \"{}\".", vm["logfile"].as<std::string>());
      }
      // Write log with info repository on system
      else {
      // old version // fmt::print("repsta: missing operand\nTry 'repsta --help' for more information.");
        fmt::print("Try 'repsta --help' for more information.");
        exit(1);
      }
    }
    catch(std::exception const&e) {
      /// Display error
      fmt::print(stderr, fmt::emphasis::bold | fg(fmt::color::red),"error");
      fmt::print(stderr, ": {}.\nTry 'repsta --help' for more information.", e.what());
      exit(1);
    }
  }
}
