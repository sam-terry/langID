#ifndef CORPUS_PROCESSOR_H__
#define CORPUS_PROCESSOR_H__

#include <filesystem>
#include <vector>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

/*
 * ListPaths() takes as an argument a fs::path to the directory containing corpus data
 * It returns a vector of paths to each corpus file in the corpora directory
 * @param corpusDirectory -- the directory containing the corpora to be enumerated
 * @return -- a vector of path objects representing the corpus files from the corpus directory
 */ 
std::vector<fs::path> ListPaths(fs::path corpusDirectory);

/*
 * ExtractCorpusFilename() takes a file path object and returns the name of the file (minus the path) as a string
 * @param fullpath -- the path object whose filename is to be extracted
 * @return -- a string containing the filename of the corpus
 */
std::string ExtractCorpusFilename(fs::path fullpath);

/*
 * GetCorpusLanguage() strips corpus filenames of their extensions to yield the name of the corpus' language
 * @param corpusFile -- the corpus' filename rendered as a string
 * @return -- a string containing the language of the corpus file
 */
std::string GetCorpusLanguage(std::string corpusFile);

#endif