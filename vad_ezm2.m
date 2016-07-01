function [answer]=vad_ezm2(filename) %声音信息，framelength, step, 
    
    %fprintf(filename);
    wlen = 200;
	inc = 80;
	NIS = 30;
    [Y fs] = wavread(filename);
	
    %降噪??
    x = filter([1 -0.9375],1, Y);
	
    x=x(:);                                 % 把x转换成列数组
    maxsilence = 25;                        % 初始化
    %minlen  = 20;    
    status  = 0;
    count   = 0;
    silence = 0;
	silencelen = 18;

    y=enframe(x,hanning(wlen),inc)';                 % 分帧
    fn=size(y,2);                           % 帧数
    %amp=sum(y.^2);                          % 求取短时平均能量
    amp=sum(abs(y));                              % 使用平均幅度的绝对值
    zcr=zc2(y,fn);                          % 计算短时平均过零率

    ampth= min(mean(amp(1:NIS)), mean(amp(end-NIS:end)));                 % 计算初始无话段区间能量和过零率的平均值               
    zcrth= min(mean(zcr(1:NIS)), mean(zcr(end-NIS:end)));
    
    amp2=max(0.03 * max(amp(:)), 3*ampth); amp1=max(amp(:)) * 0.4;             % 设置能量和过零率的阈值
    zcr2=max(2*zcrth, max(zcr) * 0.05 );
	
	x1 = fn; x2 = 1;
	for n = 1:fn
		if amp(n) > amp1
			x1 = n;
			break;
		end
	end
	for n = fn:-1:1
		if amp(n) > amp1
			x2 = n;
			break;
		end
	end
	silence = 0;
	y1 = x1;
	for n = x1:-1:1
		if amp(n) > amp2
			y1 = n;
		else
			silence = silence + 1;
			if silence >= maxsilence
				break;
			end
		end
	end
	silence = 0;
	y2 = x2;
	for n = x2:fn
		if amp(n) > amp2
			y2 = n;
		else
			silence = silence + 1;
			if silence >= maxsilence
				break;
			end
		end
	end
	
	z1 = y1; z2 = y2;
	
	for n = y1 : -1 : 1
		if zcr(n) > zcr2
			z1 = n;
		else
			break
		end
	end
	
	for n = y2 : fn
		if zcr(n) > zcr2
			z2 = n;
		else
			break
		end
	end
	
	for n = z1 - silencelen :-1:1
		if zcr(n) > zcr2
			z1 = n;
		else
			break;
		end
	end
	for n = z2 + silencelen :fn
		if zcr(n) > zcr2
			z2 = n;
		else 
			break;
		end
	end
		
	
	
	
    el=1;
    SF=zeros(1,fn);                         % 按x1和x2，对SF和NF赋值
    NF=ones(1,fn);
	SF(z1:z2)=1;
    NF(z1:z2)=0;
	speechIndex=find(SF==1);                % 计算voiceseg
    voiceseg=findSegment(speechIndex);
    vsl=length(voiceseg);
    
	answer = Y(voiceseg.begin * 80 : voiceseg.end * 80);
    %{
	sound(x);
	pause(2);
	sound(answer);
	%pause(3);
    %%%%%%%plot%%%%%%%%
	
    figure
    subplot(3,1,1);       % add first plot in 2 x 1 grid
    plot(amp);
    hold on;
    plot(xlim, [1 1]*amp1, '-r');
    plot(xlim, [1 1]*amp2, '-b');
    plot([1 1] * x1, ylim, '-r');
    plot([1 1] * x2, ylim, '-r');
	plot([1 1] * y1, ylim, '-b');
    plot([1 1] * y2, ylim, '-b');
	plot([1 1] * z1, ylim, '-g');
    plot([1 1] * z2, ylim, '-g');
    hold off;
    title('Subplot amp');

    subplot(3,1,2);       % add second plot in 2 x 1 grid
    plot(zcr);       % plot using + markers
    hold on;
    plot(xlim, [1 1]*zcr2, '-g');
    plot([1 1] * x1, ylim, '-r');
    plot([1 1] * x2, ylim, '-r');
	plot([1 1] * y1, ylim, '-b');
    plot([1 1] * y2, ylim, '-b');
	plot([1 1] * z1, ylim, '-g');
    plot([1 1] * z2, ylim, '-g');
    hold off;
    title('Subplot zcr');
    
    subplot(3,1,3);
    plot(x);
    hold on;
    plot([1 1] * x1 * 80, ylim, '-r');
    plot([1 1] * x2 * 80, ylim, '-r');
	plot([1 1] * y1 * 80, ylim, '-b');
    plot([1 1] * y2 * 80, ylim, '-b');
	plot([1 1] * z1 * 80, ylim, '-g');
    plot([1 1] * z2 * 80, ylim, '-g');
    hold off;
    title('sound');
	%}
    
    %fprintf('amp2 = %d, amp1 = %d, zcr2 = %d\n', amp2, amp1, zcr2);
    %fprintf('No.%d: %s(%03.0fms)\n', index, filename, tmp.duration * 2000 / 198);

end

function zcr = zc2(y, fn)
    if size(y,2)~=fn, y = y'; end;
    wlen = size(y,1);
    zcr = zeros(1, fn);
    delta=0.01;                                % 设置一个很小的阈值
    for i=1:fn
        yn=y(:,i);                             % 取来一帧
        for k=1 : wlen                         % 中心截幅处理
            if yn(k)>=delta
                ym(k)=yn(k)-delta;
            elseif yn(k)<-delta
                ym(k)=yn(k)+delta;
            else
                ym(k)=0;
            end
        end
        zcr(i)=sum(ym(1:end-1).*ym(2:end)<0);  % 取得处理后的一帧数据寻找过零率
    end
end

function soundSegment=findSegment(express)
    if express(1)==0
        voicedIndex=find(express);                     % 寻找express中为1的位置
    else
        voicedIndex=express;
    end

    soundSegment = [];
    k = 1;
    soundSegment(k).begin = voicedIndex(1);            % 设置第一组有话段的起始位置
    for i=1:length(voicedIndex)-1,
    if voicedIndex(i+1)-voicedIndex(i)>1,          % 本组有话段结束
    soundSegment(k).end = voicedIndex(i);      % 设置本组有话段的结束位置
    soundSegment(k+1).begin = voicedIndex(i+1);% 设置下一组有话段的起始位置  
    k = k+1;
    end
    end
    soundSegment(k).end = voicedIndex(end);            % 最后一组有话段的结束位置
    % 计算每组有话段的长度
    for i=1 :k
        soundSegment(i).duration=soundSegment(i).end-soundSegment(i).begin+1;
    end
end

