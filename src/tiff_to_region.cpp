/*
 * region.cpp
 *
 * Common LAAS Raster library
 *
 * author:  Pierrick Koch <pierrick.koch@laas.fr>
 * created: 2013-08-01
 * license: BSD
 */
#include <stdexcept>        // for runtime_error
#include <cstdlib>          // exit status

#include "clara/region.hpp"
#include "gdalwrap/gdal.hpp"

int main(int argc, char * argv[])
{
    std::cout<<"Common LAAS Raster library"<<std::endl;
    if (argc < 3) {
        std::cerr<<"usage: "<<argv[0]<<" flat.tif obstacle.tif region_out.tif"<<std::endl;
        return EXIT_FAILURE;
    }

    gdalwrap::gdal flat(argv[1]);
    gdalwrap::gdal obstacle(argv[2]);
    gdalwrap::gdal region;
    region.copy_meta(flat, clara::region::N_RASTER);
    region.names = {"NO_3D_CLASS", "FLAT", "OBSTACLE", "ROUGH", "SLOPE"};
    region.bands[clara::region::FLAT] = flat.bands[0];
    region.bands[clara::region::OBSTACLE] = obstacle.bands[0];

    region.save(argv[3]);

    return EXIT_SUCCESS;
}

