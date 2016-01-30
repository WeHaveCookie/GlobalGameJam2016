#ifndef READER_H
#define READER_H
#include <iostream>
#include <fstream>
#include <sstream>

class Reader
{
    public:
        Reader(const std::string & filePath);
        virtual ~Reader();
    protected:
        //Function//
        void open(const std::string & filePath);
        bool endFile();
        virtual void read()=0;
        void nextChar();
        std::string nextWord();
        inline void close() {m_file.close();}
        void skipSeparator();
                //Attributes//
        std::fstream m_file;
        std::string m_filePath;
        char m_curChar;
        std::string m_curWord;
    private:

};


#endif // READER_H
