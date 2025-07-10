#ifndef LIBRARY_H
#define LIBRARY_H
#include <QString>
#include <QStringList>
#include <QVector>
#include <QRegularExpression>
#include <type_traits>
#include <QTextStream>
#include <QFile>

struct Book
{
public:
    int year;
    QString author;
    QString title;
    Book(): year(0), author(""), title("") {}
    Book(int y, const QString& a, const QString& ti): year(y), author(a), title(ti) {}
    QStringList bookGetter ()
    {
        QStringList book;
        book.push_back(QString::number(year));
        book.push_back(author);
        book.push_back(title);
        return book;
    }
    bool operator == (const Book &other) const
    {
        return (year==other.year) && (author==other.author) && (title==other.title);
    }
    Book& operator = (const Book &other)
    {
        if (*this==other) return *this;
        year=other.year;
        author=other.author;
        title=other.title;
        return *this;
    }

    friend QTextStream& operator << (QTextStream&out,const Book &b)
    {
        out << b.author << ", " << b.title << ", " << b.year << " год";
        return out;
    }
};

struct Publication: public Book
{
    int pages;
    QString type;
    Publication() : Book(), pages(0), type("") {}
    Publication(int y, const QString& a, const QString& ti, int p, const QString& ty): Book(y, a, ti), pages(p), type(ty){}
    QStringList pubGetter ()
    {
        QStringList pub = bookGetter();
        pub.push_back(QString::number(pages));
        pub.push_back(type);
        return pub;
    }
    bool operator == (const Publication &other) const
    {
        return Book::operator ==(other)&&(pages==other.pages)&&(type==other.type);
    }
    Publication& operator = (const Publication &other)
    {
        if (*this==other) return *this;
        Book::operator =(other);
        pages=other.pages;
        type=other.type;
        return *this;
    }
    friend QTextStream& operator << (QTextStream&out,const Publication& p)
    {
        out << static_cast<const Book&>(p);
        out<< ", "<< p.pages << " страниц, "<< p.type;
        return out;
    }
};

template <typename T>
class Library
{
private:
    QVector <T> M;
    int amount;
public:
    Library():M(),amount(0){}
    Library(int count):M(count),amount(count){}
    ~Library(){}
    T& operator [] (const int& index)
    {
        if (index<0 || index>=M.size())
            throw std::out_of_range ("Ошибка! Индекс вне допустимого диапазона");
        return M[index];
    }
    friend QTextStream& operator << (QTextStream&out, Library& collection)
    {
        for (int i=0;i<collection.M.size();++i)
        {
            out<<i+1<<". "<<collection.M[i]<<Qt::endl;
            out.flush();
        }
        return out;
    }
    void Add(const T& NItem)
    {
        if (amount < M.size())
            M[amount]=NItem;
        else
            M.push_back(NItem);
        amount++;
    }
    void Delete (int index)
    {
        if (index < 0 || index >= amount)
            throw std::runtime_error("Ошибка! Записи с таким номером нет");
        M.removeAt(index);
        amount--;
    }
    void Replace(int index, const T& NItem)
    {
        if (index < 0 || index >= amount)
            throw std::out_of_range("Ошибка! Записи с таким номером нет");
        M[index] = NItem;
    }
    Library <T> Find(const QString& key)
    {
        Library <T> matches;
        QRegularExpression search(key, QRegularExpression::CaseInsensitiveOption);
        for (const auto& e : M)
        {
            bool match = search.match(e.title).hasMatch()|| search.match(e.author).hasMatch();
            if constexpr (std::is_same<T, Publication>::value)
            {
                match = match || search.match(e.type).hasMatch();
            }
            if (match)
                matches.Add(e);
        }
        return matches;
    }
    int GetSize()
    {
        return amount;
    }
};
#endif // LIBRARY_H
