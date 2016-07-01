#include <bits/stdc++.h>
#include "Words.h"
#define DCTNUM 16
#define VQTABLE_NUM 64
#define DTWTABLE_NUM 16
#define DTW_MAXLENGTH 128

const std::string ID[] = {"11307120032","14307130153","14307130166","13307130227","14307130222",
                          "14307130092","14307130118","12307130178","13307130174","13307130299",
						  "13307130251","14307130167","13307130309","13300160096","13307130098",
						  "14307130110","13307130248","13307130290","14307130090","14307130244",
						  "14302010043","14307130088","13307130498","13307130230","13307130520",
						  "14307130270","14307130338","14307130345","14307130381","13307130444",
						  "14307130235"};
const int gooddata[][3] = {{0,18,3},{0,18,8},{0,18,16},{0,16,3},{0,16,12},
                         {0,16,20},{0,14,1},{0,14,8},{0,14,15},{0,15,2},
						 {0,15,9},{0,15,16},{0,17,13},{0,17,15},{0,17,19},
						 {0,13,3},{0,13,11},{0,13,16},{0,11,13},{0,11,15},
						 {0,11,17},{0,19,3},{0,19,5},{0,19,18},{0,20,4},
						 {0,20,10},{0,20,15},{0,12,1},{0,12,16},{0,12,20},
						 {0,8,5},{0,8,9},{0,8,15},{0,3,2},{0,3,8},
						 {0,3,14},{0,4,4},{0,4,11},{0,4,18},{0,6,3},
						 {0,6,10},{0,6,17},{0,9,2},{0,9,15},{0,9,19},
						 {0,10,5},{0,10,12},{0,10,19},{0,1,3},{0,1,13},
						 {0,1,19},{0,7,3},{0,7,14},{0,7,17},{0,5,1},
						 {0,5,10},{0,5,20},{0,2,1},{0,2,2},{0,2,17},
						 {7,18,3},{7,18,8},{7,18,16},{7,16,3},{7,16,12},
						 {7,16,20},{7,14,1},{7,14,8},{7,14,15},{7,15,2},
						 {7,15,9},{7,15,16},{7,17,13},{7,17,15},{7,17,19},
						 {7,13,3},{7,13,11},{7,13,16},{7,11,13},{7,11,17},
						 {7,19,3},{7,19,5},{7,19,18},{7,20,10},{7,12,1},
						 {7,12,16},{7,12,20},{7,8,5},{7,8,9},{7,8,15},
						 {7,3,8},{7,3,14},{7,4,4},{7,4,11},{7,4,18},
						 {7,6,3},{7,6,10},{7,9,2},{7,9,15},{7,9,19},
						 {7,10,5},{7,10,12},{7,10,19},{7,1,3},{7,1,13},
						 {7,1,19},{7,7,3},{7,7,14},{7,7,17},{7,5,1},
						 {7,5,10},{7,5,20},{7,2,1},{7,2,2},{7,2,17},
						 {8,18,3},{8,18,8},{8,18,16},{8,16,3},{8,16,12},
						 {8,16,20},{8,14,1},{8,14,8},{8,14,15},{8,15,2},
						 {8,15,9},{8,15,16},{8,17,13},{8,17,15},{8,17,19},
						 {8,13,3},{8,13,11},{8,13,16},{8,11,13},{8,11,15},
						 {8,11,17},{8,19,5},{8,19,18},{8,20,10},{8,20,15},
						 {8,12,1},{8,12,20},{8,8,5},{8,8,9},{8,3,2},
						 {8,3,8},{8,3,14},{8,4,4},{8,4,11},{8,4,18},
						 {8,6,3},{8,6,10},{8,6,17},{8,9,2},{8,9,15},
						 {8,9,19},{8,10,5},{8,10,12},{8,10,19},{8,1,3},
						 {8,1,13},{8,1,19},{8,7,14},{8,7,17},{8,5,1},
						 {8,5,10},{8,5,20},{8,2,1},{8,2,2},{8,2,17},
						 {11,18,8},{11,18,16},{11,16,3},{11,16,12},{11,16,20},
						 {11,14,1},{11,14,8},{11,14,15},{11,15,2},{11,15,9},
						 {11,15,16},{11,17,13},{11,17,15},{11,17,19},{11,11,13},
						 {11,11,15},{11,11,17},{11,12,1},{11,12,16},{11,12,20},
						 {11,8,9},{11,3,2},{11,3,8},{11,3,14},{11,4,4},
						 {11,4,11},{11,4,18},{11,6,3},{11,6,10},{11,6,17},
						 {11,9,2},{11,9,15},{11,9,19},{11,10,5},{11,10,12},
						 {11,10,19},{11,1,3},{11,1,13},{11,1,19},{11,7,14},
						 {11,5,1},{11,2,1},{11,2,2},{11,2,17},{10,18,8},
						 {10,18,16},{10,16,3},{10,16,12},{10,16,20},{10,14,1},
						 {10,14,8},{10,14,15},{10,15,2},{10,15,9},{10,15,16},
						 {10,17,13},{10,17,15},{10,17,19},{10,13,16},{10,11,13},
						 {10,11,15},{10,11,17},{10,19,3},{10,19,5},{10,20,4},
						 {10,20,10},{10,20,15},{10,12,1},{10,12,16},{10,12,20},
						 {10,8,5},{10,8,15},{10,3,2},{10,3,8},{10,3,14},
						 {10,4,4},{10,4,11},{10,4,18},{10,6,3},{10,6,10},
						 {10,9,2},{10,9,15},{10,9,19},{10,10,5},{10,10,12},
						 {10,10,19},{10,1,3},{10,1,13},{10,1,19},{10,7,3},
						 {10,7,14},{10,7,17},{10,5,1},{10,5,10},{10,5,20},
						 {10,2,1},{10,2,2},{10,2,17},{9,18,3},{9,16,3},
						 {9,16,12},{9,16,20},{9,14,1},{9,14,8},{9,14,15},
						 {9,15,2},{9,15,9},{9,15,16},{9,17,13},{9,17,15},
						 {9,17,19},{9,13,3},{9,13,16},{9,11,13},{9,11,15},
						 {9,11,17},{9,19,3},{9,19,5},{9,20,4},{9,20,10},
						 {9,20,15},{9,12,1},{9,12,16},{9,12,20},{9,8,5},
						 {9,8,9},{9,8,15},{9,3,2},{9,3,8},{9,3,14},
						 {9,4,4},{9,4,11},{9,4,18},{9,6,3},{9,6,10},
						 {9,6,17},{9,9,2},{9,9,15},{9,9,19},{9,10,5},
						 {9,10,12},{9,10,19},{9,1,3},{9,1,13},{9,1,19},
						 {9,7,3},{9,7,14},{9,7,17},{9,5,1},{9,5,10},
						 {9,2,1},{5,16,3},{5,16,12},{5,16,20},{5,14,1},
						 {5,14,8},{5,14,15},{5,15,2},{5,15,9},{5,15,16},
						 {5,17,13},{5,17,15},{5,17,19},{5,13,16},{5,11,13},
						 {5,11,15},{5,11,17},{5,19,3},{5,19,5},{5,19,18},
						 {5,12,1},{5,12,16},{5,12,20},{5,8,5},{5,8,9},
						 {5,8,15},{5,3,2},{5,3,8},{5,3,14},{5,4,4},
						 {5,4,11},{5,4,18},{5,6,3},{5,6,17},{5,9,2},
						 {5,9,15},{5,9,19},{5,10,5},{5,10,12},{5,10,19},
						 {5,1,3},{5,1,13},{5,1,19},{5,7,3},{5,7,14},
						 {5,7,17},{5,5,1},{5,5,20},{5,2,1},{5,2,2},
						 {5,2,17},{6,16,3},{6,16,12},{6,16,20},{6,14,1},
						 {6,14,8},{6,14,15},{6,15,2},{6,15,16},{6,17,13},
						 {6,17,15},{6,17,19},{6,13,3},{6,13,11},{6,13,16},
						 {6,11,13},{6,11,15},{6,11,17},{6,19,3},{6,19,5},
						 {6,19,18},{6,20,10},{6,20,15},{6,12,1},{6,12,16},
						 {6,12,20},{6,8,9},{6,8,15},{6,3,2},{6,3,8},
						 {6,3,14},{6,4,4},{6,4,11},{6,4,18},{6,6,3},
						 {6,6,10},{6,6,17},{6,9,2},{6,9,15},{6,9,19},
						 {6,10,5},{6,10,12},{6,10,19},{6,1,3},{6,1,13},
						 {6,1,19},{6,7,3},{6,7,14},{6,7,17},{6,5,1},
						 {6,5,10},{6,5,20},{6,2,2},{6,2,17},{1,18,8},
						 {1,18,16},{1,16,3},{1,16,12},{1,16,20},{1,14,1},
						 {1,14,8},{1,14,15},{1,15,2},{1,15,9},{1,15,16},
						 {1,17,13},{1,17,15},{1,17,19},{1,13,3},{1,13,11},
						 {1,11,13},{1,11,15},{1,11,17},{1,19,3},{1,19,5},
						 {1,19,18},{1,20,4},{1,20,10},{1,20,15},{1,12,1},
						 {1,12,20},{1,8,5},{1,8,9},{1,8,15},{1,3,2},
						 {1,3,8},{1,3,14},{1,4,4},{1,4,11},{1,4,18},
						 {1,6,3},{1,6,10},{1,6,17},{1,9,2},{1,9,15},
						 {1,9,19},{1,10,5},{1,10,12},{1,10,19},{1,1,3},
						 {1,1,13},{1,7,3},{1,7,14},{1,7,17},{1,5,1},
						 {1,5,10},{1,5,20},{1,2,1},{1,2,2},{1,2,17},
						 {2,18,3},{2,18,8},{2,18,16},{2,16,3},{2,16,12},
						 {2,16,20},{2,14,1},{2,14,8},{2,14,15},{2,15,2},
						 {2,15,9},{2,15,16},{2,17,13},{2,17,15},{2,17,19},
						 {2,13,3},{2,13,16},{2,11,13},{2,11,15},{2,11,17},
						 {2,19,3},{2,20,15},{2,12,1},{2,12,16},{2,12,20},
						 {2,8,5},{2,8,9},{2,8,15},{2,3,2},{2,3,8},
						 {2,3,14},{2,4,4},{2,4,11},{2,4,18},{2,6,3},
						 {2,6,10},{2,6,17},{2,9,2},{2,9,15},{2,9,19},
						 {2,10,5},{2,10,12},{2,10,19},{2,1,3},{2,1,13},
						 {2,1,19},{2,7,3},{2,7,14},{2,7,17},{2,5,1},
						 {2,5,10},{2,5,20},{2,2,1},{2,2,2},{2,2,17},
						 {3,18,1},{3,18,2},{3,18,3},{3,18,4},{3,18,5},
						 {3,18,6},{3,18,7},{3,18,8},{3,18,10},{3,18,11},
						 {3,18,12},{3,18,13},{3,18,16},{3,16,3},{3,16,12},
						 {3,14,1},{3,14,8},{3,14,15},{3,15,2},{3,15,9},
						 {3,15,16},{3,17,13},{3,17,19},{3,13,1},{3,13,2},
						 {3,13,3},{3,13,4},{3,13,5},{3,13,6},{3,13,7},
						 {3,13,8},{3,13,9},{3,13,11},{3,13,15},{3,13,16},
						 {3,13,17},{3,13,18},{3,13,19},{3,13,20},{3,11,13},
						 {3,11,15},{3,11,17},{3,19,1},{3,19,2},{3,19,3},
						 {3,19,5},{3,19,6},{3,19,8},{3,19,10},{3,19,11},
						 {3,20,4},{3,20,5},{3,20,6},{3,20,7},{3,20,10},
						 {3,20,11},{3,20,12},{3,20,13},{3,20,14},{3,20,15},
						 {3,20,16},{3,20,17},{3,20,18},{3,12,1},{3,12,16},
						 {3,12,20},{3,8,5},{3,8,9},{3,8,15},{3,3,2},
						 {3,3,8},{3,3,14},{3,4,4},{3,4,11},{3,4,18},
						 {3,6,3},{3,6,10},{3,6,17},{3,9,15},{3,9,19},
						 {3,10,5},{3,10,12},{3,10,19},{3,1,3},{3,1,13},
						 {3,1,19},{3,7,3},{3,7,14},{3,7,17},{3,5,1},
						 {3,5,10},{3,2,1},{3,2,2},{3,2,17},{4,18,3},
						 {4,18,8},{4,18,16},{4,16,3},{4,16,12},{4,16,20},
						 {4,14,1},{4,14,8},{4,14,15},{4,15,2},{4,15,9},
						 {4,15,16},{4,17,13},{4,17,15},{4,17,19},{4,13,3},
						 {4,13,16},{4,11,13},{4,11,15},{4,11,17},{4,19,3},
						 {4,19,5},{4,20,4},{4,20,10},{4,20,15},{4,12,1},
						 {4,12,16},{4,12,20},{4,8,5},{4,8,9},{4,8,15},
						 {4,3,2},{4,3,8},{4,3,14},{4,4,4},{4,4,11},
						 {4,4,18},{4,6,3},{4,6,10},{4,6,17},{4,9,2},
						 {4,9,15},{4,9,19},{4,10,5},{4,10,12},{4,10,19},
						 {4,1,3},{4,1,13},{4,1,19},{4,7,3},{4,7,14},
						 {4,7,17},{4,5,1},{4,5,10},{4,5,20},{4,2,1},
						 {4,2,2},{4,2,17}};
const int IDNum = 31 - 9;
const int GoodIDNum = 12;
const int GoodDataNum = 687;

const char VQoutputfile[] = "VQoutput.txt";
const char DTWoutputfile[] = "DTWoutput.txt";

struct vec{
	double num[DCTNUM];
	vec(){
		memset(num, 0, sizeof num);
	}
	double & operator[] (int k){
		return num[k];
	}
	vec operator+ (vec k){
		vec re;
		for (int i = 0; i < DCTNUM; i ++ )
			re.num[i] = num[i] + k.num[i];
		return re;
	}
	vec operator+= (vec k){
		for (int i = 0; i < DCTNUM; i ++ )
			num[i] += k.num[i];
		return *this;
	}
	vec operator- (vec k){
		vec re;
		for (int i = 0; i < DCTNUM; i ++ )
			re.num[i] = num[i] - k.num[i];
		return re;
	}
	vec operator/= (double k){
		for (int i = 0; i < DCTNUM; i ++ )
			num[i] /= k;
		return *this;
	}
	vec operator/ (double k){
		vec re = *this;
		for (int i = 0; i < DCTNUM; i ++ )
			re.num[i] /= k;
		return re;
	}
	vec operator* (double k){
		vec re = *this;
		for (int i = 0; i < DCTNUM; i ++ )
			re.num[i] *= k;
		return re;
	}
	double abs2(){
		double re = 0;
		for (int i = 0; i < DCTNUM; i ++ )
			re += num[i] * num[i];
		return re;
	}
};

std::vector<vec> data[IDNum][22][22];
bool validdata[IDNum][22][22];






double dtw_d[222][222];
double dtw_fa[222][222][2];
double DTW(std::vector<vec> &a, std::vector<vec> &b, std::vector<vec> &avgvec, double aa, double bb){
	const int MAXX = 99999;
    int n = a.size();
    int m = b.size();
    avgvec.clear();
    /*if (n > m){
    	n ^= m ^= n ^= m;
        std::vector<vec> tmp = a;
        a = b;
        b = tmp;
	}*/
    if (n == 0) return MAXX;
    for (int i = 0; i <= n; i ++ )
    	for (int j = 0; j <= m; j ++ )
    		dtw_d[i][j] = MAXX;
    dtw_d[0][0] = 0;
    int www = 5;
    www = www > m - n ? www : m - n;
    for (int i = 1; i <= n; i ++ ){
    	int ii = i * m / n;
        for (int j = std::max(ii - www, 1); j <= std::min(ii + www, m); j ++ ){
            double tdis = (a[i - 1] - b[j - 1]).abs2();
            /*
            double tmp = std::min(dtw_d[i - 1][j - 1] + tdis * 2, std::min(dtw_d[i - 1][j] + tdis, dtw_d[i][j - 1] + tdis));
            if (dtw_d[i][j] > tmp)
            	dtw_d[i][j] = tmp;
            */
            if (dtw_d[i][j] > dtw_d[i - 1][j - 1] + tdis * 2){
            	dtw_d[i][j] = dtw_d[i - 1][j - 1] + tdis * 2;
            	dtw_fa[i][j][0] = i - 1;
            	dtw_fa[i][j][1] = j - 1;
            }
            if (dtw_d[i][j] > dtw_d[i - 1][j] + tdis){
            	dtw_d[i][j] = dtw_d[i - 1][j] + tdis;
            	dtw_fa[i][j][0] = i - 1;
            	dtw_fa[i][j][1] = j;
            }
            if (dtw_d[i][j] > dtw_d[i][j - 1] + tdis){
            	dtw_d[i][j] = dtw_d[i][j - 1] + tdis;
            	dtw_fa[i][j][0] = i;
            	dtw_fa[i][j][1] = j - 1;
            }
            
    	}
    }
    
    /*for (int i = 0; i <= n; i ++ ){
    	for (int j = 0; j <= m; j ++ )
    		printf("[%d %d %.4lf]", i, j, d[i][j]);
    	printf("\n");
	}*/
	
	for (int i = n, j = m; i && j; ){
		avgvec.push_back((a[i - 1] * aa + b[j - 1] * bb) / (aa + bb));
		int ii = dtw_fa[i][j][0], jj = dtw_fa[i][j][1];
		i = ii;
		j = jj;
	}
	std::reverse(avgvec.begin(), avgvec.end());
    
    return dtw_d[n][m] / (n + m);
}

double DTW(std::vector<vec> &a, std::vector<vec> &b){
	std::vector<vec> avgvec;
	double aa = 1, bb = 1;
	return DTW(a, b, avgvec, aa, bb);
}

void DTW_shorten(std::vector<vec> &input){
	std::vector<vec> res;
	for (int i = 0; i < input.size(); i += 2)
		if (i + 1 < input.size()) res.push_back((input[i] + input[i + 1]) / 2);
		else res.push_back(input[i]);
	input = res;
}


void one_sample(int trainnum){
	for (int id = 0; id < IDNum; id ++ ){
		int sample[22];
		double sampledis[22];
		for (int i = 1; i <= 20; i ++ ){
			sampledis[i] = 99999;
			for (int j = 1; j <= trainnum; j ++ ){
				if (!validdata[id][i][j]) continue;
				double tdis = 0;
				for (int k = 1; k <= trainnum; k ++ )
					if (validdata[id][i][k]) tdis += DTW(data[id][i][j], data[id][i][k]);
				if (tdis < sampledis[i]){
					sample[i] = j;
					sampledis[i] = tdis;
				}
			}
		}
		int correct = 0, total = 0;
		for (int i = 1; i <= 20; i ++ )
			for (int j = 1 + trainnum; j <= 20; j ++ ){
				if (!validdata[id][i][j]) continue;
				int judge = 0;
				double mindis = 99999;
				for (int k = 1; k <= 20; k ++ ){
					double tmp = DTW(data[(id + 1) % IDNum][i][j], data[id][k][sample[k]]);
					if (tmp < mindis){
						mindis = tmp;
						judge = k;
					}
				}
				if (judge == i) correct ++ ;
				total ++ ;
				//printf("%d %d: %d\n", i, j, judge);
			}
		printf("%s: %d/%d\n", ID[id].c_str(), correct, total);
	}
}

const int VQrand_times = 2;
const int VQrepeat_times = 200;
double VQ_KMeans_dis[50000][200];
std::vector<vec> VQ_KMeans(std::vector<vec> &input, int num, double &mindis){
	mindis = 1e100;
	std::vector<vec> res, now;
	for (int RNDTMS = VQrand_times; RNDTMS -- ; ){
		double nowmindis = 1e100;
		random_shuffle(input.begin(), input.end());
		now.clear();
		for (int i = 0; i < num; i ++ )
			now.push_back(input[i]);
		for (int REPTMS = VQrepeat_times; REPTMS -- ; ){
			for (int i = 0; i < input.size(); i ++ )
				for (int j = 0; j < num; j ++ )
					VQ_KMeans_dis[i][j] = (input[i] - now[j]).abs2();
			std::vector<vec> old = now;
			for (int j = 0; j < num; j ++ )
				memset(now[j].num, 0, sizeof now[j].num);
			int bucket[num];
			memset(bucket, 0, sizeof(int) * num);
			double nowmintot = 0;
			for (int i = 0; i < input.size(); i ++ ){
				int related = 0;
				double nowmin = 1e100;
				for (int j = 0; j < num; j ++ )
					if (VQ_KMeans_dis[i][j] < nowmin){
						nowmin = VQ_KMeans_dis[i][j];
						related = j;
					}
				now[related] += input[i];
				bucket[related] ++ ;
				//nowmintot += nowmin;
				if (nowmintot < nowmin) nowmintot = nowmin;
			}
			double change = 0;
			for (int i = 0; i < num; i ++ ){
				if (!bucket[i]){
					mindis = 1e100;
					return res;
				}
				now[i] /= bucket[i];
				change += (old[i] - now[i]).abs2();
			}
			//printf("%d time, change: %f, nowmindis: %f, nowmintot: %f\n",repeat_times - REPTMS, change, nowmindis, nowmintot);
			//getchar();
			nowmindis = nowmintot;
			if (nowmindis < mindis){
				mindis = nowmindis;
				res = now;
			}
			if (change < 1e-100) break;
		}
		printf("VQ_KMeans, %d time, mindis: %f\n", VQrand_times - RNDTMS, mindis);
	}
	return res;
}

std::vector<vec> VQTable[22];
double VQTable_dis[22];
void make_VQTable(){
	int num = VQTABLE_NUM;
	for (int i = 1; i <= 20; i ++ ){
		std::vector<vec> input;
		
		for (int id = 0; id < GoodIDNum; id ++ )
			for (int j = 1; j <= 20; j ++ )
				for (int k = 0; k < data[id][i][j].size(); k ++ )
					input.push_back(data[id][i][j][k]);
		
		/*
		for (int p = 0; p < GoodDataNum; p ++ )
			if (gooddata[p][1] == i){
				int id = gooddata[p][0], j = gooddata[p][2];
				for (int k = 0; k < data[id][i][j].size(); k ++ )
					input.push_back(data[id][i][j][k]);
			}
		*/
		double mindis = 1e100;
		std::vector<vec> tvec = VQ_KMeans(input, num, mindis);
		if (mindis < VQTable_dis[i]){
			VQTable[i] = tvec;
			VQTable_dis[i] = mindis;
		}
		printf("%d VQTable min dis: %lf\n", i, VQTable_dis[i]);
	}
	FILE *output = fopen(VQoutputfile, "w");
	for (int i = 1; i <= 20; i ++ ){
		fprintf(output, "%.15f\n", VQTable_dis[i]);
		for (int j = 0; j < num; j ++ ){
			for (int k = 0; k < DCTNUM; k ++ )
				fprintf(output, "%.15f ", VQTable[i][j][k]);
			fprintf(output, "\n");
		}
	}
	fclose(output);
	printf("write all VQTable success\n");
}

inline void VQTable_calc(std::vector<vec> &input, double *answer){
	
	for (int k = 1; k <= 20; k ++ ){
		double nowtot = 0;
		for (int l = 0; l < input.size(); l ++ ){
			double onedis = 1e100;
			for (int q = 0; q < VQTABLE_NUM; q ++ ){
				double tmp = (VQTable[k][q] - input[l]).abs2();
				if (tmp < onedis) onedis = tmp;
			}
			nowtot += onedis;
		}
		answer[k] = nowtot;
	}
	/*
	for (int k = 1; k <= 20; k ++ )
		answer[k] = 0;
	for (int l = 0; l < input.size(); l ++ ){
		double min = 1e100;
		int judge = 0;
		for (int k = 1; k <= 20; k ++ )
			for (int q = 0; q < VQTABLE_NUM; q ++ ){
				double tmp = (VQTable[k][q] - input[l]).abs2();
				if (tmp < min){
					min = tmp;
					judge = k;
				}
			}
		answer[judge] += 1;
	}
	*/
}


void VQTable_allcheck(){
	int ttotal = 0, tcorrect = 0, tsecond = 0, tthird = 0, dead = 0;
	for (int id = GoodIDNum; id < IDNum; id ++ ){
		int total = 0, correct = 0, second = 0, third = 0;
		int trainnum2 = 0;
		for (int i = 1; i <= 20; i ++ )
			for (int j = 1 + trainnum2; j <= 20; j ++ ){
				if (!validdata[id][i][j]) continue;
				double mindis = 1e100;
				double diss[22];
				VQTable_calc(data[id][i][j], diss);
				int less = 0;
				for (int ii = 1; ii <= 20; ii ++ ){
					if (diss[ii] < diss[i]) less ++ ;
					if (diss[ii] < mindis) mindis = diss[ii];
				}
				if (!less) correct ++ ;
				if (less == 1) second ++ ;
				if (less == 2) third ++ ;
				if (less != 0 && mindis / diss[i] < 0.8){
					//printf("%f/%f = %f\n", mindis, diss[i], mindis / diss[i]);
					dead ++ ;
				}
				total ++ ;
			}
		printf("%s: %d/%d %d/%d %d/%d\n", ID[id].c_str(), correct, total, second, total - correct, third, total - correct - second);
		printf("------------------------------------\n");
		ttotal += total;
		tcorrect += correct;
		tsecond += second;
		tthird += third;
	}
	printf("total: %d/%d %d/%d %d/%d dead: %d/%d\n", tcorrect, ttotal, tsecond, ttotal, tthird, ttotal, dead, ttotal);
}

const int DTWrand_times = 2;
const int DTWrepeat_times = 15;
double DTW_KMeans_dis[1000][100];
void DTW_KMeans(std::vector<std::vector<vec>> &input, std::vector<vec> *res, int num, double &mindis){
	mindis = 1e100;
	std::vector<vec> now[num];
	for (int RNDTMS = DTWrand_times; RNDTMS -- ; ){
		double nowmindis = 1e100;
		random_shuffle(input.begin(), input.end());
		for (int i = 0; i < num; i ++ )
			now[i] = input[i];
		for (int REPTMS = DTWrepeat_times; REPTMS -- ; ){
			for (int i = 0; i < input.size(); i ++ )
				for (int j = 0; j < num; j ++ )
					DTW_KMeans_dis[i][j] = DTW(input[i], now[j]);
			std::vector<vec> old[num];
			for (int i = 0; i < num; i ++ )
				old[i] = now[i];
			for (int j = 0; j < num; j ++ )
				now[j].clear();
			int bucket[num];
			memset(bucket, 0, sizeof(int) * num);
			double nowmintot = 0;
			for (int i = 0; i < input.size(); i ++ ){
				int related = 0;
				double nowmin = 1e100;
				for (int j = 0; j < num; j ++ )
					if (DTW_KMeans_dis[i][j] < nowmin){
						nowmin = DTW_KMeans_dis[i][j];
						related = j;
					}
				if (!bucket[related])
					now[related] = input[i];
				else{
					std::vector<vec> avg;
					DTW(now[related], input[i], avg, bucket[related], 1);
					if (avg.size() > DTW_MAXLENGTH) DTW_shorten(avg);
					now[related] = avg;
				}
				bucket[related] ++ ;
				//nowmintot += nowmin;
				if (nowmintot < nowmin) nowmintot = nowmin;
			}
			double change = 0;
			for (int i = 0; i < num; i ++ ){
				if (!bucket[i]){
					mindis = 1e100;
					return;
				}
				change += DTW(old[i], now[i]);
			}
			printf("%d time, change: %f, nowmindis: %f, nowmintot: %f\n", DTWrepeat_times - REPTMS, change, nowmindis, nowmintot);
			//getchar();
			nowmindis = nowmintot;
			if (nowmindis < mindis){
				mindis = nowmindis;
				for (int i = 0; i < num; i ++ )
					res[i] = now[i];
			}
			if (change < 1e-100) break;
		}
		printf("DTW_KMeans, %d time, mindis: %f\n", DTWrand_times - RNDTMS, mindis);
	}
}

std::vector<std::vector<vec>> DTWTableinput;
std::vector<vec> DTWTable[22][DTWTABLE_NUM], ttable[DTWTABLE_NUM];
double DTWTable_dis[22];
void make_DTWTable(){
	for (int i = 1; i <= 20; i ++ ){
		DTWTableinput.clear();
		for (int id = 0; id < GoodIDNum; id ++ )
			for (int j = 1; j <= 20; j ++ )
				if (validdata[id][i][j]) DTWTableinput.push_back(data[id][i][j]);
		double mindis = 1e100;
		DTW_KMeans(DTWTableinput, ttable, DTWTABLE_NUM, mindis);
		if (mindis < DTWTable_dis[i]){
			DTWTable_dis[i] = mindis;
			for (int q = 0; q < DTWTABLE_NUM; q ++ )
				DTWTable[i][q] = ttable[q];
		}
		printf("%d DTWTable min dis: %lf\n", i, DTWTable_dis[i]);
	}
	FILE *output = fopen(DTWoutputfile, "w");
	for (int i = 1; i <= 20; i ++ ){
		fprintf(output, "%.15f\n", DTWTable_dis[i]);
		for (int j = 0; j < DTWTABLE_NUM; j ++ ){
			fprintf(output, "%d\n", DTWTable[i][j].size());
			for (int k = 0; k < DTWTable[i][j].size(); k ++ ){
				for (int l = 0; l < DCTNUM; l ++ )
					fprintf(output, "%.15f ", DTWTable[i][j][k][l]);
				fprintf(output, "\n");
			}
		}
	}
	fclose(output);
	printf("write all DTWTable success\n");
}

void DTWTable_calc(std::vector<vec> input, double* answer){
	for (int i = 1; i <= 20; i ++ ){
		answer[i] = 1e100;
		for (int j = 0; j < DTWTABLE_NUM; j ++ ){
			double tmp = DTW(input, DTWTable[i][j]);
			if (tmp < answer[i]) answer[i] = tmp;
		}
	}
}

void DTWTable_allcheck(){
	int ttotal = 0, tcorrect = 0, tsecond = 0, tthird = 0, dead = 0;
	for (int id = GoodIDNum; id < IDNum; id ++ ){
		int total = 0, correct = 0, second = 0, third = 0;
		for (int i = 1; i <= 20; i ++ )
			for (int j = 1; j <= 20; j ++ ){
				if (!validdata[id][i][j]) continue;
				double mindis = 1e100;
				double diss[22];
				DTWTable_calc(data[id][i][j], diss);
				int less = 0;
				for (int ii = 1; ii <= 20; ii ++ ){
					if (diss[ii] < diss[i]) less ++ ;
					if (diss[ii] < mindis) mindis = diss[ii];
				}
				if (!less) correct ++ ;
				if (less == 1) second ++ ;
				if (less == 2) third ++ ;
				if (less != 0 && mindis / diss[i] < 0.8){
					//printf("%f/%f = %f\n", mindis, diss[i], mindis / diss[i]);
					dead ++ ;
				}
				total ++ ;
			}
		printf("%s: %d/%d %d/%d %d/%d\n", ID[id].c_str(), correct, total, second, total - correct, third, total - correct - second);
		printf("------------------------------------\n");
		ttotal += total;
		tcorrect += correct;
		tsecond += second;
		tthird += third;
	}
	printf("total: %d/%d %d/%d %d/%d dead: %d/%d\n", tcorrect, ttotal, tsecond, ttotal, tthird, ttotal, dead, ttotal);
}

void backup_DTWresult(){
	FILE *output = fopen(DTWoutputfile, "r");
	FILE *backup = fopen((std::string(DTWoutputfile) + ".bak").c_str(), "w");
	for (char ch; (ch = fgetc(output)) != EOF; fputc(ch, backup));
	fclose(output);
	fclose(backup);
}

void backup_VQresult(){
	FILE *output = fopen(VQoutputfile, "r");
	FILE *backup = fopen((std::string(VQoutputfile) + ".bak").c_str(), "w");
	for (char ch; (ch = fgetc(output)) != EOF; fputc(ch, backup));
	fclose(output);
	fclose(backup);
}

void DTW_read(){
	for (int i = 1; i <= 20; i ++ )
		DTWTable_dis[i] = 1e100;
	FILE *output = fopen(DTWoutputfile, "r");
	for (int i = 1; i <= 20; i ++ ){
		if (!~fscanf(output, "%lf", &DTWTable_dis[i])) break;
		for (int j = 0; j < DTWTABLE_NUM; j ++ ){
			int ss;
			if (!~fscanf(output, "%d", &ss)){
				DTWTable_dis[i] = 1e100;
				goto DTWReadEnd;
			}
			DTWTable[i][j].clear();
			for (int k = 0; k < ss; k ++ ){
				vec vv;
				for (int l = 0; l < DCTNUM; l ++ )
					if (!~fscanf(output, "%lf", &vv[l])){
						DTWTable_dis[i] = 1e100;
						goto DTWReadEnd;
					}
				DTWTable[i][j].push_back(vv);
			}
		}
		//printf("read %d DTWTable data success!\n", i);
	}
	DTWReadEnd:;
	fclose(output);
	backup_DTWresult();
}

void VQ_read(){
	for (int i = 1; i <= 20; i ++ )
		VQTable_dis[i] = 1e100;
	FILE *output = fopen(VQoutputfile, "r");
	for (int i = 1; i <= 20; i ++ ){
		if (!~fscanf(output, "%lf", &VQTable_dis[i])) break;
		VQTable[i].resize(VQTABLE_NUM);
		for (int j = 0; j < VQTABLE_NUM; j ++ ){
			for (int k = 0; k < DCTNUM; k ++ )
				if (!~fscanf(output, "%lf", &VQTable[i][j][k])){
					VQTable_dis[i] = 1e100;
					goto VQReadEnd;
				}
		}
		//printf("read %d VQTable data success!\n", i);
	}
	VQReadEnd:;
	fclose(output);
	backup_VQresult();
}

void read_it(){
	srand(unsigned(time(NULL)));
	rand();
	for (int i = 0; i < IDNum; i ++ ){
		FILE *file = fopen(("00000000000/" + ID[i] + ".txt").c_str(), "r");
		printf("start read %s\n", ID[i].c_str());
		int p1, p2, n, m, cnt = 0;
		while (~fscanf(file, "%d%d%d%d", &p1, &p2, &n, &m)){
			if (n == 0 || m != DCTNUM) continue;
			validdata[i][p1][p2] = 1;
			cnt ++ ;
			//printf("%d %d %d %d\n", p1, p2, n, m);
			for (int ii = 0; ii < n; ii ++ ){
				vec tv;
				for (int j = 0; j < m; j ++ )
					fscanf(file, "%lf", &tv.num[j]);
				data[i][p1][p2].push_back(tv);
			}
			p1 = p2 = n = m = 0;
		}
		printf("%s: %d\n", ID[i].c_str(), cnt);
	}
	VQ_read();
	DTW_read();
}


void allcheck_twoway(){
	int ttotal = 0, tcorrect = 0, tsecond = 0, tthird = 0, dead = 0;
	for (int id = GoodIDNum; id < IDNum; id ++ ){
		int total = 0, correct = 0, second = 0, third = 0;
		for (int i = 1; i <= 20; i ++ )
			for (int j = 1; j <= 20; j ++ ){
				//if (j == 1) printf("doing %d word\n", i);
				if (!validdata[id][i][j]) continue;
				double mindis = 1e100;
				double diss1[22], diss2[22];
				int rank1[22], rank2[22];
				VQTable_calc(data[id][i][j], diss1);
				DTWTable_calc(data[id][i][j], diss2);
				
				diss1[0] = diss2[0] = 1e100;
				for (int k = 1; k <= 20; k ++ ){
					if (diss1[0] > diss1[k]) diss1[0] = diss1[k];
					if (diss2[0] > diss2[k]) diss2[0] = diss2[k];
					rank1[k] = rank2[k] = 1;
				}
				for (int k = 1; k <= 20; k ++ ){
					diss1[k] /= diss1[0];
					diss2[k] /= diss2[0];
				}
				for (int q1 = 1; q1 <= 20; q1 ++ )
					for (int q2 = 1; q2 <= 20; q2 ++ ){
						if (diss1[q1] < diss1[q2]) rank1[q2] ++ ;
						if (diss2[q1] < diss2[q2]) rank2[q2] ++ ;
					}
				
				for (int k = 1; k <= 20; k ++ )
					diss1[k] = (rank1[k] + rank2[k]) * 0 + diss1[k] + diss2[k];
				int less = 0;
				for (int ii = 1; ii <= 20; ii ++ ){
					if (diss1[ii] < diss1[i]) less ++ ;
					if (diss1[ii] < mindis) mindis = diss1[ii];
				}
				if (!less) correct ++ ;
				if (less == 1) second ++ ;
				if (less == 2) third ++ ;
				if (less != 0 && mindis / diss1[i] < 0.8){
					//printf("%f/%f = %f\n", mindis, diss[i], mindis / diss[i]);
					dead ++ ;
				}
				total ++ ;
			}
		printf("%s: %d/%d %d/%d %d/%d\n", ID[id].c_str(), correct, total, second, total - correct, third, total - correct - second);
		printf("------------------------------------\n");
		ttotal += total;
		tcorrect += correct;
		tsecond += second;
		tthird += third;
	}
	printf("total: %d/%d %d/%d %d/%d dead: %d/%d\n", tcorrect, ttotal, tsecond, ttotal, tthird, ttotal, dead, ttotal);
}


int main(){
	/*
	//data transform use
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	
	for (; ; ){
		std::string s = "";
		std::cin >> s;
		if (s == "") break;
		for (int i = 0; i < IDNum; i ++ )
			if (s == ID[i]) std::cout << i << " ";
		int n, m;
		std::cin >> n >> m;
		std::cout << n << " " << m << std::endl;
	}
	*/
	
	//read datas
	//read_it();
	//printf("%d\n", clock());
	
	
	//choose one sample by DTW and check
	//int trainnum = 15;
	//one_sample(trainnum);
	
	
	//freopen("a.txt","w",stdout);
	
	/* 
	//train VQTable
	while (1){
		backup_VQresult();
		make_VQTable();
	}
	*/ 
	
	//check all input by VQTable
	//VQTable_allcheck();
	
	
	
	/*
	//train DTWTable
	while (1){
		backup_DTWresult();
		make_DTWTable();
	}
	*/
	
	//check all input by DTWTable
	//DTWTable_allcheck();
	
	/*
	//test STW and DTW_shorten
	for (int i = 1; i < 20; i ++ ){
		std::vector<vec> avg;
		printf("%lf\n", DTW(data[i][i][i], data[i + 1][i + 1][i + 1], avg, 1, 1));
		printf("%lf %lf\n", DTW(data[i][i][i], avg), DTW(data[i + 1][i + 1][i + 1], avg));
		DTW_shorten(avg);
		printf("%lf %lf\n-------------------\n", DTW(data[i][i][i], avg), DTW(data[i + 1][i + 1][i + 1], avg));
	}
	*/
	
	//check all input by VQTable and DTWTable
	//allcheck_twoway(); 
	
	
	//read data and calc
	printf("start checking...");
	VQ_read();
	DTW_read();
	freopen("testdata.txt","r",stdin);
	int n, m;
	scanf("%d%d", &n, &m);//printf("%d %d\n", n,m);
	std::vector<vec> input;
	for (int i = 0; i < n; i ++ ){
		vec now;
		for (int j = 0; j < m; j ++ )
			scanf("%lf", &now[j]);
		input.push_back(now);
	}
	double mindis = 1e100;
	double diss1[22], diss2[22];
	int rank1[22], rank2[22];
	VQTable_calc(input, diss1);
	DTWTable_calc(input, diss2);
	
	diss1[0] = diss2[0] = 1e100;
	for (int k = 1; k <= 20; k ++ ){
		if (diss1[0] > diss1[k]) diss1[0] = diss1[k];
		if (diss2[0] > diss2[k]) diss2[0] = diss2[k];
		rank1[k] = rank2[k] = 1;
	}
	for (int k = 1; k <= 20; k ++ ){
		diss1[k] /= diss1[0];
		diss2[k] /= diss2[0];
	}
	for (int q1 = 1; q1 <= 20; q1 ++ )
		for (int q2 = 1; q2 <= 20; q2 ++ ){
			if (diss1[q1] < diss1[q2]) rank1[q2] ++ ;
			if (diss2[q1] < diss2[q2]) rank2[q2] ++ ;
		}
	
	for (int k = 1; k <= 20; k ++ )
		diss1[k] = (rank1[k] + rank2[k]) * 0 + diss1[k] + diss2[k] * 0;
	int judge = 0;
	double min = 1e100;
	for (int k = 1; k <= 20; k ++ )
		if (min > diss1[k]){
			min = diss1[k];
			judge = k;
		}
	printf("answer: %s\n", Words[judge - 1].c_str());
	
}
