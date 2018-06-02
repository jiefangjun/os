#include<iostream>
using namespace std;

struct Process{
	string name;
	double arriveTime;
	double serverTime;
	double servedTime;
	char status;
	double turnTime; 	//周转时间
	double wTurnTime;	//带权周转时间
	Process *next; 		//指向下一个进程的指针
};

// 输出状态函数
void outStatus(int *n, Process *p)
{

	for(int i = 0; i < *n - 1; i++)
	{
		cout<<p[i].name<<"当前状态为"<<p[i].status<<" 下一个 "<<p[i].next->name<<endl;

	}

	cout<<p[*n-1].name<<"当前状态为"<<p[*n-1].status<<endl;

}

// 删除函数 *p 指向亦完成的进程
void remove(int *n)
{
	// 队首指向下一个元素, 即跳过当前元素
	*n -= 1;	
}

// 调度处理函数 *pa代表数组首地址
void proce(int *n, double size, double *endTime, Process *pa, Process *p)
{
	cout<<"当前处理"<<p->name<<endl;
		
	// 运行状态
	p->status = 'R';

	// 服务时间减去时间片大小
	p->servedTime += size;
	*endTime += size;
	
	// 输出运行态
	outStatus(n, pa);

	// 运行结束
	if(p->servedTime >= p->serverTime){
		p->status = 'F';
		p->turnTime = (*endTime - (p->servedTime - p->serverTime)) - p->arriveTime;
		p->wTurnTime = p->turnTime / p->serverTime;

		// 恢复结束时间
		*endTime -= p->servedTime - p->serverTime;
		remove(n);
	}
	else{
		// 未运行结束
		p->status = 'W'; // 恢复等待状态

	}
	
}



int main()
{
	// n 个进程
	int n, num;
	cout<<"输入进程个数"<<endl;
	cin>>n;
	cout<<"输入时间片大小"<<endl;
	double s;
	cin>>s;

	double startTime;
	double endTime;

	// 指向队首
	Process *head;

	Process p[n];

	num = n;
	cout<<"按到达时间分别输入进程名、服务时间、到达时间"<<endl;
	// 初始化进程
	for(int i = 0; i < n; i++){
		cin>>p[i].name>>p[i].serverTime>>p[i].arriveTime;
		p[i].status = 'W';

		// 已经服务的时间
		p[i].servedTime = 0;

		// 头尾指针置空
		p[i].next = NULL;
	}
	
	// 队首即第一个进程
	head = p;
	
	// 初始化指针
	for(int i = 0; i < n - 1; i++){
		p[i].next = &p[i+1];
	}
	// 最后一个重新指向第一个
	p[n-1].next = p;

	//处理前状态
	cout<<"处理前状态"<<endl;
	outStatus(&n, p);

	// 开始处理
	startTime = p[0].arriveTime;
	endTime = startTime;

	// 控制处理流程循环	
	while(n){
		if(head->status != 'F')
		{
			proce(&n, s, &endTime, p, head);
		}
		head = head->next;
	}

	// 运行结束状态
	cout<<"运行结束"<<endl;
	outStatus(&num, p);

	for(int i = 0; i < num; i++)
		cout<<p[i].name<<"周转时间:"<<p[i].turnTime<<"带权周转时间"<<p[i].wTurnTime<<endl;
	
	return 0;

}
