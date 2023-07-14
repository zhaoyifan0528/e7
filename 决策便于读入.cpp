//author:D3Tekim
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring> 
#include<ctime>
using namespace std;
int num = 1;
double money = 0, qiang = 0;
string name[10] = {"固定生命","生命百分比",
"攻击百分比","速度","暴击率","暴击伤害","效果命中",
"效果抗性","固定攻击","固定防御"};
double score_att[10]={0,0,1,2,1.5,1.1,0,0,0.11,0}; 
int add_val[10][100];
double now_score = 0,sp_score = 0,now_score_att = 0;
int add_range[10][100];//*10000 
//Each prefix sum is divided by the last prefix sum
//random in last prefix and find the next bigger number
int add_num[10]={46,5,5,4,3,4,5,5,14,8};
int add_val_p[10][100];
int add_range_p[10][100];//*10000 
int add_num_p[10]={44,5,5,4,3,4,5,5,14,8};
int val[5],typ[5];long long gen = 0;
double score[10]={0.02,1,1,2,1.5,1.1,1,1,0.11,0.167};
double rubb_p[10]={0,0,0,1.54,0,0,2.58,0,0,5.923};
double rubb_money_p[10]={0,0,0,3.7,0,0,6.2,0,0,14.2};
double rubb[10]={0,0,0,1.54,0,0,3.1,0,0,6.62};
double rubb_money[10]={0,0,0,3.7,0,0,7.43,0,0,15.88};
int speed[50],fen[100],fen_att[100];
int sum_speed[50],sum_fen[100],sum_fen_att[100];
int gl[24];
void gener_init_por(int gen_number)
{
	int v1,flag;
	while(1)
	{
		//Ensure that different initial entries are generated
		v1 = rand()%10;flag = 0;
		for(int i = 1;i <= gen_number - 1; ++i)
		{
			if(v1 == typ[i]) flag = 1;
		}
		if(!flag) {typ[gen_number] = v1;break;}
	}
	int now = rand()%add_range_p[v1][add_num_p[v1]];
	for(int i = 1;i <= add_num_p[v1];++i)//can be optimized
	{
		if(now < add_range_p[v1][i])
		{
			val[gen_number] = add_val_p[v1][i];
			now_score += val[gen_number] * score[v1];
			now_score_att += val[gen_number] * score_att[v1];
			if(v1 == 3) sp_score = val[gen_number];
			break;
		}
	}
}
void get_score(int whr,int add_fla)
{
	//printf("该装备强化到%d结束，下面是属性值\n",add_fla);
	for(int i = 1;i <= whr;++i)
	{
		//printf("第%d个词条是%s，他的值是%d\n",
		//i,name[typ[i]].c_str(),val[i]);
		if(typ[i] == 3) speed[val[i]]++;//get all speed val
	}
	fen[(int)now_score] ++;
	fen_att[(int)now_score_att] ++; 
	if(add_fla == 0)	gen += whr + 6;
	if(add_fla > 0 && add_fla < 15) 
	{
		if(whr == 4) 
		{
			money += rubb_money[add_fla] ;
			qiang -= rubb[add_fla];
		}
		if(whr == 3)
		{
			money += rubb_money_p[add_fla];
			qiang -= rubb_p[add_fla];
		}
	}
}
void gener_init(int gen_number)
{
	int v1,flag;
	while(1)
	{
		//Ensure that different initial entries are generated
		v1 = rand()%10;flag = 0;
		for(int i = 1;i <= gen_number - 1; ++i)
		{
			if(v1 == typ[i]) flag = 1;
		}
		//cout<<v1<<endl;
		if(!flag) {typ[gen_number] = v1;break;}
	}
	int now = rand()%add_range[v1][add_num[v1]];
	//cout<<"now = "<<now<<endl;
	for(int i = 1;i <= add_num[v1];++i)//can be optimized
	{
		if(now < add_range[v1][i])
		{
			val[gen_number] = add_val[v1][i];
			now_score += val[gen_number] * score[v1];
			now_score_att += val[gen_number] * score_att[v1];
			if(v1 == 3) sp_score = val[gen_number];
			break;
		}
	}
}

//add val
void add_v(int whr)
{
	int ent = rand()%whr + 1;
	int v1 = typ[ent];
	int now1 = rand()%add_range[v1][add_num[v1]] + 1;
	for(int i = 1;i <= add_num[v1];++i)//can be optimized
	{
		if(now1 < add_range[v1][i])
		{
			val[ent] += add_val[v1][i];
			//printf("%d----%d\n",v1,add_val[v1][i]);
			if(v1 == 3) sp_score = val[ent];
			now_score += add_val[v1][i] * score[v1];
			now_score_att += add_val[v1][i] * score_att[v1];
			break;
		}
	}
}
void gener_por()
{
	//printf("这是第%d件装备,他是紫装\n",num);
	now_score = 0,sp_score = 0;now_score_att = 0;
	for(int i = 1;i <= 3;++i) gener_init_por(i);
	for(int i = 1;i <= 3;++i)
	{
		//printf("第%d个词条是%s，他的值是%d\n",
		//i,name[typ[i]].c_str(),val[i]);
	}
	//printf("这件紫装的分数是%.1lf\n",now_score);
	if(sp_score < gl[3] && now_score < gl[4] && now_score_att < gl[5]) 
	{get_score(3,0);return ;}
	//+3
	add_v(3);
	money += 2.88;qiang += 2;
	if(sp_score < gl[9] && now_score < gl[10] && now_score_att < gl[11]) 
	{get_score(3,3);return ;}
	//+6
	add_v(3);
	money += 2.88;qiang += 2;
	if(sp_score < gl[15] && now_score < gl[16] && now_score_att < gl[17]) 
	{get_score(3,6);return ;}
	//+9
	add_v(3);
	money += 10.08;qiang += 7;
	if(sp_score < gl[21] && now_score < gl[22] && now_score_att < gl[23]) 
	{get_score(3,9);return ;}
	//this pos need to be super judged
	gener_init_por(4);
	add_v(4);
	money += 53.28;qiang += 37;
	get_score(4,15);
}

void solve()
{
	// remember add srand()
	int now = rand()%100;
	if(num % 30 == 0) {now = 98;}//printf("此次为必定传说");} 
	if(now <= 34) {gen += 7;return ;}
	if(now <= 87) {gener_por();return ;}
	
	//printf("这是第%d件装备,他是红装\n",num);
	now_score = 0,sp_score = 0;now_score_att = 0;
	for(int i = 1;i <= 4;++i) gener_init(i); 
	for(int i = 1;i <= 4;++i)
	{
		//printf("第%d个词条是%s，他的值是%d\n",
		//i,name[typ[i]].c_str(),val[i]);
	}
	//printf("这件红装的分数是%.1lf\n",now_score);
	if(sp_score < gl[0] && now_score < gl[1] && now_score_att < gl[2]) 
	{get_score(4,0);return ;}
	//+3
	add_v(4);
	money += 2.88;qiang += 2;
	if(sp_score < gl[6] && now_score < gl[7] && now_score_att < gl[8]) 
	{get_score(4,3);return ;}
	//+6
	add_v(4);
	money += 4.32;qiang += 3;
	if(sp_score < gl[12] && now_score < gl[13] && now_score_att < gl[14]) 
	{get_score(4,6);return ;}
	//+9
	add_v(4);
	money += 10.08;qiang += 7;
	if(sp_score < gl[18] && now_score < gl[19] && now_score_att < gl[20]) 
	{get_score(4,9);return ;}
	add_v(4);add_v(4);
	money += 59.02;qiang += 41;
	get_score(4,15);
}
int main()
{
	srand(time(0));
	//regular health
	add_val[0][1] = 157 ;
	add_range[0][1] = 113;
	add_val_p[0][1] = 149 ;
	add_range_p[0][1] = 89;
	for(int i = 2;i <= 45;++i)
	{
		add_val[0][i] = 157 + i - 1;
		add_range[0][i] = 222 + add_range[0][i-1];
		add_val_p[0][i] = 149 + i - 1;
		add_range_p[0][i] = 234 + add_range_p[0][i-1];
	}
	add_val[0][46] = 202;
	add_range[0][46] = 113 + add_range[0][45];
	add_val_p[0][44] = 192;
	add_range_p[0][44] = 89 + add_range_p[0][43];
	//percent health
	for(int i = 1;i <= 5;++i)
	{
		add_val[1][i] = 4 + i - 1;
		add_range[1][i] = 20 + add_range[1][i-1];
		add_val_p[1][i] = 4 + i - 1;
		add_range_p[1][i] = 20 + add_range_p[1][i-1];
	}
	//percent dam
	for(int i = 1;i <= 5;++i)
	{
		add_val[2][i] = 4 + i - 1;
		add_range[2][i] = 20 + add_range[2][i-1];
		add_val_p[2][i] = 4 + i - 1;
		add_range_p[2][i] = 20 + add_range_p[2][i-1];
	}
	//speed
	add_val_p[3][1] = 1;
	add_range_p[3][1] = 383 ;
	for(int i = 1;i <= 3;++i)
	{
		add_val[3][i] = i + 1;
		add_range[3][i] = 3322 + add_range[3][i-1];
		if(i > 1)
		{
			add_val_p[3][i] = i;
			add_range_p[3][i] = 3484 + add_range_p[3][i-1];
		}
	}
	add_val[3][4] = 5;
	add_range[3][4] = 33 + add_range[3][3];
	add_val_p[3][4] = 4;
	add_range_p[3][4] = 2648 + add_range_p[3][3];
	//critical rate
	for(int i = 1;i <= 3;++i)
	{
		add_val[4][i] = i + 2;
		add_range[4][i] = 1 + add_range[4][i-1];
		add_val_p[4][i] = i + 2;
		add_range_p[4][i] = 1 + add_range_p[4][i-1];
	}
	//critical dam
	for(int i = 1;i <= 4;++i)
	{
		add_val[5][i] = i + 3;
		add_range[5][i] = 1 + add_range[5][i-1];
		add_val_p[5][i] = i + 3;
		add_range_p[5][i] = 1 + add_range_p[5][i-1];
	}
	//effect
	for(int j = 6;j <= 7;++j)
		for(int i = 1;i <= 5;++i)
		{
			add_val[j][i] = i + 3;
			add_range[j][i] = 1 + add_range[j][i-1];
			add_val_p[j][i] = i + 3;
			add_range_p[j][i] = 1 + add_range_p[j][i-1];
		}
		
	//att
	add_val[8][1] = 33;
	add_range[8][1] = 610 ;
	add_val_p[8][1] = 31;
	add_range_p[8][1] = 371 ;
	for(int i = 2;i <= 13;++i)
	{
		add_val[8][i] = i + 32;
		add_range[8][i] = 735 + add_range[8][i-1];
		add_val_p[8][i] = i + 30;
		add_range_p[8][i] = 775 + add_range_p[8][i-1];
	}
	add_val[8][14] = 46;
	add_range[8][14] = 566 + add_range[8][13];
	add_val_p[8][14] = 44;
	add_range_p[8][14] = 333 + add_range_p[8][13];
	//def
	add_val[9][1] = 28;
	add_range[9][1] = 1426 ;
	add_val_p[9][1] = 26;
	add_range_p[9][1] = 614 ;
	for(int i = 2;i <= 7;++i)
	{
		add_val[9][i] = 27 + i;
		add_range[9][i] = 1426 + add_range[9][i-1];
		add_val_p[9][i] = i + 25;
		add_range_p[9][i] = 1499 + add_range_p[9][i-1];
	}
	add_val[9][8] = 35;
	add_range[9][8] = 14 + add_range[9][7];
	add_val_p[9][8] = 33;
	add_range_p[9][8] = 390 + add_range_p[9][7];
	printf("请输入你想生成的装备数量然后回车");
	int bg = 0;
	scanf("%d",&bg);
	for(int i = 0;i < 24;++i) scanf("%d",&gl[i]);
	for(;num <= bg;++num)
	{
		solve();
	}
	
	
//	printf("打造%d件装备一共花费了%lfw金币和%d个最低级强化石\n",bg,money,qiang);
//	printf("平均每件装备此策略需要花费%lfw金币和%lf个最低级强化石\n",
//	money*1.0/(double)bg,(double)qiang*1.0/bg);
//	for(int i = 90;i >= 1;i--) sum_fen[i] = sum_fen[i+1] + fen[i];
//	for(int i = 32;i >= 1;i--) sum_speed[i] = sum_speed[i+1] + speed[i];
//	printf("这%d件装备打造出了%d件54分以上的装备和%d件14速以上的装备",
//	bg,sum_fen[54],sum_speed[14]);
	money += 2.1 * bg;
	printf("打造%d件装备一共花费了%.0lfw金币和%.0lf个最低级强化石\n",bg,money,qiang);
	printf("平均10000材料此策略需要花费%lfw金币和%lf个最低级强化石\n",
	(money*1.0/(double)bg)*10000.0/42.0,
	((double)qiang*1.0/bg)*10000.0/42.0);
	for(int i = 90;i >= 1;i--) sum_fen[i] = sum_fen[i+1] + fen[i];
	for(int i = 90;i >= 1;i--) sum_fen_att[i] = sum_fen_att[i+1] + fen_att[i];
	for(int i = 32;i >= 1;i--) sum_speed[i] = sum_speed[i+1] + speed[i];
	printf("平均10000材料打造出了%.3lf件57分以上的装备和%.3lf件14速以上的装备\n",
	((double)sum_fen[57]/(double)bg)*10000.0/42.0,
	((double)sum_speed[14]/(double)bg)*10000.0/42.0);
	printf("平均10000材料打造出了%.3lf件53分以上的装备和%.3lf件10速以上的装备\n",
	((double)sum_fen[53]/(double)bg)*10000.0/42.0,
	((double)sum_speed[10]/(double)bg)*10000.0/42.0);
	printf("平均10000材料打造出了%.3lf件48输出分以上的装备\n",
	((double)sum_fen_att[48]/(double)bg)*10000.0/42.0);
	printf("平均10000材料产生了%.3lf个根源材料",
	(double)gen/(double)bg*10000.0/42.0);
	return 0;
}
