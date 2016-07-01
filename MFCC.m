function [answer, answer2] = main(filename, dctnum)

    %fprintf('%s', filename);
    
    [input, Fs, bits] = wavread(filename);
    
    %预加重
    x = filter([1 -0.9375], 1, input);
    x(1) = x(2);
    
    framesize = floor(50 / 1000 * Fs);
    step = floor(framesize / 2);
    melnum = 24;
    
    [answer answer2] = MFCC2(input, Fs, melnum, framesize, step, dctnum);
    return;
    
    x = enframe(x, framesize, step);
    
    %{
    plot(x);
    for i = 1:min(size(xx), 20)
        figure();
        plot(x(i,:));
    end;
    %}
    
    %计算MEL滤波器
    mel = melbankm(melnum, framesize, Fs);
    mel = full(mel);
    mel = mel / max(mel(:));
    
    %{
    df = Fs / framesize;
    ff = (0:floor(framesize / 2)) * df;
    for k = 1:melnum
        plot(mel(k,:)); hold on;
    end;
    hold off;
    %}
    
    w = 1 + 6 * sin(pi * [1:dctnum] ./ dctnum);
    w = w/max(w);
    
    %计算MFCC
    [tmp, ~] = size(x);
    answer = zeros(tmp, dctnum);
    answer2 = answer;
    for i = 1:size(x)
        y = x(i,:);
        y = y' .* hamming(framesize);
        y = abs(fft(y)) .^ 2;
        %{
        z = zeros(melnum, 1);
        z2 = z;
        for j = 1:melnum
            %fprintf('|%d %d %d %d %d %d|\n',i, j, size(y), size(mel(j,:)));
            z(j) = sum(y .* mel(j,:));
            z2(j) = sum(mel(j,:));
        end;
        z = z ./ z2;
        %}
        z = log(mel * y(1:framesize / 2 + 1));
        
        z = dct(z, dctnum) .* w';
        
        answer(i,:) = z;
    end;
    
    %一阶差分
    for i = 2:size(answer)
        answer2(i,:) = answer(i,:) - answer(i - 1,:);
    end;
    answer = answer(2:size(answer),:);
    answer2 = answer2(2:size(answer2),:);
end