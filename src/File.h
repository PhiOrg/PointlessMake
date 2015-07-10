#ifndef _FILE_H__
#define _FILE_H__

#include <string>

class File
{
    public:
        File(std::string&);
        std::string GetFile() const;
        std::string GetObjectFile() const;
        std::string GetError() const;
        bool CheckIfFileExists() const;
        bool CheckIfObjectFileExists() const;
        bool FileIsOk() const;
    private:
        void CreateDirectoryForObjectFile() const;

        std::string file, objectFile;
        unsigned short int error = 0;
        /********************************************
         * 0 - no error                             *
         * 1 - the file isn't in the src directory  *
         * 2 - the file doesn't exists              *
         * 3 - file permission denied               *
         * 4 - object file permission denied        *
         * ******************************************/
};

#endif

