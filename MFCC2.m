function [m dtm]=mfcc_m(x,fs,p,frameSize,inc,dctnum)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                 function ccc=mfcc_m(x);
%对输入的语音序列x进行MFCC参数的提取，返回MFCC参数和一阶
%差分MFCC参数，Mel滤波器的个数为p，采样频率为fs
%对x每frameSize点分为一帧，相邻两帧之间的帧移为inc
% fft变换的长度为帧长
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 
% 按帧长为frameSize，Mel滤波器的个数为p，采样频率为fs
% 提取Mel滤波器参数，用海明窗函数
bank=melbankm(p,frameSize,fs,0,0.5,'m');
% 归一化mel滤波器组系数
bank=full(bank);
bank=bank/max(bank(:));
 
% DCT系数,12*p
for k=1:dctnum
  n=0:p-1;
  dctcoef(k,:)=cos((2*n+1)*k*pi/(2*p));
end
 
% 归一化倒谱提升窗口
w = 1 + 6 * sin(pi * [1:dctnum] ./ dctnum);
w = w/max(w);
 
% 预加重滤波器
xx=double(x);
xx=filter([1 -0.9375],1,xx);
 
% 语音信号分帧
xx=enframe(xx,frameSize,inc);
n2=fix(frameSize/2)+1;
% 计算每帧的MFCC参数
for i=1:size(xx,1)
  y = xx(i,:);
  s = y' .* hamming(frameSize);
  t = abs(fft(s));
  t = t.^2;
  c1=dctcoef * log(bank * t(1:n2));
  c2 = c1.*w';
  m(i,:)=c2';
end
 
%差分系数
dtm = zeros(size(m));
for i=3:size(m,1)-2
  dtm(i,:) = -2*m(i-2,:) - m(i-1,:) + m(i+1,:) + 2*m(i+2,:);
end
dtm = dtm / 3;
%合并mfcc参数和一阶差分mfcc参数
m = m(3:size(m,1)-2,:);
dtm = dtm(3:size(dtm,1)-2,:);