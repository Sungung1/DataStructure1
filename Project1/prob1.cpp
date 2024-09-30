#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
	string a;
	vector<string> arr;

	while (1)
	{
		cin >> a;

		if (a == "exit")
			break;

		auto it = find(arr.begin(), arr.end(), a);

		if (it != arr.end())
			arr.erase(it);
		else
		{
			arr.push_back(a);
			sort(arr.begin(), arr.end());
		}


		for (int i = 0; i < arr.size(); i++)
			cout << arr[i] << " ";
		cout << endl;
	}

	return 0;
}