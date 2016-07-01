now_id = 24;

%输出端点检测结果到00000000000文件夹
%{
for i = 1:20
    for j = 1:20
        path1 = filepath(now_id, i, j);
        answer = endpoint_detection(path1);
        path2 = filepath(now_id, i, j, 32);
        wavwrite(answer, path2);
    end;
end;
%}


%训练
dctnum = 16;
trainnum = 15;
sampleid = zeros(20);
sampledis = zeros(20);
mfccans = zeros(20, 20, 100, dctnum);
mfccanssize = zeros(20, 20);

for i=1:20
    ww = Words(i);
    ww = ww{1};
    fprintf('mfcc word %s\n', ww);
    for j=1:20
        [~, tmp] = MFCC(filepath(now_id, i, j, 32), dctnum);
        [mfccanssize(i, j), ~] = size(tmp);
        mfccans(i,j,1:mfccanssize(i, j), :) = tmp;
    end;
end;

for i = 1:20
    ww = Words(i);
    ww = ww{1};
    fprintf('doing word %s\n', ww);
    for j = 1:trainnum
        total = 0;
        for k = 1:trainnum
            %fprintf('%d %d %d %d %d\n', i, j, k, mfccanssize(i, j), mfccanssize(i, k));
            total = total + DTW(squeeze(mfccans(i, j, 1:mfccanssize(i, j),:)), squeeze(mfccans(i, k, 1:mfccanssize(i, k),:)));
        end;
        if total < sampledis(i) || sampleid(i) == 0
            sampleid(i) = j;
            sampledis(i) = total;
        end;
    end;
end;

for i = 1:20
    ww = Words(i);
    ww = ww{1};
    fprintf('%s: %d, %f\n', ww, sampleid(i), sampledis(i));
end;

totaltrue = 0;
%验证
for i=1:20
    for j=1 + trainnum:20
        judge = 0;
        nowmin = 99999;
        for k = 1:20
            tmp = DTW(squeeze(mfccans(i, j, 1:mfccanssize(i, j),:)), squeeze(mfccans(k, sampleid(k), 1:mfccanssize(k, sampleid(k)),:)));
            if nowmin > tmp
                nowmin = tmp;
                judge = k;
            end;
        end;
        %judge = randi([1 20],1,1);
        ww1 = Words(i);
        ww1 = ww1{1};
        ww2 = Words(judge);
        ww2 = ww2{1};
        fprintf('test word:%s, %d; judge:%s ', ww1, j, ww2);
        if i == judge
            fprintf('yes\n');
            totaltrue = totaltrue + 1;
        else
            fprintf('no\n');
        end;
    end;
end;

fprintf('totaltrue: %d', totaltrue);

%{
totaltrue = 0;

for i=1:20
    for j=16:20
        judge = 0;
        nowmin = 99999;
        for k = 1:20
            for l=1:15
                tmp = DTW(squeeze(mfccans(i, j, 1:mfccanssize(i, j),:)), squeeze(mfccans(k, l, 1:mfccanssize(k, l),:)));
                if nowmin > tmp
                    nowmin = tmp;
                    judge = k;
                end;
            end;
        end;
        ww1 = Words(i);
        ww1 = ww1{1};
        ww2 = Words(judge);
        ww2 = ww2{1};
        fprintf('test word:%s, %d; judge:%s ', ww1, j, ww2);
        if i == judge
            fprintf('yes\n');
            totaltrue = totaltrue + 1;
        else
            fprintf('no\n');
        end;
    end;
end;

fprintf('totaltrue: %d', totaltrue);
%}
