#include <filesystem>
#include <vector>
#include <cstddef>


namespace fs = std::filesystem;

std::vector<fs::path> ListPaths(fs::path corpusDirectory) {

    std::vector<fs::path> CorpusPaths;

    for ( auto const& dir_element : fs::directory_iterator{corpusDirectory} ) {
        CorpusPaths.push_back(dir_element);
    }

    return CorpusPaths;
}

std::string ExtractCorpusFilename(fs::path fullpath) {
    return (std::string) fullpath.filename();
}

std::string GetCorpusLanguage(std::string corpusFile) {
    size_t lastdot = corpusFile.find_last_of(".");

    if (lastdot == std::string::npos) return corpusFile;

    else {return corpusFile.substr(0,lastdot);}
}

// size_t lastdot = fstring.find_last_of(".");
// if (lastdot == std::string::npos) {
//     std::cout << fstring << std::endl;
// }
// else {
//     std::cout << fstring.substr(0,lastdot) << std::endl;
// }