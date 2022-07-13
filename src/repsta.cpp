#include "repsta.hpp"
#include "env.hpp"

#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <cstdio>
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
        ("detailed,d", "displays very detailed information.")
        ("logfile,l", po::value<std::string>() , "saves a log file on the system. add the path after = where you want to save.");

      // I get the necessary keys from the user options
      po::variables_map vm;
      po::store(po::parse_command_line(argc, argv, desc), vm);
      po::notify(vm);
      
      // Display help
      if ( vm.count("help") ) {
        fmt::print("\nAuthors: {authors}\nVersion: {version}\nBrief: {brief}\n\nUSAGE:\n\n\t{description}\n\n",
            fmt::arg("authors",env::program_authors),
            fmt::arg("version", env::program_verison),
            fmt::arg("brief", env::program_brief),
            fmt::arg("description", "repsta [OPTIONS] [SUBCOMMAND]"));
        std::cout << desc;
        exit(1);
      }
      // Collect info repository
      else if ( vm.count("detailed") ) {
        fmt::print("Very interesting information.");
      }
      else if ( vm.count("version") ) {
        fmt::print("{}: {}",
            fmt::format(fg(fmt::color::green_yellow), "version"),
            fmt::format(fg(fmt::color::crimson), env::program_verison));
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
      fmt::print(stderr, "{}: {}.\nTry 'repsta --help' for more information.",
          fmt::format(fmt::emphasis::bold | fg(fmt::color::red),"error"),
          e.what());
      exit(1);
    }
  }
}
