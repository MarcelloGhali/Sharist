#include <cstdio>
#include <QString>
#include <QtTest>
#include "SharedEvent.h"

class Core_Test : public QObject
{
    Q_OBJECT

public:
    Core_Test();

private Q_SLOTS:
    void sharedevent_should_expand_if_new_members_added();
    void sharedevent_should_return_correct_optimization();
    void sharedevent_should_return_correct_optimization1();
    void sharedevent_should_return_correct_optimization2();
    void sharedevent_optimize_should_be_idempotent();
};

Core_Test::Core_Test()
{
}

void Core_Test::sharedevent_should_expand_if_new_members_added()
{
    Member marat("Marat");
    Member alex("Alex");
    Member slava("Slava");
    vector<const Member*> maratMembers;
    maratMembers.push_back(&alex);
    maratMembers.push_back(&slava);
    ExpenseItem gas(100, &marat, 0, &maratMembers);
    SharedEvent oregon("oregon");
    oregon.AddMember(&marat);
    oregon.AddMember(&alex);
    oregon.AddMember(&slava);
    oregon.AddExpenseItem(&gas);
    oregon.Optimize();
    int countResults = oregon.GetCapacity();
    //adding new users
    vector<const Member*> tmpMembers;
    int k=2;
    for (int i = 0; i < countResults*k; i++){
        const Member *tmpMember = new Member("test");
        tmpMembers.push_back(tmpMember);
        oregon.AddMember(tmpMember);
    }
    //check
    oregon.Optimize();
    int countExpandedResults = oregon.GetCapacity();
    QVERIFY(countResults*k*oregon.GetGrowthRate()==countExpandedResults);
    //cleanup
    for (vector<const Member*>::iterator it = tmpMembers.begin(); it < tmpMembers.end(); it++){
        delete *it;
    }
}

void Core_Test::sharedevent_should_return_correct_optimization(){
    //setup
        Member marat("Marat");
        Member alex("Alex");
        Member slava("Slava");
        vector<const Member*> maratMembers;
        maratMembers.push_back(&alex);
        maratMembers.push_back(&slava);
        vector<const Member*> slavaMembers;
        slavaMembers.push_back(&alex);
        slavaMembers.push_back(&marat);
        ExpenseItem gas(90, &marat, 0, &maratMembers);
        ExpenseItem food(120, &slava, 0, &slavaMembers);
        SharedEvent oregon("oregon");
        oregon.AddMember(&marat);
        oregon.AddMember(&alex);
        oregon.AddMember(&slava);
        oregon.AddExpenseItem(&gas);
        oregon.AddExpenseItem(&food);
        //expected
        double alexOweSlava = 50;
        double alexOweMarat = 20;
        //test
        double* results = oregon.Optimize();
        int size = oregon.GetCapacity();
        //adding new users
        QVERIFY(results[1*size + 0] == alexOweMarat);
        QVERIFY(results[1*size + 2] == alexOweSlava);
}

void Core_Test::sharedevent_should_return_correct_optimization1(){
    //setup
        Member marat("Marat");
        Member alex("Alex");
        Member ruslan("Ruslan");
        vector<const Member*> maratMembers;
        maratMembers.push_back(&alex);
        maratMembers.push_back(&ruslan);
        vector<const Member*> ruslanMembers;
        ruslanMembers.push_back(&alex);
        ruslanMembers.push_back(&marat);
        ExpenseItem gas(87.07, &marat, 0, &maratMembers);
        ExpenseItem food(126.91, &marat, 0, &maratMembers);
        ExpenseItem camping(25, &ruslan, 0, &ruslanMembers);
        SharedEvent oregon("oregon");
        oregon.AddMember(&marat);
        oregon.AddMember(&alex);
        oregon.AddMember(&ruslan);
        oregon.AddExpenseItem(&gas);
        oregon.AddExpenseItem(&food);
        oregon.AddExpenseItem(&camping);
        //expected
        double alexOweMarat = 79.660000;
        double ruslanOweMarat = 54.660000;
        //test
        double* results = oregon.Optimize();
        int size = oregon.GetCapacity();
        //adding new users
        QVERIFY(results[1*size + 0] == alexOweMarat);
        QVERIFY(results[2*size + 0] == ruslanOweMarat);
}

void Core_Test::sharedevent_should_return_correct_optimization2(){
    //setup
        Member marat("Marat");
        Member alex("Alex");
        Member ruslan("Ruslan");
        vector<const Member*> maratMembers;
        maratMembers.push_back(&alex);
        maratMembers.push_back(&ruslan);
        vector<const Member*> ruslanMembers;
        ruslanMembers.push_back(&alex);
        ruslanMembers.push_back(&marat);
//        ExpenseItem gas(45, &marat, 0, &maratMembers);
//        ExpenseItem alco(30, &marat, 0, &maratMembers);
//        ExpenseItem grocery(68.44, &marat, 0, &maratMembers);
        ExpenseItem err(143.44, &marat, 0, &maratMembers);
        ExpenseItem lodge(321, &ruslan, 0, &ruslanMembers);
        SharedEvent canada("canada");
        canada.AddMember(&marat);
        canada.AddMember(&alex);
        canada.AddMember(&ruslan);
        canada.AddExpenseItem(&err);
//        canada.AddExpenseItem(&gas);
//        canada.AddExpenseItem(&alco);
//        canada.AddExpenseItem(&grocery);
        canada.AddExpenseItem(&lodge);
        //expected
        double maratOweRuslan = 11.373333333333335;
        double alexOweRuslan = 154.81333333333333;
        //test
        double* results = canada.Optimize();
        int size = canada.GetCapacity();
        //adding new users
        QVERIFY(results[0*size + 2] == maratOweRuslan);
        QVERIFY(results[1*size + 2] == alexOweRuslan);
}

void Core_Test::sharedevent_optimize_should_be_idempotent(){
    //setup
        Member marat("Marat");
        Member alex("Alex");
        Member ruslan("Ruslan");
        vector<const Member*> maratMembers;
        maratMembers.push_back(&alex);
        maratMembers.push_back(&ruslan);
        vector<const Member*> ruslanMembers;
        ruslanMembers.push_back(&alex);
        ruslanMembers.push_back(&marat);
        ExpenseItem err(143.44, &marat, 0, &maratMembers);
        ExpenseItem lodge(321, &ruslan, 0, &ruslanMembers);
        SharedEvent canada("canada");
        canada.AddMember(&marat);
        canada.AddMember(&alex);
        canada.AddMember(&ruslan);
        canada.AddExpenseItem(&err);
        canada.AddExpenseItem(&lodge);
        //expected
        double maratOweRuslan = 11.373333333333335;
        double alexOweRuslan = 154.81333333333333;
        //test
        double* results = canada.Optimize();
        canada.Optimize();
        canada.Optimize();
        int size = canada.GetCapacity();
        //adding new users
        QVERIFY(results[0*size + 2] == maratOweRuslan);
        QVERIFY(results[1*size + 2] == alexOweRuslan);
}

QTEST_APPLESS_MAIN(Core_Test)

#include "tst_core_testtest.moc"
