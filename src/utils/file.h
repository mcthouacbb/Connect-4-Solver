#include <fstream>
#include <string>

inline std::string readFile(std::string path)
{
    std::ifstream file(path);
    if (!file.is_open())
        return "";

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    std::string buffer(size + 1, '\0');
    file.seekg(0);
    file.read(buffer.data(), size);
    return buffer;
}