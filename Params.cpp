#include "Params.hpp"

#include <iostream>
#include <string>

namespace
{
  void argNotFoundError(std::string err)
  {
    throw std::runtime_error("Error: argument " + err + " not present");
  }
}
Params::Params(int argc, char** argv):
    m_minX(), m_minY(), m_maxX(), m_maxY()
{
  if (argc == 1)
  {
    std::cout << "Usage: fractalgen --xmin xmin --xmax"
                 " xmax --ymin ymin --ymax ymax --type "
                 " fractal --color color";
    return;
  }

  for (int i = 0; i < argc; i++)
  {
    if (strcmp(argv[i], "--xmin"))
    {
      if (i < argc - 2)
        m_minX = atof(argv[i + 1]);
      else
        argNotFoundError("xmin");
    }

    if (strcmp(argv[i], "--xmax"))
    {
      if (i < argc - 2)
        m_maxX = atof(argv[i + 1]);
      else
        argNotFoundError("xmax");
    }

    if (strcmp(argv[i], "--ymin"))
    {
      if (i < argc - 2)
        m_minY = atof(argv[i + 1]);
      else
        argNotFoundError("ymin");
    }

    if (strcmp(argv[i], "--ymax"))
    {
      if (i < argc - 2)
        m_maxY = atof(argv[i + 1]);
      else
        argNotFoundError("ymax");
    }
  }

  std::cout << "xmin: " << std::to_string(m_minX) <<
    "xmax: " << std::to_string(m_maxX) << 
    "ymin: " << std::to_string(m_minY) <<
    "ymax: " << std::to_string(m_maxY) << std::endl;
}