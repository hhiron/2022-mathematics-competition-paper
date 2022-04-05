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
	int bedroom[6];//�洢���ҵĴ�С�Ŀ�����
	int livingroom[4];//�洢�����Ĵ�С�Ŀ�����
	int studyroom[5];//�洢�鷿�Ĵ�С�Ŀ�����
	int diningroom[4];//�洢�����Ĵ�С�Ŀ����� 
}N[1000001];//���͵Ŀ����Դ洢 
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
int roomSize[100],prob[20][100001][101],pro[1001],last=0x7fffffff,room[51];
void dfs_bed(int cnt,int lim,int beg,int pos){//���ҵ����� 
	if(cnt>lim){
		bedcnt++;
		for(int i=1;i<=lim;i++){
			bed[bedcnt][i]=roomSize[i];
			bedSum[bedcnt]+=roomSize[i];
		}
		return;
	}
	for(int i=beg;i<=pos;i++){
		roomSize[cnt]=be[i];
		dfs_bed(cnt+1,lim,i,pos);
	}
} 
void dfs_liv(int cnt,int lim,int beg,int pos){//���������� 
	if(cnt>lim){
		livcnt++;
		for(int i=1;i<=lim;i++){
			liv[livcnt][i]=roomSize[i];
			livSum[livcnt]+=roomSize[i];
		}
		//find(1,livcnt,livSum[livcnt]);
		return;
	}
	for(int i=beg;i<=pos;i++){
		roomSize[cnt]=li[i];
		dfs_liv(cnt+1,lim,i,pos);
	}
} 
void dfs_stu(int cnt,int lim,int beg,int pos){//�鷿������ 
	if(cnt>lim){
		stucnt++;
		for(int i=1;i<=lim;i++){
			stu[stucnt][i]=roomSize[i];
			stuSum[stucnt]+=roomSize[i];
		}
		return;
	}
	for(int i=beg;i<=pos;i++){
		roomSize[cnt]=st[i];
		dfs_stu(cnt+1,lim,i,pos);
	}
} 
void dfs_din(int cnt,int lim,int beg,int pos){//���������� 
	if(cnt>lim){
		dincnt++;
		for(int i=1;i<=lim;i++){
			din[dincnt][i]=roomSize[i];
			dinSum[dincnt]+=roomSize[i];
		}
		return;
	}
	for(int i=beg;i<=pos;i++){
		roomSize[cnt]=di[i];
		dfs_din(cnt+1,lim,i,pos);
	}
} 
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
	city[0]="�Ϻ�";
	city[1]="�Ͼ�";
	city[2]="����";
	city[3]="����";
	city[4]="�ɶ�";
	city[5]="����";
	city[6]="����";
	city[7]="�人";
	order[1]="1�űڹ�ʽ�յ�";
	order[2]="2�űڹ�ʽ�յ�";
	order[3]="1������ʽ�յ�";
	order[4]="2������ʽ�յ�";
	order[5]="2*1�űڹ�ʽ�յ�";
	order[6]="2*2�űڹ�ʽ�յ�";
	order[7]="2*1������ʽ�յ�";
	order[8]="2*2������ʽ�յ�";
	order[9]="1������ʽ�յ���2������ʽ�յ�";	
}
bool done=false;
int dfs_room(int cnt,int lim,int pos,double anss,int pn,int k){
	if(done==true) return 0;
	if(cnt>lim){
		if(int(anss)<=last){
			for(int j=1;j<pn;j++) prob[k][pos][j]=pro[j];
			last=int(anss);
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
				dfs_room(cnt+1,lim,pos,anss+a,pn+1,k);
			}else{
				pro[pn]=2;
				dfs_room(cnt+1,lim,pos,anss+b,pn+1,k);
			}
		
	}else if(room[cnt]>40&&room[cnt]<=60){
		double a=(ord[0].Value+(double)((room[cnt]*3)/ord[0].blow*ord[0].hot+(10-(room[cnt]*3)/ord[0].blow)*ord[0].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[0].blow*ord[0].cold+(10-(room[cnt]*3)/ord[0].blow)*ord[0].cold/5)*9/10*power[k])*2;
		double b=(ord[1].Value+(double)((room[cnt]*3)/ord[1].blow*ord[1].hot+(10-(room[cnt]*3)/ord[1].blow)*ord[1].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[1].blow*ord[1].cold+(10-(room[cnt]*3)/ord[1].blow)*ord[1].cold/5)*9/10*power[k])*2;
		double c=ord[2].Value+(double)((room[cnt]*3)/ord[2].blow*ord[2].hot+(10-(room[cnt]*3)/ord[2].blow)*ord[2].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[2].blow*ord[2].cold+(10-(room[cnt]*3)/ord[2].blow)*ord[2].cold/5)*9/10*power[k];
		double d=ord[3].Value+(double)((room[cnt]*3)/ord[3].blow*ord[3].hot+(10-(room[cnt]*3)/ord[3].blow)*ord[3].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[3].blow*ord[3].cold+(10-(room[cnt]*3)/ord[3].blow)*ord[3].cold/5)*9/10*power[k];
		double e=(other[0].Value*room[cnt]*2+(double)room[cnt]*other[0].hot*9/10*power[k]);
		if(a==Min(a,b,c,d)){
			pro[pn]=5;
			dfs_room(cnt+1,lim,pos,anss+a,pn+1,k);
		}else if(b==Min(a,b,c,d)){
			pro[pn]=6;
			dfs_room(cnt+1,lim,pos,anss+b,pn+1,k);
		}else if(c==Min(a,b,c,d)){
			pro[pn]=3;
			dfs_room(cnt+1,lim,pos,anss+c,pn+1,k);
		}else{
			pro[pn]=4;
			dfs_room(cnt+1,lim,pos,anss+d,pn+1,k);
		}
	}else{
		double a=ord[2].Value+(double)((room[cnt]*3)/ord[2].blow*ord[2].hot+(10-(room[cnt]*3)/ord[2].blow)*ord[2].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[2].blow*ord[2].cold+(10-(room[cnt]*3)/ord[2].blow)*ord[2].cold/5)*9/10*power[k];
		double b=ord[3].Value+(double)((room[cnt]*3)/ord[3].blow*ord[3].hot+(10-(room[cnt]*3)/ord[3].blow)*ord[3].hot/5)*9/10*power[k]+(double)((room[cnt]*3)/ord[3].blow*ord[3].cold+(10-(room[cnt]*3)/ord[3].blow)*ord[3].cold/5)*9/10*power[k];
		double C=a*2;
		double D=b+b;
		if(C<D){
			pro[pn]=7;
			dfs_room(cnt+1,lim,pos,anss+C,pn+1,k);
		}else{
			pro[pn]=8;
			dfs_room(cnt+1,lim,pos,anss+D,pn+1,k);
		}
	}
}

int dfs_onlyroom(int size,int k){
	if(size<=40){
		double a=ord[0].Value+(double)((size*3)/ord[0].blow*ord[0].hot+(10-(size*3)/ord[0].blow)*ord[0].hot/5)*9/10*power[k]+(double)((size*3)/ord[0].blow*ord[0].cold+(10-(size*3)/ord[0].blow)*ord[0].cold/5)*9/10*power[k];
		double b=ord[1].Value+(double)((size*3)/ord[1].blow*ord[1].hot+(10-(size*3)/ord[1].blow)*ord[1].hot/5)*9/10*power[k]+(double)((size*3)/ord[1].blow*ord[1].cold+(10-(size*3)/ord[1].blow)*ord[1].cold/5)*9/10*power[k];
		double d=other[0].Value*size*2+(double)size*other[0].hot*9/10*power[k];
			if(a<=b){
				return 1;
			}else{
				return 2;
			}
		
	}else if(size>40&&size<=60){
		double a=(ord[0].Value+(double)((size*3)/ord[0].blow*ord[0].hot+(10-(size*3)/ord[0].blow)*ord[0].hot/5)*9/10*power[k]+(double)((size*3)/ord[0].blow*ord[0].cold+(10-(size*3)/ord[0].blow)*ord[0].cold/5)*9/10*power[k])*2;
		double b=(ord[1].Value+(double)((size*3)/ord[1].blow*ord[1].hot+(10-(size*3)/ord[1].blow)*ord[1].hot/5)*9/10*power[k]+(double)((size*3)/ord[1].blow*ord[1].cold+(10-(size*3)/ord[1].blow)*ord[1].cold/5)*9/10*power[k])*2;
		double c=ord[2].Value+(double)((size*3)/ord[2].blow*ord[2].hot+(10-(size*3)/ord[2].blow)*ord[2].hot/5)*9/10*power[k]+(double)((size*3)/ord[2].blow*ord[2].cold+(10-(size*3)/ord[2].blow)*ord[2].cold/5)*9/10*power[k];
		double d=ord[3].Value+(double)((size*3)/ord[3].blow*ord[3].hot+(10-(size*3)/ord[3].blow)*ord[3].hot/5)*9/10*power[k]+(double)((size*3)/ord[3].blow*ord[3].cold+(10-(size*3)/ord[3].blow)*ord[3].cold/5)*9/10*power[k];
		double e=(other[0].Value*size*2+(double)size*other[0].hot*9/10*power[k]);
		cout<<c<<" "<<d<<endl;
		if(a==Min(a,b,c,d)){
			return 5;
		}else if(b==Min(a,b,c,d)){
			return 6;
		}else if(c==Min(a,b,c,d)){
			return 3;
		}else{
			return 4;
		}
	}else{
		double a=ord[2].Value+(double)((size*3)/ord[2].blow*ord[2].hot+(10-(size*3)/ord[2].blow)*ord[2].hot/5)*9/10*power[k]+(double)((size*3)/ord[2].blow*ord[2].cold+(10-(size*3)/ord[2].blow)*ord[2].cold/5)*9/10*power[k];
		double b=ord[3].Value+(double)((size*3)/ord[3].blow*ord[3].hot+(10-(size*3)/ord[3].blow)*ord[3].hot/5)*9/10*power[k]+(double)((size*3)/ord[3].blow*ord[3].cold+(10-(size*3)/ord[3].blow)*ord[3].cold/5)*9/10*power[k];
		double C=a*2;
		double D=b*2;
		double E=a+b;
		cout<<C<<"��"<<D<<" "<<E<<endl; 
		if(C==min(D,min(C,E))){
			return 7;
		}else if(D==min(D,min(C,E))){
			return 8;
		}else{
			return 9;
		}
	}
}

int main(){
	//���������ʹ������ 
	//freopen("ans.out","w",stdout);
	init();
//	for(int j=0;j<=7;j++){
//		for(int i=5;i<=100;i++) single[j][i]=dfs_onlyroom(i,j);	
//	}
//	for(int j=0;j<=7;j++){
//		cout<<city[j]<<endl;
//		for(int i=5;i<=100;i++){
//			cout<<i<<" "<<order[single[j][i]]<<endl;
//		}
//		cout<<"\n";
//	}
	
	stu[1][1]=0,din[1][1]=0;
	memset(bedSum,0,sizeof(bedSum));
	memset(livSum,0,sizeof(livSum));
	memset(stuSum,0,sizeof(stuSum));
	memset(dinSum,0,sizeof(dinSum));
	for(int i=1;i<=6;i++) dfs_bed(1,i,max(0,i-3),min(i+1,6));
	for(int i=1;i<=2;i++) dfs_liv(1,i,max(0,i-1),min(i+5,7)); 
	for(int i=1;i<=4;i++) dfs_stu(1,i,max(0,i),min(i+2,6)); 
	for(int i=1;i<=2;i++) dfs_din(1,i,max(0,i-1),min(i+3,7));
	ull cnt=0;
	for(int i=1;i<=bedcnt;i++){
		for(int j=1;j<=livcnt;j++){
			if((double)abs(livSum[j]-bedSum[i])/min(livSum[j],bedSum[i])>0.25) continue;
			int cnt1=0,cnt2=0;
			for(int x=1;bed[i][x];x++){
				cnt1++;
			}
			for(int x=1;liv[j][x];x++){
				cnt2++;
			}
			if(cnt2>=cnt1&&cnt2>=1) break;
			if(cnt1==3&&cnt2==2) break;
			for(int k=1;k<=stucnt&&k<=i;k++){
				if(stuSum[k]!=0)if((livSum[j]+bedSum[i])/stuSum[k]<=4) break;
				for(int g=1;g<=dincnt&&g<j;g++){
					if(dinSum[g]!=0)if((livSum[j]+bedSum[i])/dinSum[g]<=2.5) break;
					cnt++;
					for(int x=1;bed[i][x];x++) N[cnt].bedroom[x]=bed[i][x]; 
					for(int x=1;liv[j][x];x++) N[cnt].livingroom[x]=liv[j][x]; 
					for(int x=1;stu[k][x];x++) N[cnt].studyroom[x]=stu[k][x]; 
					for(int x=1;din[g][x];x++) N[cnt].diningroom[x]=din[g][x]; 
				}
			}
		}
	}
	int n=0,size=0,pn;
	double cost;
	bool is1;
	//cout<<cnt<<" "; 
	for(int k=0;k<=7;k++){
		for(int i=1;i<=cnt;i++){
			last=0x7fffffff;
			n=0,size=0,cost=0,pn=0;
			memset(room,0,sizeof(room));
			for(int x=1;N[i].bedroom[x];x++) room[++n]=N[i].bedroom[x];
			for(int x=1;N[i].livingroom[x];x++) room[++n]=N[i].livingroom[x];
			for(int x=1;N[i].studyroom[x];x++) room[++n]=N[i].studyroom[x];
			for(int x=1;N[i].diningroom[x];x++) room[++n]=N[i].diningroom[x];
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
					if(is1) dfs_room(q,n,i,cost,pn+1,k);
					else dfs_room(q+1,n,i,cost,pn+1,k);
				}
			}
			done=false;
			dfs_room(1,n,i,0,1,k);
			cost=0;
		}
	}	
	string central[101];
	central[2]="һ�϶�����յ�"; 
	central[3]="һ��������յ�"; 
	central[4]="һ��������յ�"; 
	central[5]="һ��������յ�"; 
	central[6]="һ��������յ�"; 
	char cciitt[5];
	for(int k=0;k<=7;k++){
		cciitt[0]=city[k][0];
		cciitt[1]=city[k][1];
		cciitt[3]=city[k][3];
		cciitt[4]=city[k][4];
		freopen(cciitt,"w",stdout);
		cout<<city[k]<<endl;
		for(int i=1;i<=cnt;i++){
			cout<<"bedroom: ";
			for(int x=1;N[i].bedroom[x];x++) cout<<N[i].bedroom[x]<<" ";
			cout<<"livingroom: ";
			for(int x=1;N[i].livingroom[x];x++) cout<<N[i].livingroom[x]<<" ";
			cout<<"study: ";
			for(int x=1;N[i].studyroom[x];x++) cout<<N[i].studyroom[x]<<" ";
			cout<<"diningroom: ";
			for(int x=1;N[i].diningroom[x];x++) cout<<N[i].diningroom[x]<<" ";
			cout<<endl;
			memset(room,0,sizeof(room));
			n=0;
			for(int x=1;N[i].bedroom[x];x++) room[++n]=N[i].bedroom[x];
			for(int x=1;N[i].livingroom[x];x++) room[++n]=N[i].livingroom[x];
			for(int x=1;N[i].studyroom[x];x++) room[++n]=N[i].studyroom[x];
			for(int x=1;N[i].diningroom[x];x++) room[++n]=N[i].diningroom[x];
			sort(room+1,room+n+1,cmp);
			for(int j=1,ss=1;ss<=n;j++,ss++){
				if(prob[k][i][j]>=10) {
					for(int pp=ss;pp<ss+prob[k][i][j]-10;pp++){
						cout<<room[pp]<<" ";
					}cout<<":"<<central[prob[k][i][j]-10]<<" ",ss+=prob[k][i][j]-11;
				}
				else cout<<room[ss]<<":"<<order[prob[k][i][j]]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	return 0;
}
