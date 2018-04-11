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

//其次按照服务时间排序
bool scomplare(Job a, Job b)
{
	return a.serverTime < b.serverTime;
}

//首先按照到达时间排序
bool fcomplare(Job a, Job b)
{
	return a.arriveTime < b.arriveTime;
}

//短服务优先，按服务时间来排序 
void sjf(int n, Job *jobs) //传入一个job数组 
{
	sort(jobs, jobs + n, scomplare);
	
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

	//按照到达时间排序
	sort(job, job + n, fcomplare);


	//处理前状态
	cout<<"处理前状态"<<endl;
	outStatus(n, job);

	//开始处理
	startTime = job[0].arriveTime;

	//处理第一个
	endTime = startTime + job[0].serverTime;
	process(endTime, &job[0]);
	outStatus(n, job);

	remove(&job[0]);

	//调度排序 
	sjf(n-1, &job[1]);
	
	//处理剩余的
	for(int i = 1; i < n; i++)
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
