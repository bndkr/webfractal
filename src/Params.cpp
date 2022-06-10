#include "Params.hpp"

#include <iostream>
#include <string>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

Params::Params(int argc, char** argv)
{
    // Command line options
    po::options_description generic("Generic options");
    generic.add_options()
        ("version,v", "display version")
        ("help,h", "produce help message")
        ("config,c", po::value<std::string>(), "path to config file")
        ;
    
    po::options_description config("Fractal Configuration");
    config.add_options()
        ("xmin", po::value<double>(), "minimum x value")
        ("ymin", po::value<double>(), "minimum y value")
        ("xmax", po::value<double>(), "maximum x value")
        ("ymax", po::value<double>(), "maximum y value")
        ("height", po::value<uint32_t>(), "height of image in pixels")
        ("width", po::value<uint32_t>(), "width of image in pixels")
        ("iterations", po::value<uint32_t>(), "number of iterations")
        ("num-colors", po::value<std::uint32_t>(), "number of colors in palette")
        ("color", po::value<std::vector<uint32_t>>()->composing(), "color values")
        ("fractal", po::value<std::string>(), "name of fractal")
        ;

    po::options_description cmdlineOptions;
    cmdlineOptions.add(generic).add(config);

    po::options_description configFileOptions;
    configFileOptions.add(generic).add(config);

    po::options_description visibleOptions;
    visibleOptions.add(generic).add(config);

    po::variables_map vm;

    po::store(po::parse_command_line(argc, argv, cmdlineOptions), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << visibleOptions << std::endl;
        exit(1);
    }

    if (!vm.count("config"))
    {
        std::cout << "Error: config path not set." << std::endl;
        exit(1);
    }
    std::string configFilePath = vm["config"].as<std::string>();
    std::cout << "Using config path: " << configFilePath << std::endl;

    po::store(po::parse_config_file(configFilePath.c_str(), configFileOptions), vm);
    po::notify(vm);

    std::vector<std::string> requiredParams =
      { "xmin", "xmax", "ymin", "ymax", "height", "width",
        "iterations", "num-colors", "color", "fractal" };
    for (auto&& param : requiredParams)
    {
        if (!vm.count(param))
        {
            std::cout << "required param " << param << " not found" << std::endl;
            exit(1);
        }
        else
        {
            if (param == "xmin") m_minX = vm["xmin"].as<double>();
            if (param == "xmax") m_maxX = vm["xmax"].as<double>();
            if (param == "ymin") m_minY = vm["ymin"].as<double>();
            if (param == "ymax") m_maxY = vm["ymax"].as<double>();
            if (param == "width") m_width= vm["width"].as<uint32_t>();
            if (param == "height") m_height = vm["height"].as<uint32_t>();
            if (param == "iterations") m_iterations = vm["iterations"].as<uint32_t>();
            if (param == "num-colors") m_numColors = vm["num-colors"].as<uint32_t>();
            if (param == "color") m_colors = vm["color"].as<std::vector<uint32_t>>();
            if (param == "fractal") m_fractal= vm["fractal"].as<std::string>();
        }
    }

    
}