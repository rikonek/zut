// Implement a simple dictionary:
// has a set of predefined words
// case insensitive

#include <iostream>
#include <set>
#include <string>

struct Dictionary
{
    void addWord(std::string word); /*noexcept*/
    void removeWord(std::string word);
    bool check(std::string word) const noexcept;

    private:
        std::set<std::string> elements;
};

void Dictionary::addWord(std::string word)
{
    this->elements.insert(word);
    std::cout << "Elements: " << elements.size() << std::endl;
}

void Dictionary::removeWord(std::string word)
{
    this->elements.erase(word);
    std::cout << "Elements: " << elements.size() << std::endl;
}

bool Dictionary::check(std::string word)
{
    return this->elements.find(word);
}

int main()
{
    Dictionary book;
    book.addWord("elephant");
    book.addWord("pig");
    book.addWord("bird");
    book.removeWord("pig");
    std::cout << book.check("elephant");
    return 0;
}