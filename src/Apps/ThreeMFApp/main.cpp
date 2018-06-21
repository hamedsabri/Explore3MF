#include <Model/COM/NMR_DLLInterfaces.h>

#include <iostream>

using namespace NMR;

int main()
{
    DWORD majorVersion;
    DWORD minorVersion;
    DWORD microVersion;

    lib3mf_getinterfaceversion( &majorVersion, &minorVersion, &microVersion );

    std::cout << "Lib3MF Version: " << majorVersion << "." << minorVersion << "." << microVersion << '\n';

    return 0;
}
