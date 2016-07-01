function [answer]=vad_ezm2(filename) %������Ϣ��framelength, step, 
    
    %fprintf(filename);
    wlen = 200;
	inc = 80;
	NIS = 30;
    [Y fs] = wavread(filename);
	
    %����??
    x = filter([1 -0.9375],1, Y);
	
    x=x(:);                                 % ��xת����������
    maxsilence = 25;                        % ��ʼ��
    %minlen  = 20;    
    status  = 0;
    count   = 0;
    silence = 0;
	silencelen = 18;

    y=enframe(x,hanning(wlen),inc)';                 % ��֡
    fn=size(y,2);                           % ֡��
    %amp=sum(y.^2);                          % ��ȡ��ʱƽ������
    amp=sum(abs(y));                              % ʹ��ƽ�����ȵľ���ֵ
    zcr=zc2(y,fn);                          % �����ʱƽ��������

    ampth= min(mean(amp(1:NIS)), mean(amp(end-NIS:end)));                 % �����ʼ�޻������������͹����ʵ�ƽ��ֵ               
    zcrth= min(mean(zcr(1:NIS)), mean(zcr(end-NIS:end)));
    
    amp2=max(0.03 * max(amp(:)), 3*ampth); amp1=max(amp(:)) * 0.4;             % ���������͹����ʵ���ֵ
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
    SF=zeros(1,fn);                         % ��x1��x2����SF��NF��ֵ
    NF=ones(1,fn);
	SF(z1:z2)=1;
    NF(z1:z2)=0;
	speechIndex=find(SF==1);                % ����voiceseg
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
    delta=0.01;                                % ����һ����С����ֵ
    for i=1:fn
        yn=y(:,i);                             % ȡ��һ֡
        for k=1 : wlen                         % ���Ľط�����
            if yn(k)>=delta
                ym(k)=yn(k)-delta;
            elseif yn(k)<-delta
                ym(k)=yn(k)+delta;
            else
                ym(k)=0;
            end
        end
        zcr(i)=sum(ym(1:end-1).*ym(2:end)<0);  % ȡ�ô�����һ֡����Ѱ�ҹ�����
    end
end

function soundSegment=findSegment(express)
    if express(1)==0
        voicedIndex=find(express);                     % Ѱ��express��Ϊ1��λ��
    else
        voicedIndex=express;
    end

    soundSegment = [];
    k = 1;
    soundSegment(k).begin = voicedIndex(1);            % ���õ�һ���л��ε���ʼλ��
    for i=1:length(voicedIndex)-1,
    if voicedIndex(i+1)-voicedIndex(i)>1,          % �����л��ν���
    soundSegment(k).end = voicedIndex(i);      % ���ñ����л��εĽ���λ��
    soundSegment(k+1).begin = voicedIndex(i+1);% ������һ���л��ε���ʼλ��  
    k = k+1;
    end
    end
    soundSegment(k).end = voicedIndex(end);            % ���һ���л��εĽ���λ��
    % ����ÿ���л��εĳ���
    for i=1 :k
        soundSegment(i).duration=soundSegment(i).end-soundSegment(i).begin+1;
    end
end

