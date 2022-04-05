#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<queue>
#include<vector>
#define maxn 0x7fffffff
#define minn 0xcf
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
inline bool cmp(int x,int y){
	return x>y?1:0;
}
inline double Min(double x,double y,double z,double w){
	return min(min(x,y),min(z,w));
}
struct house{
	int bedroom[6];//存储卧室的大小的可能性
	int livingroom[4];//存储客厅的大小的可能性
	int studyroom[5];//存储书房的大小的可能性
	int diningroom[4];//存储厨房的大小的可能性 
}N[1000001];//户型的可能性存储 
struct airco{
	double cold,hot,blow;
	double area_low,area_high;
	double length_in,width_in,height_in;
	double length_out,width_out,height_out;
	double Value;
};
airco cent[6];
airco ord[4];
airco other[3];
int bed[1001][10],bedcnt=0,bedSum[1001];
int liv[1001][7],livcnt=0,livSum[1001];
int stu[1001][7],stucnt=1,stuSum[1001];
int din[1001][5],dincnt=1,dinSum[1001];
int be[100]={6,10,20,27,35,47,54};
int li[100]={15,20,25,35,45,55,72,84};
int di[100]={13,17,25,39,55,64,75,84};
int st[100]={6,10,15,20,25,30,37,49,60};
int single[10][105];
double power[10]={0.6170,0.5283,0.5100,0.4956,0.4896,0.4400,0.5921,0.5700};
map<int,string> city;
map<int,string> order;
int roomSize[100],prob[20][101],pro[1001],last=0x7fffffff,room[51];
double pr[101];
void init(){
	cent[0].cold=2700,cent[0].hot=2700,cent[0].blow=940,cent[0].length_in=700,cent[0].width_in=450,cent[0].height_in=200,cent[0].length_out=946,cent[0].width_out=420,cent[0].height_out=810,cent[0].Value=22699,cent[0].area_high=75,cent[0].area_low=36;
	cent[1].cold=3450,cent[1].hot=3200,cent[1].blow=1410,cent[1].length_in=700,cent[1].width_in=450,cent[1].height_in=200,cent[1].length_out=946,cent[1].width_out=420,cent[1].height_out=810,cent[1].Value=28399,cent[1].area_high=75,cent[1].area_low=36;
	cent[2].cold=4000,cent[2].hot=4000,cent[2].blow=2120,cent[2].length_in=700,cent[2].width_in=450,cent[2].height_in=200,cent[2].length_out=946,cent[2].width_out=420,cent[2].height_out=810,cent[2].Value=33799,cent[2].area_high=75,cent[2].area_low=36;
	cent[3].cold=4300,cent[3].hot=4350,cent[3].blow=4000,cent[3].length_in=1010,cent[3].width_in=450,cent[3].height_in=200,cent[3].length_out=958,cent[3].width_out=417,cent[3].height_out=1333,cent[3].Value=39999,cent[3].area_high=75,cent[3].area_low=36;
	cent[4].cold=5200,cent[4].hot=5200,cent[4].blow=5400,cent[4].length_in=1010,cent[4].width_in=450,cent[4].height_in=200,cent[4].length_out=958,cent[4].width_out=417,cent[4].height_out=1333,cent[4].Value=47699,cent[4].area_high=75,cent[4].area_low=36;
	ord[0].cold=810,ord[0].hot=1250,ord[0].blow=710,ord[0].length_in=825,ord[0].width_in=196,ord[0].height_in=293,ord[0].length_out=802,ord[0].width_out=350,ord[0].height_out=555,ord[0].Value=3209,ord[0].area_high=20,ord[0].area_low=16;
	ord[1].cold=750,ord[1].hot=1320,ord[1].blow=630,ord[1].length_in=880,ord[1].width_in=210,ord[1].height_in=290,ord[1].length_out=857,ord[1].width_out=328,ord[1].height_out=555,ord[1].Value=3195,ord[1].area_high=23,ord[1].area_low=15;
	ord[2].cold=2080,ord[2].hot=2680,ord[2].blow=1200,ord[2].length_in=370,ord[2].width_in=440,ord[2].height_in=1830,ord[2].length_out=950,ord[2].width_out=360,ord[2].height_out=700,ord[2].Value=5299,ord[2].area_high=48,ord[2].area_low=32;
	ord[3].cold=1970,ord[3].hot=2650,ord[3].blow=1300,ord[3].length_in=377,ord[3].width_in=407,ord[3].height_in=1760,ord[3].length_out=960,ord[3].width_out=400,ord[3].height_out=703,ord[3].Value=5459,ord[3].area_high=40,ord[3].area_low=31;
	other[0].hot=140,other[0].length_in=1000,other[0].width_in=500,other[0].Value=188;
	other[1].cold=40,other[1].length_in=325,other[1].width_in=325,other[1].height_in=1100,other[1].Value=429,other[1].area_high=28,other[1].area_low=15;
	other[2].cold=50,other[2].length_in=450,other[2].width_in=400,other[2].height_in=1300,other[2].Value=149,other[2].area_high=18,other[2].area_low=10;
	city[0]="上海";
	city[1]="南京";
	city[2]="重庆";
	city[3]="贵阳";
	city[4]="成都";
	city[5]="昆明";
	city[6]="广州";
	city[7]="武汉";
	order[1]="Gree格力 KFR-35GW";
	order[2]="Midea美的 KFR-35GW";
	order[3]="AUX奥克斯 KFR-72LW";
	order[4]="Haier海尔 KFR-72LW";
	order[5]="2*Gree格力 KFR-35GW";
	order[6]="2*Midea美的 KFR-35GW";
	order[7]="2*AUX奥克斯 KFR-72LW";
	order[8]="2*Haier海尔 KFR-72LW";
	
}
bool done=false;
int dfs_room(int cnt,int lim,double anss,int pn,int k){
	if(done==true) return 0;
	if(cnt>lim){
		if(int(anss)<=last){
			for(int j=1;j<pn;j++) prob[k][j]=pro[j];
			last=int(anss);
			pr[k]=anss;
		}
		done=true;
		return 0;
	}
	if(room[cnt]<=40){
		double a=ord[0].Value+(double)((room[cnt]*3)/ord[0].blow*ord[0].hot+(10-(room[cnt]*3)/ord[0].blow)*ord[0].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[0].blow*ord[0].cold+(10-(room[cnt]*3)/ord[0].blow)*ord[0].cold/5)*9/10*power[k];
		double b=ord[1].Value+(double)((room[cnt]*3)/ord[1].blow*ord[1].hot+(10-(room[cnt]*3)/ord[1].blow)*ord[1].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[1].blow*ord[1].cold+(10-(room[cnt]*3)/ord[1].blow)*ord[1].cold/5)*9/10*power[k];
		double d=other[0].Value*room[cnt]*2+(double)room[cnt]*other[0].hot*9/10*power[k];
			if(a<=b){
				pro[pn]=1;
				dfs_room(cnt+1,lim,anss+a,pn+1,k);
			}else{
				pro[pn]=2;
				dfs_room(cnt+1,lim,anss+b,pn+1,k);
			}
		
	}else if(room[cnt]>40&&room[cnt]<=60){
		double a=(ord[0].Value+(double)((room[cnt]*3)/ord[0].blow*ord[0].hot+(10-(room[cnt]*3)/ord[0].blow)*ord[0].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[0].blow*ord[0].cold+(10-(room[cnt]*3)/ord[0].blow)*ord[0].cold/5)*9/10*power[k])*2;
		double b=(ord[1].Value+(double)((room[cnt]*3)/ord[1].blow*ord[1].hot+(10-(room[cnt]*3)/ord[1].blow)*ord[1].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[1].blow*ord[1].cold+(10-(room[cnt]*3)/ord[1].blow)*ord[1].cold/5)*9/10*power[k])*2;
		double c=ord[2].Value+(double)((room[cnt]*3)/ord[2].blow*ord[2].hot+(10-(room[cnt]*3)/ord[2].blow)*ord[2].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[2].blow*ord[2].cold+(10-(room[cnt]*3)/ord[2].blow)*ord[2].cold/5)*9/10*power[k];
		double d=ord[3].Value+(double)((room[cnt]*3)/ord[3].blow*ord[3].hot+(10-(room[cnt]*3)/ord[3].blow)*ord[3].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[3].blow*ord[3].cold+(10-(room[cnt]*3)/ord[3].blow)*ord[3].cold/5)*9/10*power[k];
		double e=(other[0].Value*room[cnt]*2+(double)room[cnt]*other[0].hot*9/10*power[k]);
		if(a==Min(a,b,c,d)){
			pro[pn]=5;
			dfs_room(cnt+1,lim,anss+a,pn+1,k);
		}else if(b==Min(a,b,c,d)){
			pro[pn]=6;
			dfs_room(cnt+1,lim,anss+b,pn+1,k);
		}else if(c==Min(a,b,c,d)){
			pro[pn]=3;
			dfs_room(cnt+1,lim,anss+c,pn+1,k);
		}else{
			pro[pn]=4;
			dfs_room(cnt+1,lim,anss+d,pn+1,k);
		}
	}else{
		double a=ord[2].Value+(double)((room[cnt]*3)/ord[2].blow*ord[2].hot+(10-(room[cnt]*3)/ord[2].blow)*ord[2].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[2].blow*ord[2].cold+(10-(room[cnt]*3)/ord[2].blow)*ord[2].cold/5)*9/10*power[k];
		double b=ord[3].Value+(double)((room[cnt]*3)/ord[3].blow*ord[3].hot+(10-(room[cnt]*3)/ord[3].blow)*ord[3].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[3].blow*ord[3].cold+(10-(room[cnt]*3)/ord[3].blow)*ord[3].cold/5)*9/10*power[k];
		double C=a*2;
		double D=b+b;
		if(C<D){
			pro[pn]=7;
			dfs_room(cnt+1,lim,anss+C,pn+1,k);
		}else{
			pro[pn]=8;
			dfs_room(cnt+1,lim,anss+D,pn+1,k);
		}
	}
}
int main(){
	//freopen("ans.out","w",stdout);
	init();
	int n;
	cout<<"请输入房间数量：";
	scanf("%d",&n);
	cout<<"请输入各个房间的面积：";
	for(int i=1;i<=n;i++){
		scanf("%d",&room[i]);
	}
	stu[1][1]=0,din[1][1]=0;
	ull cnt=0;
	int size=0,pn;
	double cost;
	bool is1;
	for(int k=0;k<=7;k++){
			last=0x7fffffff;
			size=0,cost=0,pn=0;
			sort(room+1,room+n+1,cmp);
			if(n>=5){
				for(int q=2;q<=n;q++){
					memset(pro,0,sizeof(pro));
					cost=0;
					pn=0;
					size=room[1];
					for(int j=2;j<=q;j++) size+=room[j];
					is1=false;
					for(int s=q;s>0;s-=6){
						int g=s>=6?6:s;
						if(g==1) {is1=true;continue;}
						cost+=cent[g-2].Value;
						pro[++pn]=10+g;
						//cout<<pn<<" ";
						cost+=(double)((size*3)/cent[g-2].blow*cent[g-2].hot+(10-(size*3)/cent[g-2].blow)*cent[g-2].hot/5)*9/10*power[k];
						cost+=(double)((size*3)/cent[g-2].blow*cent[g-2].cold+(10-(size*3)/cent[g-2].blow)*cent[g-2].cold/5)*9/10*power[k];
					}
					done=false;
					if(is1) dfs_room(q,n,cost,pn+1,k);
					else dfs_room(q+1,n,cost,pn+1,k);
				}
			}
			done=false;
			dfs_room(1,n,0,1,k);
			cost=0;
	}
		
	string central[101];
	central[2]="一拖二中央空调"; 
	central[3]="一拖三中央空调"; 
	central[4]="一拖四中央空调"; 
	central[5]="一拖五中央空调"; 
	central[6]="一拖六中央空调"; 
	for(int k=0;k<=7;k++){
		cout<<city[k]<<endl;
		for(int j=1,i=1;i<=n;j++,i++){
			if(prob[k][j]>=10){
				for(int pp=i;pp<i+prob[k][j]-10;pp++){
					cout<<room[pp]<<" ";
				}cout<<":"<<central[prob[k][j]-10]<<" ",i+=prob[k][j]-11;
			} 
			else cout<<room[i]<<":"<<order[prob[k][j]]<<" ";
		}	
		cout<<"price"<<":"<<pr[k]<<endl;
	}
	
	cout<<cnt;
	return 0;
}
