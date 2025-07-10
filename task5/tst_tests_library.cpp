/*
Хохлов Иван, 1 курс, 5 группа
Unit-тесты для задания 3 (приложено к проекту)
 */
#include <QtTest>
#include "library.h"

class tests_library : public QObject
{
    Q_OBJECT

public:
    tests_library();
    ~tests_library();

private slots:
    void initTestCase();
    void cleanupTestCase();
    // для структур Book
    void testBook_defaultConstructor();
    void testBook_valueConstructor();
    void testBook_bookGetter();
    void testBook_equalityAndAssignment();
    void testBook_streamOperator();

    // для структур Publication
    void testPub_defaultConstructor();
    void testPub_valueConstructor();
    void testPub_pubGetter();
    void testPub_equalityAndAssignment();
    void testPub_streamOperator();

    // для Library<Book>
    void testLibraryBook_addAndRetrieve();
    void testLibraryBook_indexOutOfRange();
    void testLibraryBook_deleteAndReplace();
    void testLibraryBook_find();

    // для Library<Publication>
    void testLibraryPub_addAndRetrieve();
    void testLibraryPub_find();
};

tests_library::tests_library() {}

tests_library::~tests_library() {}

void tests_library::initTestCase() {}

void tests_library::cleanupTestCase() {}


void tests_library::testBook_defaultConstructor()
{
    Book b;
    QCOMPARE(b.year,   0);
    QCOMPARE(b.author, QString(""));
    QCOMPARE(b.title,  QString(""));
}

void tests_library::testBook_valueConstructor()
{
    Book b(1999, "A. Author", "Title X");
    QCOMPARE(b.year,   1999);
    QCOMPARE(b.author, QString("A. Author"));
    QCOMPARE(b.title,  QString("Title X"));
}

void tests_library::testBook_bookGetter()
{
    Book b(2020, "Author", "T");
    auto lst = b.bookGetter();
    QCOMPARE(lst.size(), 3);
    QCOMPARE(lst.at(0), QString("2020"));
    QCOMPARE(lst.at(1), QString("Author"));
    QCOMPARE(lst.at(2), QString("T"));
}

void tests_library::testBook_equalityAndAssignment()
{
    Book a(1, "Author", "Title");
    Book c = a;
    QVERIFY(a == c);
    c.year = 2;
    QVERIFY(!(a == c));
    c = a;
    QVERIFY(a == c);
}

void tests_library::testBook_streamOperator()
{
    QString s;
    QTextStream out(&s);
    out << Book(2005, "X", "Y");
    out.flush();
    QCOMPARE(s.trimmed(), QStringLiteral("X, Y, 2005 год"));
}

void tests_library::testPub_defaultConstructor()
{
    Publication p;
    QCOMPARE(p.year,  0);
    QCOMPARE(p.pages, 0);
    QCOMPARE(p.type,  QString(""));
}

void tests_library::testPub_valueConstructor()
{
    Publication p(2010, "Au", "Ti", 123, "Magazine");
    QCOMPARE(p.year,   2010);
    QCOMPARE(p.author, QString("Au"));
    QCOMPARE(p.title,  QString("Ti"));
    QCOMPARE(p.pages,  123);
    QCOMPARE(p.type,   QString("Magazine"));
}

void tests_library::testPub_pubGetter()
{
    Publication p(2021, "Author", "Book", 55, "Dictionary");
    auto lst = p.pubGetter();
    QCOMPARE(lst.size(), 5);
    QCOMPARE(lst.at(0), QString("2021"));
    QCOMPARE(lst.at(3), QString("55"));
    QCOMPARE(lst.at(4), QString("Dictionary"));
}

void tests_library::testPub_equalityAndAssignment()
{
    Publication a(1,"a","b",2,"t");
    Publication c = a;
    QVERIFY(a == c);
    c.pages = 99;
    QVERIFY(!(a == c));
    c = a;
    QVERIFY(a == c);
}

void tests_library::testPub_streamOperator()
{
    QString s;
    QTextStream out(&s);
    out << Publication(2001,"A","B",77,"C");
    out.flush();
    QVERIFY(s.contains(QStringLiteral("A, B, 2001 год")));
    QVERIFY(s.contains(QStringLiteral("77 страниц")));
    QVERIFY(s.contains(QStringLiteral("C")));
}


void tests_library::testLibraryBook_addAndRetrieve()
{
    Library<Book> lib;
    QCOMPARE(lib.GetSize(), 0);
    Book b(5,"X","Y");
    lib.Add(b);
    QCOMPARE(lib.GetSize(), 1);
    QCOMPARE(lib[0], b);
}

void tests_library::testLibraryBook_indexOutOfRange()
{
    Library<Book> lib(1);
    QCOMPARE(lib[0].year, 0);
    QVERIFY_EXCEPTION_THROWN(lib[-1], std::out_of_range);
    QVERIFY_EXCEPTION_THROWN(lib[10], std::out_of_range);
}

void tests_library::testLibraryBook_deleteAndReplace()
{
    Library<Book> lib;
    lib.Add(Book(1,"a","t"));
    lib.Add(Book(2,"b","u"));
    QCOMPARE(lib.GetSize(), 2);
    lib.Delete(0);
    QCOMPARE(lib.GetSize(), 1);
    QCOMPARE(lib[0].year, 2);
    lib.Replace(0, Book(9,"X","Y"));
    QCOMPARE(lib[0].year, 9);
    QCOMPARE(lib[0].author, QString("X"));
}

void tests_library::testLibraryBook_find()
{
    Library<Book> lib;
    lib.Add(Book(2000,"Akunin","Azazel"));
    lib.Add(Book(2001,"Brown","Code da Vinchi"));
    auto res = lib.Find("Aku");
    QCOMPARE(res.GetSize(), 1);
    QCOMPARE(res[0].author, QString("Akunin"));
    auto none = lib.Find("zzz");
    QCOMPARE(none.GetSize(), 0);
}


void tests_library::testLibraryPub_addAndRetrieve()
{
    Library<Publication> lib;
    Publication p(3,"C","T",30,"Z");
    lib.Add(p);
    QCOMPARE(lib.GetSize(), 1);
    QCOMPARE(lib[0], p);
}

void tests_library::testLibraryPub_find()
{
    Library<Publication> lib;
    lib.Add(Publication(5,"D","X",10,"TypeA"));
    lib.Add(Publication(6,"E","Y",20,"TypeB"));
    auto r1 = lib.Find("D");
    QCOMPARE(r1.GetSize(), 1);
    QCOMPARE(r1[0].author, QString("D"));
    auto r2 = lib.Find("B");
    QCOMPARE(r2.GetSize(), 1);
    QCOMPARE(r2[0].type, QString("TypeB"));
}

QTEST_MAIN(tests_library)

#include "tst_tests_library.moc"
