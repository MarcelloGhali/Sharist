#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <memory>
using namespace::std;

class Member{
public:
    Member(string name);
    ~Member();
	string Name;
};

typedef shared_ptr<Member> MemberPtr;

#endif
