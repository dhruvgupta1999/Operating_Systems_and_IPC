/*input
5 3
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
3 3 2
*/

#include <bits/stdc++.h>


using namespace std;
#define watch(x) cout << (#x) << " is " << (x) << endl
int MAX[100][10];
int ALLOCATED[100][10];
int NEED[100][10];
int n,m;

bool Check_safe(int AVAILABLE[])
{
	vector < vector <int>> cur_need;
	vector < vector <int>> cur_alloc;

	
	for (int i = 0; i < n; ++i)  // fill in input into cur_need and cur_alloc
	{
		vector <int > tmp1;vector <int> tmp2;
		for (int j = 0; j < m; ++j)
		{
			tmp1.push_back(NEED[i][j]);
			tmp2.push_back(ALLOCATED[i][j]);
		}
		cur_need.push_back(tmp1);
		cur_alloc.push_back(tmp2);
	}
	
	int cur_avail[m];
	for (int i = 0; i < m; ++i)
	{
		cur_avail[i]=AVAILABLE[i];
	}
	while(cur_need.size()!=0) //outer loop runs till all processes are examined
	{
	int flag2=0;
	for (int i = 0; i < cur_need.size(); ++i) //for each process check whether we can provide resources and allow it to complete execution 
	{
		int flag1=0;
		for (int j = 0; j < m; ++j)
		{
			if (cur_need[i][j]<=cur_avail[j])
			{
				flag1++;
			}
		}
		// watch(flag1);
		if (flag1==m) //if flag==m , this means that the entire of the need is satisfied ,so now we provide it the required resources 
		{
			flag2++;//counts how many processes we r able to provide resources 
			// watch(flag2);

			for (int k = 0; k < m; ++k) // the process gets the resources and exits,
			{
				cur_avail[k]+=cur_alloc[i][k];	// therefore its resources are freed
			}
			cur_need.erase(cur_need.begin()+i); // its entry is removed from the need and alloc vector
			cur_alloc.erase(cur_alloc.begin()+i);
			i=-1;
		}
		
	}
	if (flag2==0) // if the need of none of the processes can be satisfied, then that is an unsafe state
	{
		return false;
	}
	} // end of for loop
	return true;

}

int main()
{
	
	cout << "Enter number of processes and no. of types of resources"<< endl;
	cin>>n>>m;
	cout << "Enter how much of each resource each process could possibly request for(MAX):"<< endl;
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin>>MAX[i][j];
		}
	}
	cout << "Enter how much of each resource each process is currently holding(allocated)"<< endl;
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin>>ALLOCATED[i][j];
		}
	}
	cout << "Enter how much of each resource the system currently has available(available)"<<endl;
	int AVAILABLE[m];
	for (int i = 0; i < m; ++i)
	{
		cin>>AVAILABLE[i];
	}
	// int NEED[n][m];
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			NEED[i][j]= MAX[i][j]-ALLOCATED[i][j];
			cout << NEED[i][j]<< " ";
			
		}cout<< endl;
		
	}
// cout << Check_safe(AVAILABLE)<< endl;

if(Check_safe(AVAILABLE)==false)
{
	cout << "System in unsafe state to begin with!"<< endl;
	return -1;
}
	
	while(1)
	{
		int p,r,req_amt;
		cout << "Enter pid,resource id,units of resource(to quit,pid as -1)"<< endl;
		cin>>p>>r>>req_amt;
		if(p==-1)
			break;
		if(req_amt>NEED[p][r])
		{
			cout << "request denied: beyond max limit"<< endl;
			continue;
		}
		if (req_amt>AVAILABLE[r])
		{
			cout << "request denied: requested amount of resources are not available yet.."<< endl;
			continue;
		}
		ALLOCATED[p][r]+=req_amt;
		NEED[p][r]-=req_amt;
		AVAILABLE[r]-=req_amt;
		if(Check_safe(AVAILABLE)==true)
		{
			cout << "request carried out! : system is in safe state"<< endl;
		}
		else
		{
			ALLOCATED[p][r]-=req_amt;
			NEED[p][r]+=req_amt;
			AVAILABLE[r]+=req_amt;
			cout << "request denied : request put system in unsafe state"<< endl;
			
		}
	}

	
}