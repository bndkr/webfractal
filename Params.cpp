#include "Params.hpp"

#include <iostream>
#include <string>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

Params::Params(int argc, char** argv):
    m_minX(), m_minY(), m_maxX(), m_maxY(), m_exit(false)
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce this help message")
        ("xmin,a", po::value<double>(), "minimum x value")
        ("xmax,b", po::value<double>(), "maximum x value")
        ("ymin,c", po::value<double>(), "minimum y value")
        ("ymax,d", po::value<double>(), "maximum y value")
        ("palette,p", po::value<std::string>(), "path of palette file")
        ("fractal,f", po::value<std::string>(), "fractal type")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        m_exit = true;
        return;
    }

    if (vm.count("xmin"))
    {
        m_minX = vm["xmin"].as<double>();
    }
    else
    {
        std::cout << "required param xmin not specified." << std::endl;
        m_exit = true;
    }
    if (vm.count("xmax"))
    {
        m_maxX = vm["xmax"].as<double>();
    }
    else
    {
        std::cout << "required param xmax not specified." << std::endl;
        m_exit = true;
    }
    if (vm.count("ymin"))
    {
        m_minY = vm["ymin"].as<double>();
    }
    else
    {
        std::cout << "required param ymin not specified." << std::endl;
        m_exit = true;
    }
    if (vm.count("ymax"))
    {
        m_maxY = vm["ymax"].as<double>();
    }
    else
    {
        std::cout << "required param ymax not specified." << std::endl;
        m_exit = true;
    }
    if (vm.count("palette"))
    {
        m_palette = vm["palette"].as<std::string>();
    }
    else
    {
        std::cout << "required param palette not specified." << std::endl;
        m_exit = true;
    }
    if (vm.count("fractal"))
    {
        m_fractal = vm["fractal"].as<std::string>();
    }
    else
    {
        std::cout << "required param fractal not specified." << std::endl;
        m_exit = true;
    }
}