#include <iostream>
#include "SkipList.hpp"
using namespace std;
int main() {
	
	SkipList *s = new SkipList(4);
	char c;
	//cout<<"BLABLA";
	Key k;
	do {
		cout<<"a - add\nf - find\nd - del\nq - quit\n";
		cin>>c;
		if (!(c!='a' || c!='f' || c!='d' || c!='q'))
			continue;
		cout<<"Value:\n";
		cin>>k;
		if(c=='a') {
			
			s->add(k);
		} else if(c == 'f') {
			
			if((s->find(k)))
				cout<<"Found!\n";
			else
				cout<<"Nod found!\n";
			
		} else if(c == 'd') {
			s->del(k);
		} else {
			break;
		}
			}while(c!='q');
	cout<<"That's all, folks!\n";
	return 0;
}
