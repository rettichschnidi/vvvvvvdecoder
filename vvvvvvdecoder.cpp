#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <stdint.h>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#define OGG_DATA_OFFSET 0x1e00
#define FILESIZE_OFFSET 52
#define FILEINFO_ENTRY_SIZE 60

using namespace std;
using namespace boost::filesystem3;
using namespace boost::program_options;

struct OggFile {
		std::string filename;
		uint32_t filesize;
		OggFile() :
			filename(""), filesize(0) {
		}
};

int main(int argc, char **argv) {
	bool overwrite;
	string source;
	string destinationDir;
	variables_map variablesMap;
	options_description desc("Allowed options");

	try {
		desc.add_options()
				("source,s", value<string> (&source)->default_value("vvvvvvmusic.vvv"), "file to read")
				("destination,d", value<string> (&destinationDir)->default_value("./"), "destination directory")
				("overwrite,o", "Try to overwrite already existing files")("help,h", "Shows this information");

		positional_options_description posOpt;
		posOpt.add("source", 1).add("destination", 1).add("overwriteDestinationIfExisting", 1);

		store(parse_command_line(argc, argv, desc), variablesMap);
		store(command_line_parser(argc, argv).options(desc).positional(posOpt).run(), variablesMap);
		notify(variablesMap);
	} catch (std::exception & e) {
		std::cerr << "Error in arguments parsing: " << e.what() << std::endl;
		exit(1);
	}

	if (variablesMap.count("help")) {
		cerr << desc;
		exit(0);
	}

	if (!exists(source)) {
		cerr << source << " does not exist." << endl;
		exit(2);
	}
	if (!is_regular(source)) {
		cerr << source << " is not a regular file." << endl;
		exit(3);
	}

	if (!is_directory(destinationDir)) {
		cerr << "\"" << destinationDir << "\"" << " is not a director or does not exist" << endl;
		exit(4);
	}

	overwrite = variablesMap.count("overwrite");

	const unsigned int numberOfFiles = 15;
	vector<OggFile> files(numberOfFiles);
	ifstream input(source.c_str(), ifstream::in);
	ofstream output;
	assert(input);
	size_t lastpos = input.tellg();
	for (unsigned int i = 0; i < numberOfFiles; i++) {
		getline(input, files[i].filename, '\0');
		files[i].filename = destinationDir + "/" + basename(files[i].filename) + ".ogg";
		input.seekg(lastpos + FILESIZE_OFFSET);
		input.read((char*) &files[i].filesize, 4);
		lastpos += FILEINFO_ENTRY_SIZE;
		input.seekg(lastpos);
	}

	input.seekg(OGG_DATA_OFFSET);

	for (vector<OggFile>::iterator it = files.begin(); it != files.end(); it++) {
		char *data = new char[it->filesize];
		input.read(data, it->filesize);
		if (exists(it->filename)) {
			if (overwrite) {
				remove(it->filename);
			} else {
				cerr << it->filename << " does already exist. You may want to use the flag --overwrite." << endl;
				exit(5);
			}
		}
		output.open(it->filename.c_str(), ofstream::binary);
		assert(output);
		output.write(data, it->filesize);
		assert(output);
		delete[] data;
		output.close();
	}
	input.close();
	return 0;
}
