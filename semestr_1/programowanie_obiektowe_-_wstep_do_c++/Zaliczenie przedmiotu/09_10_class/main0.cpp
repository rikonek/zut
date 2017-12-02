// Write a class to handle a file with all constructors, destructor, operators...
// (C++11 recommended)

#include <iostream>
#include <fstream>

using namespace std;

class File
{
    public:
        enum fileFlags: int
        {
            O_RONLY=1,
            O_WRONLY=2,
            O_APPEND=4,
        };

        File() {}
        File(File &a);
        File(std::string url,const fileFlags &flag);
        ~File();
        void close();
        void open(const fileFlags &flag);
        void setUrl(const std::string &str);
        void read();
        void write(const std::string &str);

        File operator=(const File &f)
        {
            File tmp {f.url,f.modeFlags};
            return tmp;
        }

    private:
        std::string url;
        std::fstream file;
        fileFlags modeFlags;
};

inline File::fileFlags operator|(File::fileFlags a, File::fileFlags b)
{
    return static_cast<File::fileFlags>(static_cast<int>(a) | static_cast<int>(b));
}

File::File(File &a)
{
    setUrl(a.url);
    open(a.modeFlags);
}

File::File(std::string url,const fileFlags &flag): url(url), modeFlags(flag)
{
    open(modeFlags);
};

File::~File()
{
    file.close();
}

void File::close()
{
    file.close();
}

void File::open(const fileFlags &flag)
{
    modeFlags=flag;
    close();
    if(modeFlags==O_RONLY)
    {
        file.open(url,std::ios::in);
    }
    if(modeFlags==O_WRONLY)
    {
        file.open(url,std::ios::out);
    }
    if(modeFlags==(O_WRONLY|O_APPEND))
    {
        file.open(url,std::ios::app);
    }
    if(!file.is_open())
    {
        cout << "Nie mozna otworzyc pliku!" << endl;
    }
}

void File::setUrl(const std::string &str)
{
    url=str;
}

void File::read()
{
    file.clear();
    file.seekg(0);
    std::string line;
    while(std::getline(file,line))
    {
      cout << line << endl;
    }
}

void File::write(const std::string &str)
{
    file << str;
}

int main()
{
    File a {"/tmp/aa",File::O_WRONLY};
    a.write("Pierwsza linia\n");
    a.close();

    File f {"/tmp/aa", File::O_WRONLY | File::O_APPEND}; 
    f.write("Druga linia\n");
    f.close();

    File f2 { f };
    f2.write("Trzecia linia\n");
    f2.close();

    File f3 = f2;
    f3.write("Czwarta linia\n");
    f3.close();

    File f4;
    f4.setUrl("/tmp/aa");
    f4.open(File::O_RONLY);
    f4.read();
    f4.close();

    f = f3; 
    f.open(File::O_WRONLY | File::O_APPEND);
    f.write("Piata linia\n");
    f.close();
    f.open(File::O_RONLY);
    f.read();
}