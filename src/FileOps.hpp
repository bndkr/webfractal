#ifndef FILEOPS_HPP
#define FILEOPS_HPP

#include <fstream>
#include <memory>
#include <string>

namespace fileops
{
    std::shared_ptr<std::ofstream> createBmpHeader(uint32_t const& width,
                                                   uint32_t const& height,
                                                   std::string filename);
}

#endif