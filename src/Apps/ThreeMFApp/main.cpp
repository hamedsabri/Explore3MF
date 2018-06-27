#include <import3MF.h>

#include <string>
#include <iostream>

int main()
{
	std::string resPath(RESOURCEDIR_PATH);

	E3D::Import3MF im3MF(resPath + "Cube_basematerial.3mf");
	
	return 0;
}
