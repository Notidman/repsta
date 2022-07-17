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
      po::options_description desc("Options");
      desc.add_options()
        ("help,h", "produce help message.")
        ("version,v", "produce version message.")
        ("date,d", "displays the creation date of the repository.")
        ("creator,c", "displays the creator of the repository.")
        ("fast,f", "displays brief information about the repository without tui.")
        ("logfile,l", po::value<std::string>() , "saves a log file on the system. add the path after = where you want to save.");

      // I get the necessary keys from the user options
      po::variables_map vm;
      po::store(po::parse_command_line(argc, argv, desc), vm);
      po::notify(vm);
      
      // Display help
      if ( vm.count("help") ) {
        fmt::print("\nAuthors: {authors}\nVersion: {version}\nBrief discription: {brief}\n\nUsage:\n\t{usage}\n\n",
            fmt::arg("authors",env::program_authors),
            fmt::arg("version", env::program_verison),
            fmt::arg("brief", env::program_brief),
            fmt::arg("usage", "repsta [OPTIONS] [SUBCOMMAND]"));
        std::cout << desc;
        exit(1);
      }
      // Display verison
      else if ( vm.count("version") ) {
        fmt::print("{}: {}",
            fmt::format(fg(fmt::color::green_yellow), "version"),
            fmt::format(fg(fmt::color::crimson), env::program_verison));
      }
      // Display creation date
      else if ( vm.count("date") ) {
        fmt::print("12/12/12 23:23:23.");
      }
      // Display creator
      else if ( vm.count("creator") ) {
        fmt::print("It's a me! Luigi.");
      }
      // Display brief information
      else if ( vm.count("fast") ) {
        fmt::print("GOTTA GO FAST");
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
