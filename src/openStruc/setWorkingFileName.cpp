#include <filesystem>
using std::filesystem::path;

#include "openStruc.h"

void OpenStruc::setWorkingFileName(const char *temp)
{
    path p = temp;
    fileName = p.replace_extension();
} // end of OpenStruc::setWorkingFileName() //
