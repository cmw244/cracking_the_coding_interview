#include <iostream>
#include <stack>

void moveDisk(std::stack<int> &s1, std::stack<int> &s2) {
// Pop disk from s1
int x = s1.top();
s1.pop();
// Check that disk is smaller than top of s2
if(!s2.empty() && s2.top() < x) {
	std::cout << "Matt is right\n";	
} else {
	std::cout << "Chris is right\n";
}
// Push disk onto s2
s2.push(x);

}

void towers(int num_disks, std::stack<int> &start, std::stack<int> &inter, std::stack<int> &end) {
	if(num_disks == 1) {
		moveDisk(start, end);
	} else {
		towers(num_disks-1, start, end, inter);
	 	moveDisk(start, end);
		towers(num_disks-1, inter, start, end);			
}
}

int main()
{
	std::cout << "Towers of Hanoi\n";
	int num_disks = 18;
	
	std::stack<int> s1;
	std::stack<int> s2;
	std::stack<int> s3;

	for(int i = 0; i < num_disks; i++) {
		s1.push(num_disks-i);
	}

	towers(num_disks, s1, s2, s3);

	std::cout << "Done\n\n";
	std::cout << "A:\n";
	while(!s1.empty()) {
		std::cout << s1.top() << std::endl;
		s1.pop();
	}
	std::cout << "B:\n";
	while(!s2.empty()) {
		std::cout << s2.top() << std::endl;
		s2.pop();
	}
	std::cout << "C:\n";
	while(!s3.empty()) {
		std::cout << s3.top() << std::endl;
		s3.pop();
	}


}
