#include<iostream>
#include<algorithm>
using namespace std;

struct Job 
{
	string name;
	double arriveTime;
	double serverTime;
	char status;
	Job *next;
};

bool fcomplare(Job a, Job b)
{
    return a.arriveTime < b.arriveTime;
}

//先进入先服务，按进入时间来排序 
void fCfs(int n, Job *jobs) //传入一个job数组 
{
	sort(jobs, jobs + n, fcomplare);
	
	//next生效 
	while(n)
	{
		jobs->next = jobs+1;
		jobs = jobs+1;
		n--;
	}
	
}

//调度完成
void remove(Job *job)
{
	job->status = 'F';
	
}

//即为调度函数
void process(double endTime, Job *job)
{
	cout<<"当前处理"<<job->name<<" ";
	//改变运行状态 
	job->status = 'R';
	cout<<"周转时间"<<endTime - job->arriveTime<<" ";
	cout<<"带权周转时间"<<job->serverTime / (endTime - job->arriveTime)<<endl;
	
}

void outStatus(int n, Job *job)
{
	//输出作业状态 
	for(int i = 0; i < n; i++)
	{
		cout<<job[i].name<<" "<<job[i].status<<" "<<endl;
	}
}

int main()
{
	//代表n个作业 
	int n;
	cin>>n;
	
	double startTime; //开始时间
	double endTime; //结束时间 
	struct Job job[n];
	
	//初始化作业状态 
	for(int i = 0; i < n; i++)
	{
		cin>>job[i].name>>job[i].serverTime>>job[i].arriveTime;
		job[i].status = 'W';
		job[i].next = NULL;
	}
	
	//调度排序 
	fCfs(n, job);
	
	//开始处理
	startTime = job[0].arriveTime;
	
	//处理前状态
	cout<<"处理前状态"<<endl;
	outStatus(n, job);
	
	for(int i = 0; i < n; i++)
	{

		//每个工作的结束时间 
		endTime += startTime + job[i].serverTime;
		process(endTime, &job[i]);
		outStatus(n, job);
		//调度结束
		remove(&job[i]);
		
	}
	//处理后状态
	cout<<"处理后状态"<<endl;
	outStatus(n, job);
	return 0;	
}
