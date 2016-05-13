#include <cstdio>
#include <QString>
#include <QtTest>
#include "SharedEvent.h"

class Core_Test : public QObject{
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

Core_Test::Core_Test(){
}

void Core_Test::sharedevent_should_expand_if_new_members_added(){
    MemberPtr maratP(new Member("Marat"));
    MemberPtr alexP(new Member("Alex"));
    MemberPtr slavaP(new Member("Slava"));
    vector<MemberPtr> maratMembers;
    maratMembers.push_back(alexP);
    maratMembers.push_back(slavaP);
    ExpenseItemPtr gasP(new ExpenseItem(100, maratP, vector<MemberPtr>(), maratMembers));
    SharedEvent oregon("oregon");
    oregon.AddMember(maratP);
    oregon.AddMember(alexP);
    oregon.AddMember(slavaP);
    oregon.AddExpenseItem(gasP);
    oregon.Optimize();
    int countResults = oregon.GetCapacity();
    //adding new users
    int k=2;
    for (int i = 0; i < countResults*k; i++){
        MemberPtr tmpMember(new Member("test"));
        oregon.AddMember(tmpMember);
    }
    //check
    oregon.Optimize();
    int countExpandedResults = oregon.GetCapacity();
    QVERIFY(countResults*k*oregon.GetGrowthRate()==countExpandedResults);
}

void Core_Test::sharedevent_should_return_correct_optimization(){
        //setup
        MemberPtr maratP(new Member("Marat"));
        MemberPtr alexP(new Member("Alex"));
        MemberPtr slavaP(new Member("Slava"));
        vector<MemberPtr> maratMembers;
        maratMembers.push_back(alexP);
        maratMembers.push_back(slavaP);
        maratMembers.push_back(maratP);
        vector<MemberPtr> slavaMembers;
        slavaMembers.push_back(alexP);
        slavaMembers.push_back(maratP);
        slavaMembers.push_back(slavaP);
        ExpenseItemPtr gasP(new ExpenseItem(90, maratP, vector<MemberPtr>(), maratMembers));
        ExpenseItemPtr foodP(new ExpenseItem(120, slavaP, vector<MemberPtr>(), slavaMembers));
        SharedEvent oregon("oregon");
        oregon.AddMember(maratP);
        oregon.AddMember(alexP);
        oregon.AddMember(slavaP);
        oregon.AddExpenseItem(gasP);
        oregon.AddExpenseItem(foodP);
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
        MemberPtr maratP(new Member("Marat"));
        MemberPtr alexP(new Member("Alex"));
        MemberPtr ruslanP(new Member("Ruslan"));
        vector<MemberPtr> maratMembers;
        maratMembers.push_back(alexP);
        maratMembers.push_back(ruslanP);
        maratMembers.push_back(maratP);
        vector<MemberPtr> ruslanMembers;
        ruslanMembers.push_back(alexP);
        ruslanMembers.push_back(maratP);
        ruslanMembers.push_back(ruslanP);
        ExpenseItemPtr gasP(new ExpenseItem(87.07, maratP, vector<MemberPtr>(), maratMembers));
        ExpenseItemPtr foodP(new ExpenseItem(126.91, maratP, vector<MemberPtr>(), maratMembers));
        ExpenseItemPtr campingP(new ExpenseItem(25, ruslanP, vector<MemberPtr>(), ruslanMembers));
        SharedEvent oregon("oregon");
        oregon.AddMember(maratP);
        oregon.AddMember(alexP);
        oregon.AddMember(ruslanP);
        oregon.AddExpenseItem(gasP);
        oregon.AddExpenseItem(foodP);
        oregon.AddExpenseItem(campingP);
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
        MemberPtr maratP(new Member("Marat"));
        MemberPtr alexP(new Member("Alex"));
        MemberPtr ruslanP(new Member("Ruslan"));
        vector<MemberPtr> maratMembers;
        maratMembers.push_back(alexP);
        maratMembers.push_back(ruslanP);
        maratMembers.push_back(maratP);
        vector<MemberPtr> ruslanMembers;
        ruslanMembers.push_back(alexP);
        ruslanMembers.push_back(maratP);
        ruslanMembers.push_back(ruslanP);
        ExpenseItemPtr errP(new ExpenseItem(143.44, maratP, vector<MemberPtr>(), maratMembers));
        ExpenseItemPtr lodgeP(new ExpenseItem(321, ruslanP, vector<MemberPtr>(), ruslanMembers));
        SharedEvent canada("canada");
        canada.AddMember(maratP);
        canada.AddMember(alexP);
        canada.AddMember(ruslanP);
        canada.AddExpenseItem(errP);
        canada.AddExpenseItem(lodgeP);
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
        MemberPtr maratP(new Member("Marat"));
        MemberPtr alexP(new Member("Alex"));
        MemberPtr ruslanP(new Member("Ruslan"));
        vector<MemberPtr> maratMembers;
        maratMembers.push_back(alexP);
        maratMembers.push_back(ruslanP);
        maratMembers.push_back(maratP);
        vector<MemberPtr> ruslanMembers;
        ruslanMembers.push_back(alexP);
        ruslanMembers.push_back(maratP);
        ruslanMembers.push_back(ruslanP);
        ExpenseItemPtr errP(new ExpenseItem(143.44, maratP, vector<MemberPtr>(), maratMembers));
        ExpenseItemPtr lodgeP(new ExpenseItem(321, ruslanP, vector<MemberPtr>(), ruslanMembers));
        SharedEvent canada("canada");
        canada.AddMember(maratP);
        canada.AddMember(alexP);
        canada.AddMember(ruslanP);
        canada.AddExpenseItem(errP);
        canada.AddExpenseItem(lodgeP);
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
